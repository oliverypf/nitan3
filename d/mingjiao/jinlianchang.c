// Code of JHSH
// Room: /d/mingjiao/jinlianchang.c
// Zhangchi 3/00

inherit ROOM;

void create()
{
	set("short", "������");
        set("long", @LONG
������ש�̣���Ϊ��ǽ�����������б����ܣ�ʮ�˰��������һ���С��ٳ�
���濴������÷��׮��������ɳ�����뱸�ǳ��������ϱ������ط��Ű�������С
��һ����ʯ������ʱ�м������̵��ӹ�ȥ������¡�
LONG );
	set("exits", ([ /* sizeof() == 1 */
                "north" : __DIR__"rjqlwch",
]));
	set("objects",([
		__DIR__"obj/huolu" : 1,
]));

	set("no_fight", 1);
	set("no_sleep", 1);
	set("no_steal", 1);
	set("no_clean_up", 0);
	set("cost", 1);

	setup();

}

int valid_leave(object me, string dir)
{
        if (dir == "north" && this_player()->query_temp("refining") )
               return notify_fail("�����ڴ����������뿪���\n");
        return ::valid_leave(this_player(), dir);
}