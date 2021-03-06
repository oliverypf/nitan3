#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIY"地安门广场"NOR);
        set("long", @LONG
这里就是地安门广场，灰色的城墙给人以庄严肃穆之感，往北通过紫禁城的
地安门就是城郊了。远远望去，紫禁城的轮廓益发显得雄伟高大，一条护城河绕
城而过。一条笔直的青石大道横贯东西，东边是地安门东街广场，西边是地安门
西街广场。南边通过一条小桥就是皇宫的北门了。[2;37;0m
LONG );
	set("exits", ([
		"south" : "/d/beijing/hgmen_n",
		"north" : "/d/beijing/di_dajie1",
	       "west" : "/d/beijing/di_xigc",
              "east" : "/d/beijing/di_donggc",
	]));
	set("objects", ([
		"/d/beijing/npc/bing1" : 2,
		"/d/beijing/npc/bing3" : 1,
		"/d/beijing/npc/old2" : 1,
		"/d/beijing/npc/kid1" : 1,
	]));
	set("outdoors", "beijing");
	set("coor/x", -30);
	set("coor/y", 310);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
