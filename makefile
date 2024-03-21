
srcs:=$(shell find ./* -type f | grep '.cpp' |grep -v 'main.cpp' )

$(warning srcs is $(srcs))

objs:=$(patsubst %.cpp, %.o,$(filter %.cpp, $(srcs)))

$(warning obj is $(objs))

CFLAGS = -g -O2 -Wall -Werror -Wno-unused  -fPIC -std=c++11 -I./utility
$(warning CFLAGS is ${CFLAGS})

INCLUDE = -I.

src_main = main.cpp

obj_main = main.o

exe_main = a.exe

target :$(exe_main)

$(exe_main):$(objs) $(obj_main) 
	g++ $^  $(INCLUDE) -g -o $@  

%.o: %.cpp
	g++  $(INCLUDE) -g -c $< -o $@


tar:
	g++ $(CFLAGS) ./utility/value.cpp ./utility/xml.cpp ./main.cpp ./utility/parse_xml.cpp -o tar