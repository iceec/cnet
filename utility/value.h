#pragma once

#include<string>
#include<iostream>

namespace Yu   //顶级命名空间和二级命名空间
{
    namespace utility
    {
class value
{


public:

    enum Type
    {
V_NULL=0,V_INT,V_FLOAT,V_DOUBLE,V_CONST_CHAT_ADDR,V_STRING,V_BOOL
    };
    value(){}
    value(const int input);
    value(const float input);
    value(const double input);
    value(const char *input);
    value(const std::string &input);
    value(const bool input);
    ~value();

    operator int()const;
    operator float()const;
    operator double()const;
    operator const char *()const;
    operator std::string()const;
    operator bool()const;

    Type type()const;
    bool is_int()const;
    bool is_float()const;
    bool is_double()const;
    bool is_constcharaddr()const;
    bool is_bool()const;
    bool is_string()const;


    bool operator ==(const value &p)const;
    bool operator !=(const value &p)const;

    friend std::ostream& operator<<(std::ostream &fout,const value & m);

  
    private:
        std::string stream;
        Type input_type;



};



    }


}