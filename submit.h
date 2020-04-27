#include <iostream>
#include <vector>

using namespace std;
class submit
{
    private:
        int len;
        char *data;
        string id;
        string name;
        string old_dept;
        string new_dept;
        string already_class;
    public:
        submit(/* args */);
        ~submit();
        vector<string> split(const string &str,const string &pattern);
        static int php_htoi(char *s);
        string urldecode(string &str_source);
        void addTo_submittable( submit sb );
        void addTo_apptable( submit sb, string new_Dno );
};
