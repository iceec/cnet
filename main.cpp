#include "utility/value.h"
#include "utility/xml.h"
#include "utility/parse_xml.h"
using namespace Yu::utility;
using std::cout;
using std::endl;

void show(Xml *p){
cout<<"name is:"<<p->m_name<<" end"<<endl;
cout<<"text is:"<<p->m_text<<" end"<<endl;;
for(auto p1=p->m_attr.begin();p1!=p->m_attr.end();++p1)
    cout<<"attr is:"<<p1->first<<"  "<<p1->second<<" end"<<endl;
if(p->m_children.size()>0){
    cout<<"########children#######"<<endl;
    for(auto i=p->begin();i!=p->end();++i)
        show(&(*i));
}
return ;
}
int main(){



Xml a;
a.load("./test.xml",1);
cout<<a<<endl;


}




    





  














