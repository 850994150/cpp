/***********************************************************
* Author       : M_Kepler
* EMail        : hellohuangjinjie@gmail.com
* Last modified: 2016-04-08 08:00:23
* Filename     : sort.cpp
* Description  :
    * 插入排序:
     * 直接插入排序
     * 二分插入排序
     * 表排序
     * 希尔排序
    * 选择排序
     * 直接选择排序
     * 堆排序
    * 交换排序
     * 冒泡排序
     * 快速排序
    * 分配排序
     * 基数排序
     * 桶排序
    * 归并排序
     * 二路归并排序
     * 多路归并排序
    * 其他排序
     * 计数排序
     * 煎饼排序
**********************************************************/

/**********************************************************
排序：
    blog.csdn.net/hguisu/article/details/7776068
非常详细
    https://blog.csdn.net/jnu_simba/article/details/9705111
    https://blog.csdn.net/xiazdong/article/details/8462393#t6
gif图:
    https://blog.jobbole.com/11745
**********************************************************/

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <stack>
using namespace std;
const int n = 20;
#define swap_define(x, y)    \
    {                 \
        int temp = x; \
        x = y;        \
        y = temp;     \
    }

void create(int a[])
{
    srand((unsigned)time(NULL));
    for (int i = 0; i < n; i++)
    {
        a[i] = rand() % 100 + 1;
    }
}

void print(int s[])
{
    for (int i = 0; i < n; i++)
        cout << s[i] << " ";
}

void swap(int &a, int &b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}

// 这种写法有毒。。当a==b的时候，函数运行完a和b都变成0了
void swap2(int &a, int &b)
{
    a = a + b;
    b = a - b;
    a = a - b;
}

// 跟加减法一样...
void swap3(int &a, int &b)
{
    a = a ^ b;
    b = a ^ b;
    b = b ^ a;
}

//交换排序 --- 冒泡 O(n) -> O(n^2)
/*
 * 比较相邻的两个元素，然后判断是否交换
 * 如比较s[0]和s[1], 如果s[0]>s[1]则交换; 然后比较s[1]和s[2]; 这样一轮循环下来最后一个元素肯定是最大的元素了
 */
void bubbleSort(int s[], int len)
{
    int i, j, tmp;
    for (i = 0; i < len; i++)
    {
        for (j = 0; j < len - i - 1; j++) // 因为第i遍循环已经找到第i大的值了, 所以比较的时候只需要在s[0]到s[len-i-1]之间找
        {
            if (s[j + 1] < s[j])
            {
                tmp = s[j + 1];
                s[j + 1] = s[j];
                s[j] = tmp;
            }
        }
    }
}

/*
 * @function: 快速排序
 * @brief	: 
 *           找一个数key，作为参照值, 从序列头尾两端开始扫描
 *           找出右边第一个比key小的数a，左边第一个比key大的数b，交换a b
 *           j往←，i往→，当i>=j时，交换a[j]和key,以保证key都大于左边
 *           交换之后，这样循环下来, 肯定是比key小的在左边了, 比key大的在右边了
 *           然后就像二分法那样递归地对左右两边同样的操作
 * @param	: 
 * @return	: 
 */
void quickSort(int *a, int left, int right)
{
    int i = left, j = right;
    int key = a[left];
    if (left > right) // 递归退出条件
    {
        return;
    }

    // while (i != j)
    while (i < j) // 前面 left > right 已做处理了,这里条件可以直接是i<j
    {
        //顺序很重要,先让j往左走
        //因为当i>=j的时候是要交换s[j]和key的
        //所以必须j的方向必须是寻找<key的方向
        while (a[j] >= key && i < j)
            j--;
        while (a[i] <= key && i < j)
            i++;
        if (i < j) // 如果i > j，即s[i]在s[j]右边，而s[j]<s[key]<s[i]，所以s[j]和s[i]是不需要交换的
        {
            swap(a[i], a[j]);
        }
    } // 循环结束后，i >= j
    // [6] 4 3 7 8 9
    // s[i=3] = 7, s[j=2] = 3


    /* i是比key大的值，交换key值和a[i]值
     a[left] = a[i];
     a[i] = key;
     quickSort(a, left, i - 1);
     quickSort(a, i + 1, right);
    */
    // 因为s[j]是小于s[key]的，所以交换二者值，则以s[key]分界，左边都比s[key]小，右边都比s[key]大
    // a[left] = a[j];
    // a[j] = key;
    // swap2(a[left], a[j]); // 交换,用swap2不导致错误，，，，，swap还是用最初的方法吧
    swap(a[left], a[j]); // 交换
    quickSort(a, left, j - 1);
    quickSort(a, j + 1, right);
}

int Partition(int a[], int low, int high)
{
    // 假设每次都以第一个元素作为参照值，进行一趟划分：
    int pivot = a[low];

    while (low < high)
    {
        while (low < high && a[high] >= pivot)
            --high;
        a[low] = a[high]; //停下来做交换
        while (low < high && a[low] <= pivot)
            ++low;
        a[high] = a[low]; //停下来做交换
    }

    a[low] = pivot; //pivot的最终落点
    return low;
}

/*
 * @function: 快排递归实现
 * @brief	: 
 * @param	: 
 * @return	: 
 */
void quickSort2(int a[], int left, int right)
{
    if (left < right)
    {
        int boundary = Partition(a, left, right);
        quickSort2(a, left, boundary);
        quickSort2(a, boundary + 1, right);
    }
}

/*
 * @function: 快排非递归实现
 * @brief	: 任何递归解法都可以借助栈转换为非递归
 * @param	: 
 * @return	: 
 */
void quickSort3(int a[], int left, int right)
{
    //手动利用栈来存储每次分块快排的起始点
    //栈非空时循环获取中轴入栈
    stack<int> s;
    if (left < right)
    {
        int boundary = Partition(a, left, right);

        if (boundary - 1 > left) //确保左分区存在
        {
            //将左分区端点入栈
            s.push(left);
            s.push(boundary - 1);
        }
        if (boundary + 1 < right) //确保右分区存在
        {
            s.push(boundary + 1);
            s.push(right);
        }

        while (!s.empty())
        {
            //得到某分区的左右边界
            int r = s.top();
            s.pop();
            int l = s.top();
            s.pop();

            boundary = Partition(a, l, r);
            if (boundary - 1 > l) //确保左分区存在
            {
                //将左分区端点入栈
                s.push(l);
                s.push(boundary - 1);
            }
            if (boundary + 1 < r) //确保右分区存在
            {
                s.push(boundary + 1);
                s.push(r);
            }
        }
    }
}

//选择排序 --- 直接选择排序 O(n) -> O(n^2)
/*
 * 每趟都从未排序的序列B中和B序列的第一个数B[0]做比较，
 * 如果比它小,就更新minIndex循环后,肯定是最小元素的index，
 * 然后b[minindex]和b.1交换
 * 如果比它小,就交换两个元素的值, 所以一遍下来,
 * B[0]就是待排序最小的元素了
 */
void chooseSort(int s[], int len)
{
    int i, j, minIndex;
    for (i = 0; i < len; i++)
    {
        minIndex = i;
        for (j = i + 1; j < len; j++)
        {
            if (s[j] < s[minIndex]) // 找出未排序中最小元素的下标
                minIndex = j;
        }
        // 交换最小元素和s[j];
        if (minIndex != i)
        {
            swap(s[minIndex], s[i]);
        }
    }
}

// 和上面不同的是,这个只要找到比s[i]小的就交换,
// 而上面是修改minindex来指向较小的元素的下标, // 所以这个交换次数会多一些
void chooseSort2(int s[], int len)
{
    int i, j;
    for (i = 0; i < len; i++)
    {
        for (j = i + 1; j < len; j++)
        {
            if (s[j] < s[i])
            {
                swap(s[i], s[j]);
            }
        }
    }
}

/*
// s[i]与s[0] 到 s[i-1]之间的值做比较, 找到比s[i]大的就交换位置
*/
void chooseSort3(int s[], int len)
{
    int i, j, tmp;
    for (i = 0; i < len; i++)
    {
        for (j = 0; j < i; j++) // 最终s[i]的位置肯定是s[0]到s[i]中最大的值
        {
            if (s[i] < s[j])
            {
                tmp = s[i];
                s[i] = s[j];
                s[j] = tmp;
            }
        }
    }
}

//选择排序 --- 堆排序 O(nlogn)
/*
 * 大根堆:每个节点的值都>=左右孩子节点的值
 *
 * 将待排序的序列构造成一个大顶堆.此时,整个序列的最大值就是堆顶的根结点, 将它移走(其实就是将其堆数组的末尾元素交换, 此时末尾元素就是最大值),
 * 然后将剩余的n-1个序列重新构造成一个堆,这样就会得到n个元素的次大值.如此反复执行,便能得到一个有序序列了
 * 时间复杂度为 O(nlogn),好于冒泡,简单选择,直接插入的O(n^2)
 *
 */
/*
 * @function: 堆排序调整
 * @brief	: 要知道节点关系：树下标从1开始, 则i结点的左儿子为 2*i , 右儿子为 2*i+1
 * @param	: len 表示最大结点下标
 * @param	: k   表示子树根结点下标
 * @return	: 
 */
void sink(int *s, int len, int k)
{
    // 这里为什么判断的是左儿子?
    // 如果判断右儿子，那么当k只有左儿子没有右儿子，而且左儿子比根大，则不会交换了
    while (2 * k <= len) // k的儿子结点下标不能超过总结点数
    {
        int j = 2 * k;                  // 左儿子
        if (j < len && s[j] < s[j + 1]) // 不能是=，为了不让j+1操作越界; 找树根下标为k的大儿子
            j++;
        if (s[k] > s[j])                // 这里不需要j<len了，j已是大儿子了，直接作比较, 根比大儿子还大, 无需交换
            break;

        swap_define(s[j], s[k]);
        k = j; // 调整子树，此时j已等于大儿子下标了（因为大儿子和根做交换，所以会导致大儿子的子树不满足堆结构）
    }
}

/*
 * @function: 堆排序
 * @brief	: 这里构建的二叉树下标是从 1 开始的
 *            下标为 i 或 i+1 的父节点都是 i/2
 *            下标为 i 的子节点为 2*i、2*i + 1
 * @param	: len 为节点数
 * @return	: 
 */
void heapSort(int *s, int len)
{
    // step1: 构建堆
    for (int k = len / 2; k >= 1; k--)  // 1. 从最后一个叶子结点的父节点开始
    {
        sink(s, len, k);
    }
    // 既然sink函数会调整子树，为什么不直接sink(s, len, 1)?
    // 不可以这样，因为如果根都比左右儿子大的话，就不会做后面的调整了，所以需要从下往上调整

    // step2: 调整交换
    for (; len > 1;)
    {
        swap_define(s[1], s[len]); // 将堆顶元素与末尾交换，使最大元素沉到数组末尾（因为是小根堆，所以末元素肯定是最大的）
        len--;              // 已交换元素不用再参与调整(此时s[len]元素已经就位了)
        sink(s, len, 1);    // 重新调整剩下的元素，使其满足堆定义
    }
}

// 【下标从0开始进行堆排】
/*
i结点的左右孩子分别为： 2i+1 2i+2
i结点的父节点为：
i/2：       i 为左孩子结点；
i/2-1：     i 为右孩子结点；
*/
void sink2(int *s, int len, int k)
{
    while (2 * k + 1 <= len) // 结点k的子结点下标不超过总结点, 叶子节点不处理(和下标从1开始的逻辑就这里有差异)
    {
        int j = 2 * k + 1;
        if (j < len && s[j] < s[j + 1])
        {
            j++;
        }
        if (s[k] > s[j])
        {
            break;
        }
        swap(s[j], s[k]); // 这里下标从0 ~ len-1，不会越界，可放心用swap函数
        k = j;
    }
}
void heapSort2(int *s, int len)
{
    len -= 1; // 下标从0开始

    // 如果len为左结点, 则父节点为len/2，如果为右节点，则父节点为len/2 - 1
    // 这里从len/2开始调整，因为即使len为右节点，len/2为父节点的下一个结点(肯定是最后一层的最左边的叶子结点,sink函数不处理叶子结点，所以可以以len/2开始)
    // 所以为了保持和下标从1开始的代码一致，这里也可以写成len/2
    //  for (int k = len / 2 - 1; k >= 0; k--) // 这样也可以
    for (int k = len / 2; k >= 0; k--)         // 和下标从1 开始差异是k>=0
    {
        sink2(s, len, k);
    }

    // 和下标从1开始差异是，这里是0
    for (; len > 0;)
    {
        swap(s[0], s[len]);
        len--;
        sink2(s, len, 0);
    }
}

// [时间复杂度]:O(n) -> O(n^2) * [空间复杂度]:O(1)(借用了一个空间tmp)
//
/* 已排序的序列为A,刚开始只有一个元素,从s中取元素与已排序的a中的元素做比较,
* 找到合适的位置,最后插入到a中.
* 移动元素可以不断做交换或者用前一个元素直接将后一个元素覆盖
*/
void insertSort1(int s[], int len)
{
    int tmp, i, j;
    // for (i = 1; i < len; i++)
    for (i = 0; i < len; i++)
    {
        tmp = s[i]; // 需要插入的数据
        // 取出下一个元素，在已经排序的元素序列中从后向前扫描, 知道找到一个比s[i]小的值
        for (j = i - 1; j >= 0 && s[j] > tmp; j--) // 第一个元素当然也要比较，所以j可以=0
        {
            // 如果被扫描的元素（已排序）大于新元素，将该元素后移一位
            // 直到找到已排序的元素小于或者等于新元素的位置
            s[j + 1] = s[j];
        }
        /*
        // 这样写看的清晰点
        for (j = i - 1; j >= 0; --j)
        {
			if (s[j] >= tmp)
                s[j + 1] = s[j];
			else
				break; // 找到插入位置就可以退出
		}
        */

        // 循环退出的时候, j指向<tmp的值的下标, 因为把元素复制后移了, 所以s[j+1]就是腾给tmp的
        s[j + 1] = tmp; // 注意j要在for外定义
    }
}

void insertSort2(int a[], int len)
{
    for (int i = 1; i < len; i++)
    {
        if (a[i] < a[i - 1])
        {
            //若第i个元素大于i-1元素，直接插入。小于的话，移动有序表后插入
            int j = i - 1;
            int x = a[i];    //复制为哨兵，即存储待排序元素
            a[i] = a[i - 1]; //先后移一个元素
            while (x < a[j])
            { //查找在有序表的插入位置
                a[j + 1] = a[j];
                j--; //元素后移
            }
            a[j + 1] = x; //插入到正确位置
        }
    }
}

//插入排序 --- 二分插入排序排序
// [时间复杂度]:O(n) -> O(n^2) * [空间复杂度]:O(1)(借用了一个空间tmp)
/*
 * 二分插入排序比直接插入排序好就好在可以用二分法较快地查找到
 * 需要插入的元素在已经排好序的序列中的位置, 比较次数为O(log2(n))
 */
void binSort(int a[], int len)
{
    int i, j, left, mid, right, tmp;
    for (i = 1; i < len; i++)
    {
        tmp = a[i];
        left = 0;
        right = i - 1;
        while (left <= right)
        {
            mid = (left + right) / 2;
            if (a[mid] <= tmp)
                left = mid + 1;
            else
                right = mid - 1;
        }
        // 二分查找借宿的时候,left肯定就是应该插入的位置

        for (j = i - 1; j >= left; j--)
            a[j + 1] = a[j]; // 把left后面的元素往后挪动

        // 如果新插入的元素要比已排序序列中的元素都大,就没有必要做对换了
        if (left != i)
            a[left] = tmp;
    }
}

// 二分搜索法
int BinSearch(int array[], int target, int len)
{
    int low = 0;
    // XXX 这个len不可以在函数内部通过sizeof(array)/sizeof(array[0])来计算, 因为数组已经退化为指针了
    int hight = len - 1;
    while (low <= hight)
    {
        int mid = (low + hight) / 2; //取中间值mid点位置
        if (array[mid] == target)    //寻找到目标数
            return mid;
        if (array[mid] > target) //如果中间值大于目标数，则将highr点位置移动mid位置左边
            hight = mid - 1;
        if (array[mid] < target) //如果中间值小于目标数，则将low点位置移动mid位置右边
            low = mid + 1;
    }
    return 0;
}

//插入排序 --- 表排序
//放在linklist-single.cpp里测试成功了
/*
void ListSort(LinkList llist)
{
    Node *pre, *p, *q, *now, *head;
    head = llist;
    pre = head->link;
    if (pre == NULL)
        return;
    now = pre->link;
    if (now == NULL)
        return;
    while (now != NULL)
    {
        q = head;
        p = head->link;
        while (p != now && p->info <= now->info)
        {
            q = p;
            p = p->link;
        }
        if (p == now)
        {
            pre = pre->link;
            now = pre->link;
            continue;
        }
        pre->link = now->link;
        q->link = now;
        now->link = p;

        now = pre->link;
    }
}
*/

//插入排序 --- 希尔排序(缩小增量法) O(n^(3/2))
/*
 * 从S中每隔gap取一次数，在这些数中进行分组insertsort
 * 并不是实实在在地抽取数据出来,
 * gap的选取一般是 n/2、n/4、n/8、.... 、1
 */
void shellSort(int a[], int len)
{
    // 6 2 9 1 5 4
    // 6 1 \ 2 5 \ 9 4    3
    // 1 2 4 6 5 9
    int i, j, gap;
    for (gap = len / 2; gap > 0; gap /= 2)
    { //步长
        //循环gap次，这样取过的元素不会重复被取
        for (i = 0; i < gap; i++) //直接插入排序
        {
            for (j = i + gap; j < len; j += gap)
            {
                if (a[j] < a[j - gap])
                {
                    int temp = a[j];
                    int k = j - gap;
                    while (k >= 0 && a[k] > temp)
                    {
                        a[k + gap] = a[k];
                        k -= gap;
                    }
                    a[k + gap] = temp;
                }
            }
        }
    }
}

//归并排序 --- 归并排序 O(nlogn)
/*
 * 假设初始序列含有n个记录,则可以看成n个有序的子序列,每个子序列的长度为1,然后
 * 两两归并,得到(不小于n/2的最小整数)个长度为2或1的有序子序列,再两两归并,...
 * 如此重复,直至得到一个长度为n的有序序列为止,这种排序方法称为2路归并排序
 * 时间复杂度为O(nlogn),空间复杂度为O(n+logn),如果非递归实现归并,则避免了递归时深度为logn的栈空间
 * 空间复杂度为O(n)
 */
void merge(int *a, int start, int mid, int end)
{
    if (start > mid || mid > end)
        return;
    int i = start, j = mid + 1, k = 0;
    int *L = (int *)malloc((end - start + 1) * sizeof(int));
    while (i <= mid && j <= end)
    {
        if (a[i] < a[j])
            L[k++] = a[i++];
        else
            L[k++] = a[j++];
    }
    //将剩下部分复制到L
    while (i <= mid)
        L[k++] = a[i++];
    while (j <= end)
        L[k++] = a[j++];
    //将排序好的序列从临时L重新复制到a中
    for (i = start, j = 0; i <= end; i++, j++)
        a[i] = L[j];
    //free(L);
}
void mergeSort(int *a, int start, int end)
{
    if (start < end)
    {
        int mid = (start + end) / 2;
        mergeSort(a, start, mid);
        mergeSort(a, mid + 1, end);
        merge(a, start, mid, end);
    }
}

//煎饼排序
/*
 * 1. 找到数组里最大的数 max，把arr[0,max]反转，这样 max 就到最上面了
 * 2. 然后再把整个数组arr 反转，这样 max 就到达最后面了
 * 3. 再对去掉 max 后的数组进行 1和2 的操作
 */
void flip(int *arr, int i)
{
    // 逆置数组 arr[0..i]
    int temp, start = 0;
    while (start < i)
    {
        temp = arr[start];
        arr[start] = arr[i];
        arr[i] = temp;
        start++;
        i--;
    }
}
int findMax(int *arr, int n)
{
    // 找出 arr[0..n-1] 内最大的元素的下标
    int mi, i;
    for (mi = 0, i = 0; i < n; ++i)
        if (arr[i] > arr[mi])
            mi = i;
    return mi;
}
void pancakeSort(int *arr, int n)
{
    for (int curr_size = n; curr_size > 1; --curr_size)
    {
        int mi = findMax(arr, curr_size);
        if (mi != curr_size - 1)
        {
            flip(arr, mi);
            flip(arr, curr_size - 1);
        }
    }
}

int heapsort1Test()
{
	// int s[] = {14, 6, 8, 5, 9};
    int s[] = {9999, 4, 6, 8, 5, 9, 16, 7, 3, 20, 17, 18};
    // 下标从1开始，s[0]值无意义
    int len = sizeof(s) / sizeof(s[0]) - 1; // 下标从1开始，数组下标范围:[1,len]
    heapSort(s, len);

    for (int i = 1; i <= len; i++)
        cout << s[i] << " ";
    return 0;
}

int heapsort2Test()
{
	// int s[] = {14, 6, 8, 5, 9};
    int s[] = {999, 4, 6, 8, 5, 9, 16, 7, 3, 20, 17, 18};
    int len = sizeof(s) / sizeof(s[0]); // 下标从0开始，数组下标范围:[0, len)
    heapSort2(s, len);

    for (int i = 0; i < len; i++)
        cout << s[i] << " ";
    return 0;
}

// int quickSortTest( )
int main(int argc, char *argv[])
{

    int s[] = {999, 4, 6, 8, 32, 5, 9, 16, 7, 3, 20, 17, 18,0,-1};
    int len = sizeof(s) / sizeof(s[0]);
    // quickSort(s, 0, len - 1);
    insertSort1(s, len);

    for (int i = 0; i < len; i++)
        cout << s[i] << " ";
    return 0;
}

int main2()
{
    int *s = new int[n];
    create(s);
    cout << "\n原始序列:\n";
    print(s);
    cout << endl;

    cout << "\n交换排序:\n";
    cout << "bubbleSort" << endl;
    bubbleSort(s, n);
    print(s);
    cout << endl;

    cout << "quickSort" << endl;
    quickSort(s, 0, n - 1);
    print(s);
    cout << endl;

    cout << "quickSort2" << endl;
    quickSort2(s, 0, n - 1);
    print(s);
    cout << endl;

    cout << "quickSort3" << endl;
    quickSort3(s, 0, n - 1);
    print(s);
    cout << endl;

    cout << "\n插入排序:\n";
    cout << "insertSort1" << endl;
    insertSort1(s, n);
    print(s);
    cout << endl;
    cout << "insertSort2" << endl;
    insertSort2(s, n);
    print(s);
    cout << endl;
    cout << "binSort" << endl;
    binSort(s, n);
    print(s);
    cout << endl;

    cout << "shellSort" << endl;
    shellSort(s, n);
    print(s);
    cout << endl;

    cout << "\n选择排序:\n";
    cout << "chooseSort" << endl;
    chooseSort(s, n);
    print(s);
    cout << endl;

    cout << "chooseSort2" << endl;
    chooseSort2(s, n);
    print(s);
    cout << endl;

    cout << "chooseSort3" << endl;
    chooseSort3(s, n);
    print(s);
    cout << endl;

    cout << "heapSort" << endl;
    heapSort(s, n);
    print(s);
    cout << endl;

    cout << "\n归并排序:\n";
    cout << "mergeSort" << endl;
    mergeSort(s, 0, n);
    print(s);
    cout << endl;

    cout << "\n分配排序:\n";
    cout << "\n桶排序:\n";
    cout << "\n基数排序:\n";

    cout << "\n其他:\n";
    cout << "pancakeSort" << endl;
    pancakeSort(s, n);
    print(s);
    cout << endl;

    cout << "二分搜索:\n";
    cout << "数字 " << s[7] << " 的下标是 " << BinSearch(s, s[7], n) << endl;

    return 0;
}

