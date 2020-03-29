#include "log_in.h"
#include "MysqlDB.h"
#include <sstream>
#include <unistd.h>

 log_in::log_in() {
    //printf("content-type:text/html;charset=gb2312\n\n");
    printf("content-type:text/html;charset=utf-8\n\n");
    //data = "04161128 jialululuhu";
    data=getenv("CONTENT_LENGTH");
    //printf( "data=%s\n",data );
    len=atoi(data);
    fgets(data,len+1,stdin);
    //fit = false;
 }

log_in::~log_in(){

}

void log_in::match( ) {
    int ret;
    //long len = atoi( data );
    //cout << "data=" << data << endl;
    char a1[10] = {""};
    char b1[30] = {""};
    ret = sscanf(data,"account=%8s&pwd=%s",a1,b1);
    //cout << "a1:" << (string)a1 << '\t' << "b1:" << b1 << endl;
    MysqlDB db;
    db.connect( "localhost", "root", "", "test" ); 
    string command = "select * from Account_Table where id=\"" + (string)a1 + "\";";
    //string command = "select * from Account_Table where id=\"xyjsjzzy\";";
    // cout << "command:" << command << endl;
    vector<string> vec;
    bool b = db.get_row_string( vec, command );
    if ( b ){
        //vector<string> v;
        stringstream iss( vec[0] );
        string word;
        char c = '\t';
        string ss[2];
        int i = 0;
        //分离账号和密码
        while ( getline( iss,word,c ) )
        {
            //v.push_back( word );
            ss[i] = word;
            //cout << "ss" << i << ":" << ss[i] << endl;
            ++i;
        }
        
        // for( vector<string>::iterator it = vec.begin(); it != vec.end(); ++ it )
        //     cout << *it << endl;

        //匹配
        string a2 = a1;
        string b2 = b1;
        if ( ss[0] == a2 && ss[1] == b2 ){
            if ( a2 == "xyjsjzzy" ){
                string s = "<!DOCTYPE html>\
                <html>\
                    <head>\
                        <meta charset=\"UTF-8\">\
                        <title>管理员界面</title>\
                        <link rel=\"stylesheet\" href=\"https://cdn.jsdelivr.net/npm/bootstrap@3.3.7/dist/css/bootstrap.min.css\" integrity=\"sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u\" crossorigin=\"anonymous\">\
                        <script src=\"https://cdn.jsdelivr.net/npm/bootstrap@3.3.7/dist/js/bootstrap.min.js\" integrity=\"sha384-Tc5IQib027qvyjSMfHjOMaLkfuWVxZxUPnCJA7l2mCWNIpG9mGCD8wGNIcPD7Txa\" crossorigin=\"anonymous\"></script>\
                        \
                        <style type=\"text/css\">\
                            body,div{\
                                margin: 0px; /*  元素外间距*/\
                            }\
                            .comm_top{\
                                height: 90px;\
                                background-color: #177cb0;\
                                width: 100%;\
                            }\
                            .top_nav{\
                                width: auto;\
                                height: auto;\
                                font-size: 30px;\
                                border: 1px solid salmon;\
                            }\
                            .top_left{\
                                float: left;\
                            }\
                            \
                            .top_right{\
                                float: right;\
                                margin-right: 75px;\
                            }\
                            \
                            .top_nav  *{\
                                color: white;\
                                font-family: \"微软雅黑\";\
                                font-size: 20px;\
                                word-spacing: 30px;\
                                margin-top: 20px;\
                            }\
                            .top_nav a{\
                                display: inline-block;\
                            }\
                            .top_nav .top_se{\
                                display:  inline-block; /* 行内块元素*/\
                                margin-left: 5px;\
                            }\
                            .xtmc{\
                                font-size: 35px;\
                                font-family: \"华文行楷\";\
                                color:white;\
                            }\
                            .info{\
                                height: auto;\
                                width: 100%;\
                                display: flex;\
                                flex-direction: row;\
                            }\
                            .info_left{\
                                width: 60%;\
                                height: auto;\
                            }\
                            .info_right{\
                                width: 40%;\
                                background-color: #F8F8FF;\
                                padding-top: 10%;\
                            }\
                            .info_right *{\
                                margin-left: 10%;\
                                color:black;\
                            }\
                            .mylittle{\
                                font-size: 20px;\
                                font-family: \"仿宋\";\
                                font-weight: bold;\
                            }\
                            /*.hr1{\
                                margin-bottom: 50px;\
                                size: a3;\
                                color: darkgrey;\
                            }*/\
                        </style>\
                </head>\
                <body>\
                    <div class=\"comm_top\" id=\"comm_top\">\
                        <div class=\"top_nav\">\
                            <div class=\"top_left\">\
                                <font class=\"xtmc\">西安邮电大学转专业系统</font>\
                                <a href=\"\">成绩录入</a>\
                                <a href=\"\">信息发布</a>\
                            </div>\
                            <div class=\"top_right\">\
                                <a href=\"http://localhost/login.html\">登陆</a>\
                            </div>\
                        </div>\
                    </div>\
                    <div class=\"info\">\
                        <img class=\"info_left\" src=\"http://www.zfjw.xupt.edu.cn/zftal-ui-v5-1.0.2/assets/images/login_bg_pic.jpg\">\
                        <!--<img class=\"img_right\" src=\"https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1583456921168&di=a6591644291719a7a5f2985a10ad2942&imgtype=0&src=http%3A%2F%2F5b0988e595225.cdn.sohucs.com%2Fimages%2F20170828%2Fe3d1b79bc95e4dfa9341a6280ca2d7eb.jpeg\" />-->\
                        <!--<hr class=\"hr1\"/>-->\
                        <div class=\"info_right\">\
                        <div class=\"mylittle\">\
                            <p>信息栏：</p>\
                        </div>\
                        <div class=\"mylittle\">\
                            <p>1.转专业信息将公示在这里······</p>\
                        </div>\
                            </div>\
                    </div>\
                    </body>\
                </html>" ;
                cout << s << endl;;
            }
            else{
                string s = "<!DOCTYPE html>\
                <html>\
                    <head>\
                        <meta charset=\"UTF-8\">\
                        <title>学生界面</title>\
                        <link rel=\"stylesheet\" href=\"https://cdn.jsdelivr.net/npm/bootstrap@3.3.7/dist/css/bootstrap.min.css\" integrity=\"sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u\" crossorigin=\"anonymous\">\
                        <script src=\"https://cdn.jsdelivr.net/npm/bootstrap@3.3.7/dist/js/bootstrap.min.js\" integrity=\"sha384-Tc5IQib027qvyjSMfHjOMaLkfuWVxZxUPnCJA7l2mCWNIpG9mGCD8wGNIcPD7Txa\" crossorigin=\"anonymous\"></script>\
                        <style type=\"text/css\">\
                            body,div{\
                                margin: 0px; /*  元素外间距*/\
                            }\
                            .comm_top{\
                                height: 90px;\
                                background-color: #177cb0;\
                                width: 100%;\
                            }\
                            .top_nav{\
                                width: auto;\
                                height: auto;\
                                font-size: 30px;\
                                border: 1px solid salmon;\
                            }\
                            .top_left{\
                                float: left;\
                            }\
                            .top_right{\
                                float: right;\
                                margin-right: 75px;\
                            }\
                            .top_nav  *{\
                                color: white;\
                                font-family: \"微软雅黑\";\
                                font-size: 20px;\
                                word-spacing: 30px;\
                                margin-top: 20px;\
                            }\
                            .top_nav a{\
                                display: inline-block;\
                            }\
                            .top_nav .top_se{\
                                display:  inline-block; /* 行内块元素*/\
                                margin-left: 5px;\
                            }\
                            .xtmc{\
                                font-size: 35px;\
                                font-family: \"华文行楷\";\
                                color:white;\
                            }\
                            .info{\
                                height: auto;\
                                width: 100%;\
                                display: flex;\
                                flex-direction: row;\
                            }\
                            .info_left{\
                                width: 60%;\
                                height: auto;\
                            }\
                            .info_right{\
                                width: 40%;\
                                background-color: #F8F8FF;\
                                padding-top: 10%;\
                            }\
                            .info_right *{\
                                    margin-left: 10%;\
                                    color:black;\
                            }\
                            .mylittle{\
                                font-size: 20px;\
                                font-family: \"仿宋\";\
                                font-weight: bold;\
                            }\
                            /*.hr1{\
                                    margin-bottom: 50px;\
                                    size: a3;\
                                    color: darkgrey;\
                            }*/\
                        </style>\
                    </head>\
                    <body>\
                        <!--\
                            json 格式数据\
                        -->\
                        <div class=\"comm_top\" id=\"comm_top\">\
                            <div class=\"top_nav\">\
                                <div class=\"top_left\">\
                                    <font class=\"xtmc\">西安邮电大学转专业系统</font>\
                                    <a href=\"http://localhost/submit.html\">报名入口</a>\
                                    <a href=\"\">成绩查询</a>\
                                    <a href=\"\">补修课程表</a>\
                                </div>\
                                <div class=\"top_right\">\
                                    <a href=\"http://localhost/login.html\">登陆</a>\
                                </div>\
                            </div>\
                        </div>\
                        <div class=\"info\">\
                            <img class=\"info_left\" src=\"http://www.zfjw.xupt.edu.cn/zftal-ui-v5-1.0.2/assets/images/login_bg_pic.jpg\">\
                            <!--<img class=\"img_right\" src=\"https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1583456921168&di=a6591644291719a7a5f2985a10ad2942&imgtype=0&src=http%3A%2F%2F5b0988e595225.cdn.sohucs.com%2Fimages%2F20170828%2Fe3d1b79bc95e4dfa9341a6280ca2d7eb.jpeg\" />-->\
                            <!--<hr class=\"hr1\"/>-->\
                            <div class=\"info_right\">\
                                <div class=\"mylittle\">\
                                    <p>信息栏：</p>\
                                </div>\
                                <div class=\"mylittle\">\
                                    <p>1.转专业信息将公示在这里······</p>\
                                </div>\
                            </div>\
                        </div>\
                    </body>\
                </html>";
                cout << s << endl;
            }
        }
        else{
            string s = "<!DOCTYPE html>\
            <html>\
                <head>\
                    <meta charset=\"UTF-8\">\
                    <title>管理员界面</title>\
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
                        <center><font>账号或密码错误！</font><br>\
                        <a href=\"http://localhost/login.html\">重新登陆</a></center>\
                    </div>\
                </body>\
            </html>";
            cout << s << endl;
        }
    }
    else{
        string s = "<!DOCTYPE html>\
            <html>\
                <head>\
                    <meta charset=\"UTF-8\">\
                    <title>管理员界面</title>\
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
                        <center><font>该用户不存在！</font><br>\
                        <a href=\"http://localhost/login.html\">重新登陆</a></center>\
                    </div>\
                </body>\
            </html>";
        cout << s << endl;
    }
    
}
