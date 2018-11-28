#include <iostream>
#include <unordered_map>
#include <map>
#include <string>
using namespace std;
int main( int argc, char **argv )
{
    // 三种插入方法
    unordered_map<int, string> mapStudent;
    // map<int, string> mapStudent;
    mapStudent.insert(map<int, string>::value_type(7, "张三"));
    mapStudent.insert(map<int, string>::value_type(8, "李四"));
    mapStudent.insert(map<int, string>::value_type(9, "王五"));

    auto iter = mapStudent.begin(); // auto自动识别为迭代器类型unordered_map<int, string>::iterator
    while ( iter!=mapStudent.end()  )
    {
        cout << iter->first<< ", " << iter->second<<endl;
        ++iter;
    }

    auto iterator = mapStudent.find(2); // find 返回指向2的迭代器
    if ( iterator != mapStudent.end() ) 
    {
        cout << endl << iterator->first << ", " << iterator->second << endl;
        
    }
    
    return 0;
}
