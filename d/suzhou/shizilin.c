// Room: /d/suzhou/shizilin.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
	set("short", "狮子林");
        set("long", @LONG
你一走进狮子林，便不禁为江南苏州园林的奇妙美景所折服。狮子林东南多
山，西北多水，素有『假山王国』之称。假山峰峦叠嶂，曲折盘旋，石洞连绵不
断，幽深莫测。咫尺之间，可望而不可及，变幻无穷如入迷宫，不由得不为之赞
叹不已。
LONG );
	set("outdoors", "suzhou");
	set("no_clean_up", 0);
	set("exits", ([
		"east"      : "/d/suzhou/yanyutang",
		"west"      : "/d/suzhou/nandajie1",
		"northeast" : "/d/suzhou/zhipoxuan",
	]));
	set("coor/x", 210);
	set("coor/y", -230);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

