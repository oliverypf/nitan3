//Room: /d/dali/chahua2.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","茶花园");
        set("long", @LONG
大理茶花冠绝天下，镇南王府的茶花自然更非凡品。你站在茶花园中，看万
紫千红，争奇斗妍，心胸大爽。靠东一座小石凳，凳后柳树成行，拖曳水面，把
湖面点成一个个涟漪。
LONG );
	set("objects", ([
	   "/d/dali/obj/chahua1": 1,
	   "/d/dali/npc/huanu": 1,
	]));
	set("outdoors", "dali");
	set("exits",([ /* sizeof() == 1 */
	    "west"  : "/d/dali/chahua1",
	    "northeast"  : "/d/dali/chahua3",
	    "southeast"  : "/d/dali/chahua4",
	]));
	setup();
	replace_program(ROOM);
}

