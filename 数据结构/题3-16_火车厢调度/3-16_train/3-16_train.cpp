// 3-16_train.cpp : �������̨Ӧ�ó������ڵ㡣
//

//���������һ��ѭ�������У�����������������������ɳ�������
//����ʱ��ÿ�ν�һ��������Ӳ���ջ�����ж�ջ���Ƿ�Ϊ��S������������ջ����ӣ�������һ��
//ֱ����������ɨ����ɺ󣬽�ջ�е�����Ԫ�أ�Ӧ�þ���H��ȫ����ջ����ӡ�
//��ʱ���������ǰ���ĿҪ�����кõĳ������С�

#include "stdafx.h"
#include <iostream>
#include <iomanip>    //for �������setw(...)����cout��ʹ�á�

//���������
#include <stdlib.h>
#include <time.h>

#define STACK_INIT_SIZE  60
#define STACKINCREMENT  10
using namespace std;

//ѭ���ַ�����
#define MAXQSIZE  50
struct SqQueue{
	char *base;
	int front;
	int rear;
};

// �ַ�ջ
struct SqStack {  
	char * base;
	char * top;
	int stacksize;
};

//��������ϵ��
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
	SqQueue carriages;        //�������
	
	//���������ݴ����
	do{
		cout<<"���ó������� n ( n<"<<MAXQSIZE<<") ��";
		cin>>n;			
		if (cin.fail()){			
			cin.clear();
			cin.ignore();
			while(cin.get()!='\n');	
		}
		else if (n<MAXQSIZE && n>0) break;
		cout<<"��������������룡\n\n"; 
	}while(1);
	
	initCarriages(carriages,n);  //��ʼ�������ȵĳ������
	
	//��ʼ����
	dispatched(carriages);
	cout<<"\n���Ⱥ�";
	printCar(carriages);    //���

	//��Ļͣ������
	char a;
	cout<<"\n����������ĸ��������......";
	cin>>a;	
}

int initCarriages(SqQueue &sqC,int n)
{
	initQueue(sqC);int s,i=0;

	srand((unsigned)time(0));   //ȡ����ʱ���������������	
	while(i<n)
	{
		s=rand()%2+1;               //�������1��2
		switch (s){
			case 1: {enQueue(sqC,'H');i++;break;}
			case 2: {enQueue(sqC,'S');i++;break;}
		}
	}
	printCar(sqC);return 1;
}

int initQueue(SqQueue &sq)
{//����һ���յ�˳�����
	sq.base=(char *)malloc(MAXQSIZE*sizeof(char));
	if (!sq.base) return 0;
	sq.front=sq.rear=0;
	return 1;
}

int enQueue(SqQueue &sq,char e)
{//����Ԫ��e��Q�Ķ�β	
	if ((sq.rear+1)%MAXQSIZE==sq.front) { cout<<"������"<<'\n';return 0;}
	sq.base[sq.rear]=e;
	sq.rear=(sq.rear+1)%MAXQSIZE;
	return 1;
}

char deQueue(SqQueue &sqq)
{//�Ӷ�ͷɾ��Ԫ�أ������ر�ɾ���ַ�
 //�Կα��ĳ����㷨�������޸�	
	if (sqq.front==sqq.rear) {cout<<"���п�"<<'\n';return 0;}	
	char e=sqq.base[sqq.front];
	sqq.front=(sqq.front+1)%MAXQSIZE;
	return e;
}

int initStack(SqStack &stack)
{ //��ʼ��һ����ջ
	stack.base=(char *)malloc(STACK_INIT_SIZE*sizeof(char));
	if (!stack.base) return 0;
	stack.top=stack.base;
	stack.stacksize=STACK_INIT_SIZE;
	return 1;
}

int push(SqStack &ss,char e)
{
	if (ss.top-ss.base>=ss.stacksize){ //ջ����׷�Ӵ洢�ռ�
		ss.base=(char *)realloc(ss.base,(ss.stacksize+STACKINCREMENT)*sizeof(char));
		if (!ss.base) return 0;
		ss.top=ss.base + ss.stacksize;
		ss.stacksize += STACKINCREMENT;
	}
	*ss.top++=e;   //�����topָ������һ��
	return 1;
}

char pop(SqStack &ss)
{
	if (ss.top==ss.base) { cout<<"ջ��"<<'\n';return 0;}	
	return *--ss.top;  //����topָ�룬�ٷ�����ָ��ֵ
}

void printCar(SqQueue sqq)
{ //����������
	int n=0;
	cout<<'\n'<<"����������£�\n";
	if (sqq.front!=sqq.rear) {		
		for(int i=sqq.front;i!=sqq.rear;i=(i+1)%MAXQSIZE)  //ѭ������
		{cout<<setw(3)<<sqq.base[i];
			n++;
			//cout<<n;
		}
		cout<<'\n'<<"���г���Ϊ��"<<n<<'\n';
	}
	else cout<<"\n�ն���\n"; 
}

void dispatched(SqQueue &sqq)
{ //�Գ�����а���ĿҪ��������ţ���ȫ��S�{��H��ǰ��
  //��һ��ջ��������Ź���
  //ÿ�ν�һ��������Ӳ���ջ�����ж�ջ���Ƿ�Ϊ��S������������ջ����ӣ�������һ��
  //ֱ����������ɨ����ɺ󣬽�ջ�е�����Ԫ�أ�Ӧ�þ���H��ȫ����ջ����ӡ�
	SqStack dpS;            //dp��dispatch����д	
	int p=sqq.rear;         //��¼�³�ʼʱ�Ķ�β����Ϊɨ�������λ��
	initStack(dpS);
	
	//������ģ������������ߣ����Գ��ӵ�Ԫ�ر�������ջ�ٳ�ջ
	while((sqq.front)%MAXQSIZE<p)  
	{
		push(dpS,deQueue(sqq));
		if (*(dpS.top-1)=='S') enQueue(sqq,pop(dpS));		
	}
	while (dpS.top>dpS.base)   //��ջ�е�ʣ�೵��ȫ����ջ�����
			enQueue(sqq,pop(dpS));
}

