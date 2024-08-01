CXX = g++
CXXFLAGS = -std=c++20 -Wall

all: utms.out

utms.out: main.o Student.o User.o App_Handler.o UTMS.o Prof.o Major.o Course.o Data_Reader.o Exception.o Split.o
	$(CXX) main.o Student.o User.o App_Handler.o UTMS.o Prof.o  Major.o Course.o Data_Reader.o Exception.o  Split.o -o utms.out

main.o: main.cpp App_Handler.hpp
	$(CXX) -c main.cpp -o main.o

Student.o: Student.cpp App_Handler.hpp User.hpp Course.hpp Exception.hpp
	$(CXX) -c Student.cpp -o Student.o

User.o: User.cpp Exception.hpp
	$(CXX) -c User.cpp -o User.o

App_Handler.o: App_Handler.cpp Student.hpp UTMS.hpp Exception.hpp Data_Reader.hpp Split.hpp
	$(CXX) -c App_Handler.cpp -o App_Handler.o

UTMS.o: UTMS.cpp Student.hpp Prof.hpp Major.hpp Course.hpp Exception.hpp
	$(CXX) -c UTMS.cpp -o UTMS.o

Prof.o: Prof.cpp Student.hpp
	$(CXX) -c Prof.cpp -o Prof.o	

Major.o: Major.cpp
	$(CXX) -c Major.cpp -o Major.o

Course.o: Course.cpp Prof.hpp Split.hpp
	$(CXX) -c Course.cpp -o Course.o

Exception.o: Exception.cpp
	$(CXX) -c Exception.cpp -o Exception.o

Data_Reader.o: Data_Reader.cpp UTMS.hpp
	$(CXX) -c Data_Reader.cpp -o Data_Reader.o

Split.o: Split.cpp
	$(CXX) -c Split.cpp -o Split.o

clean:
	rm -f utms.out *.o