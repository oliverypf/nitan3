#include <room.h>
inherit ROOM;

void create()
{
        set("short", "回春堂药店");
        set("long", @LONG
回春堂药店是整个北京城里最大最有名气的药铺。你还没走进这里，便闻到
一股浓浓的药材气味，那是从药柜上的几百个小抽屉里散发出来的。一位伙计在
柜台后站着，堆着笑脸招呼着客人。
LONG );
       set("exits", ([
                "west" : "/d/beijing/xi_2",
                "east" : "/d/beijing/liandan_neiting",
        ]));
        set("objects", ([
                "/d/beijing/npc/kid1" : 1,
                "/d/beijing/npc/yaopuhuoji" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -40);
	set("coor/y", 270);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}