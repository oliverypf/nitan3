// lookwall.h
// By haiyan

#include <ansi.h>

int do_look(string arg);
int do_look(string arg)
{
     object me = this_player();
     int cost;

     if( !arg || arg != "shibi" )   return 0;

     write("\n））））））））））））））））））））））））））））））））\n");
     write("）））　　　　　　　　　　　　　　　　　　　　　　　　　　）））\n");
     write("）））　　　　　　　　　　　論人佩　　　　　　　　　　　　）））\n");
     write("）））　　　　　　　　　　　　　　　　　　　　　　　　　　）））\n");
     write("）））　孕人舅鮭哥��伶抗蜂僣苧。咢旭孚易瀧��讓躋泌送佛。　）））\n");
     write("）））　　　　　　　　　　　　　　　　　　　　　　　　　　）））\n");
     write("）））　噴化姫匯繁��認戦音藻佩��並阻圏丗肇��侮茄附嚥兆。　）））\n");
     write("）））　　　　　　　　　　　　　　　　　　　　　　　　　　）））\n");
     write("）））　椀狛佚相咬��用州魯念罪。繍嵋燿幀坤��隔��醗作攪。　）））\n");
     write("）））　　　　　　　　　　　　　　　　　　　　　　　　　　）））\n");
     write("）））　眉鵜預隼典��励埓宜葎煤。凛雑串犯朔��吭賑殆爪伏。　）））\n");
     write("）））　　　　　　　　　　　　　　　　　　　　　　　　　　）））\n");
     write("）））　照孕屍署憾��昏畿枠寳妾��認拍屈彝平���@砕寄塑廓。　）））\n");
     write("）））　　　　　　　　　　　　　　　　　　　　　　　　　　）））\n");
     write("）））　忿棒論糠�磽�音珂弊貧哂��豊嬬慕佼和��易遍湊傲将。　）））\n");
     write("）））　　　　　　　　　　　　　　　　　　　　　　　　　　）））\n");
     write("））））））））））））））））））））））））））））））））\n\n");
     write("    和圭震彭匯嫌夕��夕嶄頁匯倖慕伏��麿恣返隔蛭��嘔返敬嫺��舞\n");
     write("蓑封頁單囘粲備´´都嗤匯佩廣盾堝�歳覺嗟�値胡啣侃彭返。総嗤涙\n");
     write("方弌忖��畜畜醍醍。\n\n");

     if(me->query("taixuan"))    return 1;

     if(! me->query_temp("xiakedao/think"))    return 1;

     if ((int)me->query_skill("literate", 1) > 100)
     {
           write("低辧遊士辻仇響彭墳謁貧議鮒鞘�此意埒裸郎�哥��伶抗蜂僣苧´´￣。\n\n");
           write(HIY"低響阻匯氏��在在祇�此意睚彿�亟誼匆湊噸宥阻��珊短厘徭失亟誼挫。￣\n"NOR);
           return 1;
     }

     if ( ! ultrap(me) )
     {
           write("低潮潮廷撲彭墳謁貧議鮒鞘�此威�旭孚易瀧��讓躋泌送佛´´￣。\n\n");
           write(HIY"低潮撲阻匯氏��状誼徭失斤冷僥議冩梢湊狛券燃��匯扮岻寂佃參糟氏凪嶄安虫。\n"NOR);
           return 1;
     }

     cost = me->query("int") - 20;
     if (cost < 2)  cost = 2;
     if (cost > 8)  cost = 8;

     if (random(cost) == 0)
     {
           me->set("taixuan", "force");
           write("低潮潮廷撲彭墳謁貧議鮒鞘�此鞍�鵜預冱典´´"
                 "吭賑殆爪伏´´傀砕寄塑廓´´￣。\n\n");
           write(HIY"低嗽繍墳謁貧議夕宛徙聾心阻心��貌窄状誼夕宛嶄淫根"
                 "彭匯耗互侮議冷孔��抜嗽匯扮傍音貧栖。\n峪状匯紘寔賑壓"
                 "畠附将琢産産送強。\n"NOR);
     }  else
     {
           switch(random(3))
           {
                case 0:
                     me->set("taixuan", "sword");
                     write("低潮潮廷撲彭墳謁貧議鮒鞘�此以�化"
                           "姫匯繁´´用州魯念罪´´照孕屍署憾´´￣。\n\n");
                     write(HIY"低嗽繍墳謁貧議夕宛徙聾心阻心��貌窄状誼夕宛嶄淫根"
                           "彭匯耗互侮議冷孔��抜嗽匯扮傍音貧栖。\n"
                           "峪状返峺裏戒��貌窄識圀儖匯委州栖屍玲匯桑。\n"NOR);
                     break;
                case 1:
                     me->set("taixuan", "dodge");
                     write("低潮潮廷撲彭墳謁貧議鮒鞘�此闇Ю�"
                           "音藻佩´´並阻圏丗肇´´侮茄附嚥兆´´￣。\n\n");
                     write(HIY"低嗽繍墳謁貧議夕宛徙聾心阻心��貌窄状誼夕宛嶄淫根"
                           "彭匯耗互侮議冷孔��抜嗽匯扮傍音貧栖。\n"
                           "峪状畠附貌窄延煤俯謹。\n"NOR);
                     break;
                case 2:
                     me->set("taixuan", "unarmed");
                     write("低潮潮廷撲彭墳謁貧議鮒鞘�此囲亶�"
                           "佚相咬´´励埓宜葎煤´´忿棒論糠�磧�´￣。\n\n");
                     write(HIY"低嗽繍墳謁貧議夕宛徙聾心阻心��貌窄状誼夕宛嶄淫根"
                           "彭匯耗互侮議冷孔��抜嗽匯扮傍音貧栖。\n"
                           "峪状畠附購准匯專＾琥琥鞍鞍￣羽�譟�\n"NOR);
                     break;
           }
    }
    return 1;
}

