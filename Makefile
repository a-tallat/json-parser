CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g
TARGET = app
SRC = $(wildcard *.cpp)
OBJ = $(addprefix build/, $(SRC:.cpp=.o)) 

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o build/$(TARGET)

build/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ 

prep:
	for file in $(SRC); do \
		$(CXX) $(CXXFLAGS) -E $$file -o build/$${file%.cpp}.ii; \
	done

run: $(TARGET)
	./build/$(TARGET)

clean:
	rm -f build/$(TARGET) $(OBJ) build/*.ii