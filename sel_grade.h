#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>

using namespace std;
class sel_grade
{
    private:
        char *data;
        int len;
        string dept;
    public:
        sel_grade(/* args */);
        ~sel_grade();
        int php_htoi( char *s );
        string urldecode( string &str_source );
        void print();
};