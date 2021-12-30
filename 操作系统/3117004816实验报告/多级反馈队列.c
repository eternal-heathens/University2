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

int circulate_first() /*�鿴��ǰ�Ľ�����Ŀ*/
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

int circulate_second() /*�鿴��ǰ�Ľ�����Ŀ*/
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
	printf("\n ****��ǰ��һ��������״̬Ϊ:\n"); /*��ʾ��һ��������״̬*/
	while (pr != NULL)
	{
		disp(pr);
		pr = pr->next;
	}
	pr = ready2;
	printf("\n ****��ǰ�ڶ���������״̬Ϊ:\n"); /*��ʾ�ڶ���������״̬*/
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
	if (p == ready)/*��ֹʣ���һ������ʱ��Ұָ�����*/
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



running_first(int h, int stime)/* �������̾�������(��������ʱ�䵽,�þ���״̬*/
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
			if ((wait != NULL) && (stime + (h*TIME)) > (wait->atime))/*��ǰ���н�������һ��ʱ��Ƭ��ʱ���Ƿ��в���Ľ���*/
			{
				if (ready!=NULL&&ready->next != NULL)/*�����������д��ڵ����������ϵĽ���ʱ*/
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
		printf("current_time:%d", stime + (h*TIME)); /*��ʼʱ�������ʱ��*/
	}
}


int running_second(int h, int stime,int insert)/* �������̾�������(��������ʱ�䵽,�þ���״̬*/
{

	while (1)/*����ʱ��Ƭ�в�ֹ��һ��������Ҫ�������*/
	{
		if ((wait != NULL) && (stime + (h*TIME)) > (wait->atime))/*��ǰ���н�������һ��ʱ��Ƭ��ʱ���Ƿ��в���Ľ���*/
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
		printf("current_time:%d", stime + (h*TIME)); /*��ʼʱ�������ʱ��*/
	}
	return insert;
}

void main()
{
	/*
	* @len1��len2 ��һ���ڶ����н��̸���
	* @h ����ʱ��Ƭ��
	* @insert �ڶ����н�������ʱ��һ�����н��̼��룬�жϵڶ����в���¼��ʱ��Ƭ��ʣ����ʱ��
	*/
	int len1,len2, h = 0, stime,insert = 0;/*,time = 4*/
	char ch;
	input();
	len1 = circulate_first();
	len2 = circulate_second();
	while (wait!=NULL||ready!=NULL)
	{
		if (ready == NULL)/*�������п�ʱ����ȴ����ж���Ԫ��*/
		{
			if (ready2 != NULL)
			{
				while (ready2 != NULL&&ready == NULL)/*�ȴ������н���δ�����ִ�еڶ�����*/
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
					printf("\n �����������������");
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
		if (insert != 0)/*�ڶ����н�������ʱ��һ�����н��̼��룬�жϵڶ����в����ж�ʱ�̿�ʼ���е�һ����*/
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
			printf("\n �����������������");
			ch = getchar();
		}
	}
	while (ready2 != NULL)/*���ȴ����к͵�һ���ж�Ϊ��ʱ*/
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
		printf("\n �����������������");
		ch = getchar();
	}

	printf("\n\n �����Ѿ����.\n");
	ch = getchar();
}