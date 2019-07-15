OBJS = kvfs.o
CXX = g++
CXXFLAGS = -std=c++11 -D_FILE_OFFSET_BITS=64
LDLIBS = $(shell pkg-config --libs fuse)

kvfs: $(OBJS)
	g++ -D_FILE_OFFSET_BITS=64 -o $@ $(OBJS) $(LDLIBS)

kvfs.o: kvfs.cpp
	g++ $(CXXFLAGS) -c $<

.PHONY: clean
clean:
	rm kvfs $(OBJS)
