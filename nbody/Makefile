CXX = g++
CXXFLAGS = -Wall -std=c++17
TARGET = nbody
SRC = nbody.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET) solar.tsv 86400 100

clean:
	rm -f $(TARGET) output.tsv
