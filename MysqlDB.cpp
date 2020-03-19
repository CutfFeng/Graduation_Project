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
}
void MysqlDB::add() {
    string id,passwd;
    do {
        cout << "添加账号密码:\n";

        cin >> id >> passwd;
        string command = "insert into Account_Table values('" + id + "','" + passwd + "');";
        mysql_query( &mysql, command.c_str() );
        cout << "Continue?(y/n): ";
        cin >> id;

    }while ( id == "y" );    
}

bool MysqlDB::get_row( vector<string> &vec, string command ) {
    //string command = "select * from Account_Table where id=\"xyjsjzzy\";";
    mysql_query( &mysql, command.c_str() );

    //获取MySQL检索结果
    result = mysql_store_result( &mysql );

    //cout << "result:" << result << endl;

    if( !result ) {
        cout << "result error, line : " << __LINE__ << endl;
        //return NULL;
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
            s = s + row[i++] + '\t';
		}
		vec.push_back ( s );
	}
    if ( !vec.empty() )
        return true;
    else
        return false;
	
}
/*
int main() {
    
    MysqlDB db;
    db.connect( "localhost", "root", "", "test" ); 
    //db.add();
    string command = "select * from Account_Table;";
    vector<string> vec;
    bool b = db.get_row( vec, command );
    //char *s = "f=02162028&s=980607";
    //db.get_row();
    //cout << "fit=" << db.fit << endl;
    // for ( int i = 0; i < 2; i ++ ) {
    //     cout << str[i] << endl;
    // }
    
    // delete str;
    return 0;
}
*/