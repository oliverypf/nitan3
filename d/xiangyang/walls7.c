// Room: /d/xiangyang/walls7.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
	set("short", "南城头");
        set("long", @LONG
这里是襄阳的南城头。一些宋兵正在城头巡逻，一个牙将正在这儿负责接受
各种守城材料，一些弓箭手正拈弓搭箭紧盯着城下的动静。
LONG );
        set("outdoors", "xiangyang");

	set("exits", ([
		"northwest" : "/d/xiangyang/wallw8",
		"eastdown"  : "/d/xiangyang/walls5",
	]));
	set("objects", ([
		"/d/xiangyang/npc/ya"   : 1,
		"/d/xiangyang/npc/bing" : 2,
	]));
	set("coor/x", -330);
	set("coor/y", -130);
	set("coor/z", 40);
	setup();
	replace_program(ROOM);
}
