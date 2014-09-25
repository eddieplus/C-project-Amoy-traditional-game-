#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#define DEBUG 1
#ifndef nplayer
#define nplayer 256
#endif
#ifndef FILENAME
#define FILENAME "Name.dat"
#endif
#define MaxPlayer  256
#ifndef DEFAULTNAME
#define DEFAULTNAME "Nobody"
#endif

int q=3;

//玩家结构体 
typedef struct player
{
	int id;
	char name[20];
	int score;
} *Player;
typedef struct playerlist
{
    Player *list;
	int n;//线形表list个数
	Player *sortedlist;
	Player *currentsortedlist;
	int issort;//1表示线形表已排序，0表示没有
	int currentn;//当前玩家数，
	int top;//当前玩家下标
} *PlayerList;

Player GetInitPlayer();
void SetPlayer(int id,char *name,int score,Player p); 
void ShowPlayer(Player p);
PlayerList GetDefaultPlayerList();
int SetPlayerListFromFile(PlayerList pl,char *filename);
void Sort(PlayerList pl);
int GetIdByName(PlayerList pl,char *name);
int GetHisNById(PlayerList pl,int id);
int GetCurNById(PlayerList pl,int id);
void printfcur(PlayerList pl);
void rquery(PlayerList pl);
void printfhis(PlayerList pl);
int GetTopById(PlayerList pl,int n);

/////////////////////////////////////////////////////////
/*
  函数名称： gotoxy(int   x,   int   y) 
  编写时间：6.24
  编写人：无
  参数介绍：x，y分别把整个试图定为平面直角坐标系第四象限，Y取绝对值
  函数功能：坐标定位函数
  */

static void   gotoxy(int   x,   int   y)   {   
  COORD   c;   
  c.X   =   x   -   1;   
  c.Y   =   y   -   1;   
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);   
}

/////////////////////////////////////////////////////////////
/*
  函数名称：menu
  编写时间：6.24
  编写人：吴佳武
  参数介绍：pl玩家列表
  函数功能：界面，游戏主界面
  */
void menu(PlayerList pl)
{
	int x;
	system("cls");
	gotoxy(25,3);
	printf("2013-2014第三学期C语言实训项目评审!");
    gotoxy(5,5);
	printf("当前玩家ID:%d",pl->currentsortedlist[pl->top]->id);
	gotoxy(23,5);
	printf("姓名:%s",pl->currentsortedlist[pl->top]->name);
	gotoxy(34,5);
	printf("最高分:%d",pl->currentsortedlist[0]->score);
	gotoxy(44,5);
	printf("当前排名:%d",pl->top+1);
	gotoxy(59,5);
	printf("总排名:%d",x=GetHisNById(pl,pl->currentsortedlist[pl->top]->id));
	gotoxy(9,7);
	printf("博饼项目当前排名表:");
	gotoxy(9,8);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(9,9);
	printf("■");
	gotoxy(9,10);
	printf("■");
	gotoxy(9,11);
	printf("■");
	gotoxy(9,12);
	printf("■");
	gotoxy(9,13);
	printf("■");
	gotoxy(9,14);
	printf("■");
	gotoxy(9,15);
	printf("■");
	gotoxy(9,16);
	printf("■");
	gotoxy(9,17);
	printf("■");
	gotoxy(71,9);
	printf("■");
	gotoxy(71,10);
	printf("■");
	gotoxy(71,11);
	printf("■");
	gotoxy(71,12);
	printf("■");
	gotoxy(71,13);
	printf("■");
	gotoxy(71,14);
	printf("■");
	gotoxy(71,15);
	printf("■");
	gotoxy(71,16);
	printf("■");
	gotoxy(71,17);
	printf("■");
	gotoxy(9,18);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(12,9);
	printf("名次");
	gotoxy(13,10);
	printf("1");
	gotoxy(13,11);
	printf("2");
	gotoxy(13,12);
	printf("3");
	gotoxy(13,13);
	printf("4");
	gotoxy(13,14);
	printf("5");
	gotoxy(13,15);
	printf("6");
	gotoxy(13,16);
	printf("7");
	gotoxy(22,9);
	printf("玩家ID");
	gotoxy(37,9);
	printf("玩家姓名");
	gotoxy(53,9);
	printf("分数");
	gotoxy(9,19);
	printf("■");
	gotoxy(11,19);
	printf("命令解释");
	gotoxy(71,19);
	printf("■");
	gotoxy(9,20);
	printf("■");
	gotoxy(11,20);
	printf("go--进入游戏");
	gotoxy(71,20);
	printf("■");
	gotoxy(30,20);
	printf("logout---注销");
	gotoxy(52,20);
	printf("query---玩家列表");
	gotoxy(9,21);
	printf("■");
	gotoxy(71,21);
	printf("■");
	gotoxy(11,21);
	printf("help---帮助");
	gotoxy(30,21);
	printf("history---历史排行榜");
	gotoxy(9,22);
	printf("■");
	gotoxy(71,22);
	printf("■");
	gotoxy(11,22);
	printf("Adminstrator---管理员");
	gotoxy(9,23);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	printfcur(pl);
	gotoxy(1,25);
	printf("请输入（您的编号或姓名也可输入上面的命令）:");

	

}
/////////////////////////////////////////////////////////////
/*
  函数名称：GetInitPlayer()
  编写时间：6.24
  编写人：吴佳武
  参数介绍：无
  函数功能：初始化单个玩家
 */
Player GetInitPlayer()
{
	Player p = malloc(sizeof *p);
	p->id = 1;
    strcpy(p->name,"One");
	p->score = 17;
	return p;
}
//////////////////////////////////////////////////////////
/*
  函数名称：GetDefaultPlayerList()
  编写时间：6.24
  编写人：黄汉耀
  参数介绍：无
  函数功能：初始化玩家列表
  */
PlayerList GetDefaultPlayerList()
{
	int i;
	PlayerList pl=malloc(sizeof *pl);
	pl->list=malloc(MaxPlayer*sizeof *pl->list);
	pl->n=MaxPlayer;
	pl->sortedlist=malloc(MaxPlayer*sizeof *pl->sortedlist);
	for(i=0;i<MaxPlayer;i++)
	{
		Player p=GetInitPlayer();
		SetPlayer(i,DEFAULTNAME,0,p);
		pl->list[i]=p;
		pl->sortedlist[i]=p;
	}
	pl->currentsortedlist=malloc(MaxPlayer*sizeof *pl->currentsortedlist);
	pl->currentsortedlist[0]=pl->list[0];
	pl->currentn=1;
	pl->top=0;
	pl->issort=0;
	return pl;
}

///////////////////////////////////////////////////////////////////////
/*
  函数名称：ShowPlayer()
  编写时间：6.24
  编写人：黄汉耀
  参数介绍：p
  函数功能：打印
  */

void ShowPlayer(Player p)
{
	printf("%d\n",p->id);
	
    printf("%s\n",p->name);
	
	printf("%d\n",p->score);


}
//////////////////////////////////////////////////////////
/*
  函数名称：SetPlayer
  编写时间：6.24
  编写人：黄汉耀
  参数介绍：id  *name score p
  函数功能：设置id name score p 方便测试
  */;
void SetPlayer(int id,char *name,int score,Player p)
{
	p->id = id;
    strcpy(p->name,name);
	p->score =score;

}
/////////////////////////////////////////////////////////////
/*
  函数名称：SetPlayerListFromFile(PlayerList pl,char *filename)
  编写时间：6.24
  编写人：黄汉耀
  参数介绍：PlayerList pl,char *filename
  函数功能：读取文件
  */
SetPlayerListFromFile(PlayerList pl,char *filename)
{
	
	FILE *fp;
	fp=fopen(filename,"rb+");
	system("cls");
	if(fp==NULL)
	{
		printf("无法打开历史存档文件! 历史存档为空!");
		return -1;
	}
	else{
		int tcm,score;
		char stcm[10];
		while(fscanf(fp,"%d%s%d",&tcm,stcm,&score)!=EOF){ //读取文件直到文件尾
			SetPlayer(tcm,stcm,score,pl->list[tcm]);//将读取的数据存入表中
		}
		pl->issort=0;//判断还没排序
	}
	fclose(fp);
	return 0;
	getch();
}
////////////////////////////////////////////////////////////////////
/*
  函数名称：WriteToFile(PlayerList pl,char *filename)
  编写时间：6.27
  编写人：
  参数介绍：
  函数功能：写入文件
  */
void WriteToFile(PlayerList pl,char *filename)
{
	FILE *fp;
	fp=fopen(filename,"wb");
	if(fp==NULL)
	{
		printf("无法写入历史存档文件!");
	}
	else
	{
		int i;
		for(i=0;i<MaxPlayer;i++)
		{
			fprintf(fp,"%d %s %d\r\n",pl->list[i]->id,pl->list[i]->name,pl->list[i]->score);
		}
	}
	fclose(fp);
}
///////////////////////////////////////////////////////////////////////////////////
/*
  函数名称：Sort(PlayerList pl)
  编写时间：6.25
  编写人：
  参数介绍：
  函数功能：排序
  */
void Sort(PlayerList pl)
{
	int i,j;
	int n=pl->n;//n为玩家总数
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(pl->sortedlist[i]->score >pl->sortedlist[j]->score)
			{
				Player t=pl->sortedlist[i];
				pl->sortedlist[i]=pl->sortedlist[j]; 
				pl->sortedlist[j]=t; 
			
			}
		
		}
	
	}
	n=pl->currentn;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(pl->currentsortedlist[i]->score>pl->currentsortedlist[j]->score)
			{
				Player t=pl->currentsortedlist[i];
				pl->currentsortedlist[i]=pl->currentsortedlist[j];
				pl->currentsortedlist[j]=t;
			
			}
		
		}
	}
    pl->issort =1;

}
/////////////////////////////////////////////////////////////////////////////////
/*
  函数名称:GetIdByName(PlayerList pl,char *name)
  编写时间：6.25
  编写人：
  参数介绍：无
  函数功能：通过姓名得到id
  */
int GetIdByName(PlayerList pl,char *name)
{
	int n=pl->n;
	int i;
	for(i=0;i<n;i++)
	{
		if(strcmp(name,pl->list[i]->name)==0) return pl->list[i]->id;
	
	}
	return -1;

}
////////////////////////////////////////////////////////////////////////////////
/*
  函数名称:GetHisNById(PlayerList pl,char *name)
  编写时间：6.25
  编写人：
  参数介绍：无
  函数功能：通过id得到历史排名
  */
int GetHisNById(PlayerList pl,int id)
{
	int n=pl->sortedlist;
	int i;
	for(i=0;i<n;i++)
	{
		if(id==pl->sortedlist[i]->id) return i+1;
	
	}


}
//////////////////////////////////////////////////////////////////////////////
/*
  函数名称:GetCurNById(PlayerList pl,char *name)
  编写时间：6.25
  编写人：
  参数介绍：无
  函数功能：得到当前排名通过id
  */
int GetCurNById(PlayerList pl,int id)
{
	int n=pl->currentsortedlist;
	int i;
	for(i=0;i<n;i++)
	{
		if(id==pl->currentsortedlist[i]->id ) return i+1;
	
	}
	return -1;

}
////////////////////////////////////////////////////////////////
/*
  函数名称:rquery(PlayerList pl)
  编写时间：6.25
  编写人：黄汉耀
  参数介绍：pl玩家列表
  函数功能：打印玩家列表
  */

void rquery(PlayerList pl)
{
	int i,j,counter=0;
	system("cls");
	gotoxy(34,2);
	printf("玩家列表\n");
	printf("\n\t\t\t■■■■■■■■■■■■■");
	for(i=0;i<=255;i++)
	{
		if(!strcmp(pl->list[i]->name,"Nobody")==0 && (pl->list[i]->id)!=0)
		{
			//gotoxy(2,i+3); 导致打印空格
			printf("\n");
			printf("\t\t\t■\t%003d ",pl->list[i]->id);
			printf("%s ",pl->list[i]->name);
			printf("%d\t■",pl->list[i]->score);	
		}
	}
	printf("\n\t\t\t■■■■■■■■■■■■■");
	printf("\n\t\t\t**按回车，返回上级菜单！");
    getch();
}
////////////////////////////////////////////////////////////////////////////
/*
  函数名称:printfhis(PlayerList pl)
  编写时间：6.25
  编写人：黄汉耀
  参数介绍：无
  函数功能：打印历史玩家列表
  */
void printfhis(PlayerList pl)
{
	int i,n,counter=0;
	system("cls");
	Sort(pl);
	gotoxy(32,2);
	printf("历史玩家列表\n");
	printf("\n\t\t\t■■■■■■■■■■■■■");
	for(i=0;i<=255;i++)
	{
		if(pl->list[i]->score)
			counter++;
	}
	for(n=0;n<=counter-1;n++)
	{
		
			//gotoxy(32,n+3);

			printf("\n");
			printf("\t\t\t■\t%003d ",pl->sortedlist[n]->id);
			printf("%s ",pl->sortedlist[n]->name);
			printf("%d\t■",pl->sortedlist[n]->score);
		
	}
	printf("\n\t\t\t■■■■■■■■■■■■■");
	printf("\n\t\t\t**按回车，返回上级菜单！");
	getch();
}

/////////////////////////////////////////////////////////////////////////
/*
  函数名称:printfcur(PlayerList pl)
  编写时间：6.25
  编写人：黄汉耀
  参数介绍：无
  函数功能：打印当前玩家列表
  */
void printfcur(PlayerList pl)
{
	int i,j,k;
	for(i=0;i<pl->currentn && i<7;i++)
	{
		gotoxy(22,i+10);
		printf("%d ",pl->currentsortedlist[i]->id);
	
	}

	for(j=0;j<pl->currentn && j<7;j++)
	{
		gotoxy(37,j+10);
		printf("%s ",pl->currentsortedlist[j]->name);
	
	}
	
		for(k=0;k<pl->currentn && k<7;k++)
	{
		gotoxy(53,k+10);
		printf("%d ",pl->currentsortedlist[k]->score);
	}

}
///////////////////////////////////////////////////////////////////////////////
/*
  函数名称:GetTopById(PlayerList pl,int n)
  编写时间：6.25
  编写人： 黄汉耀
  参数介绍：无
  函数功能：通过id得到当前玩家下标，即当前玩家
  */
int GetTopById(PlayerList pl,int n)
{
	int i,k;
	Player p;
	k=pl->currentn;
	if(!strcmp(pl->list[n]->name,DEFAULTNAME))
	{
		return -1;
	}
    for(i=0;i<k;i++)
	{
		if(pl->currentsortedlist[i]->id==n )
		{
			pl->top =i;
			return;
		}
	}
	p=GetInitPlayer();
	SetPlayer(n,pl->list[n]->name,pl->list[n]->score,p);
	pl->currentsortedlist[k]=p;
	pl->currentn++;
	Sort(pl);
	k=pl->currentn;
	for(i=0;i<k;i++)
	{
		if(pl->currentsortedlist[i]->id==n)
		{
			pl->top=i;
			return 0;
		}
	
	
	}

}
//----------------------------分割线---------------以下为go函数-------------------分割线-----------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
/*
  函数名称:Menu()
  编写时间：6.29
  编写人：吴佳武
  参数介绍：无
  函数功能：打印历史骰子记录
  */
void printgroup(int a[],int x,int y)
{
	int j;
	for(j=0;j<=5;j++)
	{
		gotoxy(x+(j*2),y);
		printf("%d",a[j]);
	} 
}


///////////////////////////////////////////////////////////////////////////////
/*
  函数名称:Menu()
  编写时间：6.25
  编写人： 黄汉耀
  参数介绍：无
  函数功能：摇骰子界面
  */

void Menu()
{

	gotoxy(14,3);
	printf("博饼乐--厦门传统小游戏（电子版）");
	gotoxy(1,2+q); printf("4");
	gotoxy(14,2+q);printf("4");
	gotoxy(27,2+q);printf("4");
	gotoxy(40,2+q);printf("4");
	gotoxy(53,2+q);printf("4");
	gotoxy(66,2+q);printf("4");


	gotoxy(60,3+q);printf("总分:%d",0);
	gotoxy(1,4+q);printf("第一次:");
	gotoxy(40,4+q);printf("第二次:");
	gotoxy(1,5+q);printf("第三次:");
	gotoxy(40,5+q);printf("第四次:");
	gotoxy(1,6+q);printf("第五次:");
	gotoxy(40,6+q);printf("第六次:");
	gotoxy(1,7+q);printf("第七次:");
	gotoxy(40,7+q);printf("第八次:");
	gotoxy(1,8+q);printf("第九次:");
	gotoxy(40,8+q);printf("第十次:");
	gotoxy(1,9+q);printf("第十一次:");
	gotoxy(40,9+q);printf("第十二次:");
	gotoxy(1,10+q);printf("第十三次:");
	gotoxy(40,10+q);printf("第十四次:");
	gotoxy(1,11+q);printf("第十五次:");
	gotoxy(40,11+q);printf("第十六次:");
	gotoxy(1,12+q);printf("第十七次:");
	gotoxy(40,12+q);printf("第十八次:");
	gotoxy(1,13+q);printf("第十九次:");
	gotoxy(40,13+q);printf("第二十次:");
	gotoxy(1,15+q);printf("*****按空格键开始，空格键停止，并计算分数！*****");
}


///////////////////////////////////////////////////////////////////////////////
/*
  函数名称:GetRand(int a[])
  编写时间：6.26
  编写人： 黄汉耀
  参数介绍：无
  函数功能：数字转动函数
  */
void GetRand(int a[])//通过覆盖转动
{
	int i,j;
	getch();
		while(!kbhit())
		{
			for(i=0;i<=5;i++)
			{
				a[i]=rand()%6+1;
			}
			for(j=0;j<=5;j++)
			{
				gotoxy((j+1)*13-12,2+q);
				printf("%d",a[j]);

			} 	 
		}
		getch();
}
///////////////////////////////////////////////////////////////////////////////
/*
  函数名称:GetBoBingScore(int a[])
  编写时间：6.26
  编写人： 黄汉耀
  参数介绍：无
  函数功能：通过点数得总分
  */
int GetBoBingScore(int a[])
{
	int one=0,two=0,three=0,four=0,five=0,six=0;
	int k;
	for(k=0;k<=5;k++)
	{
		if(1==a[k]) one++;
		if(2==a[k]) two++;
		if(3==a[k]) three++;
		if(4==a[k]) four++;
		if(5==a[k]) five++;
		if(6==a[k]) six++;
	}  	
	if(four==6)return 64;
	else if(four==4&&one==2)return 60;
	else if(one==6||two==6||three==6||five==6||six==6)return 56;
	else if(four==5)return 48;
	else if(one==5||two==5||three==5||five==5||six==5)return 40;
	else if(four==4)return 32;
	else if(one==1&&two==1&&three==1&&four==1&&five==1&&six==1)return 16;
	else if(four==3)return 8;
	else if(four==2&&(one==4||two==4||three==4||five==4||six==4))return 6;
	else if(four==1&&(one==4||two==4||three==4||five==4||six==4))return 5;
	else if(one==4||two==4||three==4||five==4||six==4)return 4;
	else if(four==2)return 2;
	else if(four==1)return 1;
	else return 0;
	return 0;
}
///////////////////////////////////////////////////////////////////////////////
/*
  函数名称:PrintNameByScore(int n)
  编写时间：6.26
  编写人： 黄汉耀
  参数介绍：无
  函数功能：通过得分打印是六四............
  */
void PrintNameByScore(int n)
{
	if(n==64) printf("  六四");
	if(n==60) printf("  状元插金花");
	if(n==56) printf("  六同");
	if(n==48) printf("  五四");
	if(n==40) printf("  五子");
	if(n==32) printf("  状元");
	if(n==16) printf("  对堂");
	if(n==8) printf("  三红");
	if(n==6) printf("  四进带二举");
	if(n==5) printf("  四进带一秀");
	if(n==4) printf("  四进");
	if(n==2) printf("  二举");
	if(n==1) printf("  一秀");
	if(n==0) printf("  没有");
}


///////////////////////////////////////////////////////////////////////////////
/*
  函数名称:Print(PlayerList pl)
  编写时间：6.26
  编写人： 黄汉耀
  参数介绍：无
  函数功能：打印总分和结果
  */
void Print(PlayerList pl )
{	
	int score[21]={0};
	int a[6];
	int c=1,l,i,x;
	system("cls");
	Menu();
	while(c<=20)
	{
		
		GetRand(a);

		score[c]=GetBoBingScore(a);
		switch(c)
		{
		case 1:  
			gotoxy(8,4+q);printgroup(a,8,4+q);PrintNameByScore(score[c]);printf("%3d ",score[c]);
			break;
		case 2:
			gotoxy(47,4+q);printgroup(a,47,4+q);PrintNameByScore(score[c]);printf("%3d ",score[c]);
			break;
		case 3:
			gotoxy(8,5+q);printgroup(a,8,5+q);PrintNameByScore(score[c]);printf("%3d ",score[c]);
			break;
		case 4:
			gotoxy(47,5+q);printgroup(a,47,5+q);PrintNameByScore(score[c]);printf("%3d ",score[c]);
		
			break;
		case 5:
			gotoxy(8,6+q);printgroup(a,8,6+q);PrintNameByScore(score[c]);printf("%3d ",score[c]);
			
			break;
		case 6:
			gotoxy(47,6+q);printgroup(a,47,6+q);PrintNameByScore(score[c]);printf("%3d ",score[c]);
			break;
		case 7:
			gotoxy(8,7+q);printgroup(a,8,7+q);PrintNameByScore(score[c]);printf("%3d ",score[c]);
			
			break;
		case 8:
			gotoxy(47,7+q);printgroup(a,47,7+q);PrintNameByScore(score[c]);printf("%3d ",score[c]);
			break;
		case 9:
			gotoxy(8,8+q);printgroup(a,8,8+q);PrintNameByScore(score[c]);printf("%3d ",score[c]);
			break;
		case 10:
			gotoxy(47,8+q);printgroup(a,47,8+q);PrintNameByScore(score[c]);printf("%3d ",score[c]);
			break;
		case 11:
			gotoxy(10,9+q);printgroup(a,10,9+q);PrintNameByScore(score[c]);printf("%3d ",score[c]);
			break;
		case 12:
			gotoxy(49,9+q);printgroup(a,49,9+q);PrintNameByScore(score[c]);printf("%3d ",score[c]);
			break;
		case 13:
			gotoxy(10,10+q);printgroup(a,10,10+q);PrintNameByScore(score[c]);printf("%3d ",score[c]);
			break; 
		case 14:
			gotoxy(49,10+q);printgroup(a,49,10+q);PrintNameByScore(score[c]);printf("%3d ",score[c]);
		
			break;
		case 15:
			gotoxy(10,11+q);printgroup(a,10,11+q);PrintNameByScore(score[c]);printf("%3d ",score[c]);
			break; 
		case 16:
			gotoxy(49,11+q);printgroup(a,49,11+q);PrintNameByScore(score[c]);printf("%3d ",score[c]);
			break;
		case 17:
			gotoxy(10,12+q);printgroup(a,10,12+q);PrintNameByScore(score[c]);printf("%3d ",score[c]);
			break; 
		case 18:
			gotoxy(49,12+q);printgroup(a,49,12+q);PrintNameByScore(score[c]);printf("%3d ",score[c]);
			break;
		case 19:
			gotoxy(10,13+q);printgroup(a,10,13+q);PrintNameByScore(score[c]);printf("%3d ",score[c]);
			break; 
		case 20:
			gotoxy(49,13+q);printgroup(a,49,13+q);PrintNameByScore(score[c]);printf("%3d ",score[c]);
			break;
		}
		for(l=1;l<=20;l++)
		{
			score[0]=score[0]+score[l];
			gotoxy(65,3+q); 
			printf("%d",score[0]);	
			gotoxy(13,14+q);
		}
		score[c]=0;
		c++;
	}
	x=pl->currentsortedlist[pl->top]->id;
	if(score[0]>pl->list[x]->score)
	{
		pl->list[x]->score=score[0];
		pl->currentsortedlist[pl->top]->score=score[0];
	}
	Sort(pl);
	for(i=0;i<pl->currentn;i++)
	{
		if(pl->currentsortedlist[i]->id==x)
		{
			pl->top=i;
			getch();
			return 0;
		}
	
	}

}

//================分割线=========以下是Help函数====================分割线=========================================
///////////////////////////////////////////////////////////////////////////////
/*
  函数名称:Help()
  编写时间：6.27
  编写人： 黄汉耀
  参数介绍：无
  函数功能：帮助界面
  */
void Help()
{
	system("cls");
	printf("\n\n\n\n\n\n\t  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("\t  ■                      请按键操作                        ■\n");
	printf("\t  ■   输入ID或玩家名查找该玩家当前排名或历史排名及分数     ■\n");
	printf("\t  ■                                                        ■\n");
	printf("\t  ■                  **按任意键返回                        ■\n");
	printf("\t  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	getch();
}
//================分割线=========以下是logout函数====================分割线=========================================
///////////////////////////////////////////////////////////////////////////////
/*
  函数名称:logout(PlayerList pl)
  编写时间：6.27
  编写人： 黄汉耀
  参数介绍：无
  函数功能：注销id
  */
void logout(PlayerList pl)
{
	pl->currentsortedlist[pl->top]->id = 0;
	strcpy(pl->currentsortedlist[pl->top]->name,"Guest");
	pl->currentsortedlist[pl->top]->score=0;
	pl->currentn--;
	pl->top=0;
	Sort(pl);



}

//================分割线=============以下是adminstration==============分割线===============================================
///////////////////////////////////////////////////////////////////////////////
/*
  函数名称:add(PlayerList pl)
  编写时间：6.27
  编写人： 黄汉耀
  参数介绍：无
  函数功能：增加玩家
  */
int add(PlayerList pl)
{
	int id,a;
	char c[20];
	system("cls");
	gotoxy(15,8);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	gotoxy(15,9);
	printf("■           请输入需要增加/更改的玩家ID！        ■\n");
	gotoxy(15,10);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	gotoxy(15,11);
	scanf("%d",&id);
	if(strcmp(pl->list[id]->name,DEFAULTNAME)==0)
	{
		system("cls");
		gotoxy(15,8);
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(15,9);
		printf("■         该ID号可以使用！请输入玩家姓名！       ■\n");
		gotoxy(15,10);
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(15,11);
		scanf("%s",c);
		fflush(stdin);
		strcpy(pl->list[id]->name,c);
	}
	else
	{
		system("cls");
		gotoxy(15,8);
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(15,9);
		printf("■ 玩家已存在，是否改名？改名请按1，返回上级请按2！ ■\n");
		gotoxy(15,10);
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		gotoxy(15,11);
		scanf("%d",&a);
		if(a==1&&pl->list[id]->score==0)
		{
			
			system("cls");
			gotoxy(15,8);
			printf("■■■■■■■■■■\n");
			gotoxy(15,9);
			printf("■ 请输入新名字： ■\n");
			gotoxy(15,10);
			printf("■■■■■■■■■■\n");
			gotoxy(15,11);
			scanf("%s",c);
			fflush(stdin);
			strcpy(pl->list[id]->name,c);
		}
		else if(a==1&&pl->list[id]->score!=0)
		{
			system("cls");
			gotoxy(15,8);
			printf("■■■■■■■■■■\n");
			gotoxy(15,9);
			printf("■ 请输入新名字： ■\n");
			gotoxy(15,10);
			printf("■■■■■■■■■■\n");
			gotoxy(15,11);
			scanf("%s",c);
			fflush(stdin);
			strcpy(pl->list[id]->name,c);
			pl->list[id]->score=0;
		}

		else if(a==2)
		{
			return 0;
		}
	
	}



}
///////////////////////////////////////////////////////////////////////////////
/*
  函数名称:SeeunId(PlayerList pl)
  编写时间：6.27
  编写人： 黄汉耀
  参数介绍：无
  函数功能：查看未使用id
  */
void SeeunId(PlayerList pl)
{
	int n;
	system("cls");
	for(n=0;n<MaxPlayer;n++)
	{
		if(strcmp(pl->list[n]->name,DEFAULTNAME)==0)
		{
			printf("%d  \n",pl->list[n]->id);
		}
	
	}
	getch();

}
///////////////////////////////////////////////////////////////////////////////
/*
  函数名称:SeePlayerId(PlayerList pl)
  编写时间：6.27
  编写人： 黄汉耀
  参数介绍：无
  函数功能：查看当前玩家
  */
void SeePlayerId(PlayerList pl)
{
	int n,i;
	system("cls");
	n=pl->currentn;
	for(i=0;i<n;i++)
	{
		printf("%s ",pl->currentsortedlist[i]->name);
	
	}
	getch();

}
///////////////////////////////////////////////////////////////////////////////
/*
  函数名称:del(PlayerList pl)
  编写时间：6.27
  编写人： 黄汉耀
  参数介绍：无
  函数功能：删除玩家
  */
int del(PlayerList pl)
{
	int id,n,i;
	system("cls");
	gotoxy(15,8);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	gotoxy(15,9);
	printf("■              请输入要删除的id号！              ■\n");
	gotoxy(15,10);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	gotoxy(15,11);
	scanf("%d",&id);
	fflush(stdin);
	if(strcmp(pl->list[id]->name,DEFAULTNAME)==0)
	{
	system("cls");
	gotoxy(15,8);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	gotoxy(15,9);
	printf("■              该玩家不存在，无需删除！          ■\n");
	gotoxy(15,10);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	
	}
	else
	{
		system("cls");
		gotoxy(15,8);
		printf("■■■■■■■■■■■■■■■■■■■■■■■");
		gotoxy(15,9);
		printf("             该玩家姓名: %s",pl->list[id]->name);
		gotoxy(15,10);
		printf("             该玩家分数: %d",pl->list[id]->score);
		gotoxy(15,11);
		printf("     确认删除请按1！取消并返回上级请按2！ ");
		gotoxy(15,12);
		printf("■■■■■■■■■■■■■■■■■■■■■■■");
		gotoxy(15,13);
		scanf("%d",&n);
		if(n==1)
		{
			for(i=0;i<pl->currentn;i++)
			{
				if(strcmp(pl->currentsortedlist[i]->name,pl->list[id]->name)==0)
				{
					strcpy(pl->currentsortedlist[i]->name,DEFAULTNAME);
				    pl->currentsortedlist[i]->score=0;
					Sort(pl);
				}
			}
			pl->currentn--;
			strcpy(pl->list[id]->name ,DEFAULTNAME);
			pl->list[id]->score=0;
		}
		if(n==2)
		{
			return 0;
		}

	}
	Sort(pl);

}
///////////////////////////////////////////////////////////////////////////////
/*
  函数名称:AdmistratorInterface()
  编写时间：6.27
  编写人：吴佳武
  参数介绍：无
  函数功能：管理员界面
  */
void AdmistratorInterface()
{
	system("cls");
	gotoxy(27,4);
	printf("■■■■■■■■■■■");
	gotoxy(27,5);
	printf("■  管理员后台系统  ■");
	gotoxy(27,6);
	printf("■■■■■■■■■■■");
	gotoxy(6,8);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	gotoxy(6,9);
	printf("■1、增加/更改用户                 2、删除用户                  ■\n");
	gotoxy(6,10);
	printf("■                                                              ■\n");
	gotoxy(6,11);
	printf("■3、保存并返回                    4 、放弃并返回               ■\n");
	gotoxy(6,12);
	printf("■                                                              ■\n");
	gotoxy(6,13);
	printf("■5、查看当前玩家                  6、查看未使用编号            ■\n");
	gotoxy(6,14);
	printf("■                                                              ■\n");
	gotoxy(6,15);
	printf("■7、***按T为退到主菜单                                         ■\n");
	gotoxy(6,16);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	gotoxy(6,17);
	printf("请输入您需要执行的功能：");

}
///////////////////////////////////////////////////////////////////////////////
/*
  函数名称:Adm(PlayerList pl)
  编写时间：6.27
  编写人：黄汉耀
  参数介绍：无
  函数功能：管理员操作
  */
void Adm(PlayerList pl)
{
	char c[20];
	int n;
	do
	{
	  AdmistratorInterface();
	  gets(c);
	  fflush(stdin);
	  if(strcmp(c,"T")==0)
	  {
		  return 0;
	
	  }
	  n=(atoi(c));
	  switch(n)
	  {
	  case 1:
		  add(pl);
		  break;
	  case 2:
		  del(pl);
		  break;
	  case 3:
		  WriteToFile(pl,FILENAME);
		  break;	
	  case 4:
		  SetPlayerListFromFile(pl,FILENAME);
		  break;
	  case 5:
		  SeePlayerId(pl);
		  break;
	  case 6:
		 SeeunId(pl);
		  break;
		

	  }

	}while(1);
}


