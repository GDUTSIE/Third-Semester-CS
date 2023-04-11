// 3-16_train.cpp : 定义控制台应用程序的入口点。
//

//将车厢存入一个循环队列中，本程序利用随机函数来生成车厢序列
//调度时，每次将一个车厢出队并入栈，再判断栈顶是否为“S”，如果是则出栈并入队，否则下一个
//直到整个队列扫描完成后，将栈中的所有元素（应该均是H）全部出栈并入队。
//这时，队列则是按题目要求排列好的车厢序列。

#include "stdafx.h"
#include <iostream>
#include <iomanip>    //for 输出控制setw(...)，在cout中使用。

//产生随机数
#include <stdlib.h>
#include <time.h>

#define STACK_INIT_SIZE  60
#define STACKINCREMENT  10
using namespace std;

//循环字符队列
#define MAXQSIZE  50
struct SqQueue{
	char *base;
	int front;
	int rear;
};

// 字符栈
struct SqStack {  
	char * base;
	char * top;
	int stacksize;
};

//函数声明系列
int initCarriages(SqQueue &,int);
int initQueue(SqQueue &);
int enQueue(SqQueue &,char);
char deQueue(SqQueue &);    

int initStack(SqStack &);
int push(SqStack &,char);
char pop(SqStack &);

void printCar(SqQueue);
void dispatched(SqQueue &);

void main()
{
	int n;
	SqQueue carriages;        //车厢队列
	
	//键盘输入容错控制
	do{
		cout<<"设置车厢总数 n ( n<"<<MAXQSIZE<<") ：";
		cin>>n;			
		if (cin.fail()){			
			cin.clear();
			cin.ignore();
			while(cin.get()!='\n');	
		}
		else if (n<MAXQSIZE && n>0) break;
		cout<<"输入错误，重新输入！\n\n"; 
	}while(1);
	
	initCarriages(carriages,n);  //初始化待调度的车厢队列
	
	//开始调度
	dispatched(carriages);
	cout<<"\n调度后：";
	printCar(carriages);    //输出

	//屏幕停留控制
	char a;
	cout<<"\n输入任意字母结束程序......";
	cin>>a;	
}

int initCarriages(SqQueue &sqC,int n)
{
	initQueue(sqC);int s,i=0;

	srand((unsigned)time(0));   //取本机时间来设置随机种子	
	while(i<n)
	{
		s=rand()%2+1;               //随机生成1和2
		switch (s){
			case 1: {enQueue(sqC,'H');i++;break;}
			case 2: {enQueue(sqC,'S');i++;break;}
		}
	}
	printCar(sqC);return 1;
}

int initQueue(SqQueue &sq)
{//构造一个空的顺序队列
	sq.base=(char *)malloc(MAXQSIZE*sizeof(char));
	if (!sq.base) return 0;
	sq.front=sq.rear=0;
	return 1;
}

int enQueue(SqQueue &sq,char e)
{//插入元素e到Q的队尾	
	if ((sq.rear+1)%MAXQSIZE==sq.front) { cout<<"队列满"<<'\n';return 0;}
	sq.base[sq.rear]=e;
	sq.rear=(sq.rear+1)%MAXQSIZE;
	return 1;
}

char deQueue(SqQueue &sqq)
{//从队头删除元素，并返回被删的字符
 //对课本的出队算法稍作了修改	
	if (sqq.front==sqq.rear) {cout<<"队列空"<<'\n';return 0;}	
	char e=sqq.base[sqq.front];
	sqq.front=(sqq.front+1)%MAXQSIZE;
	return e;
}

int initStack(SqStack &stack)
{ //初始化一个空栈
	stack.base=(char *)malloc(STACK_INIT_SIZE*sizeof(char));
	if (!stack.base) return 0;
	stack.top=stack.base;
	stack.stacksize=STACK_INIT_SIZE;
	return 1;
}

int push(SqStack &ss,char e)
{
	if (ss.top-ss.base>=ss.stacksize){ //栈满，追加存储空间
		ss.base=(char *)realloc(ss.base,(ss.stacksize+STACKINCREMENT)*sizeof(char));
		if (!ss.base) return 0;
		ss.top=ss.base + ss.stacksize;
		ss.stacksize += STACKINCREMENT;
	}
	*ss.top++=e;   //插入后，top指针上移一格
	return 1;
}

char pop(SqStack &ss)
{
	if (ss.top==ss.base) { cout<<"栈空"<<'\n';return 0;}	
	return *--ss.top;  //下移top指针，再返回所指的值
}

void printCar(SqQueue sqq)
{ //输出车厢队列
	int n=0;
	cout<<'\n'<<"车厢队列如下：\n";
	if (sqq.front!=sqq.rear) {		
		for(int i=sqq.front;i!=sqq.rear;i=(i+1)%MAXQSIZE)  //循环队列
		{cout<<setw(3)<<sqq.base[i];
			n++;
			//cout<<n;
		}
		cout<<'\n'<<"队列长度为："<<n<<'\n';
	}
	else cout<<"\n空队列\n"; 
}

void dispatched(SqQueue &sqq)
{ //对车厢队列按题目要求进行重排，将全部S調到H的前面
  //用一个栈来完成重排工作
  //每次将一个车厢出队并入栈，再判断栈顶是否为“S”，如果是则出栈并入队，否则下一个
  //直到整个队列扫描完成后，将栈中的所有元素（应该均是H）全部出栈并入队。
	SqStack dpS;            //dp是dispatch的缩写	
	int p=sqq.rear;         //记录下初始时的队尾，作为扫描结束的位置
	initStack(dpS);
	
	//由于是模拟火车沿铁轨行走，所以出队的元素必须先入栈再出栈
	while((sqq.front)%MAXQSIZE<p)  
	{
		push(dpS,deQueue(sqq));
		if (*(dpS.top-1)=='S') enQueue(sqq,pop(dpS));		
	}
	while (dpS.top>dpS.base)   //将栈中的剩余车厢全部出栈并入队
			enQueue(sqq,pop(dpS));
}

