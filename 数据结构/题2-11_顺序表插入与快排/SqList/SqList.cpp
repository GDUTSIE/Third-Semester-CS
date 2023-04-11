// SqList.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include <stdafx.h>
#include <stdio.h>    
#include <stdlib.h>   // for �ڴ���亯��
#include <iostream>   // �ļ�I/O��
#include <fstream>
using namespace std;

#define LIST_INIT_SIZE  100
#define LISTINCREMENT   10

//����˳���
typedef struct Sqlist{
	int *elem;
	int length;
	int listsize;
}Sqlist;

//���õ��ĺ�������(����ʡ���˱�����)
int InitList_Sq(Sqlist &);
int inputData(Sqlist &);
//��������
void quickSort(Sqlist &);
void QSort (Sqlist &,int,int);
int Partition(Sqlist &,int,int);
//�����㷨��������
int insertOrderList(Sqlist &,int);    //��˳����в������ֵ
void outputSqlist(Sqlist);             //���˳���

void main()
{
	Sqlist sq;
    int x=0;
	
	//������˳����������
	InitList_Sq(sq);
	inputData(sq);
		outputSqlist(sq);

	printf("%s\n","��������");
	quickSort(sq);
		outputSqlist(sq);

	printf("%s","���������x��");
	scanf("%d",&x);
	insertOrderList(sq,x);
	outputSqlist(sq);

	//����Ϊ���������־�� 
	printf("%s","\n\n");
	printf("%s","GAME OVER......\n");

	//��Ļͣ������
	int a=0;
	scanf("%d",&a);
}
//��ʼ��˳���
int InitList_Sq(Sqlist &sq)
{
	sq.elem=(int *)malloc(LIST_INIT_SIZE*sizeof(int));
	if (! sq.elem) return 0;

	sq.length=0;
	sq.listsize=LIST_INIT_SIZE;
	return 1;
}
//��˳�����������
int inputData(Sqlist &sq)
{
	int e=0,i=0;  
	sq.elem[0]=0;  //0��λ����

	char choice=' ';
	do{
		cout<<"��ѡ��������Դ(ֻ��Сд��ĸ)��a---�ӡ�dataForTest.txt���ļ���ȡ�� b---�����ֹ����룻c---û���ݣ�"<<'\n';
		cin>>choice;
	}while (choice!='a'&& choice!='b'&& choice!='c');

	//�ļ���ʽ˵����txt�ļ�������֮���ÿո���������뻻�У������������ַ���
	//�ԡ�-1����Ϊ������־
	switch(choice){
		case 'a': //���ļ���������
			{ ifstream fin("dataForTest.txt");
			do{
				fin>>e;
				if (e!=-1) {sq.elem[++i]=e;sq.length++;}
				else break;
			}while(sq.length<sq.listsize);
			break;
			}
		case 'b': //�Ӽ�����������
			{
				while(e!=-1)
				{
					if (sq.length==LIST_INIT_SIZE) {
						printf("%s","˳���������");return 0;}
					printf("%s","���������ݣ���-1��Ϊ��������ı�־��");
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

//���˳���
void outputSqlist(Sqlist sq)
{	
  for(int i=1;i<=sq.length;i++)
    {
      printf("%6d",sq.elem[i]);
    }
  printf("\n");
  printf("%s","˳������ǣ�");
  printf("%6d\n",sq.length);
}

//��˳����в������ֵ
int insertOrderList(Sqlist &sq,int e)
{
	if (sq.length==sq.listsize){
		printf("%s","˳��������������ٲ������ݣ�"); return 0; }
  int i=sq.length;
  while (i>0 && e<sq.elem[i])         //���Ҳ���λ�ò���������
   { sq.elem[i+1]=sq.elem[i];
     i--;
   }
  // ��i֮���������
  sq.elem[i+1]=e;
  sq.length++;
  return 1;
}

//����Ϊ���������㷨
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
	//ע�⣬�����У���¼��ֻ�йؼ���һ��������
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
 