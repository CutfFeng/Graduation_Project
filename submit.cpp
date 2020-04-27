#include "submit.h"
#include <cstring>
#include "MysqlDB.h"
#include <stdlib.h>
#include <sstream>
#include <unistd.h>

submit::submit(){
    printf("content-type:text/html;charset=utf-8\n\n");
    char *d=getenv("CONTENT_LENGTH");
    len=atoi(d);
    data = (char*)malloc(2);
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

void submit::addTo_apptable( submit sb, string new_Dno ) {
    MysqlDB db;
    db.connect( "localhost", "root", "", "test" ); 
    string command1 = "select grade from test.Adu_Grade_Table where id='" + id
                     + "' and Cno in(select Cno from test.Course_Table where Cname like '%高%数%');";
    int math = db.get_row_int( command1 );
    string command2 = "select grade from test.Adu_Grade_Table where id='" + id
                        + "' and Cno in(select Cno from test.Course_Table where Cname like '大学英语%');";
    int english = db.get_row_int( command2 );
    string command3 = "select grade from test.Adu_Grade_Table where id='" + id
                        + "' and Cno in(select Cno from test.Course_Table where Cname like '线性代数%');";
    int algebra = db.get_row_int( command3 );
    int ave = ( math + english + algebra )/3;
    char avegrade[3];
    sprintf( avegrade, "%d", ave );

    //将数据插入到申请表中
    string command4 = "insert into Application_Table values('" + id + "'," + new_Dno[0] + "," + avegrade + "," + "1);";
    db.comd( command4 );

    //降序排列
    // string command5 = "select * from Application_Table order by avegrade_ema desc;";
    // db.comd( command5 );
    // cout << "command:" << command << endl;
    // cout << "math:" << math << "english:" << english << "algebra:" << algebra << "avegrade:" << avegrade << endl;

}

void submit::addTo_submittable( submit sb ){
    MysqlDB db;
    db.connect( "localhost", "root", "", "test" );
    // string command1 = "select Dno from Dept_Table where dept='计算机学院计算机科学与技术';";
    // cout << "command1:" << command1 << endl;
    // db.print( command1 );   

    string command1 = "select Sname from Student_Table where id='" + id + "';";
    vector<string> vec1;
    bool b1 = db.get_row_string( vec1, command1 );
    int len1 = vec1[0].length();

    string command2 = "select Dno from Student_Table where id='" + id + "';";
    // vector<string> vec2;
    bool b2 = db.get_row_string( vec1, command2 );

    string command3 = "select Dno from Dept_Table where dept='" + old_dept + "';";
    // cout << "command:" << command3;
    // vector<string> vec3;
    bool b3 = db.get_row_string( vec1, command3 );
    // cout << "sname:" << vec1[0].substr( 0,len1-1 ) << "Dno:" << vec1[1] << vec1[2];

    if( !b1 or !b2 or vec1[0].substr( 0,len1-1 )!=name or vec1[1] != vec1[2] ) {
        // std::cout << "b1:b2:" + b1 + b2;
        // std::cout << "ss:" + vec1[0].substr( 0,len1-1 ) + "name:" + name + "Dno:" + vec1[1] << endl;

        string ss = "<!DOCTYPE html>\
                <html>\
                    <head>\
                        <meta charset=\"UTF-8\">\
                        <title>提交界面</title>\
                        <link rel=\"stylesheet\" href=\"https://cdn.jsdelivr.net/npm/bootstrap@3.3.7/dist/css/bootstrap.min.css\" integrity=\"sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u\" crossorigin=\"anonymous\">\
                        <script src=\"https://cdn.jsdelivr.net/npm/bootstrap@3.3.7/dist/js/bootstrap.min.js\" integrity=\"sha384-Tc5IQib027qvyjSMfHjOMaLkfuWVxZxUPnCJA7l2mCWNIpG9mGCD8wGNIcPD7Txa\" crossorigin=\"anonymous\"></script>\
                        <style>\
                            .mylittle{\
                                margin-top: 100px;\
                                font-family: \"仿宋\";\
                                font-size: 25px;\
                            }\
                        </style>\
                    </head>\
                    <body>\
                        <div class=\"mylittle\">\
                            <center><font>报名信息有误！</font><br>\
                            <a href=\"http://localhost/submit.html\">返回</a></center>\
                        </div>\
                    </body>\
                </html>";
        std::cout << ss << endl;
    }
    else {
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
        // cout << "command3:" << command3 << "b:" << b << endl;
        if ( !b ) {
            string command = "insert into Submit_Table values('" + id + "'," + new_Dno[0] + "," + old_Cno + ");";
            db.comd( command );
            sb.addTo_apptable ( sb, new_Dno );        

            // cout << "command:" << command << endl;
            string ss = "<!DOCTYPE html>\
                <html>\
                    <head>\
                        <meta charset=\"UTF-8\">\
                        <title>提交界面</title>\
                        <link rel=\"stylesheet\" href=\"https://cdn.jsdelivr.net/npm/bootstrap@3.3.7/dist/css/bootstrap.min.css\" integrity=\"sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u\" crossorigin=\"anonymous\">\
                        <script src=\"https://cdn.jsdelivr.net/npm/bootstrap@3.3.7/dist/js/bootstrap.min.js\" integrity=\"sha384-Tc5IQib027qvyjSMfHjOMaLkfuWVxZxUPnCJA7l2mCWNIpG9mGCD8wGNIcPD7Txa\" crossorigin=\"anonymous\"></script>\
                        <style>\
                            .mylittle{\
                                margin-top: 100px;\
                                font-family: \"仿宋\";\
                                font-size: 25px;\
                            }\
                        </style>\
                    </head>\
                    <body>\
                        <div class=\"mylittle\">\
                            <center><font>报名信息提交成功！</font><br>\
                            <a href=\"http://localhost/student.html\">返回</a></center>\
                        </div>\
                    </body>\
                </html>";
            std::cout << ss << endl;
        }
        else {
            string s;
            s.push_back(new_Dno[0]);
            string command = "update Submit_Table set new_Dno=" + s + ",old_Cno=" + old_Cno + " where id='" + id + "';";
            db.comd( command );
            // cout << "command:" << command << endl;
            string ss = "<!DOCTYPE html>\
                <html>\
                    <head>\
                        <meta charset=\"UTF-8\">\
                        <title>提交界面</title>\
                        <link rel=\"stylesheet\" href=\"https://cdn.jsdelivr.net/npm/bootstrap@3.3.7/dist/css/bootstrap.min.css\" integrity=\"sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u\" crossorigin=\"anonymous\">\
                        <script src=\"https://cdn.jsdelivr.net/npm/bootstrap@3.3.7/dist/js/bootstrap.min.js\" integrity=\"sha384-Tc5IQib027qvyjSMfHjOMaLkfuWVxZxUPnCJA7l2mCWNIpG9mGCD8wGNIcPD7Txa\" crossorigin=\"anonymous\"></script>\
                        <style>\
                            .mylittle{\
                                margin-top: 100px;\
                                font-family: \"仿宋\";\
                                font-size: 25px;\
                            }\
                        </style>\
                    </head>\
                    <body>\
                        <div class=\"mylittle\">\
                            <center><font>报名信息修改成功！</font><br>\
                            <a href=\"http://localhost/student.html\">返回</a></center>\
                        </div>\
                    </body>\
                </html>";
            std::cout << ss << endl;
        }
    }
    // cout << "command:" << command << endl;
}

int main(){
    submit sb;
    sb.addTo_submittable( sb );

    return 0;
}