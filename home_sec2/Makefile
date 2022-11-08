hs: HomeSecurity.o Parser.o Room.o main.o
	g++ -g -o hs HomeSecurity.o Parser.o Room.o main.o

main.o: main.cpp
	g++ -g -c main.cpp

HomeSecurity.o: HomeSecurity.cpp HomeSecurity.h
	g++ -g -c HomeSecurity.cpp

Parser.o: Parser.cpp Parser.h
	g++ -g -c Parser.cpp
	
Room.o: Room.cpp Room.h
	g++ -g -c Room.cpp

clean:
	rm -f *.o hs
	
level_1:
	@echo "\n*** Level 1 Test ***"
	./hs  hs_l1_in.txt > test1.txt
	diff test1.txt hs_l1_out.txt
	
level_2:
	@echo "\n*** Level 2 Test ***"
	./hs  hs_l2_in.txt > test2.txt
	diff test2.txt hs_l2_out.txt
	
level_3:
	@echo "\n*** Level 3 Test ***"
	./hs  hs_l3_in.txt > test3.txt
	diff test3.txt hs_l3_out.txt
	
testall: level_1 level_2 level_3
	
all: clean hs