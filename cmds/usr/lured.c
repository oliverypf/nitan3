// lured.c

#include <ansi.h>
inherit F_CLEAN_UP;

void hunting(object me);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object yr;
        int t;

        if (! mapp(environment(me)->query("resource/quarry")))
                return notify_fail("这里看不出有野兽出现的样子。\n");
 
        if (! objectp(yr = present("you er", me)) || yr->query_amount() < 1 ||
            ! yr->query("lure"))
                return notify_fail("你身上没有诱饵了。\n");    
                
        if (me->is_busy() || me->is_fighting())
                return notify_fail("等你忙完了再说吧！\n");

        if (me->query_temp("hunting"))
                return notify_fail("别着急，再等等！\n");

        message_vision(HIG "$N将" + yr->name() + "放在地上，躲在一旁静静守侯着 ……\n" NOR, me);
        yr->add_amount(-1);
        
        t = 3 + random(3);
        
        me->set_temp("hunting", 1);     
        me->set_temp("hunting_env", environment(me));

        me->start_call_out((: call_other, __FILE__, "do_hunting", me :), t);
        me->start_busy(t);

        return 1;
}

void do_hunting(object me)
{
        object obq;
        object env;
        string* temp;
        string str;
        mapping quarry;
        int i, point;

        env = environment(me);
        if (env != me->query_temp("hunting_env"))
        {
                me->delete_temp("hunting");
                me->delete_temp("huning_env");
                return;
        }

        quarry = env->query("resource/quarry");
        temp = keys(quarry);
        i = random(sizeof(temp));

        me->delete_temp("hunting");
        me->delete_temp("hunting_env");

        // 获得几率判断是否动物出现
        point = quarry[temp[i]];

        if (random(100) >= point)
        {
                write(HIY "你等了半天却不见猎物出现，而诱饵已经变质，只好作罢。\n" NOR);
                return;
        }       
        
        obq = new(temp[i]);
        obq->move(env);
        obq->set("owner", me->query("id"));

        switch(random(4))
        {
                case 0:
                        message_vision(HIG "不一会儿，一只" + obq->name() + HIG "窜了出来，将"
                                      "诱饵一口咬在嘴里。\n" NOR, me);
                        break;

                case 1:
                        message_vision(HIM "转眼间，一只" + obq->name() + HIM "突然出现，将" 
                                       "诱饵吞进嘴里。\n" NOR, me);
                        break;

                case 2:
                        message_vision(HIW "良久，一只" + obq->name() + HIW "大摇大摆地走了"
                                       "出来，仔细地打量着诱饵。\n" NOR, me);
                        break;

                default:
                        message_vision(HIC "少时，一只" + obq->name() + HIC "窜了过来，一口将"
                                       "诱饵叼在了嘴上，相貌贪婪之极。\n" NOR, me);
                        break;
        }

        return;
        
}

int help(object me)
{
        write(@HELP
指令格式 :

        lured <诱饵>：在当前地点放置诱饵等待猎物出现。
                      注：一次只能放一个诱饵。
                     
HELP
    );
    return 1;
}

