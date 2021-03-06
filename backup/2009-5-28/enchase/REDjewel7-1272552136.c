// SN:i_ZaEF9[jR1_kHMd
//  Written by ZHANG TIANSHI(Lonely 2007/10/15)	Wed May 27 13:32:19 2009
#include <ansi.h>
inherit ITEM;

int is_enchase_ob(){ return 1; }

void create()
{
	set_name(RED "神之宝石" NOR, ({ "RED jewel7" }));
	set_weight(50);
	set("unit", "块");
	set("long", RED "一块闪烁这奇异光芒的宝石，让人感到一阵阵的心悸。\n" NOR );
	set("value", 200000);
	set("can_be_enchased", 1);
	set("magic/type", "magic");
	set("magic/power", 23);
	set("enchase/SN", 6);
	set("enchase/level", 7);
	set("enchase/cur_firm", 97);
	set("enchase/wspe_data", ([
		"attack" : 40,
		"add_lighting" : 23,
		"max_jingli" : 4000,
		"max_jingli" : 4000,
		"attack" : 40,
		"ap_power" : 7,
		"practice_times" : 7,
	]));
	set("enchase/aspe_data", ([
		"learn_times" : 7,
		"defense" : 40,
		"max_neili" : 4000,
		"max_experience" : 400000,
		"dex" : 8,
		"reduce_fire" : 23,
		"max_neili" : 4000,
	]));
	set("wear_msg", HIC "$N" HIC "轻轻地把$n"HIC "戴在头上。\n" NOR);
	set("remove_msg", HIC "$N" HIC "轻轻地把$n"HIC "从头上摘了下来。\n" NOR);

	setup();
}

int query_autoload(){ return 1; }
