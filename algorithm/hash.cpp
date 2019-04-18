/*
 **********************************************************
 * Author       : M_Kepler
 * EMail        : m_kepler@foxmail.com
 * Last modified: 2019-01-01 22:27:07
 * Filename     : hash.cpp
 * 需求: 从两个文件各有50亿条数据的文件中找出相同的URL
    * https://blog.csdn.net/qingdujun/article/details/82343756
 * 哈希
    * 单机处理海量数据的大体主流思想是采取分而治之的方法, 将海量数据切分为若干小份来进
    * 行处理, 并且在处理的过程中要兼顾内存的使用情况和处理并发量情况
 ***********************************************************
 */
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <set>
#include <vector>
#include <algorithm>  // find
#include <dirent.h>   // DIR
#include <sys/stat.h> // stat
using namespace std;

//[a,b]
#define random(a, b) ((rand() % (b - a + 1)) + a)
#define N 5000
#define PER_FILE_SIZE 1000
string url = "-0123456789abcdefghijklmnopqrstuvwxyz";

typedef bool (*pCallBack)(string suffix, string store_path, unsigned long count_to_split, string line);

// 1 产生N个URL
void generateUrl(string file)
{
    ofstream out(file, ios::ate);
    int n = 0;
    if (out.is_open())
    {
        for (int i = 0; i < N; ++i)
        {
            int size = random(1, 64); // 64bit
            string s = "https://www.";
            for (int j = 0, l = 1; j < size; ++j)
            {
                s += url[random(l, 36)]; // 1 + 10 + 26 - 1 = 36
                l = (s[s.size() - 1] == '-' || j >= size - 1) ? 1 : 0;
            }
            s += ".com/";
            out << s << endl;
        }
        out.close();
    }
}

// 2 将N个URL大文件哈希为10000个小文件
// 2.1 字符串哈希函数BKDRHash
unsigned long bkdr_hash(const char *str)
{
    unsigned int seed = 131; // 也可以是 31、131、1313、13131、131313..
    unsigned int hash = 0;
    while (*str)
    {
        hash = hash * seed + (*str++);
    }
    return (hash & 0x7FFFFFFF); // 对一个大的素数取余
}

void hash_big_file(string filepath, pCallBack pf, string suffix, string store_path, unsigned long count_to_split)
{
    ifstream infile(filepath);
    string line;
    infile.seekg(0, ios::end);
    int last_position = 0; //记录当前已经处理掉的文件位置
    int filesize = infile.tellg();
    for(int n = last_position; n < filesize; n++)
    {
        infile.seekg(last_position, ios::beg);
        getline(infile, line);
        pf(suffix, store_path, count_to_split, line);
        if (infile.tellg() > 0) // 这里必须加入这个判断，因为在频繁更新目标文件时，会导致该函数返回-1
        {
            n = last_position = infile.tellg();
        }
    }
}

bool split_big_file(string suffix, string store_path, unsigned long count_to_split, string line)
{
    string split_file_name = store_path;
    split_file_name += to_string(bkdr_hash(line.c_str()) % count_to_split); // 哈希的值作为文件名
    split_file_name += suffix;
    ofstream out(split_file_name, ios::app);
    if (!out.is_open())
    {
        return false;
    }
    out << line << endl; // 把记录存储到文件中
    out.close();
    return true;
}

bool split_big_file_old(string file_name, string suffix, string store_path, unsigned long count_to_split)
{
    string line;
    if (!file_name.size())
    {
        return false;
    }
    ifstream in(file_name);

    if (!in.is_open())
    {
        return false;
    }

    while (getline(in, line)) // 这里肯定要花不少时间, 越到后面越久
    {
        string split_file_name = store_path;
        split_file_name += to_string(bkdr_hash(line.c_str()) % count_to_split); // 哈希的值作为文件名
        split_file_name += suffix;
        ofstream out(split_file_name, ios::app);
        if (!out.is_open())
        {
            in.close();
            return false;
        }
        out << line << endl; // 把记录存储到文件中
        out.close();
    }
    in.close();
    return true;
}


// 3.1 获取文件大小
unsigned long get_file_size(string file_name)
{
    if (!file_name.size())
        return 0;
    struct stat file_info;
    return stat(file_name.c_str(), &file_info) ? 0 : file_info.st_size;
}

// 3.2 获取某一目录下指定后缀的所有文件
bool str_ends_with(string s, string sub)
{
    return s.rfind(sub) == (s.length() - sub.length());
}
vector<string> get_folder_file_name_list(string folder, string ends_with)
{
    struct dirent *ptr = NULL;
    DIR *dir = opendir(folder.c_str());
    vector<string> files_name;
    while ((ptr = readdir(dir)) != NULL)
    {
        if (ptr->d_name[0] == '.')
            continue;
        if (str_ends_with(ptr->d_name, ends_with))
            files_name.push_back(ptr->d_name);
    }
    closedir(dir);
    return files_name;
}

// 3.3 把小文件里的数据放到set中
set<string> get_file_hash_set(string file_name)
{
    set<string> result;
    string line;
    ifstream in(file_name);

    if (!in.is_open())
    {
        printf("Failed to open file %s", file_name.c_str());
        abort();
    }

    while (getline(in, line))
    {
        result.insert(line);
    }
    in.close();

    return result;
}

// 3.4 获取交集
set<string> get_same_url_set(set<string> set_a, set<string> set_b)
{
    set<string> result;
    set_intersection(set_a.begin(), set_a.end(), set_b.begin(), set_b.end(), inserter(result, result.begin()));
    return result;
}

// 3 使用set将小文件进行求交集操作，最终得到相同URL
bool write_same_url_to_file(string folder_a, string folder_b, string same_url_file_name)
{
    vector<string> files_name_a = get_folder_file_name_list(folder_a, "_a.txt");
    vector<string> files_name_b = get_folder_file_name_list(folder_b, "_b.txt");
    vector<string>::iterator iter;
    ofstream out(same_url_file_name, ios::app);
    if (!out.is_open())
    {
        printf("File %s not exists!\n", same_url_file_name.c_str());
        return false;
    }
    for (int i = 0; i < files_name_a.size(); ++i)
    {
        string s = files_name_a[i];
        s[s.size() - 5] = 'b';
        if (get_file_size(files_name_a[i]) <= PER_FILE_SIZE && (iter = find(files_name_b.begin(), files_name_b.end(), s)) != files_name_b.end() && get_file_size(*iter) <= PER_FILE_SIZE)
        {
            set<string> a_set = get_file_hash_set(folder_a + files_name_a[i]);
            set<string> b_set = get_file_hash_set(folder_b + *iter);
            set<string> same_url_set = get_same_url_set(a_set, b_set);
            set<string>::iterator it = same_url_set.begin();
            for (; it != same_url_set.end(); ++it)
            {
                out << *it << endl;
                // cout << *it << endl;
            }
        }
    }
    out.close();
    return true;
}

int main(int argc, char const *argv[])
{ 
    unsigned long count_to_split = 1000;
    string strFilePath_a ="./url_a.txt";
    string strFilePath_b ="./url_b.txt";
    string strSubUrlFileSuffix_a = "_a.txt";
    string strSubUrlFileSuffix_b = "_b.txt";
    string strSubUrlFilePath_a = "./url_a/";
    string strSubUrlFilePath_b = "./url_b/";
    string strSameUrlFilePath = "./url_same.txt";

    printf("===---===---=== generate url ===---===---===\n");

    // generateUrl(strFilePath_a);
    // generateUrl(strFilePath_b);

    thread gen_a(generateUrl, strFilePath_a);
    thread gen_b(generateUrl, strFilePath_b);
    gen_a.join();
    gen_b.join();

    printf("===---===---=== hash url to file ===---===---===\n");

    // hash_big_file(strFilePath_a, split_big_file, strSubUrlFileSuffix_a, strSubUrlFilePath_a, count_to_split);
    // hash_big_file(strFilePath_b, split_big_file, strSubUrlFileSuffix_b, strSubUrlFilePath_b, count_to_split);

    // split_big_file_old(strFilePath_a, strSubUrlFileSuffix_a, strSubUrlFilePath_a, count_to_split);
    // split_big_file_old(strFilePath_b, strSubUrlFileSuffix_b, strSubUrlFilePath_b, count_to_split);

    thread hash_a(hash_big_file, strFilePath_a, split_big_file, strSubUrlFileSuffix_a, strSubUrlFilePath_a, count_to_split);
    thread hash_b(hash_big_file, strFilePath_b, split_big_file, strSubUrlFileSuffix_b, strSubUrlFilePath_b, count_to_split);
    hash_a.join();
    hash_b.join();

    printf("===---===---=== find each file's same url ===---===---===\n");
    write_same_url_to_file(strSubUrlFilePath_a, strSubUrlFilePath_b, strSameUrlFilePath);

    return 0;
}
