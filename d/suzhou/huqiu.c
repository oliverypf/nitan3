// Room: /d/suzhou/huqiu.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
	set("short", "虎丘山");
        set("long", @LONG
虎丘山因其山形似蹲虎而得名。又相传吴王葬后，有白虎出现其墓上，故名
虎丘。山前绝岩幽谷，花木繁茂，景色绮丽，后山空蒙宽广，石壁树立，气势雄
浑。有『山藏寺里』的特色，被誉为『吴中第一名胜』。
LONG );
	set("outdoors", "suzhou");
//	set("no_clean_up", 0);
	set("exits", ([
		"northeast" : "/d/suzhou/road1",
		"south"      : "/d/suzhou/toumenshan",
	]));
        set("objects", ([
		"/d/hangzhou/obj/shuzhi" : 1,
		"/d/hangzhou/obj/eluanshi" : 1,
	]));
	set("coor/x", 190);
	set("coor/y", -170);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

