// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
#include "shenlong.h"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;
inherit F_QUESTER;

mixed ask_fei();
mixed ask_xian();
mixed ask_cui();

void create()
{
        set_name("�鰲ͨ", ({ "hong antong", "hong" }));
        set("title",  HIY "������" NOR "����" );
        set("nickname", HIR "�����ɸ�" NOR);
        set("long", "�������书����������˵�̸֮ɫ��������̽����鰲ͨ��\n");
        set("gender", "����");
        set("age", 50);
        set("attitude", "friendly");

        set("str", 32);
        set("int", 35);
        set("con", 31);
        set("dex", 32);

        set("max_qi", 6000);
        set("max_jing", 3000);
        set("neili", 6800);
        set("max_neili", 6800);
        set("jiali", 100);
        set("level", 40);
        set("combat_exp", 2200000);
        set("shen_type", -1);

        set_skill("force", 450);
        set_skill("shenlong-xinfa", 450);
        set_skill("dodge", 430);
        set_skill("yixing-bufa", 430);
        set_skill("hand", 440);
        set_skill("shenlong-bashi", 440);
        set_skill("strike", 440);
        set_skill("huagu-mianzhang", 440);
        set_skill("finger", 420);
        set_skill("yingxiong-sanzhao", 420);
        set_skill("parry", 450);
        set_skill("staff", 450);
        set_skill("sword", 450);
        set_skill("shedao-qigong", 450);
        set_skill("unarmed", 450);
        set_skill("literate", 420);
        set_skill("medical", 470);
        set_skill("shenlong-jian", 420);
        set_skill("busi-shenlong", 420);
        set_skill("shenlong-mixin", 470);
        set_skill("martial-cognize", 320);

        map_skill("force", "shenlong-xinfa");
        map_skill("dodge", "yixing-bufa");
        map_skill("hand", "shenlong-bashi");
        map_skill("strike", "huagu-mianzhang");
        map_skill("parry", "shedao-qigong");
        map_skill("staff", "shedao-qigong");
        map_skill("unarmed", "shedao-qigong");
        map_skill("sword", "shenlong-jian");
//        map_skill("finger", "yingxiong-sanzhao");

        prepare_skill("strike", "huagu-mianzhang");
        prepare_skill("hand", "shenlong-bashi");

        create_family("������", 1, "����");

        set("inquiry", ([
                "������" : "һ�������벻���������̵�(join shenlongjiao)��",
                "���"   : "һ�������벻���������̵�(join shenlongjiao)��",
                "�鰲ͨ" : "�㲻������ǲ��ǣ�",
                "����"   : "�Ҿ��������̽�����",
                "����"   : "����ѧʲô��������",
                "����"   : "����ѧʲô��������",
                "���ɷ�" : (: ask_fei :),
                "��������" : (: ask_xian :),
                "���Ķϳ�" : (: ask_cui :),
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "staff.chang" :),
                (: perform_action, "staff.chang2" :),
                (: perform_action, "staff.chang3" :),
                (: perform_action, "fei" :),
                (: perform_action, "xian" :),
                (: perform_action, "cui" :),
                (: perform_action, "strike.hua" :),
                (: perform_action, "hand.xian" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }));

        set_temp("apply/attack", 150);
        set_temp("apply/defense", 150);
        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob", 5);
	setup();
        carry_object("/clone/weapon/gangzhang")->wield();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver", 35);
}

int do_flatter(string arg)
{
        if (! this_player()->query_temp("pending/flatter"))
        {
                command("say ��������ʲô���������ķ����ҵġ�");
                return 0;
        }

        if (! arg ) return notify_fail("��˵��ʲô��\n");

        this_player()->set_temp("pending/flatter", 0);
        message_vision(CYN "$N����˵����" + arg + "\n" NOR,
                       this_player());

        if (strsrch(arg, "���겻��") >=0 && (strsrch(arg, "�����ɸ�") >=0 &&
            strsrch(arg, "��������") >=0 && strsrch(arg, "������ʥ") >=0))
        {
                command("smile");
                command("say �⻹��ࡣ\n");
                command("recruit " + this_player()->query("id"));
        } else
        {
                command("say ����˲����ҷ�����������������㣿!");
                kill_ob(this_player());
        }
        return 1;
}

// ���겻��,�����ɸ�,��������,������ʥ

void die()
{
        message_vision("\n$N���������,��Ȼ������ɱ����,....��"
                       "˵���������۵������ˡ�\n", this_object());
        ::die();
}

void init()
{
        object ob;

        ::init();

        if (interactive(ob = this_player()) && ! is_fighting())
        {
                remove_call_out("greeting");
                call_out("greeting", 4, ob);
        }
        add_action("do_flatter", "flatter");
        add_action("do_join", "join");
}

void greeting(object ob)
{
        object obj;
        if (! objectp(ob)) return;
        if (interactive(ob) && objectp(obj = present("used gao", ob)))
        {
                set("combat_exp", 1000000);
                set("qi", 500);
                set("jing", 500);
        }
}

mixed ask_fei()
{
        object me;

        me = this_player();
        if (me->query("can_perform/shedao-qigong/fei"))
                return "�Լ�����������������ǰ���£�";

        if (me->query("family/family_name") != query("family/family_name"))
                return "�����Ķ����ģ���������";

        if (me->query("shen") > -40000)
                return "����ֶλ����������ҿɲ��ܴ�������У�";
        
        if (me->query("family/gongji") < 800) 
                return "��Ϊ��������Ч�����������������Ȳ�æ���㡣"; 
                
        if (me->query_skill("shedao-qigong", 1) < 100)
                return "����ߵ��湦ѧ����ô��������˼�����ң�";

        message_vision(HIM "$n" HIM "��ͷ������������ˣ���˵����"
                       "��Ϊ������ৡ����������������������ѽ���"
                       "�֣������������\n" NOR,
                       me, this_object());
        command("say ���úܼ򵥣������㶮��û�У�");
        tell_object(me, HIG "��ѧ���˷�������\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 90000);
        me->improve_skill("martial-cognize", 1500000); 
        me->set("can_perform/shedao-qigong/fei", 1);
        me->add("family/gongji", -800); 
        return 1;
}

mixed ask_xian()
{
        object me;

        me = this_player();
        if (me->query("can_perform/shedao-qigong/xian"))
                return "�Լ�����������������ǰ���£�";

        if (me->query("family/family_name") != query("family/family_name"))
                return "�����Ķ����ģ���������";

        if (me->query("shen") > -50000)
                return "��Ҫ�ú�Ϊ�����Ч�����ֶ�Ҫ���ݸ������Ҳ��ܴ������ž��У�";
                
        if (me->query("family/gongji") < 800) 
                return "��Ϊ��������Ч�����������������Ȳ�æ���㡣"; 
                
        if (me->query_skill("shedao-qigong", 1) < 120)
                return "����ߵ��湦�������������ܾͿ������а��";

        message_vision(HIM "$n" HIM "��ͷ���������ҿ��ţ�˵��˫��"
                       "���ƣ��ۼ���ʽ���ϣ���Ȼ��ȥ��һ�䣬����"
                       "������ʣ�������ת�������ۼ���\n" NOR,
                       me, this_object());
        command("say ��ɶ������а��");
        tell_object(me, HIG "��ѧ�����������֡�\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 90000);
        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 90000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 90000);
        me->improve_skill("martial-cognize", 1500000); 
        me->set("can_perform/shedao-qigong/xian", 1);
        me->add("family/gongji", -800); 
        return 1;
}

mixed ask_cui()
{
        object me;

        me = this_player();
        if (me->query("can_perform/shedao-qigong/cui"))
                return "�Լ�����������������ǰ���£�";

        if (me->query("family/family_name") != query("family/family_name"))
                return "�����Ķ����ģ���������";

        if (me->query("shen") > -50000)
                return "��Ҫ�ú�Ϊ�����Ч�����ֶ�Ҫ���ݸ������Ҳ��ܴ������ž��У�";

        if (me->query("family/gongji") < 800) 
                return "��Ϊ��������Ч�����������������Ȳ�æ���㡣"; 
                
        if (me->query_skill("shedao-qigong", 1) < 120)
                return "����ߵ��湦�������������ܾͿ������а��";

        message_vision(HIM "$n" HIM "��ͷ���������ҿ��ţ�ֻ��$n"
                       HIM "���һ����һ�ƻ���������Ȼ�з���֮����\n"
                       "һʱ��$N" HIM "ֻ���ú������ѣ�$p" HIM "����"
                       "������ɽ����һ�㣬���춯�ء�\n" NOR,
                       me, this_object());
        command("say ���в����ɱ仯����������ȡʤ��������ף�");
        tell_object(me, HIG "��ѧ���˴��Ķϳ���\n" NOR);
        if (me->can_improve_skill("sword"))
                me->improve_skill("sword", 90000);
        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 90000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 90000);
        me->improve_skill("martial-cognize", 1500000); 
        me->set("can_perform/shedao-qigong/cui", 1);
        me->add("family/gongji", -800); 
        return 1;
}

void attempt_apprentice(object ob)
{
        if (ob->query("party/party_name") != "������")
        {
                command("say �㲻�Ǳ��̽���, ����������!");
                return;
        }

        if ((int)ob->query("shen") > -1000)
        {
                command("say �ֳ����ɽ��ҪͶ��״���㲻ɱ��"
                        "���׵�������ô��ʾ���ģ���");
                return;
        }

        if (ob->query_temp("pending/flatter"))
        {
                command("say ����˲����ҷ�����������������㣿");
                kill_ob(ob);
                return 0;
        } else
        {
                command("say �Һ鰲ͨ�������������ʥ����ô������");
                message_vision("�鰲ͨ΢��˫�ۣ��������룬һ��"
                               "��������(flatter)�����ӡ�\n",
                               this_player());
                ob->set_temp("pending/flatter", 1);
                return 0;
        }
}

/*
void unconcious()
{
        die();
}
*/

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "����" :
        case "����" :
        case "����" :
                return QUEST_D->accept_ask(this_object(), me, topic);
                break;

        case "���ֻ���" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/huagu-mianzhang/hua",
                           "name"    : "���ֻ���",
                           "sk1"     : "huagu-mianzhang",
                           "lv1"     : 100,
                           "sk2"     : "strike",
                           "lv2"     : 100,
                           "sk3"     : "force",
                           "lv3"     : 100,                           
                           "gongxian": 1000,
                           "shen"    : -20000, ]));
                break;

        case "Ӣ������" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/yingxiong-sanzhao/sanzhao",
                           "name"    : "Ӣ������",
                           "sk1"     : "yingxiong-sanzhao",
                           "lv1"     : 200,
                           "sk2"     : "strike",
                           "lv2"     : 200,
                           "sk3"     : "force",
                           "lv3"     : 200,                           
                           "shen"    : -50000, ]));

                
        case "��������" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/shenlong-bashi/xian",
                           "name"    : "��������",
                           "sk1"     : "shenlong-bashi",
                           "lv1"     : 100,
                           "sk2"     : "hand",
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