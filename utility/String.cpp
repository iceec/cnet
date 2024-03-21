#include"String.h"
#include<algorithm>
#include<stdarg.h>

using namespace Yu::utility;

string String:: to_lower(const string &p){

    string str=p;
    transform(str.begin(),str.end(),str.begin(),::tolower);
    return str;

}
string String:: to_upper(const string &p){
     string str=p;
    transform(str.begin(),str.end(),str.begin(),::toupper);
    return str;

}

string String:: ltrim(const string &p,const string &s){
    string str=p;

   size_t pos=str.find_first_not_of(s);
  

   if(pos!=std::string::npos)
    str.erase(0,pos);
    else
    str.clear();
    return str;
}
string String:: rtrim(const string &p,const string &s){
        string str=p;

   size_t pos=str.find_last_not_of(s);
  

   if(pos!=std::string::npos)
    str.erase(pos+1);
    else
    str.clear();
    return str;

}
string String:: trim(const string &p,const string &s){
    string str=ltrim(p,s);
    return rtrim(str,s);
}

vector<string> String:: split(const string &p,const string &s){
   string str=p;
    vector<string>result;

   size_t last=0;
   size_t index=str.find_first_of(s,last);

   while(index!=std::string::npos){
    result.push_back(str.substr(last,index-last));
    last=index+1;
    index=str.find_first_of(s,last);
   }

   if(last<index){
    result.push_back(str.substr(last,index-last));
   }
   return result;

}
string String::join(const vector<string> &p,const string &s){
    ostringstream ss;
    if(p.size()==0)
        return "";
    ss<<p[0];
    for(int i=1;i<p.size();i++){
        ss<<s<<p[i];
    }
    return ss.str();
}

bool String::has_pre(const string &p,const string &s){
    if(p.size()<s.size())
        return 0;
    return p.substr(0,s.size())==s;

}
bool String::has_suf(const string &p,const string &s){
       if(p.size()<s.size())
        return 0;
    return p.substr(p.size()-s.size(),p.size())==s;

}

string  String::capitalize(const string &p){
    string str=p;
    if(p.size()==0||!(p[0]>='a'&&p[0]<='z'))
        return str;
    str[0]=str[0]-'a'+'A';
    return str;
}

string String::format(const char *p,...){

    string str;
    va_list s;

    va_start(s,p);

    int len=vsnprintf(nullptr,0,p,s);

    cout<<len<<endl;

    if(len>0){
        char *k=new char[len+1];

        vsnprintf(k,len+1,p,s);

        k[len]=0;

        str=k;
        return str;
    }
    return "";

    
}