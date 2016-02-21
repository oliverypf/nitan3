inherit ROOM;

void create ()
{
        set ("short", "��ջ");
        set("long", @LONG
����һ��������¡��ջ����ջ�ſڳ������������������ææµµ�ع����ţ�
���Ϸ���һЩ�ո������Ļ������������������ż��Ż��ܣ������϶��Ÿ�ʽ
�������ӻ�����һ���ƹ�ģ���������ڹ�̨����Ц�ݿɾϵ��к��ſ��ˡ���ջ��
ǽ������һ���ƾɵĸ�ʾ(gaoshi)��
LONG );
        set("item_desc", (["gaoshi" : "��������ȱ���֣������Ӷһ���̹����ɻ
work	��ʼ������
", ]));
        set("exits", 
        ([ //sizeof() == 1
                "west" : "/d/changan/yongtai-dadao1",
        ]));
        set("objects", 
        ([ //sizeof() == 1
                "/d/changan/npc/liang" : 1,
        ]));
	set("no_fight", 0);
        set("coor/x", -430);
	set("coor/y", 30);
	set("coor/z", 0);
	setup();
}

void init()
{
        add_action("do_work", "work");
}

int do_work(string arg)
{
        object ob;
        object me;
        me = this_player();
        if (! me->query_temp("working_in_huozhan"))
        {
                if (me->query("qi") < 25 ||
                    me->query("jing") < 25)
                        return notify_fail("������ۻ��ˣ��ɲ����ˡ�\n");

                message_vision("$N�ӳ���ж��һ�����Ĵ��ף���"
                               "����ǽ�ߣ��۵��������ۣ�\n",me);
                me->receive_damage("qi", 20);
                me->receive_damage("jing", 20);
                ob = new("/clone/money/coin");
                ob->set_amount(10);
                ob->move(me);
                message_vision("���ϰ�Ц���еض�$N˵����������������Ĺ�Ǯ��\n",me);
                me->set_temp("working_in_huozhan",1);
                remove_call_out ("reset_work");
                call_out ("reset_work", 2 + random(3), me);
        } else
        {
                message_vision("���ϰ�Ͻ���$N����������Ъһ�����\n",me);
        }
        return 1;
}

void reset_work(object me)
{
        me->delete_temp("working_in_huozhan");
}
