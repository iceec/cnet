#include"ini_file.h"

using namespace Yu::utility;


ini::ini(const string &f){

    load(f);
}

void ini::load(const string& f){
    
    ini_file.clear();
    file_name=f;

    ifstream ip(file_name);
   

    if(ip.fail()){
       throw logic_error("file can not open"+file_name);
    }

    string line;
    string name;
    
    while(getline(ip,line)){

        string first=trim(line," /r/n");
        if(first.size()==0)
            continue;
        if(first[0]=='['){
            auto pos=first.find(']');
            if(pos==string::npos)
                throw logic_error("section name wrong"+first);
            name=first.substr(1,pos-1);
            ini_file[name]=section();
        }
        else{
            auto pos=first.find('=');
              if(pos==string::npos)
                throw logic_error("section key wrong"+first);
            string keyname=first.substr(0,pos);
            auto keylast=keyname.find_last_not_of(" /r/n");
            if(keylast==string::npos)
                    throw logic_error("section key no name"+first);
            keyname=keyname.substr(0,keylast+1);

            string val=first.substr(pos+1);
        val=trim(val," /r/n\"");
            if(val.size()==0)
                throw logic_error("section no value "+first);
        auto lastpos=val.find_last_not_of(" /r/n\"");
            if(lastpos==string::npos)
                     throw logic_error("section no value "+first);

                     
            string temp=val.substr(0,lastpos+1);
                    if(name.size()==0)
                        throw logic_error("no name "+first);
        ini_file[name].insert({keyname,value(temp)});       
        }
        

    }

}

string ini::trim(string line,string f){

    auto pos=line.find_first_not_of(f);

    if(pos==string::npos)
        return "";
    
    return line.substr(pos);

}

string ini::str()const{

    stringstream ss;

    for(auto i:ini_file){

        ss<<'['<<i.first<<']'<<endl;
        for(auto p:i.second){
            ss<<p.first<<" = "<<p.second<<endl; 
        }

        ss<<endl;
    }

    return ss.str();

}

void ini::show()const{
    cout<<str();
}


 value & ini::get(const string &section,const string &key){
    return ini_file[section][key];
 }


bool ini::set(const string &section,const string &key,const value &val){
    ini_file[section][key]=val;

    return 1;
}


ini::section & ini::operator[](const string &section){
        return ini_file[section];
}



bool ini::has(const string &section)const{
    return ini_file.count(section)>0;
}

bool ini::has(const string &section,const string& key){
    if(has(section)){
        return ini_file[section].count(key)>0;
    }
    return 0;

}

void ini::remove(const string &section){
    if(has(section))
    ini_file.erase(section);
}

void ini::remove(const string &section,const string &key){
    if(has(section,key))
        ini_file[section].erase(key);
}
