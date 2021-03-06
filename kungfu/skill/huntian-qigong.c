// huntian-qigong.c
#include <ansi.h>
inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force)
{
        return force == "jiaohua-neigong";
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("huntian-qigong", 1);
        return lvl * lvl * 15 * 9 / 100 / 200;
}

int valid_learn(object me)
{
        if (me->query_skill("force", 1) < 30)
                return notify_fail("你的基本内功火候不够，无法学习混天气功。\n");

	    return 1;
}

int practice_skill(object me)
{
	    return notify_fail("混天气功只能用学(learn)的来增加熟练度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"huntian-qigong/" + func;
}
mapping heal_msg(object me)
{
        return ([
                "start_self"     : HIW + BLK "你缓缓坐起身来调匀呼吸，将混天功真气流遍全身。\n" NOR,
                "start_other"    : HIW + BLK + me->name() + "坐起身来，头顶立时冒出热气，额头汗如雨下，全身颤抖不已。\n" NOR,
                "finish_other"   : WHT "但见"+ me->name() + "脸上一阵红潮涌上，便即退去，又成灰白，这般红变白，白变红的转了数次，站了起来。\n" NOR,
                "unfinish_other" : HIW + BLK + me->name() + "眼睛慢慢睁开一线，吐了一滩黑血，站了起来。\n" NOR,
        ]);
}

mapping exercise_msg(object me)
{
        return ([
                "apply_short"   : "面带神光，衣袍飞舞。",
                "start_self"    : "你随意坐下，双手平放在双膝，默念口诀，开始运起独门心法。\n",
                "start_other"   : me->name() + "随意在那里坐下，双手平放在双膝，嘴唇微微颤动，身上的衣袍开始鼓动起来。\n",
                "halt_self"     : "你面色一沉，迅速收气，站了起来。\n",
                "halt_other"    : "只见" + me->name() + "面色一沉，吸了口气，站了起来。\n",
                "finish_self"   : "你吸气入丹田，真气运转渐缓，慢慢收功，双手抬起，站了起来。\n",
                "finish_other"  : "只见" + me->name() + "双手抬起，站了起来，衣袍慢慢垂了下来。\n"                
        ]);
}

