/*
 **********************************************************
 * Author       : M_Kepler
 * EMail        : m_kepler@foxmail.com
 * Last modified: 2019-05-10 17:37:10
 * Filename     : bitmap.cpp
 * Description  : 位图操作封装
 ***********************************************************
 */
 
#include <iostream>
#include <time.h>
#include <vector>
using namespace std;

#define BITWORD 32
// #define BITWORD 8 * sizeof(unsigned int) // int类型4字节每字节8位，一共 8 * sizeof(int) = 32位

#define INDEX(b) ((b) / (BITWORD))      // 除32可以用位操作: i >> 5 替代
#define BIT_OFFSET(b) ((b) % (BITWORD)) // 对32求余可以用位操作: i & 31 替代

class BitMap
{
public:
    // 申请足够的位 range / 32+1 个 unsigned int空间
    BitMap(size_t range);

    // 设置值x对应的位为 1
    void set(size_t x);

    // 判断值x对应的位是否为 1
    bool is_set(size_t x);

    // 重置值x对应的位为 0
    void clear(size_t x);

    // 全部重置为 0
    void reset();

private:
    vector<unsigned int> m_bits;
};

/*
 * @function: 申请空间, int类型4字节即32位, 计算出需要申请多少个int类型
 * @brief	: 所以第n位存放在第 n/32 个int类型中的第 n%32 位处
 *            unsigned int 范围为 0 ~ 2^32-1
 *            int 范围为 -2^31 ~ 2^31-1
 * @param	: 
 * @return	: 
 */
BitMap::BitMap(size_t range)
{
    m_bits.resize(range / BITWORD + 1); // 多开辟一个空间
}

void BitMap::set(size_t x)
{
    m_bits[INDEX(x)] |= (1 << BIT_OFFSET(x)); // 把 m_bits[i] 的第 x 位置为1
}

bool BitMap::is_set(size_t x)
{
    return m_bits[INDEX(x)] & (1 << (BIT_OFFSET(x)));
}

void BitMap::clear(size_t x)
{
    m_bits[INDEX(x)] &= ~(1 << BIT_OFFSET(x)); // &=~ 取反
}








// --------------------------------------------------------------------------------------------------



/*
 * @function: 利用位图法来排序、去重
 * @brief	: 
 * @param	: num num个随机数
 * @return	: 
 */
void bit_sort(BitMap bm, int num = 10)
{
    int i, j, count = 0;
    printf("\n排序前:\n");
    int arr[num];
    srand((unsigned)time(NULL));
    for (j = 0; j < num; j++)
    {
        arr[j] = rand() % 10 + 1;
        printf("%d\t", arr[j]);
    }

    for (j = 0; j < num; j++)
    {
        bm.set(arr[j]);
    }

    printf("\n排序后:\n");
    for (i = 0; i < num; i++)
    {
        if (bm.is_set(i))
        {
            printf("%d\t", i);
            count++;
        }
    }
    cout << "\n去重后个数为: " << count << endl;
}

int main(int argc, char *argv[])
{
    BitMap bm(10);
    bit_sort(bm);
    return 0;
}
