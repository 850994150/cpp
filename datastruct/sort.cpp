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
using namespace std;
const int n = 20;
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

void swap(int a, int b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}

void swap2(int a, int b)
{
    a = a + b;
    b = a - b;
    a = a - b;
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

//交换排序 --- 快排 O(nlogn)(平均情况)
/*
 * 找一个数key，作为参照值, 从序列头尾两端开始扫描
 * 找出右边第一个比key小的数a，左边第一个比key大的数b，交换a b
 * j往←，i往→，当i=j时，交换a[i]和key
 * 交换之后，这样循环下来, 肯定是比key小的在左边了, 比key大的在右边了
 * 然后就像二分法那样递归地对左右两边同样的操作
 */
void quickSort(int *a, int left, int right)
{
    int i, j, t, key;
    if (left > right)
    {
        return;
    }
    key = a[left];
    i = left;
    j = right;
    while (i != j)
    {
        //顺序很重要,先让j往左走
        //因为当i=j的时候是要交换s[j]和key的
        //所以必须j的方向必须是寻找<key的方向
        while (a[j] >= key && i < j)
            j--;
        while (a[i] <= key && i < j)
            i++;
        if (i < j)
        {
            t = a[i];
            a[i] = a[j];
            a[j] = t;
        }
    }
    // 交换key值和a[i]值
    a[left] = a[i];
    a[i] = key;
    quickSort(a, left, i - 1);
    quickSort(a, i + 1, right);
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
 * 大根堆:每个节点的值都>=左右孩子节点的值o
 *
 * 将待排序的序列构造成一个大顶堆.此时,整个序列
 * 的最大值就是堆顶 的根结点.将它移走(其实就是将其
 * 与堆数组的末尾元素交换, 此时末尾元素就是最大值),
 * 然后将剩余的n-1个序列重新构造成一个堆,这样就会得到
 * n个元素的次大值.如此反复执行,便能得到一个有序序列了。
 * 时间复杂度为 O(nlogn),好于冒泡,简单选择,直接插入的O(n^2)
 *
 */
void sink(int *a, int m, int k)
{
    while (2 * k <= m)
    {
        int j = 2 * k;
        if (j < m && a[j] < a[j + 1])
            j++;
        if (a[k] > a[j])
            break;
        swap(a[j], a[k]);
        k = j;
    }
}
void heapSort(int *a, int len)
{
    for (int k = len / 2; k >= 1; k--)
        sink(a, len, k);
    for (; len > 1;)
    {
        swap(a[1], a[len]);
        len--;
        sink(a, len, 1);
    }
}

// 插入排序 --- 直接插入排序
// [时间复杂度]:O(n) -> O(n^2) * [空间复杂度]:O(1)(借用了一个空间tmp)
//
/* 已排序的序列为A,刚开始只有一个元素,从s中取元素与已排序的a中的元素做比较,
* 找到合适的位置,最后插入到a中.
* 移动元素可以不断做交换或者用前一个元素直接将后一个元素覆盖
*/
void insertSort1(int s[], int len)
{
    int tmp, i, j;
    for (i = 1; i < len; i++)
    {
        tmp = s[i];
        // 取出下一个元素，在已经排序的元素序列中从后向前扫描, 知道找到一个比s[i]小的值
        for (j = i - 1; j >= 0 && s[j] > tmp; j--)
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
			{
                s[j + 1] = s[j];
            }
			else
			{
				break;
			}
		}
        */

        // 循环退出的时候,j指向<tmp的值的下标, 因为把元素复制后移, 所以s[j+1]就是腾给tmp的
        s[j + 1] = tmp;
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
        int mid = (low + hight) / 2;   //取中间值mid点位置
        if (array[mid] == target)      //寻找到目标数
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

int main()
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

    return 0;
}
