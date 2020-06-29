#include "MysqlDB.h"
#include "sel_class.h"

sel_class::sel_class() {
    printf("content-type:text/html;charset=utf-8\n\n");
    char *d=getenv("CONTENT_LENGTH");
    len=atoi(d);
    data = (char*)malloc(2);
    fgets(data,len+1,stdin);
    // cout << "data:" << dept << endl;
}

sel_class::~sel_class() {

}

void sel_class::print() {
    int ret;
    char a1[10] = {""};
    ret = sscanf( data,"account=%8s",a1 );
    // cout << "a1:" << (string)a1 << '\t' << "b1:" << b1 << endl;
    MysqlDB db;
    db.connect( "localhost", "root", "", "test" ); 

    string command3 = "select Sname from Student_Table where id=\"" + (string)a1 + "\";";
    vector<string> vec3;
    bool b3 = db.get_row_string( vec3, command3 );
    cout << "**学号" << a1 << "**姓名" << vec3[0] << "**需要补修的课程有:";

    string command1 = "select Cno from Adu_Grade_Table where id=\"" + (string)a1 + "\";";
    //string command = "select * from Account_Table where id=\"xyjsjzzy\";";
    // cout << "command:" << command << endl;
    vector<string> vec1;
    bool b1 = db.get_row_string( vec1, command1 );
    // for( vector<string>::iterator it = vec1.begin(); it != vec1.end(); ++ it )
    //     cout << *it << endl;

    string command2 = "select Cno from Scheme_Table where Dno=(select Dno from Application_Table where id=\"" + (string)a1 + "\");";
    vector<string> vec2;
    bool b2 = db.get_row_string( vec2, command2 );
    // for( vector<string>::iterator it = vec2.begin(); it != vec2.end(); ++ it )
    //     cout << *it << endl;
    for ( vector<string>::iterator it1 = vec2.begin(); it1 != vec2.end(); ++ it1 ) {
        vector<string>::iterator it2;
        for( it2 = vec1.begin(); it2 != vec1.end(); ++ it2 ) {
            // cout << *it1 << *it2;
            if ( *it1 == *it2 )
                break;
        }
        if ( it2 == vec1.end() ) {
            string command = "select Cname from Course_Table where Cno=" + *it1 + ";";
            vector<string> vec3;
            bool b = db.get_row_string( vec3, command );
            cout << vec3[0] << "*" << endl;
        }
    }
    cout << "****具体的补课时间请参照课程表公告!*****" << endl;
}

int main() {
    sel_class sel;
    sel.print();
    return 0;
}