CXX=g++
CXXFLAGS=-std=c++17 -pthread

all:
	$(CXX) $(CXXFLAGS) src/*.cpp -o log_processor

clean:
	rm -f log_processor
