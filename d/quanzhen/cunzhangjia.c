inherit ROOM;

void create()
{
        set("short", "�峤��");
        set("long", @LONG
�����Ǵ峤�ļң�������ѷ���һЩ��ͷ������֮���ũ
���þߣ���һЩ�Ǵ��д�����ﻵ�ˣ�������峤���޵ġ���
��ǰ������ʮ���ʺ������������һЩ��ɵ�Ұζ��
LONG);
        set("exits", ([
                "south" : __DIR__"guchang",
        ]));
        set("objects", ([
                __DIR__"npc/dibao" : 1,
        ]));
        setup();
        replace_program(ROOM);
}