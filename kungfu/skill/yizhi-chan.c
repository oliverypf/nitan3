// yizhi-chan.c 一指禅
#include <ansi.h>
inherit SHAOLIN_SKILL;

mapping *action = ({
([      "action": "$N双指并拢，一式「佛恩济世」，和身而上，左右手一前一后戳向$n的胸腹间",
        "force" : 340,
        "attack": 75,
        "dodge" : 35,
        "parry" : 55,
        "damage": 22,
        "skill_name" : "佛恩济世",
        "damage_type" : "刺伤"
]),
([      "action": "$N左掌护胸，一式「佛光普照」，右手中指前后划了个半弧，猛地一"
                  "甩，疾点$n的$l",
        "force" : 370,
        "attack": 70,
        "dodge" : 10,
        "parry" : 45,
        "damage": 15,
        "skill_name" : "佛光普照",
        "damage_type" : "刺伤"
]),
([      "action": "$N身形闪动，一式「佛门广渡」，双手食指端部各射出一道青气，射"
                  "向$n的全身要穴",
        "force" : 360,
        "attack": 72,
        "dodge" : 10,
        "parry" : 52,
        "damage": 15,
        "skill_name" : "佛门广渡",
        "damage_type" : "刺伤"
]),
([      "action": "$N盘膝跌坐，一式「佛法无边」，左手握拳托肘，右手拇指直立，遥"
                  "遥对着$n一捺",
        "force" : 380,
        "attack": 68,
        "dodge" : 5,
        "parry" : 48,
        "damage": 20,
        "skill_name" : "佛法无边",
        "damage_type" : "刺伤"
])
});

int valid_enable(string usage) { return usage == "finger" || usage == "parry"; }

int valid_combine(string combo) { return combo == "banruo-zhang"; }

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("练一指禅必须空手。\n");

        if ((int)me->query_skill("force") < 60)
                return notify_fail("你的内功火候不够，无法学一指禅。\n");

        if ((int)me->query("max_neili") < 300)
                return notify_fail("你的内力太弱，无法练一指禅。\n");

        if ((int)me->query_skill("finger", 1) < (int)me->query_skill("yizhi-chan", 1))
                return notify_fail("你的基本指法水平有限，无法领会更高深的一指禅。\n");

    return 1;
}

string query_skill_name(int level)
{
        return action[random(sizeof(action))]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}

int practice_skill(object me)
{
        if (me->query_temp("weapon") ||
            me->query_temp("secondary_weapon"))
                return notify_fail("你必须空手练习！\n");

        if ((int)me->query("qi") < 70)
                return notify_fail("你的内力太低了。\n");

        if ((int)me->query("neili") < 70)
                return notify_fail("你的内力不够练一指禅。\n");

        me->receive_damage("qi", 62);
        me->add("neili", -68);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"yizhi-chan/" + action;
}

void skill_improved(object me)
{
        int level = (int)me->query_skill("yizhi-chan", 1);

        if( level == 180 && ! me->query("sl/con"))
        {
                me->add("con", 1);
                me->set("sl/con", 1);
                tell_object(me, "你的一指禅和般若掌学有所成，提高了你的根骨。\n");
        }
        /*
        if ((string)me->query("family/family_name") == "少林派")
        {
                if( !(level % 10) && level >= (int)me->query_skill("hunyuan-yiqi", 1) )
                {
                        me->improve_skill("hunyuan-yiqi", (level - 5), 1);
                        tell_object(me, "你在一指禅方面的造诣增进了你的混元一气功修为。\n");
                }
        }
        */
}
mixed hit_ob(object me, object victim, int damage_bonus)
{
        mixed result;
        
        if( damage_bonus < 50 ) return 0;

        if( random(damage_bonus/2) > victim->query_str() )
        {
                result = ([ "damage" : damage_bonus ]);
                result += ([ "msg" : HIR "你听到「咻」一声轻响，一股劲气直透$n的前胸！\n" NOR ]);
                return result;
        } 
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        if (objectp(me->query_temp("weapon")))
                return 0;

        lvl = me->query_skill("yizhi-chan", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}
