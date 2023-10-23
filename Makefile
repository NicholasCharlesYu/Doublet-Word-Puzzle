compiler = g++
flags = -g -Wall -std=c++11
compile = $(compiler) $(flags)

doublet: doublet.cpp MinHeap.h
	$(compile) doublet.cpp MinHeap.h -o doublet

.PHONY: clean
clean:
	rm -rf *.o doublet
