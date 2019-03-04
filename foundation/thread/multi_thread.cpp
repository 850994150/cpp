/*
 **********************************************************
 * Author       : M_Kepler
 * EMail        : m_kepler@foxmail.com
 * Last modified: 2018-08-06 10:58:59
 * Filename     : multi_thread.cpp
 * Description  : 双缓冲多线程分析大文件词频
 ***********************************************************
 */

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <time.h>
#include <thread>
#include <cstring>
using namespace std;

struct CharCmp
{
    bool operator()(const char *str1, const char *str2) const
    {
        return strcmp(str1, str2) == 0;
    }
};

struct WordHash
{
    // BKDR hash algorithm
    int operator()(char *str) const
    {
        int seed = 131; // 31 131 1313 131313 etc..
        int hash = 0;
        while (*str)
            hash = hash * seed + (*str++);
        return hash & (0x7FFFFFFF);
    }
};

typedef unordered_map<char *, unsigned int, WordHash, CharCmp> HashMap;
typedef unordered_map<char *, unsigned int, WordHash, CharCmp>::iterator KeySet;

bool words[128];
int threadCount = 4;
// streamsize loadsize = 536870912;    // 1024*1024*1024  1879048192 1610612736 1073741824 536870912 268435456
streamsize loadsize = 104857603; // 1024*1024*1024  1879048192 1610612736 1073741824 536870912 268435456
char *loadedFile[2];
HashMap *wordMaps;

// 声明
void readBlock(int, int, streamoff, streamsize);
streamsize inline getRealSize(ifstream *, streamoff, streamsize);
void inline readLoad(int, ifstream *, streamoff, streamsize);
streamsize inline getBlockSize(int, streamoff, streamsize);

int main(int argc, char *argv[])
{

    ios::sync_with_stdio(false);
    if (argc == 1)
    {
        cout << "WordCount多线程统计词频程序\r\n  参数：\r\n    Path必需，ThreadNum可选(默认为4)\r\n    BufferSize可选(双缓冲,实际占用双倍,1879048192 1610612736 1073741824 536870912 268435456,默认512M)\r\n  Usage:  \tWordCount [Path] [ThreadNum] [BufferSize]\r\n  Example:\tWordCount input.txt" << endl;
        exit(0);
    }
    if (argc > 2)
        threadCount = atoi(argv[2]);
    if (argc > 3)
        loadsize = atol(argv[3]);
    wordMaps = new HashMap[threadCount];
    char *filename = argv[1];
    // 双缓冲
    streamsize maxsize = loadsize + 256;
    loadedFile[0] = new char[maxsize];
    loadedFile[1] = new char[maxsize];

    cout << "Starting to calculate with " << threadCount << " threads..." << endl;
    time_t t_start, t_end;
    t_start = time(NULL);

    // 初始化可识别字符
    memset(words, false, 128);
    for (char c = 97; c != 123; ++c) // 123 - 97 =  26
    {
        words[int(c)] = true;
    }
    for (char c = 65; c != 91; ++c) // 91 - 65 = 26
    {
        words[int(c)] = true;
    }
    for (char c = 48; c != 58; ++c) // 10
    {
        words[int(c)] = true;
    }

    // 读取文件
    ifstream file;
    file.open(filename, ios::binary | ios::in);
    if (!file)
    {
        cout << "Error: file \"" << filename << "\" do not exist!" << endl; // 失败
        exit(1);
    }
    else
    {
        // 确认文件大小
        streamoff start = 0;
        file.seekg(0, ios::end);
        streamoff size, len = file.tellg();
        if (len > 3)
        {
            // 确认有无BOM
            char bom[3];
            file.seekg(0);
            file.read(bom, 3);
            if (bom[0] == -17 && bom[1] == -69 && bom[2] == -65)
            {
                start = 3;
                size = len - 3;
            }
            else
                size = len;
        }
        else
            size = len;
        // 读入文件数据到缓存
        thread *threads = new thread[threadCount];
        streamsize realsize;
        streamoff index, part;
        bool step = 0, needWait = false;
        while (size)
        {
            // 缓冲
            cout << "size: " << size << "\t"
                 << "maxsize: " << maxsize << endl;
            realsize = size > maxsize ? getRealSize(&file, start, loadsize) : size;
            // debug
            cout << "size: " << size << "\t"
                 << "realsize: " << realsize << endl;
            readLoad(step, &file, start, realsize);
            start += realsize;
            size -= realsize;
            // 等待
            if (needWait)
                for (int i = 0; i < threadCount; ++i)
                    threads[i].join();
            else
                needWait = true;

            // 开线程计算
            index = 0, part = realsize / threadCount;
            // debug
            cout << "size2: " << size << "\t"
                 << "realsize2: " << realsize << endl;
            for (int i = 1; i < threadCount; ++i)
            {
                // 分块大小
                len = getBlockSize(step, index, part);
                // readblock 开算
                threads[i] = thread(readBlock, step, i, index, len);
                index += len;
            }
            threads[0] = thread(readBlock, step, 0, index, realsize - index);
            //debug
            // 转换
            step = !step;
        }
        // 清理
        for (int i = 0; i < threadCount; ++i)
            threads[i].join();
        delete loadedFile[0];
        delete loadedFile[1];
        file.close(); // 关闭
        // 结算累加
        HashMap *map = wordMaps;
        for (int i = 1; i < threadCount; ++i)
        {
            KeySet p = (wordMaps + i)->begin(), end = (wordMaps + i)->end();
            for (; p != end; ++p)
                (*map)[p->first] += p->second;
        }
        // 输出
        cout << "Done.\r\n\nDifferent words: " << map->size() << endl;
        KeySet p = map->begin(), end = map->end();
        long total = 0;
        for (; p != end; ++p)
            total += p->second;
        cout << "Total words:" << total << endl;
        cout << "\nEach words count:" << endl;
        for (KeySet i = map->begin(); i != map->end(); ++i)
            cout << i->first << "\t= " << i->second << endl;
        //out.close();
    }
    t_end = time(NULL);

    // 结束
    cout << "\r\nAll completed in " << difftime(t_end, t_start) << "s." << endl;
    return 0;
}

// 文件获取临界不截断的真正大小
streamsize inline getRealSize(ifstream *file, streamoff start, streamsize size)
{
    file->seekg(start + size);
    while (words[file->get()])
        ++size;
    return size;
}

// 文件读入到堆
void inline readLoad(int step, ifstream *file, streamoff start, streamsize size)
{
    file->seekg(start);
    file->read(loadedFile[step], size);
}

// 分块读取
void readBlock(int step, int id, streamoff start, streamsize size)
{
    char c = '\0';
    char word[128];
    int i = 0;
    HashMap *map = wordMaps + id;
    KeySet curr, end = map->end();
    char *filebuffer = loadedFile[step];
    streamsize bfSize = start + size;
    for (streamoff index = start; index != bfSize; ++index)
    {
        c = filebuffer[index];
        if (c > 0 && words[int(c)])
        {
            word[i++] = c;
        }
        else if (i > 0)
        {
            word[i++] = '\0';
            // 先判断map中有没有
            if ((curr = map->find(word)) == end)
            {
                char *str = new char[i];
                memcpy(str, word, i);
                map->insert(pair<char *, unsigned int>(str, 1));
            }
            else
                ++(curr->second);
            i = 0;
        }
    }
    if (i > 0)
    {
        word[i++] = '\0';
        if ((curr = map->find(word)) == end)
        {
            char *str = new char[i];
            memcpy(str, word, i);
            map->insert(pair<char *, unsigned int>(str, 1));
        }
        else
            ++(curr->second);
    }
}

// 内存截断检查
streamsize inline getBlockSize(int step, streamoff start, streamsize size)
{
    char *p = loadedFile[step] + start + size;
    while (words[int(*p)])
    {
        ++size;
        ++p;
    }
    return size;
}
