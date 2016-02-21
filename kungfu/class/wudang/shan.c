// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// shan.c �Ŵ�ɽ

#include <ansi.h>
#include "wudang.h"

inherit NPC;
inherit F_MASTER;
inherit F_GUARDER;

mixed ask_me();

void create()
{
        set_name("�Ŵ�ɽ", ({ "zhang cuishan", "zhang" }));  
        set("nickname","�䵱����");
        set("long", 
                "�����������������ӡ��䵱����֮�е��Ŵ�ɽ��\n"
                "����һ���ɸɾ����İ�ɫ���ۡ�\n");
        set("gender", "����");
        set("age",31);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 28);
        set("int", 35);
        set("con", 28);
        set("dex", 28);
        set("max_qi", 5000);
        set("max_jing", 5000);
        set("neili", 4500);
        set("max_neili", 4500);
        set("jiali", 150);
        set("level", 20);
        set("combat_exp", 1400000);
        set("score", 60000);

        set_skill("force", 180);
        set_skill("yinyun-ziqi", 180);
        set_skill("taiji-shengong", 180);
        set_skill("dodge", 170);
        set_skill("tiyunzong", 170);
        set_skill("unarmed", 180);
        set_skill("taiji-quan", 180);
        set_skill("strike", 180);
        set_skill("yitian-zhang", 180);
        set_skill("wudang-zhang", 170);
        set_skill("hand", 160);
        set_skill("paiyun-shou", 160);
        set_skill("parry", 180);
        set_skill("sword", 175);
        set_skill("wudang-jian", 175);
        set_skill("taiji-jian", 175);
        set_skill("taoism", 160);
        set_skill("literate", 120);

        set("no_teach", ([
                "taiji-shengong" : "Ҫ��ѧϰ̫����������������̡�",
                "taiji-jian"     : "̫���������������״���",
                "taiji-quan"     : "̫��ȭ�����������״���",
        ]));

        map_skill("force", "taiji-shengong");
        map_skill("dodge", "tiyunzong");
        map_skill("unarmed", "taiji-quan");
        map_skill("parry", "taiji-quan");
        map_skill("sword", "taiji-jian");
        map_skill("strike", "yitian-zhang");

        prepare_skill("strike", "yitian-zhang");

        create_family("�䵱��", 2, "����");

        set("inquiry", ([
                "����������": (: ask_me :),
                "˭������"  : (: ask_me :),
                "����"  : (: ask_me :),
        ]));

        set("chat_chance_combat", 40);
        set("chat_msg_combat", ({
                (: perform_action, "strike.zheng" :),
        }) );

        set("coagents", ({
                ([ "startroom" : "/d/wudang/sanqingdian",
                   "id"        : "song yuanqiao" ]),
        }));
        
        set("master_ob", 4);
	setup();

        carry_object("/d/wudang/obj/whiterobe")->wear();
}

void init()
{
        object ob;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting",2 , ob);
        }
}

void greeting(object ob)
{
        if (! ob || environment(ob) != environment())
                return;

        if (find_object(query("startroom")) == environment())
                return;

        if ((int)ob->query("shen") < -1000)
        {
                say(CYN "\n\n�Ŵ�ɽ����ŭ�ݣ���аħ��������˱���"
                    "���ˣ����Ҵ��䵱����\n\n");
                message_vision("�Ŵ�ɽ�Ӹ����£�����һ�У�$Nֻ"
                               "��Ӳ�ӣ����ӻ���һ�¡�\n", ob);
                COMBAT_D->do_attack(this_object(), ob, query_temp("weapon"));
        }
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if (ob->query_int() < 30)
        {
                command("say ������ʽ������������������ľ��磬����Ҳ�ǰ״\n");
                return;
        }

        if ((int)ob->query("shen") < 5000) {
                command("say ���䵱���������������ɣ��Ե���Ҫ���ϡ�");
                command("say �ڵ��з��棬" + RANK_D->query_respect(ob) +
                        "�Ƿ����ò�����");
                return;
        }

        if ((int)ob->query_skill("yinyun-ziqi", 1) < 70)
        {
                command("say ���䵱����ע���ڹ��ķ�" + RANK_D->query_respect(ob)+
                        "�Ƿ�Ӧ�����䵱�ķ��϶��µ㹦��?");
                return;
        }

        if ((int)ob->query_skill("taoism", 1) < 70)
        {
                command("say ϰ����Ϊ��ǿ�����壬һζ�������ǲ���ȡ�ġ�");
                command("say �ҿ��㻹��Ҫ���������Է��������������������"
                        "�ĵ����ķ���");
                return;
        }

        command("say �ðɣ��Ҿ��������ˡ�");
        command("recruit " + ob->query("id"));
}
mixed ask_me()
{
        object me;

        me = this_player();
        if (me->query("can_perform/yitian-zhang/zheng"))
                return "�㲻���Ѿ���������ô���Ǿ������ݡ�";

        if (me->query("family/family_name") != query("family/family_name"))
                return RANK_D->query_respect(me) + "���������䵱�ɵ��ˣ��γ����ԣ�";

        if (me->query_skill("yitian-zhang", 1) < 1)
                return "�������������ƶ�ûѧ����̸ʲô���п��ԣ�";

        if (me->query("family/gongji") < 200)
                return "��Ϊ���䵱��Ч�����������������Ȳ�æ���㡣";

        if (me->query("shen") < 12000)
                return "������������������Ļ��ܲ������Ҳ��ܴ�����У�";

        if (me->query("max_neili") < 800)
                return "���������Ϊ̫ǳ���������������ɡ�";

        if (me->query_skill("yitian-zhang", 1) < 120)
                return "������������ƻ������ң�Ҫ��������";

        message_vision(HIY "$n" HIY "���˵�ͷ������̫���񹦣�����������"
                       "�ƶ�ʮ����һ����\n�ɣ�Я������ɽ����֮��һ��ʩ"
                       "չ�˳�����ֻ��˫�Ʒ׷ɣ��Ʒ�\n������ֱ�ε�$N" HIY
                       "����������ʹ��\n" NOR, me, this_object());
        command("nod");
        command("say �����������ƶ�ʮ��������ʹ�����������С���������ˣ�");
        tell_object(me, HIC "��ѧ���ˡ�˭�����桹��\n" NOR);
        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("zhenshan-zhang"))
                me->improve_skill("zhenshan-zhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        me->set("can_perform/yitian-zhang/zheng", 1);
        me->add("family/gongji", -200);

        return 1;
}


