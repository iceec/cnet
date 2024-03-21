#pragma once
#include"value.h"
#include<string>
#include<vector>
#include<unordered_map>
using namespace Yu::utility;
using std::string;
using std::vector;
using std::unordered_map;


namespace Yu::utility{

class Xml{
public:
    Xml(const string &name="",const string & text=""):m_name(name),m_text(text){}
    Xml(Xml &&);
    Xml(const Xml &p){*this=p;}
    ~Xml(){clear();}

    string name()const{return m_name;}
    void set_name(const string &name){m_name=name;}

    string text()const{return m_text;}
    void set_text(const string &text){m_text=text;}

    value & attr(const string &key){return m_attr[key];}
    void add_attr(const string &key, value &&p){m_attr[key]=std::move(p);}


    void append(const Xml & p){m_children.push_back(p);}   
    void append(Xml && p){m_children.push_back(std::move(p));}

    void child_remove(int );   //remove child
    void child_remove(const string &);
    void attr_remove(const string &);

    void clear();
    string str(const string &p="")const;
    friend std::ostream & operator<<(std::ostream & ,const Xml & );
    void load(const string &name,bool is_file);
    void load_file(const string &filename);
    void load_str(const string &name); 
    void save(const string &name);


    Xml & operator=(Xml &&);
    Xml & operator=(const Xml &);


    using iterator=vector<Xml>::iterator;

    iterator begin(){return m_children.begin();}

    iterator end(){return m_children.end();}

    




public:
    string m_name;
    string m_text;
    unordered_map<string,value>m_attr;
    vector<Xml>m_children;


};

}