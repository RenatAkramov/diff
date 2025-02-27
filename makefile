all: clean diff

flags = -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall 
diff: differentiator.o grafdump.o read_tree.o lec.o main.o simplifare.o print_Latex.o
	g++ differentiator.o grafdump.o read_tree.o lec.o print_Latex.o main.o simplifare.o -o ./a.out

differentiator.o: differentiator.cpp
	g++ -c $(flags) differentiator.cpp

grafdump.o: grafdump.cpp
	g++ -c $(flags) grafdump.cpp

read_tree.o: read_tree.cpp
	g++ -c $(flags) read_tree.cpp

lec.o: lec.cpp
	g++ -c $(flags) lec.cpp

main.o: main.cpp
	g++ -c $(flags) main.cpp

simplifare.o: simplifare.cpp
	g++ -c $(flags) simplifare.cpp

print_Latex.o: print_Latex.cpp
	g++ -c $(flags) print_Latex.cpp

clean:
	rm -rf *.o *.exe *.exe.log *.exe.log.dmp *.out
