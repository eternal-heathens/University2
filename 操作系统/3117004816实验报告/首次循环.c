#include "stdio.h"
#include <stdint.h>
#include <conio.h>
#define getpartition(type) (type*)malloc(sizeof(type))
#define getwork(type) (type*)malloc(sizeof(type))

typedef struct partition {
	int num;			//分区号 
	int startAdress;    //分区开始地址 
	int size;			//剩余空间 
	int state;         //状态 , 0未分配，1已分配 
	struct partition *next;
}partition, *PART;

typedef struct work
{
	int pnum;/*分区号*/
	int wnum;/*作业号*/
	int size;
	int sAdress;
	int eAdress;
}work,*WORK;

PART A[20] = { NULL };
WORK B[20] = { NULL };

int all_available_size = 640;

initialize()
{
	for (int i = 0; i < 3; i++)
	{
		A[i] = getpartition(partition);
	}
	A[0]->num = 0;
	A[0]->startAdress = 0;
	A[0]->size = 200;
	A[0]->state = 0;
	A[0]->next = A[1];
	
	for (int i = 1; i < 3; i++)
	{
		A[i]->num = i;
		A[i]->startAdress = 20 + 200 + (A[i - 1]->startAdress);
		A[i]->size = 200;
		A[i]->state = 0;
		if (i + 1 >= 3)
			A[i]->next = NULL;
		A[i]->next = A[i + 1];
	}
}

int circulate()
{
	int i;
	for (i = 0; i < 20; i++)
	{
		if (A[i] == NULL)
		{
			A[i] = getpartition(partition);
			break;
		}
	}
	return i;
}

disp(int i)
{
	printf("\n num \t startAdress \tsize \t state  \n");
	printf("|%d\t", A[i]->num);
	printf("|%d\t", A[i]->startAdress);
	printf("|%d\t", A[i]->size);
	printf("|%d\t", A[i]->state);
	printf("\n");
}

check()
{
	printf("当前各个分区情况如下：");
	for (int i = 0; i < 20; i++)
	{
		if (A[i] != NULL)
		{
			disp(i);
		}
	}
}

apply_partition(int num, int size)/*申请分配*/
{
	PART c;
	int h;
	h = circulate();
	for (int i = 0; i < 20; i++)
	{
		if (A[i]!=NULL&&A[i]->state == 0&&size <= A[i]->size)
		{

			A[h]->size = size;
			A[h]->startAdress = A[i]->startAdress;
			A[h]->state = 1;
			A[h - 1]->next = A[h];
			A[h]->next = A[h + 1];

			c = A[h];
			A[i]->size -=size;
			A[i]->state = 0;
			A[i]->startAdress += size;
			
			for (int z = h; z > i; z--)
			{
				A[z] = A[z - 1];
				A[z]->num++;
 				if (z == h)
				{
					A[z]->next = c->next;
				}
			}

			A[i] = c;
			A[i]->num = i;
			if (i - 1 >= 0)
			{
				A[i - 1]->next = A[i];
				A[i]->next = A[i + 1];
			}

			for (int j = 0; j < 20; j++)
			{
				if (B[j] == NULL)
				{
					B[j] = getwork(work);
					B[j]->pnum = i;
					B[j]->wnum = num;
					B[j]->size = size;
					B[j]->sAdress = A[i]->startAdress;
					B[j]->eAdress = A[i]->startAdress + size;
					break;
				}
			}

			break;
		}

	}
}

destory(int j,int num)
{
	printf("作业%d已销毁\n", num);
	free(B[j]);
	B[j] = NULL;
}

merge()
{

	for (int j = 0; j < 20; j++)
	{
		if (A[j] != NULL && A[j+1]!=NULL&&A[j]->state == 0)
		{
			if (A[j]->startAdress+A[j]->size == A[j+1]->startAdress)
			{
				A[j+1]->size += A[j]->size;
				if (j - 1 >= 0) A[j - 1]->next = A[j];
				A[j + 1]->startAdress = A[j]->startAdress;
				for (int z = j; A[z]!=NULL; z++)
				{
					A[z] = A[z + 1];
					if (A[z] != NULL)
					{
						A[z]->num--;
					}
				}
				j = 0;
			}					
		}

	}

}

release_partition(int num)/*释放空间*/
{
	for (int j = 0; j < 20; j++)
	{
		if (B[j]!=NULL&&B[j]->wnum == num)
		{
			for (int i = 0; i < 20; i++)
			{
				if (A[i]!=NULL&&B[j]->pnum == A[i]->num)
				{
					A[i]->state = 0;
					destory(j,num);
					merge();
					break;
				}
			}
		}
	}
}

input()
{
	int i,num,size;
	while (1)
	{
		printf("\n请输入需要执行的操作:1.申请2.释放3.退出\n");
		scanf("%d", &i);
		if (i == 1)
		{
			printf("\n请输入作业号：\n");
			scanf("%d", &num);
			printf("\n请输入所需要的大小:\n");
			scanf("%d", &size);
			apply_partition(num, size);
			check();
		}
		if (i == 2)
		{
			printf("\n请输入作业号：\n");
			scanf("%d", &num);
			release_partition(num);
			check();
		}
		if (i == 3)
		{
			break;
		}
	}
}

void main()
{
	initialize();
	input();
}