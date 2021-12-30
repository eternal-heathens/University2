#include "stdio.h"
#include <stdint.h>
#include <conio.h>
#include "math.h"

#define gettrack(type) (type*)malloc(sizeof(type))

 typedef struct pcb
{
	char name[10];
	int track_num;/*磁道号*/
	int displacement_distance;/*移动距离*/
}pcb,*PCB;

 /*
   @p : 当先寻找的磁道号
   @ready ：存放输入的需访问的磁道号的指针数组
   @ready2: FSCAN算法所需的第二个队列
 */
 PCB p = NULL, ready[15] = { NULL }, ready2[15] ={NULL};
 int first = 0;/*标志是否使在扫描期间，新出现的请求磁盘I/O的进程*/

 check()
 {
	 int all_length = 0,i;
	 printf("\nname \ttrack_num \tdisplacement_distance\n");
	 for ( i = 0; ready[i]!=NULL; i++)
	 {
		 printf("|%s\t", ready[i]->name);
		 printf("|%d\t\t", ready[i]->track_num);
		 printf("|%d\n", ready[i]->displacement_distance);
		 all_length += ready[i]->displacement_distance;
	 }
	 printf("\n平均寻道长度为:%lf", (1.0*all_length)/i);
 }

 check2()
 {
	 int all_length = 0,i;
	 printf("\nname \ttrack_num \tdisplacement_distance\n");
	 for (i = 0; ready2[i] != NULL; i++)
	 {
		 printf("|%s\t", ready2[i]->name);
		 printf("|%d\t\t", ready2[i]->track_num);
		 printf("|%d\n", ready2[i]->displacement_distance);
		 all_length += ready[i]->displacement_distance;
	 }
	 printf("\n平均寻道长度为:%lf", (1.0*all_length) / i);
 }

 sort_FCFS()
 {
	 printf("当前输入访问磁道的进程为：");
	 check();
	 ready[0]->displacement_distance = 100 - ready[0]->track_num;
	 for (int i = 1; ready[i] != NULL; i++)
	 {
		 ready[i]->displacement_distance = abs(ready[i]->track_num - ready[i - 1]->track_num);
	 }
	 printf("\n调度后的访问磁道的进程为(从100号磁道开始)：\n");
	 check();
 }

 sort_SSTF()
 {
	 int min = 1000,target,sign;
	 printf("当前输入访问磁道的进程为：");
	 check();
	 for (int i = 0; ready[i] != NULL; i++)/*先计算出100号磁道的最近的磁道，以计算移动距离*/
	 {
		 if (abs(100 - ready[i]->track_num) < min)
		 {
			 min = abs(100 - ready[i]->track_num);
			 target = i;
		 }
	 }
	 PCB exchange = NULL;
	 if (ready[target]!=NULL)
	 {
		 exchange = ready[target];
		 ready[target] = ready[0];
		 ready[0] = exchange;
		 ready[0]->displacement_distance = min;
	 }
	 for (int i = 0; ready[i] != NULL; i++)
	 {
		 min = 1000;
		 for (int j = i+1; ready[j] != NULL; j++)
		 {
			 if (abs(ready[i]->track_num-ready[j]->track_num) < min)
			 {
				 min = abs(ready[i]->track_num - ready[j]->track_num);
				 target = j;
			 }
		 }
		 if (ready[target] != NULL&&ready[i+1]!=NULL)
		 {
			 exchange = ready[target];
			 ready[target] = ready[i+1];
			 ready[i+1] = exchange;
			 ready[i+1]->displacement_distance = min;
		 }
		 else
		 {
			 ready[i]->displacement_distance = abs(ready[i]->track_num - ready[i-1]->track_num);/*最后的访问的磁道的移动距离计算*/
		 }
	 }
	 printf("\n调度后的访问磁道的进程为(从100号磁道开始)：\n");
	 check();
 }

 sort_SCAN()
 {
	 int min = 1000, target = 0;
	 printf("当前输入访问磁道的进程为：");
	 check();
	 for (int i = 0; ready[i] != NULL; i++)
	 {
		 if ((ready[i]->track_num > 100) && (abs(100 - ready[i]->track_num) < min))
		 {
			 min = abs(100 - ready[i]->track_num);
			 target = i;
		 }
	 }
	 PCB exchange = NULL;
	 if (target == 0)
	 {
		 for (int i = 0; ready[i] != NULL; i++)/*先计算出100号磁道的最近的磁道，以计算移动距离*/
		 {
			 if (abs(100 - ready[i]->track_num) < min)
			 {
				 min = abs(100 - ready[i]->track_num);
				 target = i;
			 }
		 }
		 PCB exchange = NULL;
		 if (ready[target] != NULL)
		 {
			 exchange = ready[target];
			 ready[target] = ready[0];
			 ready[0] = exchange;
			 ready[0]->displacement_distance = min;
		 }
	 }
	 else if (ready[target] != NULL)
	 {
		 exchange = ready[target];
		 ready[target] = ready[0];
		 ready[0] = exchange;
		 ready[0]->displacement_distance = min;
	 }
	 for (int i = 0; ready[i] != NULL; i++)/*由里往外计算*/
	 {
		 min = 1000;
		 for (int j = i + 1; ready[j] != NULL; j++)
		 {
			 if (ready[j]->track_num > 100 && abs(ready[i]->track_num - ready[j]->track_num) < min)
			 {
				 min = abs(ready[i]->track_num - ready[j]->track_num);
				 target = j;
			 }
		 }
		 if (ready[target] != NULL && ready[i + 1] != NULL)
		 {
			 exchange = ready[target];
			 ready[target] = ready[i + 1];
			 ready[i + 1] = exchange;
			 ready[i + 1]->displacement_distance = min;
		 }
		 else
		 {
			 ready[i]->displacement_distance = abs(ready[i]->track_num - ready[i - 1]->track_num);/*最后的访问的磁道的移动距离计算*/
		 }
	 }
	 for (int i = 0; ready[i] != NULL; i++)/*由外往里计算*/
	 {
		 min = 1000;
		 if (ready[i+1]!=NULL&&ready[i+1]->track_num > 100)
		 {
			 continue;
		 }
		 for (int j = i + 1; ready[j] != NULL; j++)
		 {
			 if (ready[j]->track_num <= 100 && abs(ready[i]->track_num - ready[j]->track_num) < min)
			 {
				 min = abs(ready[i]->track_num - ready[j]->track_num);
				 target = j;
			 }
		 }
		 if (ready[target] != NULL && ready[i + 1] != NULL)
		 {
			 exchange = ready[target];
			 ready[target] = ready[i + 1];
			 ready[i + 1] = exchange;
			 ready[i + 1]->displacement_distance = min;
		 }
		 else
		 {
			 ready[i]->displacement_distance = abs(ready[i]->track_num - ready[i - 1]->track_num);/*最后的访问的磁道的移动距离计算*/
		 }
	 }
	 printf("\n调度后的访问磁道的进程为(从100号磁道开始)：\n");
	 check();
 }

 sort_CSCAN()
 {
	 int min = 1000, target = 0,max= 0 ;
	 printf("当前输入访问磁道的进程为：");
	 check();
	 for (int i = 0; ready[i] != NULL; i++)/*由里往外计算*//*与100比较*/
	 {
		 if ((ready[i]->track_num > 100) && (abs(100 - ready[i]->track_num) < min))
		 {
			 min = abs(100 - ready[i]->track_num);
			 target = i;
		 }
	 }
	 PCB exchange = NULL;
	 if (ready[target] != NULL)
	 {
		 exchange = ready[target];
		 ready[target] = ready[0];
		 ready[0] = exchange;
		 ready[0]->displacement_distance = min;
	 }
	 for (int i = 0; ready[i] != NULL; i++)/*后面与前面比较*/
	 {
		 min = 1000;
		 for (int j = i + 1; ready[j] != NULL; j++)
		 {
			 if (ready[j]->track_num > 100 && abs(ready[i]->track_num - ready[j]->track_num) < min)
			 {
				 min = abs(ready[i]->track_num - ready[j]->track_num);
				 target = j;
			 }
		 }
		 if (ready[target] != NULL && ready[i + 1] != NULL)
		 {
			 exchange = ready[target];
			 ready[target] = ready[i + 1];
			 ready[i + 1] = exchange;
			 ready[i + 1]->displacement_distance = min;
		 }
		 else
		 {
			 ready[i]->displacement_distance = abs(ready[i]->track_num - ready[i - 1]->track_num);/*最后的访问的磁道的移动距离计算*/
		 }
	 }


	 for (int i = 0; ready[i] != NULL; i++)/*由外往里计算*/
	 {
		 min = 1000;
		 PCB exchange = NULL;
		 if (ready[i+1]!=NULL&&ready[i+1]->track_num > 100)
		 {
			 continue;
		 }
		 if (ready[i + 1] != NULL && ready[i]->track_num > 100 && ready[i + 1]->track_num < 100)
		 {
			 for (int j = i+1; ready[j] != NULL; j++)
			 {
				 if ((abs(ready[j]->track_num - ready[i]->track_num)>max))
				 {
					 max = abs(ready[j]->track_num - ready[i]->track_num);
					 target = j;
				 }
			 }
			 if (ready[target] != NULL)
			 {
				 exchange = ready[target];
				 ready[target] = ready[i+1];
				 ready[i+1] = exchange;
				 ready[i+1]->displacement_distance = max;
			 }
			 continue;
		 }
		 for (int j = i + 1; ready[j] != NULL; j++)
		 {
			 if (ready[j]->track_num <= 100 && abs(ready[i]->track_num - ready[j]->track_num) < min)
			 {
				 min = abs(ready[i]->track_num - ready[j]->track_num);
				 target = j;
			 }
		 }
		 if (ready[target] != NULL && ready[i + 1] != NULL)
		 {
			 exchange = ready[target];
			 ready[target] = ready[i + 1];
			 ready[i + 1] = exchange;
			 ready[i + 1]->displacement_distance = min;
		 }
		 else
		 {
			 ready[i]->displacement_distance = abs(ready[i]->track_num - ready[i - 1]->track_num);/*最后的访问的磁道的移动距离计算*/
		 }
	 }
	 printf("\n调度后的访问磁道的进程为(从100号磁道开始)：\n");
	 check();
 }

 sort_FSCAN()
 {
	 int min = 1000, target = 0, max = 0;
	 if (first == 0)
	 {
		 sort_SCAN();
	 }
	 else
	 {
		 printf("当前输入第二队列访问磁道的进程为：");
		 check2();
		 for (int i = 0; ready2[i] != NULL; i++)/*由里往外计算*/
		 {
			 if ((ready2[i]->track_num > 100) && (abs(100 - ready2[i]->track_num) < min))
			 {
				 min = abs(100 - ready2[i]->track_num);
				 target = i;
			 }
		 }
		 PCB exchange = NULL;
		 if (target == 0)
		 {
			 for (int i = 0; ready2[i] != NULL; i++)/*先计算出100号磁道的最近的磁道，以计算移动距离*/
			 {
				 if (abs(100 - ready2[i]->track_num) < min)
				 {
					 min = abs(100 - ready2[i]->track_num);
					 target = i;
				 }
			 }
			 PCB exchange = NULL;
			 if (ready2[target] != NULL)
			 {
				 exchange = ready2[target];
				 ready2[target] = ready2[0];
				 ready2[0] = exchange;
				 ready2[0]->displacement_distance = min;
			 }
		 }
		 else if (ready2[target] != NULL)
		 {
			 exchange = ready2[target];
			 ready2[target] = ready2[0];
			 ready2[0] = exchange;
			 ready2[0]->displacement_distance = min;
		 }
		 for (int i = 0; ready2[i] != NULL; i++)
		 {
			 min = 1000;
			 for (int j = i + 1; ready2[j] != NULL; j++)
			 {
				 if (ready2[j]->track_num > 100 && abs(ready2[i]->track_num - ready2[j]->track_num) < min)
				 {
					 min = abs(ready2[i]->track_num - ready2[j]->track_num);
					 target = j;
				 }
			 }
			 if (ready2[target] != NULL && ready2[i + 1] != NULL)
			 {
				 exchange = ready2[target];
				 ready2[target] = ready2[i + 1];
				 ready2[i + 1] = exchange;
				 ready2[i + 1]->displacement_distance = min;
			 }
			 else
			 {
				 ready2[i]->displacement_distance = abs(ready2[i]->track_num - ready2[i - 1]->track_num);/*最后的访问的磁道的移动距离计算*/
			 }
		 }


		 for (int i = 0; ready2[i] != NULL; i++)/*由外往里计算*/
		 {
			 min = 1000;
			 if (ready2[i + 1] != NULL && ready2[i + 1]->track_num > 100)
			 {
				 continue;
			 }
			 for (int j = i + 1; ready2[j] != NULL; j++)
			 {
				 if (ready2[j]->track_num <= 100 && abs(ready2[i]->track_num - ready2[j]->track_num) < min)
				 {
					 min = abs(ready2[i]->track_num - ready2[j]->track_num);
					 target = j;
				 }
			 }
			 if (ready2[target] != NULL && ready2[i + 1] != NULL)
			 {
				 exchange = ready2[target];
				 ready2[target] = ready2[i + 1];
				 ready2[i + 1] = exchange;
				 ready2[i + 1]->displacement_distance = min;
			 }
			 else
			 {
				 ready2[i]->displacement_distance = abs(ready2[i]->track_num - ready2[i - 1]->track_num);/*最后的访问的磁道的移动距离计算*/
			 }
		 }
		printf("\n调度后第一的访问磁道的进程为(从100号磁道开始)：\n");
		check();
		printf("\n调度后第二的访问磁道的进程为(从100号磁道开始)：\n");
		check2();
	 }
 }

 int circulate()
 {
	 int i = 0;
	 if (first == 0)
	 {
		 for (; ready[i] != NULL; i++)
		 {

		 }
	 }
	 else
	 {
		 for (; ready2[i] != NULL; i++)
		 {
		 }
	 }
	 return i ;
 }

 input_pcb(int choise)
 {
	 int i, num,null_target = 0;
	 printf("\n请输入当前需要读取磁盘的进程的数目：");
	 scanf("%d", &num);
	 for (i = 0; i < num; i++)
	 {
		 null_target = circulate();
		 printf("当前进程号为：%d", null_target);
		 printf("\n请输入进程号:");
		 p = gettrack(pcb);
		 scanf("%s", p->name);
		 printf("请输入所在磁道号:");
		 scanf("%d", &p->track_num);
		 p->displacement_distance = 0; 
		 if(first == 0)	 ready[null_target] = p;
		 else
		 {
			 ready2[null_target] = p;
		 }
	 }
	 if (choise == 1)
	 {
		 sort_FCFS();
	 }
	 if (choise == 2)
	 {
		 sort_SSTF();
	 }
	 if (choise == 3)
	 {
		 sort_SCAN();
	 }
	 if (choise == 4)
	 {
		 sort_CSCAN();
	 }
	 if (choise == 5)
	 {
		 sort_FSCAN();
	 }
 }

 input()
 {
	 int choise = 0;
	 while (1)
	 {
		 printf("\n************************************");
		 printf("        \n请输入需要的算法:       ");
		 printf("        \n1.先来先服务(FCFS)      ");
		 printf("  \n2.最短寻道时间优先算法（SSTF）");
		 printf("        \n3.扫描算法(SCAN)        ");
		 printf("        \n4.循环扫描算法(CSCAN)   ");
		 printf("        \n5.FSCAN             ");
		 printf("        \n6.quit             ");
		 printf("\n************************************\n");
		 scanf("%d", &choise);
		 if (choise == 6)
		 {
			 return;
		 }
		 input_pcb(choise);
		 printf("\n初次输入的进程以排序完成,是否输入新的算法服务：");
		 if (first == 0) first = 1;
		 else
		 {
			 first = 0;
		 }
	 }
 }

 void main()
 {
	 int i;
	 input();
 }