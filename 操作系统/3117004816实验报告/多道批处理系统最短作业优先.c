#include "stdio.h"
#include <stdint.h>
#include <conio.h>

#define  getjcb(type)(type*)malloc(sizeof(type))
typedef struct jcb {
	char name[10];   //��ҵ�� 
	int atime;   //��ʼʱ�� 
	int ntime;    //����ʱ�� 
	int ftime;  //���ʱ��
	int needMemory;  //�����ڴ�
	int needSource;  //������Դ(�Ŵ���̨��) 
	char state;      //״̬ 
	struct jcb *next;//��һ��ָ�� 
}jcb, *JCB;

JCB wait, ready = NULL, p,fast, n2[10] = { NULL };/*n2: �����еĶ��� ready:�ѵ���Ķ��� wait:δ���ﵽ��ʱ��Ķ���*/
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

void input()/* ������ҵ���ƿ麯��*/
{
	int i, num;
	system("cls");/*����*/
	printf("\n �������ܹ���ҵ����Ŀ��");
	scanf("%d", &num);
	for (i = 0; i < num; i++)
	{
		printf("\n ��ҵ��No.%d", i);
		p = getjcb(jcb);
		printf("\n��������ҵ����");
		scanf("%s", p->name);
		printf("\n�����뵽��ʱ�䣺");
		scanf("%d", &p->atime);
		printf("\n����������ʱ�䣺");
		scanf("%d", &p->ntime);
		printf("\n�����������ڴ棺");
		scanf("%d", &p->needMemory);
		printf("\n������������Դ����ӡ������");
		scanf("%d", &p->needSource);
		printf("\n");
		p->ftime = 0;
		p->state = 'w';
		p->next = NULL;
		sort_wait(); /* ����sort����*/
	}
}
disp(jcb *pr)/*����������ʾ����,������ʾ��ǰ����*/
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
check() /* �������̲鿴���� */
{
	jcb *pr;
	for (int i = 0; i < 10; i++)
	{
		if (n2[i] != NULL)
		{
			printf("\n **** ��ǰ�������еĽ�����:%s", n2[i]->name);/*�������еĶ���*/
			disp(n2[i]);
		}

	}
	printf("\n ****��ǰ����ȴ�����״̬Ϊ:\n"); /*��ʾ����ȴ�����״̬*/
	pr = ready;
	if (ready != NULL)
	{
		while (pr != NULL)
		{
			disp(pr);
			pr = pr->next;
		}
	}
	printf("\n ****��ǰδ�������״̬Ϊ:\n"); /*��ʾδ�������״̬*/
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
p_jcb(JCB p2)/*����ҵ����CPU*/
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
	printf("����%s�����", A->name);
	free(A);
}

running()/*���ȴ������е���ļӽ��ȴ���������*/
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

v_jcb(int target)/*����ҵִ�У��ͷ��ڴ�*/
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
		if (ready == NULL)/*���������к����ж��ж�����ҵ����δ�������ǰ����*/
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
				while (ready != NULL && ready->needMemory <= Memory && ready->needSource <= Source)/*ȷ�ϵ�һ����Դ�������ҵ*/
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
				if (p3->needMemory < Memory&&p3->needSource < Source)/*���Һ����Ƿ��з��ϵ���Դ���õ���ҵ*/
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