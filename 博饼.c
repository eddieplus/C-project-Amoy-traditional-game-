#include "head.h"
///////////////////////////////////////////////////////////////////////////////
/*
  函数名称:Input(PlayerList pl,char *a)
  编写时间：6.27
  编写人：黄汉耀
  参数介绍：无
  函数功能：命令输入转换函数
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
  函数名称:Control(PlayerList pl,int n)
  编写时间：6.27
  编写人：黄汉耀
  参数介绍：无
  函数功能：控制函数
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
  函数名称:main()
  编写时间：6.27
  编写人：黄汉耀
  参数介绍：无
  函数功能：主函数
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