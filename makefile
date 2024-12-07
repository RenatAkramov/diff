all: diff clean

flags = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE


diff: differentiator.o grafdump.o read_tree.o
	g++ differentiator.o grafdump.o read_tree.o -o .\a.exe

differentiator.o: differentiator.cpp
	g++ -c $(flags) differentiator.cpp

grafdump.o: grafdump.cpp
	g++ -c $(flags) grafdump.cpp

read_tree.o: read_tree.cpp
	g++ -c $(flags) read_tree.cpp

clean:
	rm -rf *.o *.exe *.exe.log *.exe.log.dmp