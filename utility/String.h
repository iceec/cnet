#pragma once

#include<sstream>
#include<iostream>
#include<string>
#include<vector>

using namespace std;

namespace Yu{
    namespace utility{
        class String{
            public:
             static string to_lower(const string &p);
             static string to_upper(const string &p);
             static string ltrim(const string &p,const string &s);
             static string rtrim(const string &p,const string &s);
            static string trim(const string &p,const string &s);
            static vector<string> split(const string &p,const string &s);
            static string join(const vector<string> &p,const string &s);
            static bool has_pre(const string &p,const string &s);
            static bool has_suf(const string &p,const string &s);
            static string capitalize(const string &p);
            static string format(const char *p,...);




        };
    }
}