#include "stdio.h"
#include <stdint.h>
#include <conio.h>
#define getpcb(type) (type*)malloc(sizeof(type))
#define TIME 4

struct  pcb
{
	char name[10];
	int ntime;/*需要的时间数*/
	int rtime;/*运行的时间数*/
	int atime;/*到达的时间数*/
	char state;/*运行状态*/
	struct pch *next;/*下一进程的位置*/
}*ready = NULL, *p,*tail,*wait;

typedef struct pcb PCB;

sort_wait()/*将未到达的放入等待队列并排序*/
{
	PCB *first, *second;
	int insert = 0;
	if ((wait == NULL) || (p->atime) < (wait->atime))
	{
		p->next = wait;
		wait = p;
	}
	else
	{
		first = wait;
		second = first->next;
		while (second != NULL)
		{
			if ((p->atime) < (second->atime))
			{
				p->next = second;
				first->next = p;
				second = NULL;
				insert = 1;
			}
			else
			{
				first = first->next;
				second = second->next;
			}
		}
		if (insert == 0) first->next = p;
	}
}


void input()/* 建立进程控制块函数*/
{
	int i, num;
	system("cls");/*清屏*/
	printf("\n 请输入进程号？");
	scanf("%d", &num);
	for (i = 0; i < num; i++)
	{
		printf("\n 进程号No.%d", i);
		p = getpcb(PCB);
		printf("\n请输入进程名：");
		scanf("%s", p->name);
		printf("\n请输入所需时间：");
		scanf("%d", &p->ntime);
		printf("\n请输入到达时间：");
		scanf("%d", &p->atime);
		printf("\n");
		p->rtime = 0;
		p->state = 'w';
		p->next = NULL;
		sort_wait(); /* 调用sort函数*/
	}
}

int circulate() /*查看当前的进程数目*/
{
	int  n = 0;
	PCB *pr = ready;
	while (pr != NULL)
	{
		n++;
		tail = pr;
		pr = pr->next;
		
	}
	return(n);
}

disp(PCB *pr)/*建立进程显示函数,用于显示当前进程*/
{
	printf("\n qname \t needtime \truntime \t arrivetime \t state \n");
	printf("|%s\t", pr->name);
	printf("|%d\t", pr->ntime);
	printf("|%d\t", pr->rtime);
	printf("|%d\t", pr->atime);
	printf("|%c\t", pr->state);
	printf("\n");
}
check() /* 建立进程查看函数 */
{
	PCB *pr;
	printf("\n **** 当前正在运行的进程是:%s", p->name);
	disp(p);
	pr = ready;
	printf("\n ****当前就绪队列状态为:\n"); /*显示就绪队列状态*/
	while (pr != NULL)
	{
		disp(pr);
		pr = pr->next;
	}
	pr = wait;
	printf("\n ****当前等待队列状态为:\n"); /*显示等待队列状态*/
	while (pr != NULL)
	{
		disp(pr);
		pr = pr->next;
	}

}

destory()/*销毁进程*/
{
	printf("\n 进程 [%s] 已完成.\n", p->name);
	if (p==ready)/*防止剩最后一个进程时的野指针情况*/
	{
		ready = NULL;
	}
	free(p);

}



running(int h,int stime)/* 建立进程就绪函数(进程运行时间到,置就绪状态*/
{
	PCB *pr = tail;
	(p->rtime) += TIME;
	if (p->rtime >= p->ntime)
	{
		destory();
	}
	else
	{
		while (1)/*单个时间片中不止有一个进程需要加入队列*/
		{
			if ((wait != NULL) && (stime+(h*TIME)) > (wait->atime))/*当前运行进程运行一个时间片的时候是否有插入的进程*/
			{
				if (ready->next != NULL)/*就绪队列中有大于等于两个以上的进程时*/
				{
					tail = wait;
					pr->next = tail;
					wait = wait->next;
				}
				else/*第一个进程运行一个时间片时加入第二个进程*/
				{
					tail = wait;
					wait = wait->next;
					tail->next = NULL;
					ready = tail;
					ready->next = p;
				}

			}
			else break;
		}
		if (p!=ready)
		{
			tail->next = p;
		}
		p->state = 'w';
		printf("current_time:%d", stime + (h*TIME));
	}
}
/***
 running_test(int*h3, int *stime3, int time)
{
	PCB *pr = tail;
	(p->rtime) += time;
	if (p->rtime >= p->ntime)
	{
		destory();		
		if (p->rtime - p->ntime < 4)
		{
			check_start(h3, stime3);
			running(h3, stime3, (p->rtime) - (p->ntime));
		}
		
	}
	else
	{
		while (1)
		{
			if ((wait != NULL) && (*stime3 + (*h3*TIME)) > (wait->atime))
			{
				if (ready->next != NULL)
				{
					tail = wait;
					pr->next = tail;
					wait = wait->next;
				}
				else
				{
					tail = wait;
					wait = wait->next;
					tail->next = NULL;
					ready = tail;
					ready->next = p;
				}

			}
			else break;
		}
		if (p != ready)
		{
			tail->next = p;
		}
		p->state = 'w';
		printf("current_time:%d", *stime3 + (*h3*TIME));
	}
}
***/

/***
check_start(int *h2, int *stime2)
{
	if (ready == NULL)
	{
		ready = wait;
		tail = ready;
		wait = wait->next;
		ready->next = NULL;
		*stime2 = ready->atime;
		*h2 = 0;
	}
	*h2++;
	printf("\n The execute number:%d \n", *h2);
	p = ready;
	if (ready->next != NULL)
	{
		ready = p->next;
		p->next = NULL;
	}
	p->state = 'R';
	check();
}
***/

void main()
{
	int len, h = 0, stime;/***,time = 4***/
	char ch;
	input();
	len = circulate();
	while (wait!=NULL||ready!=NULL)
	{
		if (ready == NULL)/*就绪队列空时插入等待队列*/
		{
			ready = wait;
			tail = ready;
			wait = wait->next;
			ready->next = NULL;
			stime = ready->atime;
			h = 0;
		}
		h++;
		printf("\n The execute number:%d \n", h);
		p = ready;
		if (ready->next != NULL)
		{
			ready = p->next;
			p->next = NULL;
		}
		p->state = 'R';
		check();
		running (h,stime);
		if (ready!=NULL)
		{
			len = circulate();
		}
		printf("\n 按任意键继续···");
		ch = getchar();

	}

	printf("\n\n 进程已经完成.\n");
	ch = getchar();
}
