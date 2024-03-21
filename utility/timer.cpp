#include"timer.h"

using namespace Yu::utility;


timer::timer(){
    time_t x=time(NULL);
    secc=x;

    #ifdef WIN32
        localtime_s(&tv,&x);
    #else
        localtime_r(&x,&tv);
    #endif
     #ifdef WIN32
     SYSTEMTIME P;
     GetLocalTime(&P);
     u_sec=P.wMilliseconds*1000;
    #else
    struct timeval p;
    gettimeofday(&p,0);
    u_sec=p.tv_usec
    #endif

}

void timer::sleep(unsigned long msecond){

    #ifdef WIN32
    Sleep(msecond);
    #else
    usleep(msecond*1000);
    #endif
}


 double timer::operator -(const timer &p){
   
    return (u_sec-p.u_sec)/1000.0+(secc-p.secc)*1000;
 }

string  timer::format(const string &s){

    char p[30];
    strftime(p,sizeof(p),s.c_str(),&tv);

    return p;
}