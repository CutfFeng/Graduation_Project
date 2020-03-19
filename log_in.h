#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
using namespace std;

class log_in {
    private:
        int len;
        char *data;
        //bool fit;
    public:
        log_in();
        ~log_in();
        void match( );
};