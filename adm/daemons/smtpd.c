/**************************
 *                        *
 * /adm/daemons/smtp_d.c  *
 *                        *
 * by Find@TX.            *
 *                        *
 **************************/

// Modified by jjgod@FYTX For 「侠客新传」邮件注册

#include <net/socket.h>
#include <login.h>
#include <ansi.h>
#include <origin.h>
#include <mudlib.h>

#define PUBLIC_MUD_MAIL         "lonely-21@163.com" 
#define RANDOM_PWD_LEN		8 /* 随机密码长度 */
#define REGFILE			"/data/mail_reg.o"
#define REG_ROOM                "/d/register/regroom"
#define BASE64_D                "/adm/daemons/base64d" 

inherit F_SAVE;

// class类型是C++新增的，想不到LPC也支持
class email
{
	string rcpt;	// 收件者地址
	string body;	// 内容
	int status;     // 状态码
	string id;	// 用户 ID
	string passwd;	// 密码
	object user;
	int normal;
}

protected void write_callback(int fd,string outgoing);
protected varargs void write_callback(int fd,string outgoing);
protected void close_callback(int fd);
protected int permit_reg_email(string mail);
protected int mail_have_reg(object user,string mail);
string    random_passwd(int len);
void      check_user(object user);

/*
 * 这里是服务器你的登陆名和密码。有一些服务器发信也是要进行
 * 身份认证的，现在不少提供商深受垃圾邮件毁坏名誉之苦，越来
 * 越多的采用发信身份认证，就像用 Outlook express 设置服务
 * 器必须选择“我的服务器要求身份认证”。
 * 这个程序 SMTP 和 ESMTP 都可用，如果你的服务提供商不要求
 * 身份认证，你尽可以不理会这个设定。
 */
// ESMTP在新的FoxMail v3.11也支持。

string  *mail_reg; // 这里保存已注册的Email地址。
mapping user_unreg=([]); // 这里保存邮件已发出但尚未确认的用户的ID

protected string mailname = "lonely_21",mailpasswd = "921121";

protected mixed content = ([]);

/* 这里设定你的 SMTP 服务器的域名和 IP 地址 */
protected string domain_name = "smtp.21cn.com", address = "202.104.32.230";

/*
 * 下面这部分是进行 SMTP 服务器 IP 地址的解析用的。
 * 一般 SMTP 服务器的域名是不会变的，但 IP 地址有可
 * 能变化。而且在游戏运行中很少会注意这个。一旦出现
 * 变化是很麻烦的，263 有一次就改变了 IP 地址也没有
 * 通知我们，我到三天以后才发现，搞的我很尴尬，因此
 * 加上了这个功能。
 */
protected void resolve_callback( string o_address, string resolved, int key )
{
	if( stringp(resolved) && (resolved != "") && (address != resolved) )
	{
		address = resolved;
		save();
		restore();
		log_file("smtp",sprintf("SMTP: 远程 SMTP 邮件服务器IP地址被转换为 %s\n",address));
	}
}

/* 这个函数我们是由 CRON_D 定时呼叫的，我们是1小时检查一次。*/
void update_mail_server_ip()
{/*
	if(previous_object() && (geteuid(previous_object()) != ROOT_UID))
	return;*/
	resolve( domain_name, "resolve_callback" );
}

string query_save_file()
{
	return REGFILE;
}

protected void create()
{
	seteuid(getuid());
	if (file_size(REGFILE)<=0){
		mail_reg=({});
		user_unreg=([]);
		save();
	}
	restore();
	resolve( domain_name, "resolve_callback" );
}

/*
 * 这个函数是由玩家注册用的那个房间里的注册命令
 * 呼叫的，user 是进行注册的玩家物件，mail 是注
 * 册的电子邮件地址。
 * 谨慎的人应当对呼叫此函数的物件进行一下检查。
 */
void send_mail(object user,string mail)
{
	object link;
	string msg,passwd,server;
	int s,err;
	class email newmail;

	if(!user) return;
	if(!stringp(mail) || mail == "") return;

	mail = lower_case(mail);

	if(!objectp(link = user->query_temp("link_ob")))
	{
		tell_object(user,"您的档案不完全，无法进行注册，请重新连线完成注册.\n\n");
		destruct(user);
		return;
	}

	if(strsrch(mail,',') >= 0)
	{
	write(sprintf("你的电子邮件地址：%s 里包含非法字符，\n请认真检查后重新注册。\n",mail));
	return;
	}

	if(mail_have_reg(user,mail)) return;

	passwd = random_passwd(RANDOM_PWD_LEN);
	server = sprintf("%s 25",address);

	/*
	 * PUBLIC_MUD_MAIL 是在其它的地方定义的，就是游戏
	 * 对外交流的电子邮件地址。
	 */
	msg = sprintf("From: \"%s\" <%s>\nTo: %s\nSubject: 您在%s的密码\n\n",
	MUD_NAME,PUBLIC_MUD_MAIL,mail,CHINESE_MUD_NAME);
	msg += sprintf(user->name()+"，你好，感谢您光临"+MUD_NAME+"网络游戏。\n\n您的账号：%s\n    密码：%s\n",user->query("id"),passwd);
	msg += "\n注意：这个账号目前为临时账号，请您于48小时之内登陆确认。\n";
	msg +=   "\t  过期未登陆将会被自动删除。\n";
	msg +=   "\t  如有注册登陆方面的问题可以与 "+ PUBLIC_MUD_MAIL+" 联系。\n";
	msg += "\n\t  本游戏的主页在 "+MUD_WEB+"
	  那里有详细的帮助和玩家写的新手指南、经验介绍，相信会\n\t  对你很有用处。

                 祝您在"+CHINESE_MUD_NAME+"玩的愉快！";

	newmail = new(class email);
	newmail->rcpt = mail;
	newmail->body = msg;
	newmail->id = user->query("id");
	newmail->passwd = passwd;
	newmail->user = user;
	user->start_busy(100);

	s = socket_create(STREAM,"read_callback", "close_callback");
	if(s<0)
	{
		log_file("socket","Socket create err: "+socket_error(s)+"\n");
		tell_object(user,"注册过程中服务器发生错误，请再注册一次。\n");
		return;
	}

	content += ([ s : newmail ]);

	err = socket_connect(s,server,"read_callback", "write_call_back");
	if(err < 0)
	{
		map_delete(content,s);
		log_file("socket","Socket connect err: "+socket_error(err)+"\n");
		tell_object(user,"注册过程中服务器发生错误，请再注册一次。\n");
		socket_close(s);
		return;
	}

	tell_object(user,"邮件发送中，请稍候1分半钟．．．．．\n");
	call_out("time_out",90,s);
}

protected void time_out(int fd)
{
	class email mailmsg;

	if(undefinedp(content[fd]))
		return;

	mailmsg = content[fd];

	if(objectp(mailmsg->user))
	{
		tell_object(mailmsg->user,"\n发送过程超时，请重新再注册一次。
		问题有可能是：SMTP邮件服务器的IP地址已经更改。\n");
		(mailmsg->user)->stop_busy();
	}

	map_delete(content,fd);
	socket_close(fd);
}

protected void success_register(int fd)
{
	class email mailmsg;
	object usr,link;

	if(undefinedp(content[fd]))
		return;

	mailmsg = content[fd];
	if(!objectp(usr = mailmsg->user))
		return;
	if(!objectp(link = usr->query_temp("link_ob")))
		return;

	(mailmsg->user)->stop_busy();
	map_delete(content,fd);
	tell_object(usr,sprintf("给您分配的随机密码已根据您登记的地址发往："HIW"%s"NOR"
请您"HIG"五分钟"NOR"后检查您的邮箱。如果您在"HIC"24"NOR"小时后还未能收到我们
给您发出的邮件，请您向 "HIY"%s"NOR" 发信说明详细情况，
我们会尽快为您解决。不便之处请多谅解。
祝您在%s玩的愉快，再见！\n",mailmsg->rcpt,PUBLIC_MUD_MAIL,MUD_NAME));
	
	mail_reg=mail_reg+({mailmsg->rcpt});
	save();
	restore();

	link->set("last_on", time());
	link->set("last_from", query_ip_name(usr));
	link->set("email",mailmsg->rcpt);
	link->set("oldpass",link->query("password"));
	link->set("password",crypt(mailmsg->passwd,0));
	usr->set("email",mailmsg->rcpt);
	usr->set("have_reg",1);
	usr->delete("new_begin");
	link->save();
	usr->save();
	tell_room(environment(usr),"你只觉得眼前一花，"+usr->query("name")+"不见了。\n",({usr}));
	message("channel:sys",sprintf(HIR"【邮件注册精灵】"HIW"%s(%s)邮件发出退出游戏。\n"NOR,
		usr->name(),geteuid(usr)),filter_array(users(),(: wizardp($1) :)));
	user_unreg[mailmsg->id]=time(); // 添加这个用户的ID到未确认名单中
	log_file("smtp",sprintf("%s(%s)的邮件已经发往 %s。\n",usr->name(),geteuid(usr),mailmsg->rcpt));
	save();
	restore();
	destruct(link);
	destruct(usr);
}

protected void close_callback(int fd)
{
	socket_close(fd);
}

/* 此函数处理发送过程中的致命错误 */
protected void mail_error(int fd,string message)
{
	class email mailmsg;

	mailmsg = content[fd];

	log_file("smtp_err",sprintf("ERROR:\n%s\nid: %s\nmail: %s\n\n",
			message,mailmsg->id,mailmsg->rcpt));

	if(objectp(mailmsg->user))
	{
		tell_object(mailmsg->user,sprintf("\n发送过程中出现异常错误：\n%s\n请重新再注册一次。\n\n",
			message));
		(mailmsg->user)->stop_busy();
	}

	map_delete(content,fd);
	socket_close(fd);
}

protected void read_callback(int fd,string message)
{
	int rcode,err;
	string mechanism;
	class email mailmsg;

	if(undefinedp(content[fd]))
	{
		socket_close(fd);
		return;
	}

	mailmsg = content[fd];

	rcode = atoi(message[0..2]);

	if(!rcode || (rcode > 500))
	{
		mail_error(fd,message);
		return;
	}

	if(!mailmsg->status)  // 握手连通
	{
		socket_write(fd,sprintf("EHLO %s\r\n",query_host_name()));
		mailmsg->status++;
		return;
	}

	if(mailmsg->status == 1) // server ready
	{
		if((rcode == 500))	// command not recognized
		{
			if(mailmsg->normal)
			{
				mail_error(fd,message);
				return;
			}

			socket_write(fd,sprintf("HELO %s\r\n",query_host_name()));
			mailmsg->normal = 1;
			return;
		}

		if(mailmsg->normal)
		{
			socket_write(fd,sprintf("MAIL FROM: <%s>\r\n",PUBLIC_MUD_MAIL));
			mailmsg->status = 3;
			return;
		}

		if(sscanf(message,"%*sAUTH=%s\n%*s",mechanism) == 3)
		{

			socket_write(fd,sprintf("AUTH %s\r\n",mechanism));
			mailmsg->status = 2;
			return;
		}

		// ESMTP 协议不需要认证
		socket_write(fd,sprintf("MAIL FROM: <%s>\r\n",PUBLIC_MUD_MAIL));
		mailmsg->status = 3;
		return;
	}

	if(mailmsg->status == 2)	// Authentication
	{
		string quest;

		if(rcode == 334)	// 认证提问
		{
			/*
			 * 这里是 ESMTP 协议的认证部分，ESMTP 协议规定
			 * 认证信息使用 BASE64 编码。
			 * 这里的 base64_decode 和 base64_encode 函数
			 * 就是 base64_d 里面的 decode 和 encode 函数，
			 * 我们是定义成了 simul_efun。
			 */
			quest = message[4..];
			quest = replace_string(quest,"\n","");
			quest = replace_string(quest,"\r","");
			quest = BASE64_D->decode(quest);
			if(quest[0..3] == "User")
			{
				socket_write(fd,sprintf("%s\r\n",BASE64_D->encode(mailname)));
				return;
			}
			else if(quest[0..3] == "Pass")
			{
				socket_write(fd,sprintf("%s\r\n",BASE64_D->encode(mailpasswd)));
				return;
			}
		}

		// 认证通过
		socket_write(fd,sprintf("MAIL FROM: <%s>\r\n",PUBLIC_MUD_MAIL));
		mailmsg->status = 3;
		return;
	}

	if(mailmsg->status == 3)
	{
		socket_write(fd,sprintf("RCPT TO: <%s>\r\n",mailmsg->rcpt));
		mailmsg->status = 4;
		return;
	}

	if(mailmsg->status == 4)
	{
		socket_write(fd,sprintf("DATA\r\n"));
		mailmsg->status = 5;
		return;
	}

	if(mailmsg->status == 5)
	{
		if(rcode == 354)	// ready receive data
		{
			err = socket_write(fd,sprintf("%s\r\n.\r\n",mailmsg->body));
			if( (err < 0) && (err != EEALREADY) )
				call_out("write_callback",1,fd,sprintf("%s\r\n.\r\n",mailmsg->body));
			mailmsg->status = 6;
			return;
		}
		else
		{
			mail_error(fd,message);
			return;
		}
	}

	if(mailmsg->status == 6)
	{
		socket_write(fd,sprintf("QUIT\r\n"));
		mailmsg->status = 7;
		return;
	}

	if((mailmsg->status == 7) && (rcode == 221))
	{
		success_register(fd);
		return;
	}

	mail_error(fd,message);
}

protected varargs void write_callback(int fd,string outgoing)
{
	int err;

	if(stringp(outgoing) && (outgoing != ""))
	{
		err = socket_write(fd,outgoing);

		if( (err < 0) && (err != EEALREADY) )
		{
			call_out("write_callback",1,fd,outgoing);
			return;
		}
	}
}

/*
 * 对玩家注册的电子邮件地址的各类检查就在这里实现，
 * 可以根据自己的需要增减代码。
 * 要加入对某些 mail 地址的限制，也在这里实现。
 */

protected int mail_have_reg(object user,string mail)
{
	object link;
	string id;

	if(!user) return 1;
	link = user->query_temp("link_ob");
	if(!link) return 1;
	if(!stringp(mail)) return 1;

	id = user->query("id");

	if(member_array(mail,mail_reg)!=-1)
	{
		tell_object(user,"这个邮件地址已经注册过了，本游戏不允许同一地址多重注册。\n对不起！\n");
		message("channel:sys",sprintf(HIR"【邮件注册精灵】：%s(%s)注册请求被拒绝，退出游戏。\n"NOR,
		user->name(),geteuid(user)),filter_array(users(),(: wizardp($1) :)));
		destruct(user);
		destruct(link);
		rm(DATA_DIR + "login/" + id[0..0] + "/" + id + ".o");
		rm(DATA_DIR + "user/"  + id[0..0] + "/" + id + ".o");
		return 1;
	}

	else
		return 0;
}

/*
 * 超过48小时未连线确认删除档案
 * 这个函数我们是由 CRON_D 定时呼叫的，
 * 一小时检查一次。
 */
void user_no_login()
{
	string *player,time;
	string *name;
	object user,link;
	int i;

// 这两句是用来检查权限的
	if(!previous_object()||(geteuid(previous_object()) != ROOT_UID)&&(geteuid(previous_object()) != "jjgod"))
		return;

	name=keys(user_unreg); // 获得所有邮件已发出等待确认的用户array
	for(i=0; i<sizeof(name); i++){
		if ((time()-user_unreg[name[i]])>=172800){ // 假如这些id的注册时间与现在时间相差2天=48小时=172800秒
			if (!sizeof(player)) player=({name[i]});
			else player+=({name[i]}); // 在player 这个array中加入这个玩家
			map_delete(user_unreg,name[i]); // 在原先的mapping中删除这个玩家
			save();
			restore();
		}
	}

// 下面就是对player这个array的处理了
	if(!player || !sizeof(player)){
		message("system",HIW"．．．无符合条件的玩家" NOR,users() );
		return;
	}

	time = ctime(time());

	foreach(string one in player)
	{
		string f;

		if(objectp(user = find_player(one)))
		{
			if(objectp(link = user->query("link_ob")))
			destruct(link);
			destruct(user);
		}

		if(file_size(f = sprintf(DATA_DIR+"login/%c/%s.o",one[0],one)) > 0)
			rm(f);
		if(file_size(f = sprintf(DATA_DIR+"user/%c/%s.o",one[0],one)) > 0)
			rm(f);
		log_file("smtp",sprintf("(%s)超过48小时未连线确认被删除。%s\n",one,time));
	}
}

/* 这个函数产生一个长度为 len 的随机密码 */
string random_passwd(int len)
{
	int cap,low,num,n;
	string passwd;
	string Random_Passwd ="ABCDEFGHIJKL1234567890mnopqrstuvwxyzabcdefghi1jk9MNOPQRS4TUVW9XYZ";

	if(!intp(len))
		return "12345";

	if(len < 4 || len > 8)
		len = 8;

	do
	{
		cap=0; low=0; num=0; passwd = "";
		for(int i=0;i<len;i++)
		{
			n = random(sizeof(Random_Passwd));
			if( Random_Passwd[n] <='Z' && Random_Passwd[n] >='A' )
				cap++;
			else if( Random_Passwd[n] <='z' && Random_Passwd[n] >='a' )
				low++;
			else if( Random_Passwd[n] <='9' && Random_Passwd[n] >='0' )
				num++;
			passwd += Random_Passwd[n..n];
		}
	}
	while(!cap || !low || !num);

	return passwd;
}

// 下面的这个函数时我加上为了处理48小时内已经登陆的玩家，从未注册用户列表中删除这些玩家。
void finish_reg(string id)
{
	int i;

	for (i=0;i<sizeof(user_unreg);i++)
	if (intp(user_unreg[id])&&user_unreg[id]!=0)
	{
		map_delete(user_unreg, id);
		save();
		restore();
		return;
	}
}

// 下面的是我用来调试的接口函数
mapping query_users()
{return user_unreg;}

string *query_mail_reg()
{return mail_reg;}

string query_smtp_info()
{
	string msg;
	msg="\n服务器域名："+domain_name;
	msg+=("\n服务器IP地址："+address);
	msg+=("\n用户名："+mailname);
	msg+=(" 用户密码：*****");
	msg+="\n";
	return msg;
}

void remove_mail(string mail)
{
	mail_reg -= ({ mail });
	save();
}

void stop_reg(object ob)
{
	ob->delete("password");
	ob->set("password", ob->query("oldpass"));

	ob->delete("have_reg");
	ob->delete("oldpass");

	remove_mail(ob->query("email"));
	map_delete(user_unreg, ob->query("id"));
}
