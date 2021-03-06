// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// su.c 苏荃

#include "shenlong.h"

inherit NPC;
inherit F_UNIQUE;
inherit F_MASTER;
inherit F_QUESTER;

void create()
{
	set_name("苏荃", ({ "su quan", "su" }));
	set("title",  HIY"神龙教"NOR"教主夫人" );
	set("long", "她就是神龙教教主洪安通的夫人。\n");
	set("gender", "女性");
	set("age", 23);
	set("attitude", "friendly");
	set("str", 35);
	set("int", 30);
	set("con", 30);
	set("dex", 38);
	
	set("max_qi", 3500);
	set("max_jing", 1800);
	set("neili", 3700);
	set("max_neili", 3700);
	set("jiali", 50);
	set("level", 30);
	set("combat_exp", 620000);
	set("shen_type", -1);

        set_skill("force", 450);
	set_skill("shenlong-xinfa", 450);
        set_skill("dodge", 480);
	set_skill("yixing-bufa", 460);
        set_skill("hand", 450);
        set_skill("sword", 450);
        set_skill("meiren-sanzhao", 450);
        set_skill("strike", 480);
	set_skill("shenlong-bashi", 450);
	set_skill("huagu-mianzhang", 420);
        set_skill("parry", 450);
        set_skill("staff", 450);
	set_skill("shedao-qigong", 420);
	set_skill("literate", 400);
	set_skill("medical", 400);
	set_skill("shenlong-mixin", 400);
	set_skill("martial-cognize", 200);
        set_skill("shenlong-jian", 400);

	map_skill("force", "shenlong-xinfa");
	map_skill("dodge", "yixing-bufa");
	map_skill("strike", "huagu-mianzhang");
	map_skill("hand", "shenlong-bashi");
        map_skill("sword", "shenlong-jian");
	map_skill("parry", "shedao-qigong");
        map_skill("staff", "shedao-qigong");
	prepare_skill("strike", "huagu-mianzhang");
	prepare_skill("hand", "shenlong-bashi");

	create_family("神龙教", 1, "教主夫人");

        set("inquiry", ([
		"神龙教" : "一般人是入不了我神龙教的(join shenlongjiao)。",
		"入教"   : "一般人是入不了我神龙教的(join shenlongjiao)。",
		"退教"   : "哈哈哈哈！退教？这么多年我还真听过几起，不过他们已经都死了。",
		"口号"   : "万年不老！永享仙福！寿与天齐！文武仁圣！",
		"rujiao" : "一般人是入不了我神龙教的(join shenlongjiao)。",
		"tuijiao": "哈哈哈哈！退教？这么多年我还真听过几起，不过他们已经都死了。",
        ]));

	set("chat_chance_combat", 50);
	set("chat_msg_combat", ({
		(: command("smile") :),
		(: command("haha") :),
		(: command("chat 凭你这" + RANK_D->query_rude(this_player())+",也敢在太岁爷头上动土?\n") :),
		(: command("say 你活得不耐烦了找死啊？\n") :),
                (: perform_action, "staff.chang" :),
                (: perform_action, "staff.chang" :),
                (: perform_action, "staff.chang" :),
                (: perform_action, "staff.chang2" :),
                (: perform_action, "staff.chang2" :),
                (: perform_action, "staff.chang2" :),
                (: perform_action, "staff.chang3" :),
                (: perform_action, "staff.chang3" :),
                (: perform_action, "staff.chang3" :),
                (: exert_function, "recover" :),
                (: exert_function, "recover" :),
        }) );
	set("master_ob", 5);
	setup();
	carry_object("/clone/misc/cloth")->wear();
	add_money("silver", 50);
}

void init()
{
	object ob;

	::init();

	if (interactive(ob = this_player()) && ! is_fighting())
        {
		remove_call_out("greeting");
		call_out("greeting", 2, ob);
	}
	add_action("do_join", "join");
}

void greeting(object ob)
{
	object obj;
	if (! objectp(ob)) return;
        if (interactive(ob) && objectp(obj = present("used gao", ob)))
        {
	   	set("combat_exp", 100000);
	   	set("qi", 100);
	   	set("jing", 100);
	}
}

void attempt_apprentice(object ob)
{
        command("say 好吧，你就和我学武功吧。");
        command("recruit " + ob->query("id"));
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "历练" :
        case "历炼" :
        case "锻炼" :
                return QUEST_D->accept_ask(this_object(), me, topic);
                break;

        case "玉女无情" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/meiren-sanzhao/wuqing",
                           "name"    : "玉女无情",
                           "sk1"     : "meiren-sanzhao",
                           "lv1"     : 100,
                           "sk2"     : "sword",
                           "lv2"     : 100,
                           "sk3"     : "force",
                           "lv3"     : 100,                           
                           "gongxian": 600,
                           "shen"    : -10000, ]));
                break;

        default:
                return 0;
        }
}
