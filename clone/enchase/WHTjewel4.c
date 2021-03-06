#include <ansi.h>
inherit ITEM;
// by dream
int is_enchase_ob() { return 1; }
void create()
{
        set_name(WHT "帝之宝石" NOR, ({ "WHT jewel4","jewel4" }));
        set_weight(30);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", WHT "一块闪烁这奇异光芒的白色宝石，"
                    "让人感到一阵阵的心悸。\n" NOR);
                set("unit", "块");
                set("value", 140000);
                set("no_identify", 1);
                set("wear_msg", HIC "$N" HIC "轻轻地把$n"
                    HIC "戴在头上。\n" NOR);
                set("remove_msg", HIC "$N" HIC "轻轻地把$n"
                    HIC "从头上摘了下来。\n" NOR);
                    
                set("enchase/type", "all");   // 可镶嵌的道具类型"all"或"sword"或"blade"或"cloth"等
                set("enchase/cur_firm", 90);  // 抗磨损度
                set("enchase/wspe_data",      // 兵器上附加属性汇总
                   ([
                        ////////////////////     兵防共有属性


                        "int" : 5,           // 增加智慧
                        "dex" : 5,           // 增加根骨

                        ////////////////////     兵器特有属性

                        "cold_attack"   : 40, // 冷冻攻击
                        "suck_neili"    : 15, // 吸取内力
                        "suck_jingli"   : 15, // 吸取精力

                   ]));

                set("enchase/aspe_data",       // 防具上附加属性汇总
                   ([
                        ////////////////////     兵防共有属性

                        "int" : 5,           // 增加智慧
                        "dex" : 5,            // 增加根骨
                        ////////////////////     防具特有属性

                        "reduce_cold"   : 40, // 化解冷冻：40%
                        "defense": 40,       // 防御等级：+40
                        "max_jingli"    : 15, // 精力上限：+15%

                        "jing_recover_speed"   : 20, // 精气恢复速度: +20%
                   ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}

