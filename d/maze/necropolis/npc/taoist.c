#include <ansi.h> 
inherit "/d/maze/necropolis/necropolis_npc";

object m_mazeobj;
object get_mazeobj();
object *players = ({});

void set_players(object *ob) {
	players = ob;
}

void add_player(object ob) {
	if(member_array(ob,players)==-1) {
		players += ({ob});
		message_vision(BLU"$N对$n说道：谢谢！\n"NOR,this_object(),ob);
	} else
		message_vision(BLU"$N对$n说道：你已经答应帮忙，你不会反悔吧！\n"NOR,this_object(),ob);
}

object* query_players() {
	players -= ({0});
	return players;
}

void smart_fight();

void create()
{
        set_name("丁一", ({ "ding yi","ding"}) );
        set("gender", "男性" );
        //set("title", HIC "三清宫"NOR);
        set("age", 80);
        set("str", 50);
        set("con", 120);
        set("dex", 22); 
        set("int", 50);
        set("class","shaolin");     
        set("long",
        ""
        );
        //set("force_factor", 150);
        set("auto_perform", 2); 
        set("max_qi", 8000000);
	set("eff_qi", 480000);        
        set("max_jing", 8500000);
        set("eff_jing",850000);
        set("neili", 8000000);
        set("max_neili", 4500000);
        set("max_jingli", 500000);
        set("combat_exp", 300000000);

        set_skill("array", 1500);
        set_skill("zhenwu-jianzhen", 1500);
        set_skill("force", 1500);
        set_skill("taiji-shengong", 1500);
        set_skill("wudang-jiuyang", 1500);
        set_skill("yinyun-ziqi", 1500);
        set_skill("dodge", 1500);
        set_skill("tiyunzong", 1500);
        set_skill("cuff", 1500);
        set_skill("taiji-quan", 1500);
	set_skill("strike", 1490);
	set_skill("wudang-zhang", 1490);
        set_skill("hand", 1490);
        set_skill("paiyun-shou", 1490);
        set_skill("parry", 1500);
        set_skill("sword", 1500);
	set_skill("wudang-jian", 1500);
	set_skill("blade", 1460);
	set_skill("taiji-dao", 1460);
        set_skill("taiji-jian", 1500);
        set_skill("taoism", 1500);
        set_skill("literate", 1500);
        set_skill("wudang-yaoli", 1500);
        set_skill("medical", 1500);
        set_skill("liandan-shu", 1500);
        set_skill("martial-cognize", 1420); 

        map_skill("force", "taiji-shengong");
        map_skill("dodge", "tiyunzong");
        map_skill("cuff", "taiji-quan");
        map_skill("parry", "taiji-jian");
        map_skill("sword", "taiji-jian");
	map_skill("hand", "paiyun-shou");
	map_skill("strike", "wudang-zhang");        
	map_skill("blade", "taiji-dao");
        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: smart_fight():),
        }) ); 

	prepare_skill("cuff", "taiji-quan");
	prepare_skill("strike", "wudang-zhang");
        set_temp("apply/attack", 3000);
        set_temp("apply/defense", 3000);
        set_temp("apply/damage", 1500);
        set_temp("apply/unarmed_damage", 1500);
        setup();
        carry_object("/clone/weapon/sword");
        carry_object("/clone/cloth/cloth")->wear();
}  

int is_undead() {
	return 0;
}

void init()
{       
        object ob; 
        ::init();
        
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_answer", "answer");
        add_action("do_accept", "accept");
        add_action("do_report", "report");
	add_action("do_help", "help");
} 

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        if( query_temp("开场白结束") || query_temp("开始说开场白") || query_temp("任务") )
                return;
        message_vision(CYN "$N有气无力地说道：这位" + RANK_D->query_respect(ob) +
                "，能听我一言吗？(answer yes/no)\n" NOR, this_object(), ob);
} 

int do_answer(string arg) {
	object ob;
	if(arg=="yes") {
		if(query_temp("in_speech"))
			return 0;
		if(present("tape",environment()))
			return 0;
		set_temp("开始说开场白",1);
		ob = new(__DIR__"obj/taoist_tape");
		ob->move(environment());
		ob->play_sound_0(this_object(),0);
	} else if(arg=="no") {
		message_vision(BLU"$N说道：谁想听你这个牛鼻子废话！\n",this_player());
	} else
		return notify_fail("你要回答什么？\n");
	return 1;
}

int do_accept(string arg) {
	object ob,*team;
	if(!query_temp("开场白结束"))
		return 0;
	if(query_temp("任务"))
		return 0;
	if(arg=="yes") {		
		if(present("tape",environment()))
			return 1;
		delete_temp("开场白结束");
		team = this_player()->query_team();
		if(!team || sizeof(team)==0)
			team = ({this_player()});
		set_players(team);
		ob = new(__DIR__"obj/taoist_tape");
		ob->move(environment());
		ob->play_sound_1(this_object(),0);
	}	
	else if(arg=="no") {
		delete_temp("开场白结束");
		delete_temp("开始说开场白");
		message_vision(BLU"$N说道：没好处的事情我可不干！\n",this_player());
	}
	else
		return 0;
	return 1;
}

int do_help(string arg) {
	if(arg!="ding" && arg!="ding yi")
		return 0;
	add_player(this_player());
	return 1;
}

int do_report(string arg) {
	object mazeobj,ob,env,*obs;
	int quest_index,has_enemy;
	if(query_temp("in_speech"))
			return 0;
	mazeobj = get_mazeobj();
	if(!mazeobj)
			return 0;
	
	quest_index = mazeobj->query("quest/quest_index");
	switch(quest_index) {
			case(1):
				if(mazeobj->query("quest/killed/骷髅")>=mazeobj->query("quest/to_kill/骷髅") &&
					 mazeobj->query("quest/killed/僵尸")>=mazeobj->query("quest/to_kill/僵尸") &&
					 mazeobj->query("quest/killed/幽灵")>=mazeobj->query("quest/to_kill/幽灵")
					 ) {
					 	//mazeobj->delete("quest/to_kill");
					 	set_temp("in_speech",1);
					 	ob = new(__DIR__"obj/taoist_tape");
						ob->move(environment());
						ob->play_sound_2(this_object(),0); 
				} else 
						return notify_fail("你尚未完成任务！\n");
				break;
			case(2):
				if(mazeobj->query("quest/killed/骷髅武士")>=mazeobj->query("quest/to_kill/骷髅武士") &&
					 mazeobj->query("quest/killed/骷髅法师")>=mazeobj->query("quest/to_kill/骷髅法师") &&
					 mazeobj->query("quest/killed/血僵尸")>=mazeobj->query("quest/to_kill/血僵尸") &&
					 mazeobj->query("quest/killed/尸煞")>=mazeobj->query("quest/to_kill/尸煞") &&
					 mazeobj->query("quest/killed/幽冥之火")>=mazeobj->query("quest/to_kill/幽冥之火") &&
					 mazeobj->query("quest/killed/幽冥之眼")>=mazeobj->query("quest/to_kill/幽冥之眼")
					 ) {
					 	//mazeobj->delete("quest/to_kill");
					 	set_temp("in_speech",1);
					 	ob = new(__DIR__"obj/taoist_tape");
						ob->move(environment());
						ob->play_sound_3(this_object(),0); 
				} else 
						return notify_fail("你尚未完成任务！\n");
				break;
			case(3):
				if(mazeobj->query("quest/killed/心武")>=mazeobj->query("quest/to_kill/心武") &&
					 mazeobj->query("quest/finded/聚灵塔")>=mazeobj->query("quest/to_find/聚灵塔")
				 ) {
					 	//mazeobj->delete("quest/to_kill");
					 	//mazeobj->delete("quest/to_find");
					 	set_temp("in_speech",1);
					 	ob = new(__DIR__"obj/taoist_tape");
						ob->move(environment());
						ob->play_sound_4(this_object(),0); 
				} else 
						return notify_fail("你尚未完成任务！\n");
				break;
		 case(4):
				if(mazeobj->query("quest/finded/骨杖")>=mazeobj->query("quest/to_find/骨杖") &&
					 mazeobj->query("quest/finded/幽冥之火")>=mazeobj->query("quest/to_find/幽冥之火") &&
					 mazeobj->query("quest/finded/僵尸血")>=mazeobj->query("quest/to_find/僵尸血")
				 ) {
					 	//mazeobj->delete("quest/to_find");
					 	set_temp("in_speech",1);
					 	ob = new(__DIR__"obj/taoist_tape");
						ob->move(environment());
						ob->play_sound_5(this_object(),this_player(),0); 
				} else 
						return notify_fail("你尚未完成任务！\n");
				break;
		case(5):
				if(!query_leader()) {
					message_vision(BLU"$N对$n说：你带路吧。\n"NOR,this_object(),this_player());
					set_leader(this_player());
					return 1;
				}
				env = environment(this_object());
				if(env->query("short") == HIY"聚灵法阵"NOR) {
						obs = all_inventory(env);
						has_enemy = 0;
						foreach(ob in obs) {
							if(ob && ob->is_undead()) {
								has_enemy = 1;
								break;
							}
						}
						if(has_enemy)
								return 0;
						set_leader(0);
						ob = new(__DIR__"obj/taoist_tape");
						ob->move(environment());
						ob->play_sound_6(this_object(),0); 
				} else
						return 0;
				break;
		case(6):
				if(mazeobj->query("quest/killed/亡灵")>=mazeobj->query("quest/to_kill/亡灵") 
				 ) {
					 	mazeobj->delete("quest/to_kill");
					 	set("last_quester",this_player());
					 	set_temp("in_speech",1);
					 	ob = new(__DIR__"obj/taoist_tape");
						ob->move(environment());
						ob->play_sound_7(this_object(),0); 
				} else 
						return notify_fail("你尚未完成任务！\n");
				break;
	
	}
	return 1;
}

void smart_action3()
{
        object target,me,*enemies;
        string msg;
        int damage = 0;
        mixed yourexp,myexp;
        
        me = this_object();
        if(is_fighting() && !me->is_busy()) {
	        enemies = query_enemy();
	        if(!enemies || sizeof(enemies)==0)
		        return;

	        target = enemies[random(sizeof(enemies))];
	        if(target) 
	        {	               		                
                        msg = HIG "$N口中喃喃地念着咒文，左手一挥，手中聚起五色光芒，霎时化为叁股！\n\n";
                        msg += HIC "一团青光射向$n！\n" NOR; 

	                yourexp = count_div(target->query("combat_exp"),100);
	                myexp = count_div(me->query("combat_exp"), 100);
	                if( count_gt(random(atoi(count_add(myexp,yourexp))), yourexp) ) 
	                {
                                damage = 10000 + random(10000);
                                damage = damage + random(damage);       
             
                                msg +=  HIR "结果「嗤」地一声，青光从$p身上透体而过，拖出一条长长的黑气钻入地下！\n"NOR;
                                target->receive_damage("qi", damage, me);
                                target->receive_wound("qi", damage/3, me);
                        } else
                                msg += "结果「嗤」地一声，青光从$p身上透体而过，无声无息地钻入地下！\n";
                                
		        message_vision(msg, me, target);
		        if (damage > 0)
		                COMBAT_D->report_status(target);
		        
		        msg = HIW "\n一团白光射向$n！\n" NOR;
	                yourexp = target->query("max_neili");
	                myexp = me->query("max_neili");
	                if( random(myexp + yourexp) > yourexp ) 
	                {
                                damage = 10000 + random(10000);
                                damage = damage + random(damage);       
             
                                msg +=  HIR "结果「嗤」地一声，白光从$p身上透体而过，拖出一条长长的黑气钻入地下！\n"NOR;
                                target->receive_damage("qi", damage, me);
                                target->receive_wound("qi", damage/3, me);
                        } else		        
	                        msg += "结果「嗤」地一声，白光从$p身上透体而过，无声无息地钻入地下！\n";
		        message_vision(msg, me, target);
		        if (damage > 0)
		                COMBAT_D->report_status(target);
		        
		        msg = HIM "\n一团紫光射向$n！\n" NOR; 
	                yourexp = target->query_skill("martial-cognize", 1);
	                myexp = me->query_skill("martial-cognize", 1);
	                if( random(myexp + yourexp) > yourexp ) 
	                {
                                damage = 20000 + random(20000);
                                damage = damage + random(damage);       
             
                                msg +=  HIR "结果「嗤」地一声，紫光从$p身上透体而过，拖出一条长长的七彩光气，光气绕了\n"
                                            "回转过来又从$N顶门注入$P的体内！\n" NOR;
                                target->receive_damage("qi", damage, me);
                                target->receive_wound("qi", damage/3, me);
                        } else	        
                                msg += "结果「嗤」地一声，紫光从$p身上透体而过，无声无息地钻入地下！\n";
                        message_vision(msg, me, target);
		        if (damage > 0)
		                COMBAT_D->report_status(target);
	        }
        }
	return;
}

void smart_fight() {
	smart_action3();
}

int count_undead(object env) {
		object *obs,ob;
		int count;
		obs = all_inventory(env);
		count = 0;
		foreach(ob in obs) {
				if(ob && ob->is_undead())
					count++;
			}
		return count;
}


void summon_undead(object env,object mazeobj) {
	object *obs,ob;
	int i,j;
	string file;
	
	if(!env)
		return;
	
	if(!mazeobj)
		return;
	
	if(mazeobj->query("quest/quest_index")!=6)
		return;
	
	if(count_undead(env)>=5)  {
			start_call_out( (:call_other,__FILE__, "summon_undead",env,mazeobj :),20);
			return;
	}
	
	/*
	if(mazeobj->query("quest/killed/亡灵")>=mazeobj->query("quest/to_kill/亡灵")) {
			message_vision(BLINK HIC"\n聚灵塔升上天空，聚灵法阵发出耀眼的五彩光芒。\n\n"NOR,this_object());
			obs = all_inventory(env);
			foreach(ob in obs) {
				if(ob->is_undead())
					ob->die();
			}
	}
	*/
	//message_vision(HIC"\n聚灵塔上光华一闪，一个鬼灵钻了出来。\n\n"NOR,this_object());
	tell_room(env,HIC"\n聚灵塔上光华一闪，一个鬼灵被吸了过来！\n\n"NOR);
	i = random(100);
	if(i<5) {
		j = random(2);
		switch(j) {
			case(0):
				file = "/d/maze/necropolis/npc/skeleton_lich";
				break;
			case(1):
				file = "/d/maze/necropolis/npc/zombie_lord";
				break;
			/*case(2):
				file = "/d/maze/necropolis/npc/ghost_devil";
				break;*/
		}
	} else if (i<25) {
		j = random(2);
		switch(j) {
			case(0):
				file = "/d/maze/necropolis/npc/skeleton_mage";
				break;
			case(1):
				file = "/d/maze/necropolis/npc/zombie_blood";
				break;
		/*	case(2):
				file = "/d/maze/necropolis/npc/ghost_eye";
				break;*/
		}
	
	} else if (i<45) {
		j = random(2);
		switch(j) {
			case(0):
				file = "/d/maze/necropolis/npc/skeleton_fighter";
				break;
			case(1):
				file = "/d/maze/necropolis/npc/zombie_power";
				break;
	/*		case(2):
				file = "/d/maze/necropolis/npc/ghost_fire";
				break;*/
		}
	
	} else {
		j = random(2);
		switch(j) {
			case(0):
				file = "/d/maze/necropolis/npc/skeleton";
				break;
			case(1):
				file = "/d/maze/necropolis/npc/zombie";
				break;
		/*	case(2):
				file = "/d/maze/necropolis/npc/ghost";
				break;*/
		}
	}
		ob = new(file);
		ob->set("attitude","aggressive");
		ob->set("bellicosity",50000);
		ob->move(env);
		start_call_out( (:call_other,__FILE__, "summon_undead",env,mazeobj :),20);
}

object get_mazeobj() {
	if(!m_mazeobj)
		m_mazeobj = MAZE_D->query_maze_mainobj(this_object());
	return m_mazeobj;
}

int accept_object(object me, object obj)
{
	object mazeobj;
	int quest_index;
	if(!mazeobj=get_mazeobj())
			return 0;
	quest_index = mazeobj->query("quest/quest_index");
	switch(quest_index) {
		case(3):
				if(obj->name()=="聚灵塔" &&
				   obj->query("id") == "spirit tower") {
						mazeobj->set("quest/finded/聚灵塔",1);
                                                command("pat "+me->query("id"));
                                                destruct(obj);
						return 1;
				}
				break;
		 case(4):
		 		if(obj->name()=="骨杖" &&
                                   obj->query("id") == "bone staff") {
						mazeobj->set("quest/finded/骨杖",1);
						command("pat "+me->query("id"));
						destruct(obj);
						return 1;
				}
				if(obj->name()=="幽冥之火" &&
				   obj->query("id") == "ghost fire") {
						mazeobj->set("quest/finded/幽冥之火",1);
						command("pat "+me->query("id"));
						destruct(obj);
						return 1;
				}
				if(obj->name()=="僵尸血" &&
				   obj->query("id") == "zombie blood") {
						mazeobj->set("quest/finded/僵尸血",1);
						command("pat "+me->query("id"));
						destruct(obj);
						return 1;
				}
				break;
	}
	return 0;
}

void give_reward_necropolis(object *ob,object reward_giver) {
	int ref_pot;
	int ref_exp;
        int ref_tih;
	int gold = 100;
	int score = 500;
        int exp,pot,tih;
	object *team,member;
	string reward_msg,mazedir;
	
	if(!ob || sizeof(ob)==0 || !reward_giver)
			return;
	team = ob;
	mazedir = MAZE_D->query_maze_dir(reward_giver);
	foreach(member in team) {
			if(!member)
				continue;
			//if(!environment(member) || !environment(member)->query("virtual_room"))
				//continue;
			if(mazedir!=MAZE_D->query_maze_dir(member))//不在同一个副本里
				continue;
                        ref_pot = 300000;
                        ref_exp = 600000;
                        ref_tih = 50000;
                        /*
                        if(count_gt(member->query("combat_exp"),1000000000)) {
                                        ref_tih = 10000;
                                        ref_pot = 50000;
                                        ref_exp = 100000;
                        } else if (count_gt(member->query("combat_exp"),600000000)) {
                                        ref_tih = 20000;
                                        ref_pot = 100000;
                                        ref_exp = 200000;
			} else if (count_gt(member->query("combat_exp"),300000000)) {
                        */
                        if(count_gt(member->query("combat_exp"),1000000000)) {
                                        ref_tih = 30000;
                                        ref_pot = 150000;
                                        ref_exp = 300000;
			}
			exp = ref_exp;
			pot = ref_pot;
                        tih = ref_tih;
			
			reward_msg =HIR"墓园的危机解除，你被奖励了：\n\t\t" +
			chinese_number(exp) + "点实战经验\n\t\t"+
			chinese_number(pot) + "点潜能\n\t\t" +
                        chinese_number(tih) + "点体会\n\t\t" +
			chinese_number(score) + "点评价\n\t\t" + 
			chinese_number(gold) + "两黄金\n"NOR;
			tell_object(member,reward_msg);
			member->add("combat_exp",exp);
			member->add("potential",pot);
                        member->add("experience",tih);
			member->add("score",score);
                        member->add("balance",gold*10000);
			member->set_temp("maze/time",time());
	}
}

void die() {
	object mazeobj,item,ob,killer;
	string dir,userid,quest;
	int quest_index;
	object owner;
	if(!mazeobj=get_mazeobj())
			return;
	
	killer = query_last_damage_from();
	if(!killer) return;
	quest_index = mazeobj->query("quest/quest_index");
	if(quest_index == 7) {
			give_reward_necropolis(query_players(),this_object());
			dir = base_name(mazeobj);

			if (sscanf(dir,"/data/maze/%s/%s/maze",userid, quest)==2) {
					dir = "/data/maze/"+userid+"/"+quest+"/";
                                        tell_room(environment(),HIY"副本将在三十秒后消失！\n"NOR);
					if (! sizeof(killer->query_team_member()))
					        owner = killer;
					else
					{ 
					        if (killer->is_team_leader())
					                owner = killer;
					        else
					                owner = killer->query_team_leader();
			                }
                                        MAZE_D->delay_remove_maze(owner, "necropolis");
					ob = new(__DIR__"obj/taoist_tape");
					ob->move(environment());
					ob->play_sound_8(dir,0); 
			}

			reset_eval_cost();
                        for (int i = 0; i < 10; i++) 
                        {
                                item = new("/clone/enchase/rune1" + random(10));
    		                item->move(environment());
                                item = new("/clone/enchase/BLKjewel" + (3 + random(3))); 
                                item->move(environment()); 
                        }  		

                        if (random(100) < 2)
                        {
                                item = new("/clone/enchase/rune33");
                                item->move(environment());
                        }
                        if (random(100) < 5)
                        {
                                item = new("/clone/enchase/rune31");
                                item->move(environment());
                        }
                        if (random(100) < 9)
                        {
                                item = new("/clone/enchase/rune29");
                                item->move(environment());
                        }
	}
	::die();
}

