#include "stdio.h"
#include <stdint.h>
#include <conio.h>

#define  getjcb(type)(type*)malloc(sizeof(type))
typedef struct jcb {
	char name[10];   //作业名 
	int atime;   //开始时刻 
	int ntime;    //所需时间 
	int ftime;  //完成时刻
	int needMemory;  //所需内存
	int needSource;  //所需资源(磁带机台数) 
	char state;      //状态 
	struct jcb *next;//下一个指针 
}jcb, *JCB;

JCB wait, ready = NULL, p,fast, n2[10] = { NULL };/*n2: 在运行的队列 ready:已到达的队列 wait:未到达到达时间的队列*/
int time = 0, Memory = 100, Source = 5;



sort_wait()
{
	jcb *first, *second;
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

void input()/* 建立作业控制块函数*/
{
	int i, num;
	system("cls");/*清屏*/
	printf("\n 请输入总共作业号数目：");
	scanf("%d", &num);
	for (i = 0; i < num; i++)
	{
		printf("\n 作业号No.%d", i);
		p = getjcb(jcb);
		printf("\n请输入作业名：");
		scanf("%s", p->name);
		printf("\n请输入到达时间：");
		scanf("%d", &p->atime);
		printf("\n请输入所需时间：");
		scanf("%d", &p->ntime);
		printf("\n请输入所需内存：");
		scanf("%d", &p->needMemory);
		printf("\n请输入所需资源（打印机）：");
		scanf("%d", &p->needSource);
		printf("\n");
		p->ftime = 0;
		p->state = 'w';
		p->next = NULL;
		sort_wait(); /* 调用sort函数*/
	}
}
disp(jcb *pr)/*建立进程显示函数,用于显示当前进程*/
{
	printf("\n qname \t arrivetime \tneedtime \t finishtime \t needMemory \t needSource \t state \n");
	printf("|%s\t", pr->name);
	printf("|%d\t", pr->atime);
	printf("|%d\t", pr->ntime);
	printf("|%d\t", pr->ftime);
	printf("|%d\t", pr->needMemory);
	printf("|%d\t", pr->needSource);
	printf("|%c\t", pr->state);
	printf("\n");
}
check() /* 建立进程查看函数 */
{
	jcb *pr;
	for (int i = 0; i < 10; i++)
	{
		if (n2[i] != NULL)
		{
			printf("\n **** 当前正在运行的进程是:%s", n2[i]->name);/*正在运行的队列*/
			disp(n2[i]);
		}

	}
	printf("\n ****当前到达等待队列状态为:\n"); /*显示到达等待队列状态*/
	pr = ready;
	if (ready != NULL)
	{
		while (pr != NULL)
		{
			disp(pr);
			pr = pr->next;
		}
	}
	printf("\n ****当前未到达队列状态为:\n"); /*显示未到达队列状态*/
	pr = wait;
	if (wait != NULL)
	{
		while (pr != NULL)
		{
			disp(pr);
			pr = pr->next;
		}
	}
}

int circulation()
{
	int i, min = 100, target = 0;
	for (i = 0; i < 10; i++)
	{
		if (n2[i] != NULL)
		{
			if ((n2[i]->atime) + (n2[i]->ntime) < min)
			{
				min = (n2[i]->atime) + (n2[i]->ntime);
				target = i;
			}
			time = min;
		}
	}
	return target;
}
p_jcb(JCB p2)/*将作业调入CPU*/
{
	int i = 0, min, target;
	for (i = 0; i < 10; i++)
	{
		if (n2[i] == NULL)
		{
			n2[i] = p2;
			break;
		}
	}

}

destory(JCB A)
{
	printf("进程%s已完成", A->name);
	free(A);
}

running()/*将等待队列中到达的加进等待就绪队列*/
{
	JCB p3 = ready;
	while (wait != NULL && wait->atime < time)
	{
		if (ready == NULL)
		{
			ready = wait;
			wait = wait->next;
			ready->next = NULL;
			p3 = ready;
		}
		else
		{
			while (p3->next != NULL)
			{
				p3 = p3->next;
			}
			p3->next = wait;
			wait = wait->next;
			p3->next->next = NULL;
		}
	}
}

v_jcb(int target)/*将作业执行，释放内存*/
{
	if (n2[target] != NULL)
	{
		Memory += n2[target]->needMemory;
		Source += n2[target]->needSource;
		n2[target]->ftime = time;
		running();
		check();
		destory(n2[target]);
		n2[target] = NULL;
	}
}

sort_fast2()
{
	jcb *first, *second;
	int insert = 0;
	if ((fast == NULL) || (p->ntime) < (fast->ntime))
	{
		p->next = fast;
		fast = p;
	}
	else
	{
		first = fast;
		second = first->next;
		while (second != NULL)
		{
			if ((p->ntime) < (second->ntime))
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

sort_fast()
{
	while (ready != NULL)
	{
		p = ready;
		ready = ready->next;
		p->next = NULL;
		sort_fast2();
	}
	ready = fast;
}


void main()
{
	JCB p2 = NULL, p3 = NULL;
	int i, target = 0, insert = 0;
	char ch;
	input();
	while (wait != NULL || ready != NULL || n2[target] != NULL)
	{
		running();
		if (ready == NULL)/*若就绪队列和运行队列都无作业，将未加入的提前加入*/
		{
			for (i = 0; i < 10; i++)
			{
				if (n2[i] != NULL)
					insert = 1;
			}
			if (wait != NULL && insert == 0)
			{
				ready = wait;
				wait = wait->next;
				ready->next = NULL;
				time = ready->atime + ready->ntime;
				running();
			}
		}

	
		if (ready != NULL)
		{
			p2 = ready;
			if (ready != NULL && ready->needMemory <= Memory && ready->needSource <= Source)
			{
				while (ready != NULL && ready->needMemory <= Memory && ready->needSource <= Source)/*确认第一个资源不足的作业*/
				{
					p2 = ready;
					ready = p2->next;
					p2->next = NULL;
					p_jcb(p2);
					Memory -= (p2->needMemory);
					Source -= (p2->needSource);
				}
			}
			p3 = ready;
			if (p2 == ready) p3 = ready->next;
			while (p3 != NULL)
			{
				if (p3->needMemory < Memory&&p3->needSource < Source)/*查找后面是否有符合的资源利用的作业*/
				{
					p2->next = p3->next;
					p2 = p3;
					p3 = p2->next;
					p2->next = NULL;
					p_jcb(p2);
					Memory -= (p2->needMemory);
					Source -= (p2->needSource);
					p2 = p3;
				}
				else
				{
					p3->atime = time;
					p2 = p3;
					p3 = p3->next;
				}
			}
			sort_fast();
		}
		check();
		target = circulation();
		v_jcb(target);
		target = circulation();
		
		fast = NULL;

	}
}