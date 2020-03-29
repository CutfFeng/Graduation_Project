#include "submit.h"
#include <cstring>
#include "MysqlDB.h"
#include <stdlib.h>

submit::submit(){
    printf("content-type:text/html;charset=utf-8\n\n");
    data=getenv("CONTENT_LENGTH");
    len=atoi(data);
    fgets(data,len+1,stdin);
    // cout << "data:" << data << endl;
    string str = data;
    string pattern = "&";
    vector<string> vec = split(str,pattern);
    // for (int i = 0; i < 5; i++ ) {
    //     cout << vec[i] << endl;
    // }
    string id1 = vec[0].substr(3);
    id = urldecode(id1);
    string name1 = vec[1].substr(5);
    name = urldecode(name1);
    string old_dept1 = vec[2].substr(9);
    old_dept = urldecode(old_dept1);
    string new_dept1 = vec[3].substr(9);
    new_dept = urldecode(new_dept1);
    string already_class1 = vec[4].substr(14);
    already_class = urldecode(already_class1);
    // cout << "id:" << id << "name:" << name << "old_dept:" << old_dept << "new_dept:" << new_dept << "already_class:" << already_class << endl;
}

submit::~submit(){

}

vector<string> submit::split(const string &str,const string &pattern)
{
    //const char* convert to char*
    char * strc = new char[strlen(str.c_str())+1];
    strcpy(strc, str.c_str());
    vector<string> resultVec;
    char* tmpStr = strtok(strc, pattern.c_str());
    while (tmpStr != NULL)
    {
        resultVec.push_back(string(tmpStr));
        tmpStr = strtok(NULL, pattern.c_str());
    }

    delete[] strc;

    return resultVec;
}

/* {{{ php_htoi
 */
int submit::php_htoi(char *s)
{
    int value;
    int c;
    
    c = ((unsigned char *)s)[0];
    if (isupper(c))
        c = tolower(c);
    value = (c >= '0' && c <= '9' ? c - '0' : c - 'a' + 10) * 16;
    
    c = ((unsigned char *)s)[1];
    if (isupper(c))
        c = tolower(c);
    value += c >= '0' && c <= '9' ? c - '0' : c - 'a' + 10;
    
    return (value);
}
/* }}} */

/* {{{ URL解码，提取自PHP 5.2.17
 用法：string urldecode(string str_source)
 时间：2012-8-14 By Dewei
 */
string submit::urldecode(string &str_source)
{
    char const *in_str = str_source.c_str();
    int in_str_len = strlen(in_str);
    int out_str_len = 0;
    string out_str;
    char *str;
    
    str = strdup(in_str);
    char *dest = str;
    char *data = str;
    
    while (in_str_len--) {
        if (*data == '+') {
            *dest = ' ';
        }
        else if (*data == '%' && in_str_len >= 2 && isxdigit((int) *(data + 1))
                 && isxdigit((int) *(data + 2))) {
            *dest = (char) php_htoi(data + 1);
            data += 2;
            in_str_len -= 2;
        } else {
            *dest = *data;
        }
        data++;
        dest++;
    }
    *dest = '\0';
    out_str_len =  dest - str;
    out_str = str;
    // free(str);
    return out_str;
}

bool submit::addTo_mysql(){
    MysqlDB db;
    db.connect( "localhost", "root", "", "test" ); 
    // string command1 = "select Dno from Dept_Table where dept='计算机学院计算机科学与技术';";
    // cout << "command1:" << command1 << endl;
    // db.print( command1 );   

    string command1 = "select Dno from Dept_Table where dept='" + new_dept + "';"; 
    int dno = db.get_row_int( command1 );
    char new_Dno[1];
    sprintf( new_Dno, "%d", dno );
    // cout << "command1:" << command1 << "new_Dno=" << new_Dno << endl;

    string command2 = "select Cno from Course_Table where Cname='" + already_class + "';";
    int cno = db.get_row_int( command2 );
    char old_Cno[1];
    sprintf( old_Cno, "%d", cno );
    // cout << "command2:" << command2 << "old_Cno=" << cno << endl;

    string command3 = "select * from Submit_Table where id='" + id + "';";
    vector<string> v;
    bool b = db.get_row_string( v, command3 );
    cout << "command3:" << command3 << "b:" << b << endl;
    if ( !b ) {
        string command = "insert into Submit_Table values('" + id + "'," + new_Dno[0] + "," + old_Cno + ");";
        db.comd( command );
        cout << "command:" << command << endl;
    }
    else {
        string s;
        s.push_back(new_Dno[0]);
        string command = "update Submit_Table set new_Dno=" + s + ",old_Cno=" + old_Cno + " where id='" + id + "';";
        db.comd( command );
        cout << "command:" << command << endl;
    }
    
    // cout << "command:" << command << endl;
    return true;
}

int main(){
    submit sb;
    bool b = sb.addTo_mysql();
    if ( !b )   
        return -1;
    else        
        cout << "提交成功！" << endl;
    return 0;
}