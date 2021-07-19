CC=g++
CFLAGS=-Isrc

OBJDIR=obj
SRCDIR=src

_DEPS=Lexer.hpp Token.hpp
_OBJ=main.o Lexer.o

DEPS=$(patsubst %,$(SRCDIR)/%,$(_DEPS))
OBJ=$(patsubst %,$(OBJDIR)/%,$(_OBJ))

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	@mkdir -p $(@D)
	$(CC) -c -o $@ $< $(CFLAGS)

calc: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
