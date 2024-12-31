# Compiler and flags
CC = g++
CCFLAGS = -g -w -std=c++11
DEPFLAGS = -MMD -MP
CCFLAGS += $(DEPFLAGS)
CCLIBS = -lncurses

# List of object files
OBJS = main.o Gui.o Game.o Player.o Bullet.o

# Target executable
mygame: $(OBJS)
	$(CC) $(CCFLAGS) -o $@ $(OBJS) $(CCLIBS)

# Pattern rule for compiling .C files to .o files
%.o: %.C
	$(CC) $(CCFLAGS) -c -o $@ $<

# Include generated dependency files
-include $(OBJS:.o=.d)

# Phony targets
.PHONY: clean rebuild
clean:
	rm -rf mygame $(OBJS) $(OBJS:.o=.d)

rebuild: clean mygame