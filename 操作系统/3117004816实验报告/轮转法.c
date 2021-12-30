#include "stdio.h"
#include <stdint.h>
#include <conio.h>
#define getpcb(type) (type*)malloc(sizeof(type))
#define TIME 4

struct  pcb
{
	char name[10];
	int ntime;/*��Ҫ��ʱ����*/
	int rtime;/*���е�ʱ����*/
	int atime;/*�����ʱ����*/
	char state;/*����״̬*/
	struct pch *next;/*��һ���̵�λ��*/
}*ready = NULL, *p,*tail,*wait;

typedef struct pcb PCB;

sort_wait()/*��δ����ķ���ȴ����в�����*/
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


void input()/* �������̿��ƿ麯��*/
{
	int i, num;
	system("cls");/*����*/
	printf("\n ��������̺ţ�");
	scanf("%d", &num);
	for (i = 0; i < num; i++)
	{
		printf("\n ���̺�No.%d", i);
		p = getpcb(PCB);
		printf("\n�������������");
		scanf("%s", p->name);
		printf("\n����������ʱ�䣺");
		scanf("%d", &p->ntime);
		printf("\n�����뵽��ʱ�䣺");
		scanf("%d", &p->atime);
		printf("\n");
		p->rtime = 0;
		p->state = 'w';
		p->next = NULL;
		sort_wait(); /* ����sort����*/
	}
}

int circulate() /*�鿴��ǰ�Ľ�����Ŀ*/
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

disp(PCB *pr)/*����������ʾ����,������ʾ��ǰ����*/
{
	printf("\n qname \t needtime \truntime \t arrivetime \t state \n");
	printf("|%s\t", pr->name);
	printf("|%d\t", pr->ntime);
	printf("|%d\t", pr->rtime);
	printf("|%d\t", pr->atime);
	printf("|%c\t", pr->state);
	printf("\n");
}
check() /* �������̲鿴���� */
{
	PCB *pr;
	printf("\n **** ��ǰ�������еĽ�����:%s", p->name);
	disp(p);
	pr = ready;
	printf("\n ****��ǰ��������״̬Ϊ:\n"); /*��ʾ��������״̬*/
	while (pr != NULL)
	{
		disp(pr);
		pr = pr->next;
	}
	pr = wait;
	printf("\n ****��ǰ�ȴ�����״̬Ϊ:\n"); /*��ʾ�ȴ�����״̬*/
	while (pr != NULL)
	{
		disp(pr);
		pr = pr->next;
	}

}

destory()/*���ٽ���*/
{
	printf("\n ���� [%s] �����.\n", p->name);
	if (p==ready)/*��ֹʣ���һ������ʱ��Ұָ�����*/
	{
		ready = NULL;
	}
	free(p);

}



running(int h,int stime)/* �������̾�������(��������ʱ�䵽,�þ���״̬*/
{
	PCB *pr = tail;
	(p->rtime) += TIME;
	if (p->rtime >= p->ntime)
	{
		destory();
	}
	else
	{
		while (1)/*����ʱ��Ƭ�в�ֹ��һ��������Ҫ�������*/
		{
			if ((wait != NULL) && (stime+(h*TIME)) > (wait->atime))/*��ǰ���н�������һ��ʱ��Ƭ��ʱ���Ƿ��в���Ľ���*/
			{
				if (ready->next != NULL)/*�����������д��ڵ����������ϵĽ���ʱ*/
				{
					tail = wait;
					pr->next = tail;
					wait = wait->next;
				}
				else/*��һ����������һ��ʱ��Ƭʱ����ڶ�������*/
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
		if (ready == NULL)/*�������п�ʱ����ȴ�����*/
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
		printf("\n �����������������");
		ch = getchar();

	}

	printf("\n\n �����Ѿ����.\n");
	ch = getchar();
}
