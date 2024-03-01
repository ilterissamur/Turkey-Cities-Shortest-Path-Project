CC=g++
CFLAGS=-g -Wall

SRCDIR=src
HEADERDIR=include
BINDIR=bin
OBJDIR=obj
BIN=$(BINDIR)/main

SRCS=$(wildcard $(SRCDIR)/*.cpp)
OBJS=$(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

all:$(BIN)

release: CFLAGS=-O2 -DNDEBUG
release: clean
release:$(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -I $(HEADERDIR) -c $< -o $@

run:
	$(BIN)

clean:
	powershell rm -r $(OBJDIR)/*.o