# Variables
CC = g++
CFLAGS = -Wall -g -O3
SRCDIR = src
BUILDDIR = build
TARGET = $(BUILDDIR)/Poker

Poker: $(SRCDIR)/*
	$(CC) $(SRCDIR)/*.cpp $(CFLAGS) -o $(TARGET)

clean:
	rm -rf $(BUILDDIR)







