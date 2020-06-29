#include "MysqlDB.h"

MysqlDB::MysqlDB() {
    //初始化一个数据库对象
    if( mysql_init( &mysql ) == NULL ) {
        cout << "init error, line: " << __LINE__ << endl;
        exit(-1);
    }
    //fit = false;
}
MysqlDB::~MysqlDB() {
    mysql_close( &mysql );
}
void MysqlDB::connect( string host, string user, string passwd,  string database ) {
    //连接数据库
    if( !mysql_real_connect( &mysql, host.c_str(), user.c_str(), passwd.c_str(), 
                             database.c_str(), 0, NULL, 0 ) ) {
        cout << "connect error, line: " << __LINE__ << endl;
        exit(-1);
    }
    string command = "SET NAMES UTF8;";
    mysql_query( &mysql, command.c_str() );
}
void MysqlDB::comd( string command ) {
    // string id,passwd;
    // do {
    //     cout << "添加账号密码:\n";

    //     cin >> id >> passwd;
    //     string command = "insert into Account_Table values('" + id + "','" + passwd + "');";
        mysql_query( &mysql, command.c_str() );
    //     cout << "Continue?(y/n): ";
    //     cin >> id;

    // }while ( id == "y" );    
}

bool MysqlDB::get_row_string( vector<string> &vec, string command ) {
    //string command = "select * from Account_Table where id=\"xyjsjzzy\";";
    mysql_query( &mysql, command.c_str() );

    //获取MySQL检索结果
    result = mysql_store_result( &mysql );

    //cout << "result:" << result << endl;

    if( !result ) {
        //cout << "result error, line : " << __LINE__ << endl;
        return false;
    }
     
    //num_fields为结果集的字段数
    int col_num;
    col_num = mysql_num_fields( result );  //返回字段个数
    //cout << "num=" << num << endl;
    int row_num = 0;
	while ( row = mysql_fetch_row( result ),row ) {
        int i = 0;
        string s = "";
		while ( i < col_num ) {
            // cout << "getrow:" << row[i] << endl;
            s = s + (string)row[i++] + '\t';
		}
		vec.push_back ( s );
	}
    if ( !vec.empty() )
        return true;
    else
        return false;
	
}

int MysqlDB::get_row_int (string command ) {
    mysql_query( &mysql, command.c_str() );

    result = mysql_store_result( &mysql );
    if( !result ) {
        cout << "result error, line : " << __LINE__ << endl;
        return -1;
    }

    // int num;
    // num = mysql_num_fields( result );  //返回字段个数
    // for( int i = 0; i < num; i++ ) {
    //     field = mysql_fetch_field_direct( result, i );  //返回字段类型
    //     cout << field->name << "\t\t";  //输出字段名
    // }
    // cout << endl;
    int n;
    while( row = mysql_fetch_row( result ), row ) {
        n = atoi(row[0]);
        // cout << "n:" << n << endl;
    }
    return n;
}

void MysqlDB::print( string command ) {

    // string sql = "select * from info where name = '" + name + "';";  //要有''
    // string sql = "select * from info;";
    //cout << command << endl;
    int ret = mysql_query( &mysql, command.c_str() );

    //cout << "ret1:" << ret;

    result = mysql_store_result( &mysql );
    if( !result ) {
        cout << "result error, line : " << __LINE__ << endl;
        return ;
    }  
    string ss = "<!DOCTYPE html>\
                <html>\
                    <head>\
                        <meta charset=\"UTF-8\">\
                        <title>成绩查询</title>\
                        <link rel=\"stylesheet\" href=\"https://cdn.jsdelivr.net/npm/bootstrap@3.3.7/dist/css/bootstrap.min.css\" integrity=\"sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u\" crossorigin=\"anonymous\">\   
                        <script src=\"https://cdn.jsdelivr.net/npm/bootstrap@3.3.7/dist/js/bootstrap.min.js\" integrity=\"sha384-Tc5IQib027qvyjSMfHjOMaLkfuWVxZxUPnCJA7l2mCWNIpG9mGCD8wGNIcPD7Txa\" crossorigin=\"anonymous\"></script>\
                    </head>\
                    <body>\
                <table class=\"table table-striped\">\
                <thead>\
                    <tr>\
                    <th>姓名</th>\
                    <th>学号</th>\
                    <th>笔试成绩</th>\
                    <th>面试成绩</th>\
                    <th>最终成绩</th>\
                    <th>排名</th>\
                    </tr>\
                </thead>\
                <tbody>";
    int num;
    num = mysql_num_fields( result );  //返回字段个数
    
    // for( int i = 0; i < num; i++ ) {
    //     field = mysql_fetch_field_direct( result, i );  //返回字段类型
    //     // cout << field->name << "\t\t";  //输出字段名
    //     ss = ss + field->name + "          ";
    // }

    int rank1 = 1;
    
    while( row = mysql_fetch_row( result ), row ) {
        ss = ss + "<tr>";
        for( int i = 0; i < num; i++ ) {
            // cout << row[i] << "\t\t";

            //姓名
            if ( i == 0 ) {
                string command = "select Sname from Student_Table where id=\"" + (string)row[i] + "\";";
                // cout << command;
                vector<string> vec;
                MysqlDB db;
                db.connect( "localhost", "root", "", "test" ); 
                bool b = db.get_row_string( vec, command );
                // cout << vec[0];
                ss = ss + "<td>" + vec[0] + "</td>";
            }
            // string s = row[i];

            ss = ss + "<td>" + row[i] + "</td>";
        }
        char rank[2];
        sprintf( rank, "%d", rank1 );
        ss = ss + "<td>" + rank + "</td>";
        rank1++ ;
        ss += "</tr>";
    }
    ss += "  </tbody>\
        </table>\
        </body>\
        </html>";
    
    std::cout << ss << endl;

}

/*
int main() {
    
    MysqlDB db;
    db.connect( "localhost", "root", "", "test" ); 
    
    // string command1 = "select grade from test.Adu_Grade_Table where id='02162028' and Cno in(select Cno from test.Course_Table where Cname like '%高%数%');";
    // int math = db.get_row_int( command1 );
    // cout << "math:" << math << endl;
    // string command = "select Dno from Dept_Table where dept='计算机学院计算机科学与技术';";
    string command = "select id,written_grade,interview_grade,final_grade from Grade_Table where Dno='1'order by final_grade desc;";
    // cout << "command:" << command << endl;
     db.print( command );
    
    return 0;
}
*/