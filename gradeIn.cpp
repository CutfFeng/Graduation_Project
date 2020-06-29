#include "gradeIn.h"
#include "MysqlDB.h"

gradeIn::gradeIn() {
    printf("content-type:text/html;charset=utf-8\n\n");
    char *d=getenv("CONTENT_LENGTH");
    len=atoi(d);
    data = (char*)malloc(2);
    fgets(data,len+1,stdin);
 }

gradeIn::~gradeIn() {

}

void gradeIn::print() {
    int j = addTo_gradeTable();
    char row_num[2]; 
    std::sprintf( row_num, "%d", j );
    if( j != 0 ) {
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
                            <center><font>第" + (string)row_num + "行信息有误！</font><br>\
                            <a href=\"http://192.168.1.102/gradeIn_1.html\">返回</a></center>\
                        </div>\
                    </body>\
                </html>";
            std::cout << ss << endl;
    }
    else {
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
                                <center><font>成绩提交成功！</font><br>\
                                <a href=\"http://192.168.1.102/teacher.html\">返回</a></center>\
                            </div>\
                        </body>\
                    </html>";
            std::cout << ss << endl;
    }
}

int gradeIn::addTo_gradeTable() {
    string str = data;
    string pattern = "&";
    vector<string> vec = split(str,pattern);

    MysqlDB db;
    db.connect( "localhost", "root", "", "test" );
    int j = 1;
    for (int i = 0; i < 120; i+=4 ) {
        string sno = vec[i].substr(4);
        if ( sno == "" )
            break;
        //检查学号姓名
        string command1 = "select Sname from Student_Table where id='" + sno + "';";
        vector<string> vec1;
        bool b1 = db.get_row_string( vec1, command1 );

        string name1 = vec[i+1].substr(5);
        string name = urldecode( name1 );
        int len = vec1[0].length();
        // cout << "vec:" << vec1[0].substr( 0,len-1 ) << "name:" << name << "b1:" << b1 << endl;
        
        if ( !b1 or vec1[0].substr( 0,len-1 )!= name ) {
            return j;
        }
        else {
            string score1 = vec[i+2].substr(7);
            string score2 = vec[i+3].substr(7);
            int score = atoi( score1.c_str() ) * 0.5 + atoi( score2.c_str() ) * 0.5;
            char score3[3]; 
            std::sprintf( score3, "%d", score );
            // cout << sno + " " << name + " " << score1 + " " << score2 << " " << score3 << endl;
            string command = "insert into Grade_Table values('" + sno + "'," + "2," + score1 + "," + score2 + "," + score3 + ");";
            db.comd( command );
        }
        ++j;
    }

    // string command = "select * from Grade_Table where Dno=1 order by final_grade desc;";
    // db.comd( command );
    // cout << command << endl;

    return 0;
}

vector<string> gradeIn::split(const string &str,const string &pattern)
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

int gradeIn::php_htoi(char *s)
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
string gradeIn::urldecode(string &str_source)
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

int main() 
{
    gradeIn grade;
    grade.print();
    // cout << "data=" << data << endl;
    // cout << "hehe" << endl;
    return 0;
}