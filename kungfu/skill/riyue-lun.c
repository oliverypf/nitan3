#include <ansi.h>;
inherit SKILL;

mapping *action = ({
([      "action" : "$N使一招「破竹势」，抡起手中的$w向$n的$l砸去",
        "force"  : 120,
        "attack" : 27,
        "dodge"  : -10,
        "parry"  : 40,
        "lvl"    : 0,
        "damage" : 62,
        "damage_type" : "挫伤",
        "skill_name"  : "破竹势",
]),
([      "action" : "$N使一招「隐山谷势」，双肩一沉，舞动手中$w向$n的$l横扫",
        "force"  : 160,
        "attack" : 38,
        "dodge"  : -20,
        "parry"  : 45,
        "lvl"    : 35,
        "damage" : 66,
        "damage_type" : "挫伤",
        "skill_name"  : "隐山谷势",
]),
([      "action" : "$N使一招「隐微势」，就地一滚，手中自下而上撩向$n的$l",
        "force"  : 200,
        "attack" : 43,
        "dodge"  : -20,
        "parry"  : 47,
        "lvl"    : 70,
        "damage" : 70,
        "damage_type" : "挫伤",
        "skill_name"  : "隐微势",
]),
([      "action" : "$N使一招「擒纵势」，身形起伏之际$w扫向$n的$l",
        "force"  : 240,
        "attack" : 51,
        "dodge"  : 5,
        "parry"  : 50,
        "lvl"    : 100,
        "damage" : 75,
        "damage_type" : "挫伤",
        "skill_name"  : "擒纵势",
]),
([      "action" : "$N使一招「圆满势」，$w如离弦之箭般直捣$n的$l",
        "force"  : 280,
        "attack" : 55,
        "dodge"  : -10,
        "parry"  : 55,
        "lvl"    : 120,
        "damage" : 80,
        "damage_type" : "挫伤",
        "skill_name"  : "圆满势",
]),
([      "action" : "$N跃入半空，使一招「月重辉势」，高举$w敲向$n的$l",
        "force"  : 320,
        "attack" : 61,
        "dodge"  : 10,
        "parry"  : 60,
        "lvl"    : 140,
        "damage" : 85,
        "damage_type" : "挫伤",
        "skill_name"  : "月重辉势",
]),
([      "action" : "$N使一招「捉月势」，斜举手中$w击向$n的$l",
        "force"  : 360,
        "attack" : 65,
        "dodge"  : -15,
        "parry"  : 68,
        "lvl"    : 150,
        "damage" : 95,
        "damage_type" : "挫伤",
        "skill_name"  : "捉月势",
]),
([      "action" : "$N提一口真气，使出「显吉祥」，$w扫向$n的头部",
        "force"  : 400,
        "attack" : 70,
        "dodge"  : -20,
        "parry"  : 75,
        "lvl"    : 160,
        "damage" : 110,
        "damage_type" : "挫伤",
        "skill_name"  : "显吉祥",
]),
});

string  *msg = ({
        CYN"空中那五只$w"CYN"对击，声若龙吟，悠悠不绝，就在$n"CYN"一呆之际，$w"CYN"飞砸了出去！"NOR,
        MAG"呜呜声响中，$w"MAG"旋转飞舞着撞向$n"MAG"，在$p"MAG"便要挡隔时，却绕过$n"MAG"飞到了身後"NOR,
        MAG"$w"MAG"连续掷出，连续飞回，绕著$n"MAG"兜个圈子，忽高忽低，或正或斜，所发声音也是有轻有响，旁观众人均给扰得眼花撩乱，心神不定"NOR,
        YEL"一声「小心了！」，蓦然间$w"YEL"五体归一，并排向$n"YEL"撞去，势若五牛冲阵，威不可挡"NOR,
        HIB"只见$w"HIB"绕著$n"HIB"，上下翻飞，$w"HIB"跳跃灵动，呜呜响声不绝，掀的阵阵狂风有如刀割，似要把$n"HIB"从中劈开"NOR,
        HIR"突然，狂风乱起，激荡中那$w"HIR"相碰相撞，五轮归一，合并了向$n砸去"NOR,
        HIG"法轮在$n"HIG"身前环饶，猛地向$p"HIG"迎头击下，接着又飞来一轮，一抄一送，呜呜声响，兜向$n"HIG"$l"NOR,
        HIW"呼呼飞啸声中，那五只$w"HIW"或直飞、或斜飞、或回旋、或下坠、或上升，霎时间$n"HIW"的全部退路已被封死"NOR,
        HIC"猛地里$w"HIC"向$n"HIC"$l飞砸下，在$p"HIC"沉肩卸避之时，$w"HIC"又突然上飞击出，砸向$p"HIC"的$l"NOR,
        HIM"那$w"HIM"飞旋砸到，$n"HIM"却并不回头，听风辨器，一一挡开，但$w"HIM"便如长上了眼睛一般，竟然又旋飞到了$n"HIM"$l"NOR,
        HIG"随着森森慑人的厉吼，$w"HIG"锤蓦而急颤晃动，轮身嗡嗡震响，在不及眨眼的瞬息间，耀目的电光金蛇四射迸闪，飞掠周遭，迅捷无匹的击$n！"NOR,
        MAG"法轮再次合围，紫电精芒围著$n"MAG"的四周旋舞闪射，千百轮影幻映出一幅美丽而眩目的图案，这图案美极了，似是一片多角形的紫色雪晶体"NOR,
});

int valid_enable(string usage)
{
	return usage == "hammer" || usage == "parry";
}

int valid_learn(object me)
{
        /*
        if (me->query("str") < 32)
                return notify_fail("你先天膂力不足，难以修炼日月轮法。\n");
        */

        if ((int)me->query("max_neili") < 1000)
                return notify_fail("你的内力不够。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的内功火候太浅。\n");

        if ((int)me->query_skill("hammer", 1) < 100)
                return notify_fail("你的基本锤法不够，难以修炼日月轮法。\n");

        if ((int)me->query_skill("hammer", 1) < (int)me->query_skill("riyue-lun", 1))
                return notify_fail("你的基本锤法水平有限，无法领会更高深的日月轮法。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action) - 1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        string str, message;        
        level = (int) me->query_skill("riyue-lun",1);
        
        if (! userp(me) && weapon)
        {
                if (weapon->query("id") == "jin lun") 
                        str = "金轮";
                else if (weapon->query("id") == "yin lun") 
                        str = "银轮";
                else if (weapon->query("id") == "fa lun") 
                        str = "法轮";
                else str = weapon->name();
                message = msg[random(sizeof(msg))];
                message = replace_string(message, "$w", str);
                switch(str)
                {
                case "金轮" : 
                        message = HIY+message+NOR; break;
                case "银轮" : 
                        message = HIW+message+NOR; break;
                case "法轮" : 
                        message = HIC+message+NOR; break;
                default : break;
                }
                return ([
                        "action" : message,
                        "damage" : 200,
                        "damage_type" : random(2)?"砸伤":"瘀伤",
                        "dodge" : 100,
                        "parry" : 100,
                        "attack": 200,
                ]);
        }        
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        object weapon;

        if (! objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "hammer")
                return notify_fail("你使用的武器不对。\n");

        if ((int)me->query("qi") < 70)
                return notify_fail("你的体力不够，练不了日月轮法。\n");

        if ((int)me->query("neili") < 70)
                return notify_fail("你的内力不够，练不了日月轮法。\n");

        me->receive_damage("qi", 62);
        me->add("neili", -68);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"riyue-lun/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        object weapon, weapon1;
        //  object master;   
        weapon = me->query_temp("weapon");
        weapon1= victim->query_temp("weapon");

        if (weapon1 && me->query_skill("riyue-lun", 1) > 150 && me->query("jiali")
        &&  me->query("neili") > 1000 
        &&  random(10) >= 5 && (string)weapon->query("skill_type") == "hammer"
        &&  me->query_skill_mapped("parry") == "riyue-lun")
        {
                message_combatd(HIW"$N手臂暴长，施展「锁」字诀，"+weapon->name()+
                                HIW"探出，嚓的一声锁住了$n"+weapon1->name()+HIW"。\n"NOR, 
                                me, victim);

                if (random(me->query_str()) > victim->query_str())
                {           
                        me->add("neili", -100);
                        message_combatd(HIG+me->query("name")+"运劲回拉，$n臂骨喀的一声，险些就被拉断，剧痛之下手一松，"+
                                        weapon1->name()+HIG"被夺了过去！\n"NOR, me, victim);
                        weapon1->unequip();
                        weapon1->move(me);
                } else 
                if (random(me->query_str()) > victim->query_str() / 2)
                {           
                        me->add("neili", -50);
                        message_combatd(HIG+me->query("name")+"运劲回拉，$N被带得踉跄几步，但觉虎口剧痛，"+
                                        weapon1->name()+HIG"脱手飞出！\n"NOR, victim);
                        weapon1->unequip();
                        weapon1->move(environment(victim));
                } else
                if (victim->query_temp("shield"))
                {           
                        me->add("neili", -50);
                        message_combatd(HIY"$N借势前冲，"+weapon1->name()+HIY"直刺过去，但被"+
                                        victim->query("name")+"护体真气荡得滑了开去。\n"NOR, victim);
                }

                else    message_combatd(HIY"$N借势前冲，"+weapon->name()+HIY"直刺"+victim->query("name")+"，"+
                                        victim->query("name")+"变招奇快，"+weapon->name()+HIY"一抖松脱，纵身退了开去。\n"NOR, 
                                        victim);
        }
}

