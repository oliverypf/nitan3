inherit VRM_SERVER;

void create()
{
        // 迷宫房间所继承的物件的档案名称。
        set_inherit_room( ROOM );

        //迷宫房间里的怪物。
        set_maze_npcs( ([
                "/clone/quarry/hu" :  1, 
                "/clone/quarry/lang" :  2, 
                "/clone/quarry/xiong" :  1, 
                "/clone/quarry/bao" :  1, 
                "/clone/quarry/zhu" :  1, 
                "/clone/quarry/zhu2" :  1, 
        ]) );
        
        // 迷宫出口的怪物。
        set_exit_npcs( ([
                "/d/maze/npc/hunter" : 1,
        ]) );
        // 迷宫入口的怪物。
        set_entry_npcs( "/d/maze/npc/hunter" );
        
        //迷宫的单边长
        set_maze_long(10);

        //入口方向(出口在对面)
        set_entry_dir("east");

        //入口与区域的连接方向
        set_link_entry_dir("east");

        //入口与区域的连接档案名
        set_link_entry_room("/d/maze/zhaoze");

        //出口与区域的连接方向
        set_link_exit_dir("west");

        //出口与区域的连接档案名
        set_link_exit_room("/d/maze/zhaoze");

        //入口房间短描述
        set_entry_short("森林入口");

        //入口房间描述
        set_entry_desc(@LONG
原始森林树叶苍黑如盖，遮天蔽日，林中弥漫着枯叶腐烂 
和树脂混合的味道，地上的苔鲜落叶踩上去软绵绵的，上面还 
布满野兽的痕迹，四周浓密的山雾，让人难以分辨方向。 
LONG);

        //出口房间短描述
        set_exit_short("森林出口");

        //出口房间描述
        set_exit_desc(@LONG
你眼前一亮，深深的吸了口气，心想总算是出来了。四周小鸟
的鸣叫声和风吹过树林的沙沙声交织成美丽的大自然的旋律。
LONG
);

        //迷宫房间的短描述
        set_maze_room_short("原始森林");

        //迷宫房间的描述，如果有多条描述，制造每个房
        //间的时候会从中随机选择一个。
        set_maze_room_desc(@LONG
原始森林树叶苍黑如盖，遮天蔽日，林中弥漫着枯叶腐烂 
和树脂混合的味道，地上的苔鲜落叶踩上去软绵绵的，上面还 
布满野兽的痕迹，四周浓密的山雾，让人难以分辨方向。 
LONG
);
        // 迷宫房间是否为户外房间？
        set_outdoors(1);
        /*
        set_valid_rooms( ({
                "/d/maze/senlin1",
                "/d/maze/senlin1",
                "/d/maze/senlin2",
                "/d/maze/senlin3",
        }));
        */
        // create_maze();
}


string query_my_map(){  return read_file(__DIR__"senlin.map");}

