inherit ROOM;

void create()
{
        set("short", "��");
        set("long", @LONG
���С�񷿶������ɲ񣬶�������ĺ�����Ϊ������ȥ��
��������һ�͵ġ�Ҳ��Щ���������ɽ���˷��׸�����ģ���
�ڿ���ߵ�Ұ���ֶ�������������Ե�Ҳ��ûȱ����̡�
LONG);

        set("objects", ([
  		__DIR__"npc/obj/chaihe1" : 1,
	]));

        set("no_clean_up", 0);
        set("exits", ([
  		"south" : __DIR__"zoulang2",
  		"east" : __DIR__"caidi3",
	]));

        setup();
        replace_program(ROOM);
}