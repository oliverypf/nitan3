// leidong 雷动九天
// by winder 98.12

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int perform(object me)
{
        int skill, count, count1;

        if ((int)me->query_temp("leidong"))
                return notify_fail("你已经在运功中了。\n");

 	if (me->query_temp("weapon"))
		return notify_fail("只有空手才能使用雷动九天。\n");

       if ((int)me->query("neili") < 500)
                return notify_fail("你现在的真气不够。\n");

        if ((int)me->query_skill("zixia-shengong",1) < 100)
                return notify_fail("你的紫霞神功修为还不够。\n");

        if ( me->query_skill_mapped("force") != "zixia-shengong")
                return notify_fail("你所使内功于破玉拳心法不符合！\n");  

        skill = me->query_skill("cuff");
        if (skill < 135)
                return notify_fail("你的破玉拳修为还不够。\n");

        me->add("neili", -400);
        message_combatd(HIM "$N" HIM "深深吸了一口气，脸上顿时"
                        "紫气大盛，出手越来越重！\n" NOR, me);

        count = skill / 20;

        if (me->is_fighting())
                me->start_busy(2);

        me->add_temp("apply/str", count);
        me->add_temp("apply/dex", count);
        me->set_temp("leidong", 1);
        me->start_call_out((: call_other,  __FILE__, "remove_effect", me, count :), skill / 3);

        return 1;
}

void remove_effect(object me, int amount)
{
        if ((int)me->query_temp("leidong"))
        {
                me->add_temp("apply/str", -amount);
                me->add_temp("apply/dex", -amount);
                me->delete_temp("leidong");
                tell_object(me, CYN "你的雷动九天运行完毕，将内力收回丹田。\n" NOR);
        }
}

