CXX = g++
CXXFLAGS=-std=c++17 -Wall

OBJS = Value.o main.o


#all depends on value
all:a.out

#value depends on objs. it compiules and links the variables to produce value
a.out : $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

Value.o : Value.cpp Value.h
	$(CXX) $(CXXFLAGS) -c Value.cpp

main.o : main.cpp Value.h
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f value $(OBJS)
