#include "stdio.h"
#include <stdint.h>
#include <conio.h>
#define getpcb(type) (type*)malloc(sizeof(type))
#define TIME 4

struct  pcb
{
	char name[10];
	int ntime;
	int rtime;
	int atime;
	char state;
	struct pch *next;
}*ready = NULL, *p, *tail, *wait,*ready2 = NULL,*tail2 = NULL;

typedef struct pcb PCB;

sort_wait()
{
	PCB *first, *second;
	int insert = 0;
	if ((wait == NULL) || (p->atime) < (p->atime))
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

int circulate_first() /*查看当前的进程数目*/
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

int circulate_second() /*查看当前的进程数目*/
{
	int  n = 0;
	PCB *pr = ready2;
	while (pr != NULL)
	{
		n++;
		tail2 = pr;
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
	printf("\n ****当前第一就绪队列状态为:\n"); /*显示第一就绪队列状态*/
	while (pr != NULL)
	{
		disp(pr);
		pr = pr->next;
	}
	pr = ready2;
	printf("\n ****当前第二就绪队列状态为:\n"); /*显示第二就绪队列状态*/
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
	if (p == ready)/*防止剩最后一个进程时的野指针情况*/
	{
		ready = NULL;
	}
	if (p == ready2)
	{
		ready2 = NULL;
	}
	free(p);
	p = NULL;
}



running_first(int h, int stime)/* 建立进程就绪函数(进程运行时间到,置就绪状态*/
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
			if ((wait != NULL) && (stime + (h*TIME)) > (wait->atime))/*当前运行进程运行一个时间片的时候是否有插入的进程*/
			{
				if (ready!=NULL&&ready->next != NULL)/*就绪队列中有大于等于两个以上的进程时*/
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
				}

			}
			else break;
		}
		if (ready2 == NULL)
		{
			ready2 = p;
			tail2 = p;
		}
		else
		{
			tail2->next = p;
			tail2 = p;
		}
		p->state = 'w';
		printf("current_time:%d", stime + (h*TIME)); /*起始时间加运行时间*/
	}
}


int running_second(int h, int stime,int insert)/* 建立进程就绪函数(进程运行时间到,置就绪状态*/
{

	while (1)/*单个时间片中不止有一个进程需要加入队列*/
	{
		if ((wait != NULL) && (stime + (h*TIME)) > (wait->atime))/*当前运行进程运行一个时间片的时候是否有插入的进程*/
		{
			if (ready == NULL)
			{
				ready = wait;
				tail = wait;
				wait = wait->next;
				tail->next = NULL;
			}
			else
			{
				tail->next = wait;
				tail = wait;
				wait = wait->next;
				tail->next = NULL;
			}
			p->rtime +=( ready->atime -(( (h-1) * TIME) + stime));
			insert = ((h*TIME)+stime-ready->atime);
		}
		else break;
	}
	
	if (ready == NULL) p->rtime += TIME;
	if (p->rtime >= p->ntime)
	{
		destory();
	}
	else
	{	
		if (p != ready2)
		{
			tail2->next = p;
		}
		p->state = 'w';
		printf("current_time:%d", stime + (h*TIME)); /*起始时间加运行时间*/
	}
	return insert;
}

void main()
{
	/*
	* @len1、len2 第一、第二队列进程个数
	* @h 请求时间片数
	* @insert 第二队列进程运行时第一队列有进程加入，中断第二队列并记录该时间片还剩多少时间
	*/
	int len1,len2, h = 0, stime,insert = 0;/*,time = 4*/
	char ch;
	input();
	len1 = circulate_first();
	len2 = circulate_second();
	while (wait!=NULL||ready!=NULL)
	{
		if (ready == NULL)/*就绪队列空时插入等待队列队首元素*/
		{
			if (ready2 != NULL)
			{
				while (ready2 != NULL&&ready == NULL)/*等待队列有进程未到达，先执行第二队列*/
				{
					h++;

					printf("\n The execute number:%d \n", h);
					p = ready2;
					if (ready2->next != NULL)
					{

						ready2 = p->next;
						p->next = NULL;
					}
					p->state = 'W';
					check();
					insert = running_second(h, stime,insert);
					if (ready2 != NULL)
					{
						len2 = circulate_second();
					}
					printf("\n 按任意键继续···");
					ch = getchar();
				}
			}
			else
			{
				ready = wait;
				tail = ready;
				wait = wait->next;
				ready->next = NULL;
				stime = ready->atime;
				h = 0;
			}
		}
		if (insert != 0)/*第二队列进程运行时第一队列有进程加入，中断第二队列并从中断时刻开始运行第一队列*/
		{
			stime -= insert;
			insert = 0;
		}
		h++;
		printf("\n The execute number:%d \n", h);
		if (ready != NULL)
		{
			p = ready;
			ready = p->next;
			p->next = NULL;			
		}
		if(p!=NULL)
		{
			p->state = 'W';
			check();
			running_first(h, stime);
			if (ready != NULL)
			{
				len1 = circulate_first();
			}
			printf("\n 按任意键继续···");
			ch = getchar();
		}
	}
	while (ready2 != NULL)/*当等待队列和第一队列都为空时*/
	{
		h++;
		printf("\n The execute number:%d \n", h);
		p = ready2;
		if (ready2->next != NULL)
		{
			ready2 = p->next;
			p->next = NULL;
		}
		p->state = 'R';
		check();
		running_second(h, stime,insert);
		if (ready2 != NULL)
		{
			len2 = circulate_second();
		}
		printf("\n 按任意键继续···");
		ch = getchar();
	}

	printf("\n\n 进程已经完成.\n");
	ch = getchar();
}