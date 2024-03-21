#include "xml.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include"parse_xml.h"
using namespace std;
using namespace Yu::utility;
// 容器最好用swap用move也行
// move 只是表示意思不清楚 move也成功了
Xml::Xml(Xml &&other)
{
    clear();
    m_name.swap(other.m_name);
    m_text.swap(other.m_text);
    m_attr.swap(other.m_attr);
    m_children.swap(other.m_children);

    // m_name=std::move(other.m_name);
    // m_text=std::move(other.m_text);
    // m_attr=std::move(other.m_attr);
    // m_children=std::move(other.m_children);
}

Xml &Xml::operator=(Xml &&other)
{
    if(this==&other)
        return *this;
    clear();
    //  m_name=std::move(other.m_name);
    // m_text=std::move(other.m_text);
    // m_attr=std::move(other.m_attr);
    // m_children=std::move(other.m_children);
    m_name.swap(other.m_name);
    m_text.swap(other.m_text);
    m_attr.swap(other.m_attr);
    m_children.swap(other.m_children);

    return *this;
}

Xml &Xml::operator=(const Xml &p)
{
    if (&p == this)
        return *this;

    clear();
    m_name = p.m_name;
    m_text = p.m_text;
    m_children = p.m_children;
    m_attr = p.m_attr;
    return *this;
}

void Xml::child_remove(int index)
{
    int size = m_children.size();
    if (index < 0 || index >= size)
        return;
    m_children.erase(m_children.begin() + index);
}

void Xml::child_remove(const string &key)
{
    int size = m_children.size();
    auto it = m_children.begin();

    for (; it != m_children.end();)
    {
        if (it->name() == key)
            it = m_children.erase(it);
        else
            ++it;
    }
}

void Xml::attr_remove(const string &p)
{
    m_attr.erase(p);
}

void Xml::clear()
{
    m_name.clear();
    m_text.clear();
    m_children.clear();
    m_attr.clear();
}

string Xml::str(const string &p) const
{
    if (m_name.size() == 0)
        return "";
    stringstream ss;
    ss << p;
    ss << "<" << m_name;
    if (m_attr.size())
    {
        for (auto it = m_attr.begin(); it != m_attr.end(); ++it)
            ss << " " << it->first << "="
               << "\"" << it->second << "\"";
    }
    ss << ">";
    if (m_text.size())
        ss << m_text;

    if (m_children.size() != 0)
    {
        ss << endl;
        string temp = p + "    ";
        for (auto it = m_children.begin(); it != m_children.end(); ++it)
            ss << it->str(temp);
        ss << p;
    }
    ss << "</" << m_name << ">" << endl;
    return ss.str();
}
namespace Yu::utility
{
    ostream &operator<<(std::ostream &fout, const Xml &p)
    {
        fout << p.str() << endl;
        return fout;
    }

    void Xml::save(const string &name)
    {
        std::ofstream it(name);
        if (it.fail())
            return;

        it << str() << std::endl;
    }

}

void Xml::load(const string &name, bool is_file)
{
    if (is_file)
        return load_file(name);
    return load_str(name);
}

void Xml::load_file(const string &filename)
{
    clear();

    single<Parse>::instance()->load_file(filename);
    *this=single<Parse>::instance()->parse();
}
void Xml::load_str(const string &name)
{
      clear();
    single<Parse>::instance()->load_str(name);
    *this=single<Parse>::instance()->parse();
    
}