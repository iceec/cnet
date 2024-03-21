#pragma once
#include "xml.h"
#include"singleton.h"
using namespace Yu::utility;

namespace Yu::utility
{

    class Parse
    {
    public:
        bool load(const string &filename, bool is_file);
        bool load_file(const string &name);
        bool load_str(const string &name);
        Xml parse();

    private:
        void skip_white();
        void parse_declaration();
        void parse_comment();
        Xml parse_element();
        string parse_element_name();
        string parse_element_text();
        string parse_element_attr_key();
        string parse_element_attr_val();

    SINGLE(Parse);

    private:
        string m_str;
        size_t m_idx = 0;
    };

}