CC=g++
CFLAGS=-Isrc

OBJDIR=obj
SRCDIR=src

DEPS=$(wildcard $(SRCDIR)/*.hpp)
SRC=$(wildcard $(SRCDIR)/*.cpp)
OBJ=$(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRC))

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	@mkdir -p $(@D)
	$(CC) -c -o $@ $< $(CFLAGS)

calc: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
