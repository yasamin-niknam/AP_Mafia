a.out: main.o interface.o players.o mafia.o godfather.o silencer.o villager.o detector.o doctor.o rouintan.o joker.o room.o BadInputException.o
	g++ main.o interface.o players.o mafia.o godfather.o silencer.o villager.o detector.o doctor.o rouintan.o joker.o room.o BadInputException.o

main.o: interface.o main.cpp 
	g++ -c main.cpp -o main.o 

interface.o: interface.cpp interface.hpp players.o mafia.o godfather.o silencer.o villager.o detector.o doctor.o rouintan.o joker.o room.o BadInputException.o 
	g++ -c interface.cpp -o interface.o

room.o: room.cpp room.hpp players.o mafia.o godfather.o silencer.o villager.o detector.o doctor.o rouintan.o joker.o
	g++ -c room.cpp -o room.o

players.o: players.cpp players.hpp
	g++ -c players.cpp -o players.o

BadInputException.o: BadInputException.cpp BadInputException.hpp
	g++ -c BadInputException.cpp -o BadInputException.o

mafia.o: mafia.cpp mafia.hpp
	g++ -c mafia.cpp -o mafia.o

godfather.o: godfather.cpp godfather.hpp mafia.hpp
	g++ -c godfather.cpp -o godfather.o

silencer.o: silencer.cpp silencer.hpp mafia.hpp
	g++ -c silencer.cpp -o silencer.o

villager.o: villager.cpp villager.hpp
	g++ -c villager.cpp -o villager.o

detector.o: detector.cpp detector.hpp villager.o players.o
	g++ -c detector.cpp -o detector.o

doctor.o: doctor.cpp doctor.hpp villager.o
	g++ -c doctor.cpp -o doctor.o

rouintan.o: rouintan.cpp rouintan.hpp villager.o
	g++ -c rouintan.cpp -o rouintan.o

joker.o: joker.cpp joker.hpp players.o
	g++ -c joker.cpp -o joker.o

clean:
	rm -r *.o
	rm -r *.out