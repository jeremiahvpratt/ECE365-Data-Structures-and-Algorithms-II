dictionary.exe: dictionary.o hash.o
	g++ -o dictionary.exe dictionary.o hash.o

dictionary.o: dictionary.cpp hash.h
	g++ -c dictionary.cpp

hash.o: hash.cpp hash.h
	g++ -c hash.cpp

debug:
	g++ -g -o dictionaryDebug.exe dictionary.cpp hash.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
