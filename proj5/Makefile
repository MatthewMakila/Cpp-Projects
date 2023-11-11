CXX = g++
CXXFLAGS = -Wall -g

proj5: Vector.o Runner.o proj5.cpp
	$(CXX) $(CXXFLAGS) Vector.o Runner.o proj5.cpp -o proj5

Runner.o: Runner.cpp Vector.cpp
	$(CXX) $(CXXFLAGS) -c Runner.cpp

Vector.o: Vector.cpp
	$(CXX) $(CXXFLAGS) -c Vector.cpp

run1:
	./proj5 data1.txt

run2:
	./proj5 data2.txt

run3:
	./proj5 data3.txt

run4:
	./proj5 data4.txt

val1:
	valgrind ./proj5 data1.txt

val2:
	valgrind ./proj5 data2.txt

val3:
	valgrind ./proj5 data3.txt

val4:
	valgrind ./proj5 data4.txt

##Use this to clean out your directory
clean:
	rm *~
	rm *.o

##Use this when you want to debug your whole project
debug1:
	gdb gdbarg1 --args ./proj5 data1.txt
