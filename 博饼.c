#include "head.h"
///////////////////////////////////////////////////////////////////////////////
/*
  ��������:Input(PlayerList pl,char *a)
  ��дʱ�䣺6.27
  ��д�ˣ��ƺ�ҫ
  �������ܣ���
  �������ܣ���������ת������
  */
int Input(PlayerList pl,char *a)
{
	int n;
	n=atoi(a);
	if(n<=0||n>MaxPlayer) n=GetIdByName(pl,a);
	if(strcmp("go",a)==0) n=300;
	else if(strcmp("logout",a)==0)  n=400;
	else if(strcmp("query",a)==0)  n=500;
	else if(strcmp("help",a)==0)  n=600;
	else if(strcmp("history",a)==0)  n=700;
	else if(strcmp("Adminstrator",a)==0)  n=800;
	return n;
}
///////////////////////////////////////////////////////////////////////////////
/*
  ��������:Control(PlayerList pl,int n)
  ��дʱ�䣺6.27
  ��д�ˣ��ƺ�ҫ
  �������ܣ���
  �������ܣ����ƺ���
  */
void Control(PlayerList pl,int n)
{
	if(n<256&&n>0)
	{
		 GetTopById( pl, n);
	}

	else if(n==300)
	{
		Print( pl );
	}
	else if(n==400)
	{
		logout(pl);
	}
	else if(n==500)
	{
		rquery(pl);
	}
	else if(n==600)
	{
		Help();
	}
	else if(n==700)
	{
		printfhis(pl);
	}
	else if(n==800)
	{
		Adm(pl);
	}

}
///////////////////////////////////////////////////////////////////////////////
/*
  ��������:main()
  ��дʱ�䣺6.27
  ��д�ˣ��ƺ�ҫ
  �������ܣ���
  �������ܣ�������
  */

main()
{
	int a,b,n;
	char c[10];
	Player p;
	PlayerList pl;
	p = GetInitPlayer();
	pl = GetDefaultPlayerList();
	SetPlayerListFromFile(pl,FILENAME);
	do
	{
		menu(pl);
		gets(c);
		fflush(stdin);
		n=Input(pl,c);
		Control(pl,n);


	
	
	
	}while(1);
		
	

}