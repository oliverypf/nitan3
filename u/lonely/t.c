int a(string arg)
{
object ob;
object me = this_player();
int n;
      if ( ! n = 0 )
    tell_object(me, sprintf("查看结果正确\n"));
if (! ob = find_player(arg) )
     tell_object(me, sprintf("没有找到" + arg + "\n"));
if (! (ob = find_player(arg)) )
     tell_object(me, sprintf("还是没有找到" + arg + "\n"));
return 1;
}
