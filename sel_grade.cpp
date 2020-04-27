#include "MysqlDB.h"
#include "sel_grade.h"

sel_grade::sel_grade() {
    printf("content-type:text/html;charset=utf-8\n\n");
    char *d=getenv("CONTENT_LENGTH");
    len=atoi(d);
    data = (char*)malloc(2);
    fgets(data,len+1,stdin);
    string ss = data;
    string dept1 = urldecode( ss );
    dept = dept1.substr(9);
    // cout << "data:" << dept << endl;
}

sel_grade::~sel_grade() {

}

int sel_grade::php_htoi(char *s)
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
string sel_grade::urldecode(string &str_source)
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

void sel_grade::print() {
    MysqlDB db;
    db.connect( "localhost", "root", "", "test" );

    string command1 = "select Dno from Dept_Table where dept='" + dept + "';";
    vector<string> vec;
    bool b = db.get_row_string( vec, command1 );
    int len = vec[0].length();
    string command2 = "select id,written_grade,interview_grade,final_grade from Grade_Table where Dno='" + vec[0].substr( 0, len-1 ) + "'order by final_grade desc;";
    // cout << "command2:" << command2 << endl;
    db.print( command2 );
}

int main() 
{
    sel_grade gra;
    gra.print();
    return 0;
}