class Page(object):
    def __init__(self, pagenum):
        self.page_num = pagenum
        self.page_t = 0


page_list = list()       # 待访问页面号列表
page_set = set()         # 页面号集合
temp_set = set()
page_flaglist = list()   # 页面号时间标记集合
memory_list = list()     # 内存中页面列表
swap_interrupt_list = list()  # 中断置换页面列表
flag = 0                 # 标记当前内存块页表数
lost_num = 0             # 缺页中断次数
lost_rate = 0            # 缺页率
set_size = 0             # 页面号标记集合大小
memory_size = 0          # 内存块页表大小


def page_input():
    print("Please input page seq:")
    data = input()
    print("please input memory size:")
    mem_size = input()
    mem_size = int(mem_size)
    return data, mem_size


def deal_input(data):
    """输入处理"""
    data.strip('\n')
    for num in data.split(' '):
        num = int(num)
        page_list.append(num)
        if num not in temp_set:
            page_set.add(Page(num))
        temp_set.add(num)


def clear_time(xx):
    """时间标记清0"""
    for j in range(set_size):
        if page_flaglist[j].page_num is xx:
            page_flaglist[j].page_t = 0


def find_oldest():
    """找出内存块中页表号时间标记最大的"""
    page_flaglist.sort(key=lambda a: a.page_t, reverse=True)

    for j in range(set_size):
        if page_flaglist[j].page_num in memory_list:
            max_num = page_flaglist[j].page_num
            return max_num


def page_swap(oldx, newx):
    """页表置换"""
    for j in range(memory_size):
        if memory_list[j] is oldx:
            memory_list[j] = newx


def time_add():
    """内存块已存在的页面号时间标记全部+1"""
    for k in range(set_size):
        if page_flaglist[k].page_num in memory_list:
            page_flaglist[k].page_t += 1


if __name__ == '__main__':
    datam, memory_size = page_input()
    deal_input(datam)
    page_flaglist = list(page_set)
    set_size = len(page_flaglist)
    print("memory_list: ")
    for x in page_list:
        time_add()                           # 内存块已存在的页面号,时间标记全部+1
        if flag < memory_size:               # 如果内存块页表数 < 最大
            if x not in memory_list:         # 如果内存块中,不存在当前需要访问的页面号
                memory_list.append(x)        # 当前需要访问的页面号加入内存块
            else:                            # 如果内存块中,存在当前需要访问的页面号
                clear_time(x)                # 访问时间标记清零
            flag += 1
        else:                                # 如果内存块页表数 >= 最大
            if x not in memory_list:         # 如果内存块中,不存在当前需要访问的页面号
                old_num = find_oldest()      # 找出内存块中页表号,时间标记最大的
                swap_interrupt_list.append(old_num)  # 存储置换出的页号
                page_swap(old_num, x)        # 当前页表号置换内存块时间标记最大的页表号
                lost_num += 1                # 缺页中断次数增加
            clear_time(x)                    # 访问时间标记清零
        print(memory_list)
    print("\ninterrupt swap page sequence:")
    print(swap_interrupt_list)                    # 打印置换出的页号
    interrupt_time = lost_num + memory_size
    print("\n\nlost page interrupt nums: {}".format(interrupt_time))
    print("lost page rate: {:.2f}%".format(float(interrupt_time / len(page_list) * 100)))

# Test data
# 7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
# 3