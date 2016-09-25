CC = g++
CFLAGS = -Wall -std=c++11 -g -I$(INCDIR)
INCDIR = ./include/
OBJDIR = ./obj/
SRCDIR = ./src/

TrieTest: $(OBJDIR)TrieTest.o $(OBJDIR)Trie.o $(OBJDIR)Node.o
	$(CC) $(CFLAGS) -o TrieTest $(OBJDIR)TrieTest.o $(OBJDIR)Trie.o $(OBJDIR)Node.o 

	
$(OBJDIR)TrieTest.o: $(SRCDIR)TrieTest.cpp $(INCDIR)Trie.h
	$(CC) $(CFLAGS) -c $(SRCDIR)TrieTest.cpp -o $(OBJDIR)TrieTest.o
	
$(OBJDIR)Trie.o: $(SRCDIR)Trie.cpp $(INCDIR)Trie.h
	$(CC) $(CFLAGS) -c $(SRCDIR)Trie.cpp -o $(OBJDIR)Trie.o		

$(OBJDIR)Node.o: $(SRCDIR)Node.cpp
	$(CC) $(CFLAGS) -c $(SRCDIR)Node.cpp -o $(OBJDIR)Node.o

clean:
	rm TrieTest $(OBJDIR)*
