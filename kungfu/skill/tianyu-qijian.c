// tianyu-qijian.c 天羽奇剑
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([	"action":"$N使一式「海天一线」，手中$w嗡嗡微振，幻成一条疾光刺向$n的$l",
	"force" : 60,
        "dodge" : 0,
	"damage": 10,
	"lvl" : 0,
	"skill_name" : "海天一线",
	"damage_type":	"割伤"
]),
([	"action":"$N错步上前，使出「闪电惊虹」，手中$w划出一道剑光劈向$n的$l",
	"force" : 70,
        "dodge" : 10,
	"damage": 15,
	"lvl" : 30,
	"skill_name" : "闪电惊虹",
	"damage_type":	"割伤"
]),
([	"action":"$N手中$w一抖，一招「日在九天」，斜斜一剑反腕撩出，攻向$n的$l",
	"force" : 80,
        "dodge" : 5,
	"damage": 20,
	"lvl" : 40,
	"skill_name" : "日在九天",
	"damage_type":	"割伤"
]),
([	"action":"$N手中剑锵啷啷长吟一声，一式「咫尺天涯」，一道剑光飞向$n的$l",
	"force" : 90,
        "dodge" : 10,
	"damage": 25,
	"lvl" : 50,
	"skill_name" : "咫尺天涯",
	"damage_type":	"刺伤"
]),
([	"action":"$N一式「怒剑狂花」，手中$w舞出无数剑花，使$n难断虚实，无可躲避",
	"force" : 120,
        "dodge" : 15,
	"damage": 30,
	"lvl" : 60,
	"skill_name" : "怒剑狂花",
	"damage_type":	"刺伤"
]),
([	"action":"$N手中$w斜指苍天，剑芒吞吐，一式「九弧震日」，对准$n的$l斜斜击出",
	"force" : 140,
        "dodge" : 5,
	"damage": 35,
	"lvl" : 70,
	"skill_name" : "九弧震日",
	"damage_type":	"刺伤"
]),
([	"action":"$N一式「漫天风雪」，手腕急抖，挥洒出万点金光，刺向$n的$l",
	"force" : 160,
        "dodge" : 5,
	"damage": 40,
	"lvl" : 80,
	"skill_name" : "漫天风雪",
	"damage_type":	"刺伤"
]),
([	"action":"$N一式「天河倒泻」，$w飞斩盘旋，如疾电般射向$n的胸口",
	"force" : 190,
        "dodge" : 5,
	"damage": 45,
	"lvl" : 100,
	"skill_name" : "天河倒泻",
	"damage_type":	"刺伤"
]),
([	"action":"$N一式「天外飞仙」，$w突然从天而降，一片金光围掠$n全身",
	"force" : 210,
        "dodge" : 5,
	"damage": 50,
	"lvl" : 120,
	"skill_name" : "天外飞仙",
	"damage_type":	"刺伤"
])
});

string *hit_msg = ({ 
        HIY"\n$N前招将落，后招已至，前后两招形如一式，此起彼伏，连绵不绝！\n"NOR,
        HIC"\n对方正惊愕间，却见$N的剑光已闪至眼前，剑光闪处寒气四射，咄咄逼人！\n"NOR,
        HIR"\n只见$N人影一闪，身形已然欺近对方，手中剑光闪烁，嗡嗡做响！\n"NOR,
        HIM"\n却见$N一剑未定二剑已至，随有前后之分却同时到达，速度之快晃如两剑同时发出！\n"NOR,
        HIG"\n不见$N手臂动作，只听一声龙吟之生，这第二剑已破空而至，刺至身前！\n"NOR,
        HIB"\n紧跟着，$N又是一剑刺至，剑招虽分前后，但剑锋几乎同时到达，速度之快难以言表！\n"NOR,
        HIW"\n一眨眼间$N的身形已欺至身前，若有若无，这第二剑已于电光火石间刺至身前！\n"NOR,
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
        if (me->query_skill("force") < 40)
                return notify_fail("你的内功火候不够，不能学习天羽奇剑。\n");

        if (me->query("max_neili") < 200)
                return notify_fail("你的内力不够，不能学习天羽奇剑。\n");

	return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
	level = (int) me->query_skill("tianyu-qijian",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	object weapon;

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "sword")
		return notify_fail("你使用的武器不对。\n");

	if ((int)me->query("qi") < 50)
		return notify_fail("你的体力不够练天羽奇剑。\n");

        if ((int)me->query("neili") < 40)
		return notify_fail("你的内力不够练天羽奇剑。\n");

	me->receive_damage("qi", 40);
        me->add("neili", -25);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"tianyu-qijian/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        object weapon;
        string amsgs;

        weapon = me->query_temp("weapon");

        if ( me->query_temp("09_pfm/zhu")
             && me->query_temp("09_pfm/zhu") > 0
             && weapon
             && weapon->query("skill_type") == "sword"
             && !me->query_temp("09_pfm/zhu_hit_done") )
        {
                amsgs = hit_msg[random(sizeof(hit_msg))];
                me->add("neili", -40);
                me->add_temp("09_pfm/zhu", -1);
                message_vision(amsgs, me);
                me->set_temp("09_pfm/zhu_hit_done", 1);
                COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), 1);
                COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), 1); 
                COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), 1); 
                me->delete_temp("09_pfm/zhu_hit_done");
        }
}

string query_description() 
{
        return 
        "天羽奇剑，顾名思义，其步伐如羽，剑法之奇，乃是当今武林中少有"
        "的之上乘剑法。然而由于灵鹫宫弟子均为女子，因此此剑法闪躲能力较高，"
        "而威力却明显不足，加之灵鹫宫主要以空手武功的天山六阳掌而闻名天下，"
        "因此此剑法只适合新入宫的弟子修习，以为日后学习高深武学打下坚实的"
        "基础。尽管如此，倘若此剑法当真修练得出神入化，亦可凭此在江湖上扬"
        "名立万了。";
}
