#include"value.h"
#include<sstream>

using namespace Yu::utility;
using std::cout;
using std::endl;




value::value(const int input)
{
    stream=std::to_string(input);   //std命名空间底下的
    input_type=V_INT;
}








value::value(const double input)
{
    stream=std::to_string(input);
    input_type=V_DOUBLE;   
}

value::value(const float input)
{
    stream=std::to_string(input);   
    input_type=V_FLOAT;
}

value::value(const char *input)
{
    stream=input;  
    input_type=V_CONST_CHAT_ADDR;
}

value::value(const std::string &input)
{
    stream=input; 
    input_type=V_STRING;
}

value::value(const bool input)
{
   if(input)
   stream="True";
   else
   stream="False"; 

   input_type=V_BOOL;

}


value::~value()
{

}



//其他都是成员函数不用加命名空间 友元函数就是类外函数所以得加

namespace Yu::utility{
std::ostream& operator<<(std::ostream &fout,const value& m)
{
       fout<<m.stream;
       return fout;
}
}



value::operator int()const
{
    
        if(!(input_type==V_FLOAT||input_type==V_DOUBLE))
        return atoi(stream.c_str());
        else
        {
           int pos=stream.find('.');
        
        return atoi(stream.substr(0,pos).c_str());
        }

    
    //else
       // throw std::logic_error("Can't do that");

}


value::operator float()const
{
        std::stringstream ss;
        ss<<stream;
        
        float result;
        ss>>result;

        return result;
}

value::operator double()const
{
    std::stringstream ss;
        ss<<stream;
        
        double result;

        ss>>result;

        return result;
}

value::operator const char *()const
{
    return stream.c_str();
}

value::operator std::string()const
{
    return stream;
}

value::operator bool ()const
{
    return stream=="True";
}


value::Type value::type()const
{
    return input_type;
} 

bool value::operator ==(const value &p)const
{
    if(input_type!=p.input_type)
    return false;


    return stream==p.stream;
}

bool value::operator!= (const value &p)const
{
     if(input_type!=p.input_type)
    return true;


    return stream!=p.stream;
}

bool value::is_int()const
{
   return input_type==V_INT;
}

bool value::is_float()const
{
    return input_type==V_FLOAT;
}

bool value::is_double()const
{
    return input_type==V_DOUBLE;
}

bool value::is_constcharaddr()const
{
    return input_type==V_CONST_CHAT_ADDR;
}

bool value::is_bool()const
{
    return input_type==V_BOOL;
}

bool value::is_string()const
{
    return input_type==V_STRING;
}


