// Room: /d/suzhou/liuyuan.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
	set("short", "留园");
        set("long", @LONG
留园是苏州的一大名景之一，它以结构布局紧密、厅堂华丽宏敝、装饰精美
典雅而享有『吴中第一名园』之誉。
LONG );
	set("outdoors", "suzhou");
//	set("no_clean_up", 0);
	set("exits", ([
		"east"  : "/d/suzhou/nandajie2",
		"west"  : "/d/suzhou/hehuating",
	]));
	set("objects", ([
		"/d/suzhou/npc/lady1" : 1,
	]));
	set("coor/x", 190);
	set("coor/y", -240);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

