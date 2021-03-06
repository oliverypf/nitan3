// haha
// f.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;
        string item;
        string target;

        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;

        if (! arg) return notify_fail("你要做什么？\n");

        if (sscanf(arg, "%s for %s", item, target) != 2)
                return notify_fail("你要给什么兵器设置10lvl呢？\n");
                
        if (! objectp(ob = present(item, me)))
                return notify_fail("这里没有这个物品。\n");
        
        ob->set("combat/MKS", 2100);
        ob->set("owner/" + target, 21000000);
        ob->set("magic/imbue_ok", 1);
        ob->set("magic/blood", 21000);
        ob->save();
        
        tell_object(me, "设置10lvl成功。\n");
        return 1;
}
