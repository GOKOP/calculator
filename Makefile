CC=g++
CFLAGS=-Isrc

OBJDIR=obj
SRCDIR=src

SRC=$(wildcard $(SRCDIR)/*.cpp)
DEPS=$(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.d,$(SRC))
OBJ=$(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRC))

calc: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

-include $(DEPS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) -MMD -MP -c -o $@ $< $(CFLAGS)
