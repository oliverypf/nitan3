// qingbomen.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "清波门");
        set("long", @LONG
园门口有一大门楼，大匾上刻着『清波门』。门楼下站着几个嬉嬉哈哈的少
女，惹人坠步相观。在往西就进了聚景园，往东便回到大路。
LONG );
        set("exits", ([
            "east"   : "/d/hangzhou/road14",
            "west"   : "/d/hangzhou/jujingyuan",
        ]));
        set("objects", ([
            "/d/hangzhou/npc/girl" : 2,
        ]));
        set("outdoors", "hangzhou");
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
