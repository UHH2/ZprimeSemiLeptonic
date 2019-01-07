CC = g++
CFLAGS = -std=c++0x -Wall -lMinuit
LFLAGS = -Wall -I. -lm
LIBSMAIN = `root-config --cflags --evelibs`
LIBS = `root-config  --cflags --evelibs`

INCDIR   = include
SRCDIR   = src
OBJDIR   = obj

SOURCES  := $(wildcard $(SRCDIR)/*.cc)
INCLUDES := $(wildcard $(INCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cc=$(OBJDIR)/%.o)

all: main

main: $(OBJECTS)
	@$(CC) $(OBJECTS) $(LFLAGS) -o $@ $(LIBSMAIN)

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cc
	@$(CC) $(CFLAGS) -c $< -o $@ $(LIBSMAIN)


clean:
	@rm -f $(OBJECTS)
