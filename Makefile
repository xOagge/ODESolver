CXX = g++
CXXFLAGS = `root-config --libs --cflags`

SRCS = $(wildcard src/*.cpp)

A:
	$(CXX) main/main.cpp $(SRCS) $(CXXFLAGS) -Isrc -o bin/main.exe

B:
	$(CXX) main/rImagem_B.cpp $(SRCS) $(CXXFLAGS) -Isrc -o bin/rImagem_B.exe

# bin/rImagem_A.exe: main/rImagem_A.cpp
#	$(CXX) $< $(SRCS) $(CXXFLAGS) -Isrc -o $@

# bin/rImagem_B.exe: main/rImagem_B.cpp
# 	$(CXX) $< $(SRCS) $(CXXFLAGS) -Isrc -o $@

