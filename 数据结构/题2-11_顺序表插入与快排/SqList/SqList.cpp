// SqList.cpp : 定义控制台应用程序的入口点。
//
#include <stdafx.h>
#include <stdio.h>    
#include <stdlib.h>   // for 内存分配函数
#include <iostream>   // 文件I/O流
#include <fstream>
using namespace std;

#define LIST_INIT_SIZE  100
#define LISTINCREMENT   10

//定义顺序表
typedef struct Sqlist{
	int *elem;
	int length;
	int listsize;
}Sqlist;

//所用到的函数声明(参数省略了变量名)
int InitList_Sq(Sqlist &);
int inputData(Sqlist &);
//快速排序
void quickSort(Sqlist &);
void QSort (Sqlist &,int,int);
int Partition(Sqlist &,int,int);
//插入算法及结果输出
int insertOrderList(Sqlist &,int);    //在顺序表中插入给定值
void outputSqlist(Sqlist);             //输出顺序表

void main()
{
	Sqlist sq;
    int x=0;
	
	//以下向顺序表存入数据
	InitList_Sq(sq);
	inputData(sq);
		outputSqlist(sq);

	printf("%s\n","以下排序：");
	quickSort(sq);
		outputSqlist(sq);

	printf("%s","待插入的数x：");
	scanf("%d",&x);
	insertOrderList(sq,x);
	outputSqlist(sq);

	//以下为程序结束标志： 
	printf("%s","\n\n");
	printf("%s","GAME OVER......\n");

	//屏幕停留控制
	int a=0;
	scanf("%d",&a);
}
//初始化顺序表
int InitList_Sq(Sqlist &sq)
{
	sq.elem=(int *)malloc(LIST_INIT_SIZE*sizeof(int));
	if (! sq.elem) return 0;

	sq.length=0;
	sq.listsize=LIST_INIT_SIZE;
	return 1;
}
//向顺序表输入数据
int inputData(Sqlist &sq)
{
	int e=0,i=0;  
	sq.elem[0]=0;  //0号位留空

	char choice=' ';
	do{
		cout<<"请选择数据来源(只认小写字母)：a---从“dataForTest.txt”文件读取； b---键盘手工输入；c---没数据；"<<'\n';
		cin>>choice;
	}while (choice!='a'&& choice!='b'&& choice!='c');

	//文件格式说明：txt文件，数字之间用空格隔开，不须换行，不得有其它字符，
	//以“-1”作为结束标志
	switch(choice){
		case 'a': //从文件读入数据
			{ ifstream fin("dataForTest.txt");
			do{
				fin>>e;
				if (e!=-1) {sq.elem[++i]=e;sq.length++;}
				else break;
			}while(sq.length<sq.listsize);
			break;
			}
		case 'b': //从键盘输入数据
			{
				while(e!=-1)
				{
					if (sq.length==LIST_INIT_SIZE) {
						printf("%s","顺序表已满！");return 0;}
					printf("%s","请输入数据，以-1作为输入结束的标志：");
					scanf("%d",&e);
					if(e!=-1)
					{ sq.elem[++i]=e;
					  sq.length++;
					}
				}
			break;
			}
		case 'c':return 0;
	}
	return 1;
}

//输出顺序表
void outputSqlist(Sqlist sq)
{	
  for(int i=1;i<=sq.length;i++)
    {
      printf("%6d",sq.elem[i]);
    }
  printf("\n");
  printf("%s","顺序表长度是：");
  printf("%6d\n",sq.length);
}

//在顺序表中插入给定值
int insertOrderList(Sqlist &sq,int e)
{
	if (sq.length==sq.listsize){
		printf("%s","顺序表已满！不能再插入数据！"); return 0; }
  int i=sq.length;
  while (i>0 && e<sq.elem[i])         //查找插入位置并后移数据
   { sq.elem[i+1]=sq.elem[i];
     i--;
   }
  // 在i之后插入数据
  sq.elem[i+1]=e;
  sq.length++;
  return 1;
}

//以下为快速排序算法
void quickSort(Sqlist &sq)
{
	QSort(sq,1,sq.length);
}
void QSort (Sqlist &sq,int low,int high)
{
	int pivotloc=0;
	if (low<high){
		pivotloc=Partition(sq,low,high);
		QSort(sq,low,pivotloc-1);
		QSort(sq,pivotloc+1,high);
	}
}
int Partition(Sqlist &sq,int low,int high)
{
	int pivotkey=0;
	//注意，本例中，记录中只有关键字一个数据项
	sq.elem[0]=sq.elem[low];
	pivotkey=sq.elem[low];
	while (low<high) {
		while (low<high && sq.elem[high]>=pivotkey) --high;
		sq.elem[low]=sq.elem[high];
		while (low<high && sq.elem[low]<=pivotkey) ++low;
		sq.elem[high]=sq.elem[low];
	}
	sq.elem[low]=sq.elem[0];
	return low;
}
 