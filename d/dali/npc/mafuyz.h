int do_rideyz()
{
        string hname;
        object ob = this_player();
	int i;
	string *yz_dl = ({
                HIC"�͵�"NOR,
                HIC"�����"NOR,
                HIC"����㳡"NOR,
                HIC"�ϴ��"NOR,
                HIC"�ϴ��"NOR,
                HIC"����"NOR,
                HIC"��ʯ���"NOR,
                HIC"��ʯ���"NOR,
                HIC"��ʯ���"NOR,
                HIC"��ʯ���"NOR,
                HIC"��ʯ���"NOR,
                HIC"С·"NOR,
                HIC"С·"NOR,
                HIC"С·"NOR,
                HIC"������"NOR,
                HIC"���"NOR,
                HIC"С·"NOR,
                HIC"С·"NOR,
                HIC"��ʯ��"NOR,
                HIC"��ʯ��"NOR,
                HIC"��ʯ��"NOR,
                HIC"�ٵ�"NOR,
                HIC"�ٵ�"NOR,
                HIC"�ٵ�"NOR,
                HIC"��گ�»���"NOR,
                HIC"̫�ͳ�"NOR,
                HIC"�����Ǳ�"NOR,
                HIC"����"NOR,
                HIC"�Ʒ�"NOR,
                HIC"̫�ͽֿ�"NOR,
                HIC"���Ĺ㳡"NOR,
                HIC"ʮ��·��"NOR,
                HIC"��ͽ�"NOR,
                HIC"��Ӫ"NOR,
	});
        if (ob->query_temp("marks/horserent")!=1 && ob->query("age")>14)
                return notify_fail("С���Ӳſ��������������Ҫ��Ǯ��\n");
        switch (random(4))
        {
                case 1:
                        hname=MAG"������"NOR;
                        break;
                case 2:
                        hname=RED"�����"NOR;
                        break;
                case 3:
                        hname=HIW"������"NOR;
                        break;
                default:
                        hname=HIY"������"NOR;
                        break;
        }
        message_vision(
"�������ָ�$Nǣ��һƥ"+hname+"��$N����Ծ��"+hname+"������������������·������һ��
���: �����ޡ�\n"NOR , ob );
        message_vision("\nֻ��$N����һ�У�"+hname+"������Ӫ��ȥ��\n",ob);
	for ( i = sizeof(yz_dl) - 1;i >= 0;i--)
		tell_object(ob,yz_dl[i] + "\n");
        ob->move("/d/city/majiu");
        tell_room(environment(ob),ob->query("name")+"����"+hname+"һ·˳���������ݳǡ�\n");

        message_vision("\n$N����һת��������أ���̬ʮ������������Ҳ��$Nһ��塣\n",ob);
        ob->delete_temp("marks/horserent");
        return 1;
}