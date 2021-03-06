#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action": "$N使出一招「棒打双犬」，手中$w化作两道青光砸向$n的$l",
        "force" : 280,
        "attack": 98,
        "dodge" : 120,
        "parry" : 100,
        "damage": 80,
        "damage_type": "挫伤"
]),
([      "action": "$N手中$w左右晃动，一招「拨草寻蛇」向$n的$l攻去",
        "force" : 300,
        "attack": 100,
        "dodge":  100,
        "parry" : 120,
        "damage": 100,
        "damage_type": "挫伤"
]),
([      "action": "$N举起$w，居高临下使一招「打草惊蛇」敲向$n的$l",
        "force" : 290,
        "attack": 99,
        "dodge":  120,
        "parry" : 100,
        "damage": 70,
        "damage_type": "挫伤"
]),
([      "action": "$N施出「拨狗朝天」，$w由下往上向$n撩去",
        "force" : 310,
        "attack": 105,
        "dodge" : 80,
        "parry" : 140,
        "damage": 90,
        "damage_type": "挫伤"
]),
});

int valid_enable(string usage)
{
        return usage == "staff" || usage == "parry";
}

int valid_learn(object me)
{
        if (me->query("dex") < 26)
                return notify_fail("你的先天身法太差，无法学习打狗棒法。\n");

        if ((int)me->query("max_neili") < 1500)
                return notify_fail("你的内力修为不足，无法学习打狗棒法。\n");

        if ((int)me->query_skill("staff", 1) < 100)
                return notify_fail("你的基本杖法不够，无法学习打狗棒法。\n");

        if ((int)me->query_skill("staff", 1) < (int)me->query_skill("dagou-bang", 1))
                return notify_fail("你的基本杖法水平有限，无法领会更高深的打狗棒法。\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;

        if ((int) me->query_skill("dagou-bang", 1) < 100
           || ! me->query_temp("feng_zijue")
           || ! (weapon = me->query_temp("weapon"))
           || ! living(me)
           || weapon->query("skill_type") != "staff")
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("force") + mp;
        dp = me->query_skill("parry", 1) / 2 +
             me->query_skill("dagou-bang", 1);

        if (ap / 2 + random(ap) < dp * 3 / 4)
        {
                result = ([ "damage": -damage ]);

                switch (random(2))
                {
                case 0:
                        result += (["msg" : HIG "$n" HIG "巧妙的施展打狗棒「" HIY "封"
                                            HIG "」字诀，手中" + weapon->name() + HIG
                                            "左封右闭，使得$N" HIG "的攻势全然落空。\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIG "$n" HIG "急转手中" + weapon->name() +
                                            HIG "，打狗棒「" HIY "封" HIG "」字诀发挥"
                                            "得淋漓尽致，顿将$N" HIG "的招式驱于无形。\n" NOR]);
                        break;
                }
                return result;
        } else
        if (mp >= 100)
        {
                switch (random(2))
                {
                case 0:
                        result = HIY "$n" HIY "蓦地施展出打狗棒「封」字"
                                 "诀，可是$N" HIY "理也不理，当即挥招直"
                                 "入，进袭$n" HIY "。\n" NOR;
                        break;
                default:
                        result = HIY "$n" HIY "急转手中" + weapon->name() +
                                 HIY "，左封右闭，然而$N" HIY "却是精演"
                                 "天数，丝毫不受$n" HIY "的迷惑。\n"  NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
        }
}

int practice_skill(object me)
{
        object weapon;

        if (! objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "staff")
                return notify_fail("你使用的武器不对。\n");

        if ((int)me->query("qi") < 80)
                return notify_fail("你的体力不够练打狗棒法。\n");

        if ((int)me->query("neili") < 100)
                return notify_fail("你的内力不够练打狗棒法。\n");

        me->receive_damage("qi", 75);
        me->add("neili", -80);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"dagou-bang/" + action;
}
/*
mixed hit_ob(object me, object victim, int damage)
{
        string msg;
        int ap, dp, zhencost;
        string result;
        object weapon;

        if (! objectp(weapon = me->query_temp("weapon")))
                return 0;
        
        zhencost = sqrt(weapon->weight() / 10) + 10;
        if (me->query("neili") < zhencost || me->query("jing") < zhencost)
                return 0;
                
        ap = me->query_skill("stick", 1) / 2 +
             me->query_skill("dagou-bang", 1);

        dp = victim->query_skill("dodge", 1) / 2 +
              victim->query_skill("parry", 1) / 4;
        dp += victim->query_skill("martial-cognize", 1);
        

        
        if (random(ap+dp) > ap) 
        {
                result = HIG "突然青光闪动，棒招来势神妙无方，" + (string)weapon->query("name") + HIG "击中了$n。\n" NOR;
                damage = weapon->query("weapon_prop/damage") * 3;
                if (! victim->is_busy())
                        victim->start_busy(1 + random(3));
                me->add("neili", -zhencost);
                me->add("jing",  -zhencost);
                return ([ "msg" : result, "damage" : damage ]);
        }
        else if (random(ap + 2 * dp) > ap) 
        {
                result = HIG "$N猛地递出一招，这一棒迅捷无伦，直取$n眉心，$p「啊」的一声，连退出数尺！\n" NOR;
                damage = weapon->query("weapon_prop/damage") * 2;
                if (! victim->is_busy())
                        victim->start_busy(1 + random(2));
                me->add("neili", -zhencost);
                me->add("jing",  -zhencost);
                return ([ "msg" : result, "damage" : damage ]);
        }
        else
        {
                result = weapon->name()+ HIG "幌动，霎眼之间竟已转到$n身后，拍的一声，在$p臀上抽了一下。！\n" NOR;
                damage = weapon->query("weapon_prop/damage");
                if (! victim->is_busy())
                        victim->start_busy(1+random(1));
                me->add("neili", -zhencost);
                me->add("jing",  -zhencost);
                return ([ "msg" : result, "damage" : damage ]);
        }
}
*/
int query_effect_parry(object attacker, object me)
{
        int lvl;
        object weapon;

        if (! objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "staff")
                return 0;

        lvl = me->query_skill("dagou-bang", 1);
        if (lvl < 80)  return 50;
        if (lvl < 200) return 100;
        if (lvl < 280) return 160;
        if (lvl < 350) return 200;
        return 240;
}
