#include "parse_xml.h"
#include <fstream>
#include <stdexcept>
#include <sstream>
using namespace Yu::utility;
using problem = std::logic_error;

void f(const string &a)
{
    throw problem(a);
}

Parse::Parse():m_idx(0){}
Parse::~Parse(){}
bool Parse::load(const string &filename, bool is_file)
{
    m_str.clear();
    m_idx=0;
    if (is_file)
        return load_file(filename);
    return load_str(filename);
}
bool Parse::load_file(const string &name)
{
    std::ifstream os(name);
    if (os.fail())
    {
        throw problem("load file failed\n");
    }
    std::stringstream ss;
    ss << os.rdbuf();
    m_str = ss.str();
    return true;
}
bool Parse::load_str(const string &name)
{
    m_str = name;
    return true;
}

void Parse::skip_white()
{
    while (m_str[m_idx] == ' ' || m_str[m_idx] == '\n' || m_str[m_idx] == '\t' || m_str[m_idx] == '\r')
        ++m_idx;
}

Xml Parse::parse()
{
    skip_white();
    if (m_str.compare(m_idx, 5, "<?xml") == 0)
        parse_declaration();
    skip_white();
    while (m_str.compare(m_idx, 4, "<!--") == 0)
    {
        parse_comment();
        skip_white();
    }
    skip_white();

    if (m_str[m_idx] == '<')
    {
        ++m_idx;
        skip_white();

        if (isalpha(m_str[m_idx]) || m_str[m_idx] == '_')
            return parse_element();
    }

    f("parse wrong");
    return Xml();
}

void Parse::parse_declaration()
{
    skip_white();
    m_idx += 5;
    size_t pos = m_str.find("?>", m_idx);
    if (pos == std::string::npos)
        f("parse_declaration wrong");
    m_idx = pos + 2;
}

void Parse::parse_comment()
{
    skip_white();
    m_idx += 4;
    size_t pos = m_str.find("-->", m_idx);
    if (pos == std::string::npos)
        f("parse_comment wrong");
    m_idx = pos + 3;
}

Xml Parse::parse_element()
{
    Xml ans;
    skip_white();
  //  std::cout<<m_str[m_idx]<<std::endl;
    ans.set_name(parse_element_name());
    //std::cout<<ans.name()<<std::endl;
    while (m_str[m_idx] != '\0')
    {
        skip_white();
        if (m_str[m_idx] == '/')
        {
            if (m_str[m_idx + 1] == '>')
            {
                m_idx += 2;
                break;
            }
            else
                f("parse case1 wrong");
        }
        else if (m_str[m_idx] == '>')
        {
            m_idx++;
            skip_white();
            ans.set_text(parse_element_text());
        }
        else if (m_str[m_idx] == '<')
        {
            if (m_str[m_idx + 1] == '/')
            {
                string endtag = "</" + ans.name() + ">";
                size_t pos = m_str.find(endtag, m_idx);
                if (pos == std::string::npos){
                    // std::cout<<m_idx<<" "<<m_str[m_idx]<<std::endl;
                   //  std::cout<<endtag<<std::endl;
                    f("</ has wrong");      
                }
                    
                m_idx = pos + endtag.size();
                skip_white();
               // std::cout<<m_str[m_idx]<<std::endl;
                break;
            }
            else
            {
                ++m_idx;
                if (isalpha(m_str[m_idx]) || m_str[m_idx] == '_')
                    ans.append(parse_element());
                else
                    f("<and name wrong");
            }
        }
        else
        {

            string key = parse_element_attr_key();
            skip_white();
            if (m_str[m_idx] != '='){
                //std::cout<<m_str[m_idx]<<' '<<m_idx<<std::endl;
                 f("parse in parse = wrong");
            }
               
            m_idx++;
            skip_white();
            string val = parse_element_attr_val();
            ans.add_attr(key, val);
        }
    }

    return ans;
}

string Parse::parse_element_name()
{
    size_t pos = m_idx;

    if (!(isalpha(m_str[m_idx]) || m_str[m_idx] == '_'))
        f("parse_element_name wrong");
    ++m_idx;
    while (isalpha(m_str[m_idx]) || m_str[m_idx] == '_' || m_str[m_idx] == '-' || m_str[m_idx] == '.'||(m_str[m_idx] == ':'))
        ++m_idx;
    return m_str.substr(pos, m_idx - pos);
}

string Parse::parse_element_text()
{

    size_t pos = m_idx;

    while (m_idx < m_str.size() && m_str[m_idx] != '<')
        ++m_idx;

    if (m_idx == m_str.size())
        f("parse_element_text wrong");

    return m_str.substr(pos, m_idx - pos);
}

string Parse::parse_element_attr_key()
{
    skip_white();
    size_t pos = m_idx;
    if (!(isalpha(m_str[m_idx]) || m_str[m_idx] == '_'))
        f("parse_element_key wrong");

    while (isalpha(m_str[m_idx]) || m_str[m_idx] == '_' || m_str[m_idx] == '-' || m_str[m_idx] == '.'||m_str[m_idx] == ':')
        ++m_idx;
    return m_str.substr(pos, m_idx - pos);
}

string Parse::parse_element_attr_val()
{
    if (m_str[m_idx] != '"')
        f("parse_element_attr_val wrong");
    m_idx++;
    size_t pos = m_idx;

    while (m_idx < m_str.size() && m_str[m_idx] != '"')
        ++m_idx;

    if (m_idx == m_str.size())
        f("parse_element_val wrong");

    m_idx++;

    return m_str.substr(pos, m_idx - pos - 1);
}