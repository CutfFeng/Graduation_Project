#include "submit.h"
#include <string>
//#include "MysqlDB.h"

submit::submit(){
    printf("content-type:text/html;charset=utf-8\n\n");
    data=getenv("CONTENT_LENGTH");
    len=atoi(data);
    fgets(data,len+1,stdin);
}

submit::~submit(){

}

void submit::addTo_mysql(){
    int ret;
    char id[10] = {""};
    char name[20] = {""};
    char old_dept[20] = {""};
    char new_dept[20] = {""};
    char already_class[20] = {""};
    ret = sscanf(data,"id=%8s&name=%s&old_dept=%s&new_dept=%s&already_class=%s",id,name,old_dept,new_dept,already_class);
    cout << "data:" << (string)data << endl;
    cout << "id:" << id << endl << "name:" << name << endl << "old:" << old_dept << endl;
    // string id;
    // string name;
    // string old_dept;
    // string new_dept;
    // string already_class;
}

int main(){
    submit sb;
    sb.addTo_mysql();
    return 0;
}