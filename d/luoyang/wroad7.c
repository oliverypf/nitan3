inherit ROOM;

void create()
{
	set("short", "��µ�");
	set("long", @LONG
��������Ҫ�����ڳ����ˣ�ԶԶ��ȥ�����Կ����سǵĹٱ����ڼ��
�Ŷӳ��ǵ�·�ˣ�Ҳ����̫�������ŵ�Ե�ʣ���������Ѳ���ǰ����ô��
�ˡ�������һ����꣬��Ի����ɮ��ꡱ���ϱ���һ���ľ�����ʯС·��
LONG);
        set("outdoors", "luoyang");
	set("no_clean_up", 0);
	set("exits", ([
  		"east" : __DIR__"wroad4",
  		"north" : __DIR__"shudian",
  		"south" : __DIR__"suishi12",
  		"west" : __DIR__"xidoor",
	]));
        set("objects", ([
                "/d/beijing/npc/kid1" : 1,
        ]));
	set("coor/x", -220);
	set("coor/y", 0);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}