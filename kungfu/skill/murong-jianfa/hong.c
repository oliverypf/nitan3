// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
#include <combat.h>

#define NING "「" HIM "白虹贯日" NOR "」"

inherit F_SSERVER;
#include <balance.h>
 
int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
 
        if (! target) target = offensive_target(me);

        if (userp(me) && ! me->query("can_perform/murong-jianfa/hong"))
                return notify_fail("你还没有受过高人指点，无法施展" NING "。\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(NING "只能在战斗中对对手使用。\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
              (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对，难以施展" NING "。\n");

        if (me->query_skill("dodge", 1) < 100)
                return notify_fail("你的基本轻功的修为不够，难以施展" NING "。\n");

        if (me->query_skill("force", 1) < 100)
                return notify_fail("你的基本内功的修为不够，难以施展" NING "。\n");

        if (me->query_skill("murong-jianfa", 1) < 100)
                return notify_fail("你的慕容剑法修为不够，难以施展" NING "。\n");

        if (me->query_skill_mapped("sword") != "murong-jianfa")
                return notify_fail("你没有激发慕容剑法，难以施展" NING "。\n");

        if (me->query("neili") < 250)
                return notify_fail("你现在真气不够，难以施展" NING "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "\n$N" HIW "大喝一声，飞身而起，使出绝招「" HIM "白虹贯日" HIW "」将毕生功力运于"
              + weapon->name() + HIW "上，\n顿时剑光四射，剑势如虹，强大的剑气追将$n。\n" NOR;

        ap = ap_power(me, "sword");
        dp = dp_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = da_power(me, "sword");
                
                me->add("neili", - 220);
                me->start_busy(1 + random(2));
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 65,
                                           HIR "$n" HIR "开料不及，正欲躲闪，却已经中剑。\n" NOR);
        } else
        {
                me->add("neili", -120);
                me->start_busy(2);
                msg += CYN "可是$n" CYN "随手招架，竟将这招化解。\n"NOR;
        }

        message_sort(msg, me, target);

        return 1;
}

