#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp, lvl;
        int jing, skill;
        object ob;

        if (! objectp(ob = me->query_temp("handing")) ||
            ! ob->valid_as_xiao())
                return notify_fail("你手里没有拿萧，无法使出这个绝招！\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(HIW "碧海潮生按玉箫" NOR
                                   "只能对战斗中的对手使用。\n");

        skill = me->query_skill("yuxiao-jian", 1);

        if (skill < 150)
                return notify_fail("你的玉箫剑法等级不够, 不能使用"
                                   HIW "碧海潮生按玉箫" NOR "。\n");

        if (me->query("neili") < 300)
                return notify_fail("你的内力不够，无法运用"
                                   HIW "碧海潮生按玉箫" NOR "。\n");

        ap = me->query_skill("yuxiao-jian", 1) +
             me->query_skill("sword");
        dp = target->query_skill("force");

        lvl = (int) me->query_skill("yuxiao-jian", 1) / 5 + 1;

        msg = HIC "$N" HIC "手按玉箫，脚踏八卦方位，奏出" NOR
              HIW "§" NOR+HIC "碧海潮生按玉箫" NOR+HIW "§" NOR
              HIC "............\n" NOR;
        msg += HIW "\n只听得如鸣琴，如击玉，发了几声，接着悠悠"
                   "扬扬，飘下一阵清亮柔和的洞箫声来。\n" NOR;

        if (dp < random(ap * 2))
        {
                msg += HIR "$n" HIR "心头一荡，脸上不自禁的露出微笑！\n" NOR;
                jing = (int) target->query("max_jing");
                target->receive_damage("jing", jing * lvl / 300, me);
                target->receive_wound("jing", jing * lvl / 500, me);
                message_combatd(msg, me, target);
        } else
        {
                msg += HIY "$n" HIY "暗暗凝神守一，对这箫声自是应付裕如！\n" NOR;
                message_vision(msg, me, target);
        }

        msg = HIW "那洞箫声情致飘忽，缠绵宛转，便似一个女子一会"
                  "儿叹息，一会儿呻吟，一会儿又软语温存或\n"
                  "柔声叫唤。\n" NOR;

        if (dp < random(ap))
        {
                msg+= HIR "$n只感全身热血沸腾，就只想手舞足蹈的乱动一番！\n"NOR;
                jing = (int) target->query("max_jing");
                target->receive_damage("jing", jing * lvl / 100, me);
                target->receive_wound("jing", jing * lvl / 240, me);
                message_combatd(msg, me, target);
        } else
        {
                msg += HIY "$n" HIY "暗暗凝神守一，对这箫声自是应付裕如！\n"NOR;
                message_vision(msg, me, target);
        }

        msg = HIW  "那箫声清亮宛如大海浩淼，万里无波，远处潮水缓缓推近，渐近渐快，其后洪涛汹涌，白浪连\n"
                   "山，而潮水中鱼跃鲸浮，海面上风啸鸥飞，再加上水妖海怪，群魔弄潮，忽而冰山飘至，忽而\n"
                   "热海如沸，极尽变幻之能事。\n" NOR;

        if (dp < random(ap / 2))
        {
                msg+= HIR "$n" HIR "只感心头滚热，喉干舌燥！\n" NOR;
                jing = (int) target->query("max_jing");
                target->receive_damage("jing", jing * lvl / 50, me);
                target->receive_wound("jing", jing * lvl / 120, me);
                message_combatd(msg, me, target);
        } else
        {
                msg += HIY "$n" HIY "暗暗凝神守一，对这箫声自是应付裕如！\n" NOR;
                message_vision(msg, me, target);
        }

        msg = HIW "箫声愈来愈细，几乎难以听闻，尤如潮退后水平如"
                  "镜，海底却又是暗流湍急。\n" NOR;

        if (dp < random(ap / 4))
        {
                msg+= HIR "$n" HIR "此时已陷绝境，再也无法脱身！\n" NOR;
                jing = (int) target->query("max_jing");
                target->receive_damage("jing", jing * lvl / 25, me);
                target->receive_wound("jing", jing * lvl / 50, me);
                me->start_busy(1 + random(2));
                me->add("neili", -200);
                message_combatd(msg, me, target);
                return 1;
        } else
        {
                msg+= HIY "$n" HIY "暗暗凝神守一，对这箫声自是应付裕如！\n" NOR;
                me->start_busy(2 + random(3));
                me->add("neili", -200);
                message_vision(msg, me, target);
                return 1;
        }

        message_combatd(msg, me, target);

        return 1;
}

