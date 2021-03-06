// Written By Lonely@Nitan3

#include <ansi.h>

#pragma optimize
#pragma save_binary

#define NAME    0
#define DESC    1
#define VALUE   2

mixed *jewel = ({
        ({ "宝石碎片", "一片宝石碎片。", 80000 }),
        ({ "宝石", "一块金光闪闪的精美宝石，华丽异常。", 100000 }),
        ({ "稀世宝石", "一块金光闪闪的精美宝石，给人以不同寻常的感觉。", 120000 }),
        ({ "帝之宝石", "一块闪烁这奇异光芒的宝石，让人感到一阵阵的心悸。", 140000 }),
        ({ "圣之宝石", "一块闪烁这奇异光芒的宝石，让人感到一阵阵的心悸。", 160000 }),
        ({ "魔之宝石", "一块闪烁这奇异光芒的宝石，让人感到一阵阵的心悸。", 180000 }),
        ({ "神之宝石", "一块闪烁这奇异光芒的宝石，让人感到一阵阵的心悸。", 200000 }),
});

mapping special_data = ([
        "int"   : "后天悟性增加",
        "str"   : "后天臂力增加",
        "con"   : "后天根骨增加",
        "dex"   : "后天身法增加",
        "max_neili"     : "最大内力上限增加",
        "max_jingli"    : "最大精力上限增加",
        "max_qi"        : "最大气血上限增加",
        "max_jing"      : "最大精气上限增加",
        "max_potential" : "最大潜能上限增加",
        "max_experience": "最大体会上限增加",
        "attack"        : "战斗攻击力有效等级增加",
        "defense"       : "战斗防御力有效等级增加",
        "parry"         : "战斗招架力有效等级增加",
        "dodge"         : "战斗躲闪力有效等级增加",
        "armor"         : "战斗保护力增加",
        "damage"        : "战斗兵器伤害力增加",
        "unarmed_damage": "战斗拳脚伤害力增加",
        "ap_power"      : "绝招战斗攻击力增加百分比",
        "dp_power"      : "绝招战斗防御力增加百分比",
        "da_power"      : "绝招战斗伤害力增加百分比",
        "add_poison"            : "附带毒气攻击效果增加百分比",
        "reduce_poison"         : "化解毒气攻击效果百分比",
        "avoid_poison"          : "回避毒气攻击机率百分比",
        "add_cold"              : "附带冷冻攻击效果增加百分比",
        "add_fire"              : "附带火焰攻击效果增加百分比",
        "add_lighting"          : "附带闪电攻击效果增加百分比",
        "add_magic"             : "附带魔法攻击效果增加百分比",
        "reduce_cold"           : "化解冷冻攻击效果百分比",
        "reduce_fire"           : "化解火焰攻击效果百分比",
        "reduce_lighting"       : "化解闪电攻击效果百分比",
        "reduce_magic"          : "化解魔法攻击效果百分比",
        "avoid_cold"            : "回避冷冻攻击机率百分比",
        "avoid_fire"            : "回避火焰攻击机率百分比",
        "avoid_lighting"        : "回避闪电攻击机率百分比",
        "avoid_magic"           : "回避魔法攻击机率百分比",
        "effjing_recover"       : "提高每次最大精气恢复值",
        "effqi_recover"         : "提高每次最大气血恢复值",
        "research_times": "提升研究的次数",
        "learn_times"   : "提升学习的次数",
        "practice_times": "提升练习的次数",
        "derive_times"  : "提升汲取的消耗",
        "study_times"   : "提升读书的次数",
        "study_effect"  : "提升读书的效果百分比",
        "learn_effect"  : "提升学习的效果百分比",
        "avoid_parry"   : "回避特殊招架机率百分比",                     // 符文防具
        "avoid_dodge"   : "回避特殊躲闪机率百分比",                     // 符文防具
        "avoid_attack"  : "回避特殊攻击机率百分比",                     // 符文防具
        "reduce_age"    : "降低自己的年纪",
        "research_effect"       : "提升研究的效果百分比",
        "practice_effect"       : "提升练习的效果百分比",
        "derive_effect"         : "提升汲取的效果百分比",
        /*  ultimate */
        "avoid_noperform"       : HIR "回避绝招使用限制机率百分比",         // 终极兵器
        "target_noperform"      : HIB "限制对手使用绝招机率百分比",         // 终极防具
        "add_busy"      : HIR "增加对手忙乱秒数",                           // 终极兵器
        "reduce_busy"   : HIB "化解忙乱秒数",                               // 终极防具
        "avoid_busy"    : HIB "回避忙乱机率百分比",                         // 终极防具
        "xuruo_status"  : HIR "让对手处于虚弱状态机率百分比",               // 终极兵器
        "avoid_xuruo"   : HIB "回避虚弱机率百分比",                         // 终极防具
        "add_skilllevel": HIR "提升所有技能等级",                           // 终极兵器
        "add_damage"    : HIR "追加最终伤害百分比",                         // 终极兵器
        "reduce_damage" : HIB "化解最终伤害百分比",                         // 终极防具
]);

string special_desc(string arg)
{
        if (! undefinedp(special_data[arg]))
                return special_data[arg];
        else
                return to_chinese(arg);
}

mapping spe_level = ([
        "int,str,con,dex"       : ({ 2, 3, 4, 5, 6, 7, 8 }),       	                                          // 数值
        "max_neili,max_jingli"  : ({ 1000, 1500, 2000, 1500, 3000, 3500, 4000 }),                                 // 数值
        "attack,defense,parry,dodge"    : ({ 10, 15, 20, 25, 30, 35, 40 }),   	                                  // 数值
        "effjing_recover,effqi_recover" : ({ 20, 30, 40, 50, 60, 70, 80 }),                                       // 数值
        "reduce_age"            : ({ 1, 2, 3, 4, 5, 6, 7 }),                                                      // 数值
        "max_potential,max_experience"  : ({ 100000, 150000, 200000, 150000, 300000, 350000, 400000 }),           // 数值
        "max_qi,max_jing,damage,unarmed_damage,armor"   : ({ 200, 300, 400, 500, 600, 700, 800 }),                // 数值
        "research_times,learn_times,practice_times,derive_times,study_times"     : ({ 1, 2, 3, 4, 5, 6, 7 }),     // 数值
        "add_cold,add_fire,add_lighting,add_poison,add_magic"   : ({ 5, 8, 11, 14, 17, 20, 23 }),   	          // 百分比
        "reduce_code,reduce_fire,reduce_lighting,reduce_poison,reduce_magic"     : ({ 5, 8, 11, 14, 17, 20, 23 }),// 百分比
        "avoid_cold,avoid_fire,avoid_lighting,avoid_poison,avoid_magic"          : ({ 1, 2, 3, 4, 5, 6, 7 }),     // 百分比
        "research_effect,learn_effect,practice_effect,derive_effect,study_effect": ({ 1, 2, 3, 4, 5, 6, 7 }),     // 百分比
        "ap_power,dp_power,da_power" : ({ 1, 2, 3, 4, 5, 6, 7 }),                                                 // 百份比
        // 终极属性
        "add_skilllevel": ({ 300, 400, 500, 600 }),                             // 数值
        "add_busy"      : ({ 6, 8, 10, 12, 14, 16 }),                           // 数值
        "xuruo_status,add_damage,avoid_noperform"       : ({ 30, 36, 42, 48 }), // 百分比
        "avoid_busy,target_noperform,avoid_xuruo"   : ({ 8, 10, 12, 14, 16 }),  // 百分比
        "reduce_busy"   : ({ 4, 5, 6 }),                                        // 数值
        "reduce_damage" : ({ 10, 12, 14, 16 }),                                 // 百分比
]);

string *wspe_data = ({
        "int", "str", "con", "dex", "attack", "damage", "add_cold",
        "add_fire", "add_lighting", "add_poison", "add_magic",
        "max_neili", "max_jingli", "max_qi", "max_jing", "max_potential",
        "max_experience", "research_effect", "learn_effect",
        "practice_effect", "derive_effect", "study_effect", "research_times",
        "learn_times", "practice_times","derive_times", "study_times",
        "reduce_age", "ap_power", "da_power",
});

string *aspe_data = ({
        "int", "str", "con", "dex", "defense", "parry", "dodge",
        "armor", "reduce_poison", "reduce_cold", "reduce_fire",
        "reduce_lighting", "reduce_magic", "unarmed_damage",
        "avoid_poison", "avoid_cold", "avoid_fire", "avoid_lighting",
        "avoid_magic", "max_neili", "max_jingli", "max_qi", "max_jing",
        "max_potential", "max_experience", "effjing_recover", "effqi_recover",
        "research_effect", "learn_effect", "practice_effect", "derive_effect",
        "study_effect", "research_times", "learn_times", "practice_times",
        "derive_times", "study_times", "reduce_age", "dp_power",
});


string *ultimate_data = ({
        "add_busy", "reduce_busy", "avoid_busy", "xuruo_status",
        "target_noperform", "add_damage", "reduce_damage",
});

int query_spe_level(string special, int lvl)
{
        int i, flag, level;
        int *c;
        string s;
        string *spe;
        string *spec;

        level = 0;
        flag = 0;

        spe = keys(spe_level);
        for(i=0;i<sizeof(spe);i++)
        {
        	reset_eval_cost();

                spec = explode(spe[i], ",");
                foreach(s in spec)
                        if (s == special) {
                                flag = 1;
                                c = spe_level[spe[i]];
				level = c[lvl-1];
                                break;
                        }
        	if ( flag ) break;
        }

        return level;
}

mixed *apply_special(string type, int level)
{
        string *prop;
        string *p;
        string p1, p2, p3, p4, p5, p6, p7;

        if (type == "weapon")
                prop = wspe_data;
        else
                prop = aspe_data;

        p1 = prop[random(sizeof(prop))];
        prop -= ({ p1 });
        p2 = prop[random(sizeof(prop))];
        prop -= ({ p2 });
        p3 = prop[random(sizeof(prop))];
        prop -= ({ p3 });
        p4 = prop[random(sizeof(prop))];
        prop -= ({ p4 });
        p5 = prop[random(sizeof(prop))];
        prop -= ({ p5 });
        p6 = prop[random(sizeof(prop))];
        prop -= ({ p6 });
        p7 = prop[random(sizeof(prop))];

        if (level == 1)
                p = ({ p1 });
        else if (level == 2)
                p = ({ p1, p2 });
        else if (level == 3)
                p = ({ p1, p2, p3 });
        else if (level == 4)
                p = ({ p1, p2, p3, p4 });
        else if (level == 5)
                p = ({ p1, p2, p3, p4, p5 });
        else if (level == 6)
                p = ({ p1, p2, p3, p4, p5, p6 });
        else
                p = ({ p1, p2, p3, p4, p5, p6, p7 });

        return p;
}

mixed identify_ob(object me, object ob)
{
        int     i, level, line;
        string  fn, filename;
        string  buf, rf, spe;
        string  color;
        string  header;
        string  *filetext;
        mapping info = ([]);

        header = "//  Written by ZHANG TIANSHI(Lonely 2007/10/15)\t" + ctime(time()) + "\n";
        filename = base_name(ob);
        filename += ".c";

        if (sscanf(filename, "/clone/gift/%s.c", fn))
        {
                switch(fn) {
                case "cdiamond" :
                case "diamond"  :
                case "fdiamond" :
                case "mdiamond" :
                case "cagate"   :
                case "agate"    :
                case "fagate"   :
                case "magate"   :
                case "cjade"    :
                case "jade"     :
                case "fjade"    :
                case "mjade"    :
                case "ccrystal" :
                case "crystal"  :
                case "fcrystal" :
                case "mcrystal" :
                        if (fn[0..0] == "m")
                                level = 5;
 			else
                                level = 1 + random(3);
                        buf  = sprintf("\t\tset(\"enchase/SN\", %d);\n", (random(9) + 1));
               		buf += sprintf("\t\tset(\"enchase/cur_firm\", %d);\n", 80 + random(21));
                   	buf += sprintf("\t\tset(\"enchase/wspe_data\", ([\n");

        		for (i = 0; i < level; i++)
        		{
        			spe = apply_special("weapon", level)[i];
          			buf += sprintf("\t\t\t\"%s\" : %d,\n", spe, query_spe_level(spe, level + 2));
          		}
                  	buf += sprintf("\t\t]));\n");
                   	buf += sprintf("\t\tset(\"enchase/aspe_data\", ([\n");
                    	for (i = 0; i < level; i++)
                    	{
                    		spe = apply_special("armor", level)[i];
                             	buf += sprintf("\t\t\t\"%s\" : %d,\n", spe, query_spe_level(spe, level + 2));
                      	}
                        buf += sprintf("\t\t]));\n");

                        rf = read_file("/clone/gift/" + fn + ".c");
                        // rf = replace_string(rf, "set\(\"no_identify\", 1\);", "");
                        filetext = explode(rf, "\n");
                        for (i = 0;i < sizeof(filetext);i ++)
                        {
                                if (strsrch(filetext[i], "set\(\"no_identify\", 1\);") != -1)
                                {
                                        line = i;
                                        break;
                                }
                        }
                        while(1)
                        {
                                filename = "/data/enchase/" + fn + "-" + (time() + random(99999999));
                                if (file_size(filename + ".c") == -1)
                                        break;
                        }
                        filename += ".c";
                        assure_file(filename);
                        write_file(filename, header, 0);
                        for (i = 0; i < line; i ++)
                                write_file(filename, filetext[i] + "\n", 0);
                        write_file(filename, buf, 0);
                        for (i = line + 1; i < sizeof(filetext); i ++)
                                write_file(filename, filetext[i] + "\n", 0);
                        return filename;
                default         :
                        return "";
                }
        }


        if (! sscanf(filename, "/clone/enchase/%sjewel.c", color) &&
            sscanf(filename, "/clone/enchase/%sjewel%d.c", color, level) != 2)
                return "";

        if (! level)
        {
                if (random(100) == 0) level = 4;
                else if (random(20) == 0) level = 3;
                else if (random(5) == 0) level = 2;
                else level = 1;
        }
        color=upper_case(color);

        if (color == "BLK")
        info["color"] = "NOR";
        else
        info["color"] = color;
        info["id"] = color + " jewel" + level;
        info["name"] = jewel[level-1][NAME];
        info["desc"] = jewel[level-1][DESC];
        info["value"] = jewel[level-1][VALUE];

        buf = header;
        buf += "#include <ansi.h>\n";
        buf += "inherit ITEM;\n\n";
        buf += "int is_enchase_ob(){ return 1; }\n\n";
        buf += "void create()\n{\n";
        buf += sprintf("\tset_name(%s \"%s\" NOR, ({ \"%s\" }));\n",
                       info["color"], info["name"], info["id"]);
        buf += sprintf("\tset_weight(50);\n");
        buf += sprintf("\tset(\"unit\", \"块\");\n");
        buf += sprintf("\tset(\"long\", %s \"%s\\n\" NOR );\n", info["color"], info["desc"]);
        buf += sprintf("\tset(\"value\", %d);\n", info["value"]);

        if (level == 7)
        {
                buf += sprintf("\tset(\"can_be_enchased\", 1);\n");
                buf += sprintf("\tset(\"magic/type\", \"magic\");\n");
                buf += sprintf("\tset(\"magic/power\", %d);\n", 15 + random(16));
        }
        buf += sprintf("\tset(\"enchase/SN\", %d);\n", (random(9) + 1));
        buf += sprintf("\tset(\"enchase/level\", %d);\n", level);
      	buf += sprintf("\tset(\"enchase/cur_firm\", %d);\n", 80 + random(21));
    	buf += sprintf("\tset(\"enchase/wspe_data\", ([\n");

        for (i = 0; i < level; i++)
        {
        	spe = apply_special("weapon", level)[i];
                buf += sprintf("\t\t\"%s\" : %d,\n", spe, query_spe_level(spe, level));
  	}

        buf += sprintf("\t]));\n");
	buf += sprintf("\tset(\"enchase/aspe_data\", ([\n");

        for (i = 0; i < level; i++)
        {
        	spe = apply_special("armor", level)[i];
                buf += sprintf("\t\t\"%s\" : %d,\n", spe, query_spe_level(spe, level));
    	}

        buf += sprintf("\t]));\n");
        buf += sprintf("\tset(\"wear_msg\", HIC \"$N\" HIC \"轻轻地把$n\"HIC \"戴在头上。\\n\" NOR);\n");
        buf += sprintf("\tset(\"remove_msg\", HIC \"$N\" HIC \"轻轻地把$n\"HIC \"从头上摘了下来。\\n\" NOR);\n");
        buf += sprintf("\n\tsetup();\n}\n\n");
        buf += sprintf("int query_autoload(){ return 1; }\n");

        while(1)
        {
                filename = "/data/enchase/" + color + "jewel" + level + "-" + (time() + random(99999999));
                if (file_size(filename + ".c") == -1)
                        break;
        }
        filename += ".c";
        assure_file(filename);
        if (write_file(filename, buf)) // 写入文件
                VERSION_D->append_sn(filename); // 给物品增加识别码
        else
        {
                tell_object(me, "写入档案(" + filename + ")时出错，请通知巫师处理。\n");
                return "";
        }
        return filename;
}

// 无上神品->上古神品->中古神品->远古神品->太古神品
// 太始、太初、太玄 太虚、洪荒
// 冥古宙、太古宙、元古宙和显生宙
// 其中元古宙又划分为古元古代、中元古代和新元古代；
// 显生宙划分古生代、中生代和新生代。
varargs int identify_ultimate_ob(object item, int close)
{
        mapping data;
        string *apply;
        int i, s;

        s = (int)item->query("enchase/SN");
        if (s == 37 && ! item->query("ultimate/37"))
        {
                item->add("enchase/spe_data/research_effect", 10);
                item->add("enchase/spe_data/practice_effect", 10);
                item->add("enchase/spe_data/derive_effect", 10);
                item->add("enchase/flute", 1);
                item->add("enchase/SN", -(random(9) + 1));
                item->set("ultimate/37", 1);
                item->save();
                return 1;
        } else
        if (s == 39 && ! item->query("ultimate/39"))
        {
                item->add("enchase/spe_data/research_effect", 15);
                item->add("enchase/spe_data/practice_effect", 15);
                item->add("enchase/spe_data/derive_effect", 15);
                item->add("enchase/flute", 1);
                item->set("ultimate/39", 1);
                item->save();
                return 1;
        } else
        if (s == 69 && ! item->query("ultimate/69") &&
            item->query("armor_type") && item->query("armor_type") != "hands")
        {
                data = item->query("enchase/spe_data");
                if (! mapp(data)) data = ([ ]);
                apply = keys(data);
                for(i=0; i<sizeof(apply); i++)
                        data[apply[i]] = data[apply[i]] * 3 / 2;

                data["reduce_busy"]     = query_spe_level("reduce_busy", 1 + random(2));
                data["avoid_busy"]      = query_spe_level("avoid_busy", 1 + random(4));
                data["avoid_xuruo"]     = query_spe_level("avoid_xuruo", 1 + random(4));
                data["target_noperform"]= query_spe_level("target_noperform", 1 + random(4));
                data["reduce_damage"]   = query_spe_level("reduce_damage", 1 + random(3));

                item->set("enchase/spe_data", data);
                item->set("ultimate/69", 1);
                item->save();

                if (! close)
                CHANNEL_D->do_channel(find_object(ITEM_D), "rumor",
                              "听说上古神品" + item->name() + HIM +
                              "来到了人间。");


                log_file("static/ultimate", sprintf("ENCHASE_D: %s Have 69. %s\n",
                          base_name(item), ctime(time())));
                return 1;
        } else
        if (s == 87 && ! item->query("ultimate/87"))
        {
                data = item->query("enchase/spe_data");
                if (! mapp(data)) data = ([ ]);
                apply = keys(data);
                if (item->query("skill_type") ||
                    (item->query("armor_type") && item->query("armor_type") == "hands"))
                {
                        for(i=0; i<sizeof(apply); i++)
                                data[apply[i]] = data[apply[i]] * 3 / 2;

                        data["add_busy"]        = query_spe_level("add_busy", 1 + random(5));
                        data["xuruo_status"]    = query_spe_level("xuruo_status", 1 + random(3));
                        data["avoid_noperform"] = query_spe_level("avoid_noperform", 1 + random(3));
                        data["add_damage"] = query_spe_level("add_damage", 1 + random(3));
                        data["add_skilllevel"]  = query_spe_level("add_skilllevel", 1 + random(3));

                        item->set("enchase/spe_data", data);
                        item->set("ultimate/87", 1);
                        item->save();

                        if (! close)
                        CHANNEL_D->do_channel(find_object(ITEM_D), "rumor",
                                "听说上古神品" + item->name() + HIM +
                                "来到了人间。");

                } else
                {
                        for(i=0; i<sizeof(apply); i++)
                                data[apply[i]] *= 2;

                        data["reduce_busy"]     = 6;
                        data["avoid_busy"]      = 16;
                        data["avoid_xuruo"]     = 16;
                        data["target_noperform"]= 16;
                        data["reduce_damage"]   = 16;
                        item->set("enchase/spe_data", data);
                        item->set("ultimate/87", 1);
                        item->save();
                        if (! close)
                        CHANNEL_D->do_channel(find_object(ITEM_D), "rumor",
                                "听说远古神品" + item->name() + HIM +
                                "来到了人间。");
                }

                log_file("static/ultimate", sprintf("ENCHASE_D: %s Have 87. %s\n",
                          base_name(item), ctime(time())));
                return 1;
        } else
        if (s == 105 && ! item->query("ultimate/105"))
        {
                data = item->query("enchase/spe_data");
                if (! mapp(data)) data = ([ ]);
                apply = keys(data);
                for(i=0; i<sizeof(apply); i++)
                        data[apply[i]] *= 2;

                data["add_busy"]        = 16;
                data["xuruo_status"]    = 48;
                data["avoid_noperform"] = 48;
                data["add_damage"]      = 48;
                data["add_skilllevel"]  = 600;

                item->set("enchase/spe_data", data);
                item->set("ultimate/105", 1);
                item->save();
                if (! close)
                CHANNEL_D->do_channel(find_object(ITEM_D), "rumor",
                              "听说远古神品" + item->name() + HIM +
                              "来到了人间。");

                log_file("static/ultimate", sprintf("ENCHASE_D: %s Have 105. %s\n",
                          base_name(item), ctime(time())));
                return 1;
        } else
        if (s == 121 && ! item->query("ultimate/121"))
        {
                data = item->query("enchase/spe_data");
                if (! mapp(data)) data = ([ ]);
                apply = keys(data);
                for(i=0; i<sizeof(apply); i++)
                        data[apply[i]] *= 3;

                data["add_busy"]        = 36;
                data["xuruo_status"]    = 96;
                data["avoid_noperform"] = 96;
                data["add_damage"]      = 96;
                data["add_skilllevel"]  = 800;

                data["reduce_busy"]     = 32;
                data["avoid_busy"]      = 96;
                data["avoid_xuruo"]     = 96;
                data["target_noperform"]= 96;
                data["reduce_damage"]   = 96;

                data["ap_power"]        = 96;
                data["dp_power"]        = 96;
                data["da_power"]        = 96;
                data["avoid_parry"]     = 96;
                data["avoid_dodge"]     = 96;
                data["avoid_attack"]    = 96;
                
                item->set("enchase/spe_data", data);
                item->set("ultimate/121", 1);
                item->save();
                if (! close)
                CHANNEL_D->do_channel(find_object(ITEM_D), "rumor",
                              "听说太古神品" + item->name() + HIM +
                              "来到了人间。");

                log_file("static/ultimate", sprintf("ENCHASE_D: %s Have 121. %s\n",
                          base_name(item), ctime(time())));
                return 1;
        } else
                return 0;
}
