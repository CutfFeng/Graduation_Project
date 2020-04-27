#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
using namespace std;

class gradeIn {
    private:
        int len;
        char *data;
        //bool fit;
    public:
        gradeIn();
        ~gradeIn();
        vector<string> split( const string &str,const string &pattern );
        int php_htoi( char *s );
        string urldecode( string &str_source );
        void print();
        int addTo_gradeTable();
};