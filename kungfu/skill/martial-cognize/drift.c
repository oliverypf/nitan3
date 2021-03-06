// drift.c
// Modified by Dumbness, 2003-5-25 13:24

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        int i;
        object *inv;
        string *can_perform;

        // ???不明白什么意思
        can_perform = me->query("can_perform/martial-cognize");
        me->set("test",can_perform);

        if(!arrayp(can_perform) || 
                !sizeof(can_perform) || 
                member_array("drift",can_perform) == -1)
                return notify_fail("你还没有学会使用天龙之翼！\n");

        if( me->is_fighting() )
                return notify_fail("战斗中无法使用天龙之翼！\n");

        if(me->is_busy())
                return notify_fail("你上一个动作还没有完成，无法使用天龙之翼。\n");
        
        //By Dumbness, 设置了no_drift属性的房间禁止飞入与飞出
        if(environment(me)->query("no_drift"))
                return notify_fail("这里禁止使用天龙之翼。\n");

        if( me->query("jing") < 300 )
                return notify_fail("你的精神不好！\n");

        if( me->query("jingli") < 500 )
              return notify_fail("你的精力不够！\n");
 
        if( me->query("max_jingli") <= 1000 )
              return notify_fail("你的精力还没有达到这个层次！\n");

        if( me->is_ghost())
                return notify_fail("鬼魂无法使用天龙之翼！\n");

        if( me->in_prison())
                return notify_fail("监狱里无法使用天龙之翼！\n");

        if( environment(me)->query("trds") )
                return notify_fail("屠人场里无法使用天龙之翼！\n");     
        
        if((int) me->query_skill("martial-cognize",1) < 300)
                return notify_fail("你的武学修养不够高深！\n");

        inv = deep_inventory(me);
        for (i = 0; i < sizeof(inv); i++)
        {
                if (! userp(inv[i]) && ! inv[i]->is_muxiang()) continue;
                if (userp(inv[i]))
                        return notify_fail("你背的是谁？背一个大活人还怎么飞？\n");
                if (inv[i]->is_muxiang())
                        return notify_fail("你又不是飞机，背着这么大一个木箱，能飞得动么？\n");
        }

        inv = 0;
        write("你要移动到哪一个人身边？");
        input_to( (: call_other, __FILE__, "select_target", me :));
        return 1;
}

void select_target(object me, string name)
{
        object ob;
        int effect;

        if( !name || name=="" ) {
                write("中止使用天龙之翼。\n");
                return;
        }

        ob = find_player(name);
        if( !ob || !me->visible(ob) || wizardp(ob) )
                ob = find_living(name);

        //by rama 修正了可以通过晕倒的大米drift到别人身上get物品的bug
        if( !ob || 
            !living(ob) || 
            !me->visible(ob) || 
            wizardp(ob) || 
            !environment(ob) || 
            !ob->query("max_jingli") || 
            (strsrch(base_name(ob), "/kungfu/class/generate/") == 0 ) ||
            !ob->query("jingli")) {
                write("你无法感受到这个人的存在 ....\n");
                write("你要移动到哪一个人身边？");
                input_to( (: call_other, __FILE__, "select_target", me :));
                return;
        }

        if( environment(ob) == environment(me)) {
                write(ob->name() + "不就正在你身边嘛 ....\n");
                return;
        }

        //By Dumbness, 设置了no_drift属性的房间禁止飞入与飞出
        if(environment(me)->query("no_drift"))
        {
                write("这里禁止使用太龙之翼。\n");
                return;
        }

        if( me->is_fighting() ) {
                write("战斗中无法使用天龙之翼！\n");
                return;
        } else if( me->query("jingli") < 100 ) {
                write("你的精力不够！\n");
                return;
        } else if( me->query("jing") < 300) {
                write("你的精神不好! \n");
                return;
        } else if( me->is_ghost()) {
                write("鬼魂不能使用天龙之翼！\n");
                return;
        } else if( me->in_prison()) {
                write("监狱里不能使用天龙之翼！\n");
                return;
        } else if( environment(me)->query("trds") ) {
                write("屠人场里不能使用天龙之翼！\n");
                return;
        }

        effect = random(200);
        me->add("jingli", -(100+effect));
        me->receive_damage("jing", 100+effect);
        
        if ( ob->query("max_jingli") < 500 ) {
                write("你感受到了对方的存在，但是不能精确定位。\n");
                return;
        }

        //By Dumbness, 设置了no_drift属性的房间禁止使用天龙之翼进出
        if(environment(ob)->query("no_drift") || environment(ob)->query("no_fight"))
        {
                write("你想要去的地方不可以用天龙之翼。\n");
                return;
        }

        // 一些特别的区域不允许使用天龙之翼
        if( environment(ob)->query("trds") ||
            strsrch(base_name(environment(ob)),"/data/room/") != -1 ||
            strsrch(base_name(environment(ob)),"/u/") != -1 ||
            strsrch(base_name(environment(ob)),"/d/xiakedao/") != -1 ||
            strsrch(base_name(environment(ob)),"/d/tulong/") != -1 ) {
                write("你想要去的地方不可以用天龙之翼！\n");
                return;
        }

        message_vision( HIY "$N一阵长啸，浑身弥漫一阵金色云雾，逐渐在后背汇聚，形成一对金色翅膀，似乎要振翅高飞 ....\n" NOR, me);

        //if( random(ob->query("max_jingli")) > me->query("max_jingli")) {
        //Modified by Dumbness for use effect jingli as conform condition
        if(random(ob->query("max_jingli")) > (me->query("max_jingli")>me->query("eff_jingli")?me->query("max_jingli"):me->query("eff_jingli"))){
                write("你因为不够熟练而失败了。\n");
                return;
        }

        /* Sigh, 失败。鉴于目前华夏已经是一个运行“稳定”地MUD，就算是设计上的失败，也已经难以
        从本质上作出有效的控制，多次讨论并参考一些玩家意见后对天龙之翼地控制尝试迫于阻力取消，
        原因很大程度上源于玩家的习惯性思维方式很难改变。至此宣布所有有关解体的设想与构思也一并
        取消，本巫师不再对此作任何尝试。
        //Added by Dumbness for contract with level of skill which named 'martial-cognize'
        if( (random(( (int) me->query_skill("martial-cognize",1)-250)) > 50) 
                && (me->query_temp("drift_fail_times")<4) ) {
                me->add_temp("drift_fail_times", 1);
                write("你因为不够熟练而失败了。\n");
                return;
        }
        me->delete_temp("drift_fail_times");
        */
        
        message( "vision", HIY "\n" + me->name() + "轻轻展开双臂，背后的金色翅膀温柔的卷起一阵暖风"
                + "，只见" + me->name() + "缓缓升空，瞬间消失得无影无踪！\n\n" NOR, environment(me), ({ me }) );
        me->move(environment(ob));
        message( "vision", HIY "\n一阵微风吹过，" + me->name() + "宛若天神般缓缓而降，金色的翅膀光芒四射。\n\n" NOR,
                environment(ob), ({ me }) );
}

