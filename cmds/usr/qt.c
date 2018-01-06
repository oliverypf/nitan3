// quest.c

#include <ansi.h>
 
int main(object me, string arg)
{
        int status = me->query("to_pvp/status");
        string str, master = me->query("family/master_name");

        if( !me->query("to_pvp") )
                return 0;

        if( !status )
        {
                if( me->query("to_pvp/time") < time() )
                {
                        me->delete("to_pvp");
                        return notify_fail(master+"长叹道：“难道本派中就没有人能杀此贼？悲呼！！！”");
                }
                if( arg == "cancel" )
                {
                        me->delete("to_pvp");
                        return notify_fail(master+"怒道：“哼，象你如此胆小之人，怎能成大器！！！”\n");
                }
                if( arg == "ok" )
                {
                        me->set("to_pvp/status",1);
                        me->set("to_pvp/time",time() + 600);
                        return notify_fail("你怒道：“岂有此理，如此恶贼，我岂能容他在此世上，待我去杀了此贼，替本派除害”。\n");
                }
                str =  sprintf("你将要被派去杀的本门仇敌%s(%s)。\n", 
                        me->query("to_pvp/name"), me->query("to_pvp/id"));
                str += sprintf("你还有%s秒来接受这个任务。\n",
                        CHINESE_D->chinese_number(me->query("to_pvp/time") - time()));
                str += "如果你要接受任务请输入“qt ok”\n";
                write(str);
                return 1;
        }
        else
        {
                if( me->query("to_pvp/time") < time() )
                {
                        me->delete("to_pvp");
                        return notify_fail(master+"：“杀此小贼，居然用了这么久的时间还没杀死，我看也不再找你了，你给我好好的学艺吧，我另外找人，哼！！！”");
                }
                str =  sprintf("你要杀的本门仇敌是%s(%s)。\n", 
                        me->query("to_pvp/name"), me->query("to_pvp/id"));
                str += sprintf("你需要在%s前来完成这个任务。\n",
                        CHINESE_D->chinese_date(me->query("to_pvp/time")));
                write(str);
                return 1;
        }
        return 0;
}

