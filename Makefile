

main: *.cc *.cpp
	g++ -ggdb -O3 *.cpp main.cc -o main

shell: *.cc
	g++ -ggdb -O3 shell.cc -o shell

