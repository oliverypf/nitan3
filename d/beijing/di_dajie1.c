#include <room.h>
inherit ROOM;

void create()
{
	set("short", "地安门大街");
        set("long", @LONG
这里是北京城的地安门大街。街道是整整齐齐的杨树林，道上行人络绎不绝，
车辆马匹穿插其中。大街上有闲逛的游人，上京赶考的考生，背负着担子的挑夫
以及正在玩耍着的幼童构出了一幅繁忙热闹的盛世景象。北边过地安门到达京城
的城郊，南边是热闹的地安门广场。
LONG );
       set("exits", ([
		"north" : "/d/beijing/di_dajie2",
		"south" : "/d/beijing/dianmen",
		"east" : "/d/beijing/dong_2",
		"west" : "/d/beijing/di_5",
	]));

	set("outdoors", "beijing");
	set("coor/x", -30);
	set("coor/y", 320);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
