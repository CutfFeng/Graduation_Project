#include <iostream>
#include <string>
#include <mysql/mysql.h>
#include <vector>

using namespace std;

class MysqlDB {
private:
    MYSQL mysql;    //mysql标记对应某个数据库
    MYSQL_ROW row;  //row[i]可用于输出该行第i个字段的数据
    MYSQL_RES *result;  //存储数据库检索信息结果的对象
    MYSQL_FIELD *field; //field->name存储对应字段名称
public:
    //bool fit;
    MysqlDB();
    ~MysqlDB();
    void connect( string host, string user, string passwd,  string database );
    void comd( string command );
    bool get_row_string( vector<string> &vec, string command );
    int get_row_int( string command );
    void print( string command );
};