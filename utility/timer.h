#pragma once
#include<ctime>
#include<string>

#ifdef WIN32
#include <windows.h>
#else
#include <sys/time.h>
#include<unistd.h>
#endif

using namespace std;
namespace Yu::utility{
    class timer{

    public:
    timer();
    int year(){return tv.tm_year+1900;}
    int month(){return tv.tm_mon;}
    int days(){return tv.tm_mday;}
    int hours(){return tv.tm_hour;}
    int min(){return tv.tm_min;}
    int sec(){return tv.tm_sec;}

    unsigned long second(){return secc;}

    unsigned long long milisecond(){return u_sec/1000;}

    void sleep(unsigned long msecond);
    double operator -(const timer &p);

    string format(const string &s);



    private:
    struct tm tv;
    unsigned long secc;
    unsigned long long u_sec;

};

}
