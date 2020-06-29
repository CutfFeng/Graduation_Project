#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>

using namespace std;
class sel_class
{
    private:
        char *data;
        int len;
        string id;
    public:
        sel_class(/* args */);
        ~sel_class();
        void print();
};