CXX=gcc
CPP=g++


all: singleton pollServer pollClient guard

guard: guard.o
	$(CPP) guard.o -o guard -lpthread
guard.o: guard.cpp
	$(CPP) -c guard.cpp
singleton: singleton.o
	$(CPP) singleton.o -o singleton
singleton.o: singleton.cpp
	$(CPP) -c singleton.cpp
pollServer: pollServer.o 
	$(CPP) pollServer.cpp reactor.cpp -o pollServer -pthread -lpthread 
pollServer.o: pollServer.cpp
	$(CPP) -c pollServer.cpp
pollClient: pollClient.o
	$(CPP) pollClient.cpp -o pollClient -lpthread
pollClient.o: pollClient.cpp
	$(CPP) -c pollClient.cpp

.PHONY: all clean
clean:
	rm -f *.o main1 guard singleton pollServer pollClient ao_client test_ao_client
