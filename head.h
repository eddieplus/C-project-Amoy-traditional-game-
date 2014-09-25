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

//��ҽṹ�� 
typedef struct player
{
	int id;
	char name[20];
	int score;
} *Player;
typedef struct playerlist
{
    Player *list;
	int n;//���α�list����
	Player *sortedlist;
	Player *currentsortedlist;
	int issort;//1��ʾ���α�������0��ʾû��
	int currentn;//��ǰ�������
	int top;//��ǰ����±�
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
  �������ƣ� gotoxy(int   x,   int   y) 
  ��дʱ�䣺6.24
  ��д�ˣ���
  �������ܣ�x��y�ֱ��������ͼ��Ϊƽ��ֱ������ϵ�������ޣ�Yȡ����ֵ
  �������ܣ����궨λ����
  */

static void   gotoxy(int   x,   int   y)   {   
  COORD   c;   
  c.X   =   x   -   1;   
  c.Y   =   y   -   1;   
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);   
}

/////////////////////////////////////////////////////////////
/*
  �������ƣ�menu
  ��дʱ�䣺6.24
  ��д�ˣ������
  �������ܣ�pl����б�
  �������ܣ����棬��Ϸ������
  */
void menu(PlayerList pl)
{
	int x;
	system("cls");
	gotoxy(25,3);
	printf("2013-2014����ѧ��C����ʵѵ��Ŀ����!");
    gotoxy(5,5);
	printf("��ǰ���ID:%d",pl->currentsortedlist[pl->top]->id);
	gotoxy(23,5);
	printf("����:%s",pl->currentsortedlist[pl->top]->name);
	gotoxy(34,5);
	printf("��߷�:%d",pl->currentsortedlist[0]->score);
	gotoxy(44,5);
	printf("��ǰ����:%d",pl->top+1);
	gotoxy(59,5);
	printf("������:%d",x=GetHisNById(pl,pl->currentsortedlist[pl->top]->id));
	gotoxy(9,7);
	printf("������Ŀ��ǰ������:");
	gotoxy(9,8);
	printf("����������������������������������������������������������������");
	gotoxy(9,9);
	printf("��");
	gotoxy(9,10);
	printf("��");
	gotoxy(9,11);
	printf("��");
	gotoxy(9,12);
	printf("��");
	gotoxy(9,13);
	printf("��");
	gotoxy(9,14);
	printf("��");
	gotoxy(9,15);
	printf("��");
	gotoxy(9,16);
	printf("��");
	gotoxy(9,17);
	printf("��");
	gotoxy(71,9);
	printf("��");
	gotoxy(71,10);
	printf("��");
	gotoxy(71,11);
	printf("��");
	gotoxy(71,12);
	printf("��");
	gotoxy(71,13);
	printf("��");
	gotoxy(71,14);
	printf("��");
	gotoxy(71,15);
	printf("��");
	gotoxy(71,16);
	printf("��");
	gotoxy(71,17);
	printf("��");
	gotoxy(9,18);
	printf("����������������������������������������������������������������");
	gotoxy(12,9);
	printf("����");
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
	printf("���ID");
	gotoxy(37,9);
	printf("�������");
	gotoxy(53,9);
	printf("����");
	gotoxy(9,19);
	printf("��");
	gotoxy(11,19);
	printf("�������");
	gotoxy(71,19);
	printf("��");
	gotoxy(9,20);
	printf("��");
	gotoxy(11,20);
	printf("go--������Ϸ");
	gotoxy(71,20);
	printf("��");
	gotoxy(30,20);
	printf("logout---ע��");
	gotoxy(52,20);
	printf("query---����б�");
	gotoxy(9,21);
	printf("��");
	gotoxy(71,21);
	printf("��");
	gotoxy(11,21);
	printf("help---����");
	gotoxy(30,21);
	printf("history---��ʷ���а�");
	gotoxy(9,22);
	printf("��");
	gotoxy(71,22);
	printf("��");
	gotoxy(11,22);
	printf("Adminstrator---����Ա");
	gotoxy(9,23);
	printf("����������������������������������������������������������������");
	printfcur(pl);
	gotoxy(1,25);
	printf("�����루���ı�Ż�����Ҳ��������������:");

	

}
/////////////////////////////////////////////////////////////
/*
  �������ƣ�GetInitPlayer()
  ��дʱ�䣺6.24
  ��д�ˣ������
  �������ܣ���
  �������ܣ���ʼ���������
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
  �������ƣ�GetDefaultPlayerList()
  ��дʱ�䣺6.24
  ��д�ˣ��ƺ�ҫ
  �������ܣ���
  �������ܣ���ʼ������б�
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
  �������ƣ�ShowPlayer()
  ��дʱ�䣺6.24
  ��д�ˣ��ƺ�ҫ
  �������ܣ�p
  �������ܣ���ӡ
  */

void ShowPlayer(Player p)
{
	printf("%d\n",p->id);
	
    printf("%s\n",p->name);
	
	printf("%d\n",p->score);


}
//////////////////////////////////////////////////////////
/*
  �������ƣ�SetPlayer
  ��дʱ�䣺6.24
  ��д�ˣ��ƺ�ҫ
  �������ܣ�id  *name score p
  �������ܣ�����id name score p �������
  */;
void SetPlayer(int id,char *name,int score,Player p)
{
	p->id = id;
    strcpy(p->name,name);
	p->score =score;

}
/////////////////////////////////////////////////////////////
/*
  �������ƣ�SetPlayerListFromFile(PlayerList pl,char *filename)
  ��дʱ�䣺6.24
  ��д�ˣ��ƺ�ҫ
  �������ܣ�PlayerList pl,char *filename
  �������ܣ���ȡ�ļ�
  */
SetPlayerListFromFile(PlayerList pl,char *filename)
{
	
	FILE *fp;
	fp=fopen(filename,"rb+");
	system("cls");
	if(fp==NULL)
	{
		printf("�޷�����ʷ�浵�ļ�! ��ʷ�浵Ϊ��!");
		return -1;
	}
	else{
		int tcm,score;
		char stcm[10];
		while(fscanf(fp,"%d%s%d",&tcm,stcm,&score)!=EOF){ //��ȡ�ļ�ֱ���ļ�β
			SetPlayer(tcm,stcm,score,pl->list[tcm]);//����ȡ�����ݴ������
		}
		pl->issort=0;//�жϻ�û����
	}
	fclose(fp);
	return 0;
	getch();
}
////////////////////////////////////////////////////////////////////
/*
  �������ƣ�WriteToFile(PlayerList pl,char *filename)
  ��дʱ�䣺6.27
  ��д�ˣ�
  �������ܣ�
  �������ܣ�д���ļ�
  */
void WriteToFile(PlayerList pl,char *filename)
{
	FILE *fp;
	fp=fopen(filename,"wb");
	if(fp==NULL)
	{
		printf("�޷�д����ʷ�浵�ļ�!");
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
  �������ƣ�Sort(PlayerList pl)
  ��дʱ�䣺6.25
  ��д�ˣ�
  �������ܣ�
  �������ܣ�����
  */
void Sort(PlayerList pl)
{
	int i,j;
	int n=pl->n;//nΪ�������
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
  ��������:GetIdByName(PlayerList pl,char *name)
  ��дʱ�䣺6.25
  ��д�ˣ�
  �������ܣ���
  �������ܣ�ͨ�������õ�id
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
  ��������:GetHisNById(PlayerList pl,char *name)
  ��дʱ�䣺6.25
  ��д�ˣ�
  �������ܣ���
  �������ܣ�ͨ��id�õ���ʷ����
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
  ��������:GetCurNById(PlayerList pl,char *name)
  ��дʱ�䣺6.25
  ��д�ˣ�
  �������ܣ���
  �������ܣ��õ���ǰ����ͨ��id
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
  ��������:rquery(PlayerList pl)
  ��дʱ�䣺6.25
  ��д�ˣ��ƺ�ҫ
  �������ܣ�pl����б�
  �������ܣ���ӡ����б�
  */

void rquery(PlayerList pl)
{
	int i,j,counter=0;
	system("cls");
	gotoxy(34,2);
	printf("����б�\n");
	printf("\n\t\t\t��������������������������");
	for(i=0;i<=255;i++)
	{
		if(!strcmp(pl->list[i]->name,"Nobody")==0 && (pl->list[i]->id)!=0)
		{
			//gotoxy(2,i+3); ���´�ӡ�ո�
			printf("\n");
			printf("\t\t\t��\t%003d ",pl->list[i]->id);
			printf("%s ",pl->list[i]->name);
			printf("%d\t��",pl->list[i]->score);	
		}
	}
	printf("\n\t\t\t��������������������������");
	printf("\n\t\t\t**���س��������ϼ��˵���");
    getch();
}
////////////////////////////////////////////////////////////////////////////
/*
  ��������:printfhis(PlayerList pl)
  ��дʱ�䣺6.25
  ��д�ˣ��ƺ�ҫ
  �������ܣ���
  �������ܣ���ӡ��ʷ����б�
  */
void printfhis(PlayerList pl)
{
	int i,n,counter=0;
	system("cls");
	Sort(pl);
	gotoxy(32,2);
	printf("��ʷ����б�\n");
	printf("\n\t\t\t��������������������������");
	for(i=0;i<=255;i++)
	{
		if(pl->list[i]->score)
			counter++;
	}
	for(n=0;n<=counter-1;n++)
	{
		
			//gotoxy(32,n+3);

			printf("\n");
			printf("\t\t\t��\t%003d ",pl->sortedlist[n]->id);
			printf("%s ",pl->sortedlist[n]->name);
			printf("%d\t��",pl->sortedlist[n]->score);
		
	}
	printf("\n\t\t\t��������������������������");
	printf("\n\t\t\t**���س��������ϼ��˵���");
	getch();
}

/////////////////////////////////////////////////////////////////////////
/*
  ��������:printfcur(PlayerList pl)
  ��дʱ�䣺6.25
  ��д�ˣ��ƺ�ҫ
  �������ܣ���
  �������ܣ���ӡ��ǰ����б�
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
  ��������:GetTopById(PlayerList pl,int n)
  ��дʱ�䣺6.25
  ��д�ˣ� �ƺ�ҫ
  �������ܣ���
  �������ܣ�ͨ��id�õ���ǰ����±꣬����ǰ���
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
//----------------------------�ָ���---------------����Ϊgo����-------------------�ָ���-----------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
/*
  ��������:Menu()
  ��дʱ�䣺6.29
  ��д�ˣ������
  �������ܣ���
  �������ܣ���ӡ��ʷ���Ӽ�¼
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
  ��������:Menu()
  ��дʱ�䣺6.25
  ��д�ˣ� �ƺ�ҫ
  �������ܣ���
  �������ܣ�ҡ���ӽ���
  */

void Menu()
{

	gotoxy(14,3);
	printf("������--���Ŵ�ͳС��Ϸ�����Ӱ棩");
	gotoxy(1,2+q); printf("4");
	gotoxy(14,2+q);printf("4");
	gotoxy(27,2+q);printf("4");
	gotoxy(40,2+q);printf("4");
	gotoxy(53,2+q);printf("4");
	gotoxy(66,2+q);printf("4");


	gotoxy(60,3+q);printf("�ܷ�:%d",0);
	gotoxy(1,4+q);printf("��һ��:");
	gotoxy(40,4+q);printf("�ڶ���:");
	gotoxy(1,5+q);printf("������:");
	gotoxy(40,5+q);printf("���Ĵ�:");
	gotoxy(1,6+q);printf("�����:");
	gotoxy(40,6+q);printf("������:");
	gotoxy(1,7+q);printf("���ߴ�:");
	gotoxy(40,7+q);printf("�ڰ˴�:");
	gotoxy(1,8+q);printf("�ھŴ�:");
	gotoxy(40,8+q);printf("��ʮ��:");
	gotoxy(1,9+q);printf("��ʮһ��:");
	gotoxy(40,9+q);printf("��ʮ����:");
	gotoxy(1,10+q);printf("��ʮ����:");
	gotoxy(40,10+q);printf("��ʮ�Ĵ�:");
	gotoxy(1,11+q);printf("��ʮ���:");
	gotoxy(40,11+q);printf("��ʮ����:");
	gotoxy(1,12+q);printf("��ʮ�ߴ�:");
	gotoxy(40,12+q);printf("��ʮ�˴�:");
	gotoxy(1,13+q);printf("��ʮ�Ŵ�:");
	gotoxy(40,13+q);printf("�ڶ�ʮ��:");
	gotoxy(1,15+q);printf("*****���ո����ʼ���ո��ֹͣ�������������*****");
}


///////////////////////////////////////////////////////////////////////////////
/*
  ��������:GetRand(int a[])
  ��дʱ�䣺6.26
  ��д�ˣ� �ƺ�ҫ
  �������ܣ���
  �������ܣ�����ת������
  */
void GetRand(int a[])//ͨ������ת��
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
  ��������:GetBoBingScore(int a[])
  ��дʱ�䣺6.26
  ��д�ˣ� �ƺ�ҫ
  �������ܣ���
  �������ܣ�ͨ���������ܷ�
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
  ��������:PrintNameByScore(int n)
  ��дʱ�䣺6.26
  ��д�ˣ� �ƺ�ҫ
  �������ܣ���
  �������ܣ�ͨ���÷ִ�ӡ������............
  */
void PrintNameByScore(int n)
{
	if(n==64) printf("  ����");
	if(n==60) printf("  ״Ԫ���");
	if(n==56) printf("  ��ͬ");
	if(n==48) printf("  ����");
	if(n==40) printf("  ����");
	if(n==32) printf("  ״Ԫ");
	if(n==16) printf("  ����");
	if(n==8) printf("  ����");
	if(n==6) printf("  �Ľ�������");
	if(n==5) printf("  �Ľ���һ��");
	if(n==4) printf("  �Ľ�");
	if(n==2) printf("  ����");
	if(n==1) printf("  һ��");
	if(n==0) printf("  û��");
}


///////////////////////////////////////////////////////////////////////////////
/*
  ��������:Print(PlayerList pl)
  ��дʱ�䣺6.26
  ��д�ˣ� �ƺ�ҫ
  �������ܣ���
  �������ܣ���ӡ�ֺܷͽ��
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

//================�ָ���=========������Help����====================�ָ���=========================================
///////////////////////////////////////////////////////////////////////////////
/*
  ��������:Help()
  ��дʱ�䣺6.27
  ��д�ˣ� �ƺ�ҫ
  �������ܣ���
  �������ܣ���������
  */
void Help()
{
	system("cls");
	printf("\n\n\n\n\n\n\t  ������������������������������������������������������������\n");
	printf("\t  ��                      �밴������                        ��\n");
	printf("\t  ��   ����ID����������Ҹ���ҵ�ǰ��������ʷ����������     ��\n");
	printf("\t  ��                                                        ��\n");
	printf("\t  ��                  **�����������                        ��\n");
	printf("\t  ������������������������������������������������������������\n");
	getch();
}
//================�ָ���=========������logout����====================�ָ���=========================================
///////////////////////////////////////////////////////////////////////////////
/*
  ��������:logout(PlayerList pl)
  ��дʱ�䣺6.27
  ��д�ˣ� �ƺ�ҫ
  �������ܣ���
  �������ܣ�ע��id
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

//================�ָ���=============������adminstration==============�ָ���===============================================
///////////////////////////////////////////////////////////////////////////////
/*
  ��������:add(PlayerList pl)
  ��дʱ�䣺6.27
  ��д�ˣ� �ƺ�ҫ
  �������ܣ���
  �������ܣ��������
  */
int add(PlayerList pl)
{
	int id,a;
	char c[20];
	system("cls");
	gotoxy(15,8);
	printf("����������������������������������������������������\n");
	gotoxy(15,9);
	printf("��           ��������Ҫ����/���ĵ����ID��        ��\n");
	gotoxy(15,10);
	printf("����������������������������������������������������\n");
	gotoxy(15,11);
	scanf("%d",&id);
	if(strcmp(pl->list[id]->name,DEFAULTNAME)==0)
	{
		system("cls");
		gotoxy(15,8);
		printf("����������������������������������������������������\n");
		gotoxy(15,9);
		printf("��         ��ID�ſ���ʹ�ã����������������       ��\n");
		gotoxy(15,10);
		printf("����������������������������������������������������\n");
		gotoxy(15,11);
		scanf("%s",c);
		fflush(stdin);
		strcpy(pl->list[id]->name,c);
	}
	else
	{
		system("cls");
		gotoxy(15,8);
		printf("������������������������������������������������������\n");
		gotoxy(15,9);
		printf("�� ����Ѵ��ڣ��Ƿ�����������밴1�������ϼ��밴2�� ��\n");
		gotoxy(15,10);
		printf("������������������������������������������������������\n");
		gotoxy(15,11);
		scanf("%d",&a);
		if(a==1&&pl->list[id]->score==0)
		{
			
			system("cls");
			gotoxy(15,8);
			printf("��������������������\n");
			gotoxy(15,9);
			printf("�� �����������֣� ��\n");
			gotoxy(15,10);
			printf("��������������������\n");
			gotoxy(15,11);
			scanf("%s",c);
			fflush(stdin);
			strcpy(pl->list[id]->name,c);
		}
		else if(a==1&&pl->list[id]->score!=0)
		{
			system("cls");
			gotoxy(15,8);
			printf("��������������������\n");
			gotoxy(15,9);
			printf("�� �����������֣� ��\n");
			gotoxy(15,10);
			printf("��������������������\n");
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
  ��������:SeeunId(PlayerList pl)
  ��дʱ�䣺6.27
  ��д�ˣ� �ƺ�ҫ
  �������ܣ���
  �������ܣ��鿴δʹ��id
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
  ��������:SeePlayerId(PlayerList pl)
  ��дʱ�䣺6.27
  ��д�ˣ� �ƺ�ҫ
  �������ܣ���
  �������ܣ��鿴��ǰ���
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
  ��������:del(PlayerList pl)
  ��дʱ�䣺6.27
  ��д�ˣ� �ƺ�ҫ
  �������ܣ���
  �������ܣ�ɾ�����
  */
int del(PlayerList pl)
{
	int id,n,i;
	system("cls");
	gotoxy(15,8);
	printf("����������������������������������������������������\n");
	gotoxy(15,9);
	printf("��              ������Ҫɾ����id�ţ�              ��\n");
	gotoxy(15,10);
	printf("����������������������������������������������������\n");
	gotoxy(15,11);
	scanf("%d",&id);
	fflush(stdin);
	if(strcmp(pl->list[id]->name,DEFAULTNAME)==0)
	{
	system("cls");
	gotoxy(15,8);
	printf("����������������������������������������������������\n");
	gotoxy(15,9);
	printf("��              ����Ҳ����ڣ�����ɾ����          ��\n");
	gotoxy(15,10);
	printf("����������������������������������������������������\n");
	
	}
	else
	{
		system("cls");
		gotoxy(15,8);
		printf("����������������������������������������������");
		gotoxy(15,9);
		printf("             ���������: %s",pl->list[id]->name);
		gotoxy(15,10);
		printf("             ����ҷ���: %d",pl->list[id]->score);
		gotoxy(15,11);
		printf("     ȷ��ɾ���밴1��ȡ���������ϼ��밴2�� ");
		gotoxy(15,12);
		printf("����������������������������������������������");
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
  ��������:AdmistratorInterface()
  ��дʱ�䣺6.27
  ��д�ˣ������
  �������ܣ���
  �������ܣ�����Ա����
  */
void AdmistratorInterface()
{
	system("cls");
	gotoxy(27,4);
	printf("����������������������");
	gotoxy(27,5);
	printf("��  ����Ա��̨ϵͳ  ��");
	gotoxy(27,6);
	printf("����������������������");
	gotoxy(6,8);
	printf("������������������������������������������������������������������\n");
	gotoxy(6,9);
	printf("��1������/�����û�                 2��ɾ���û�                  ��\n");
	gotoxy(6,10);
	printf("��                                                              ��\n");
	gotoxy(6,11);
	printf("��3�����沢����                    4 ������������               ��\n");
	gotoxy(6,12);
	printf("��                                                              ��\n");
	gotoxy(6,13);
	printf("��5���鿴��ǰ���                  6���鿴δʹ�ñ��            ��\n");
	gotoxy(6,14);
	printf("��                                                              ��\n");
	gotoxy(6,15);
	printf("��7��***��TΪ�˵����˵�                                         ��\n");
	gotoxy(6,16);
	printf("������������������������������������������������������������������\n");
	gotoxy(6,17);
	printf("����������Ҫִ�еĹ��ܣ�");

}
///////////////////////////////////////////////////////////////////////////////
/*
  ��������:Adm(PlayerList pl)
  ��дʱ�䣺6.27
  ��д�ˣ��ƺ�ҫ
  �������ܣ���
  �������ܣ�����Ա����
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


