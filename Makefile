.PHONY: all clean # Mark all and clean as phony, so make does not get confused if we ever create files called all and clean.

#Variables
EXE_NAME = game
OBJDIR   = obj
CXX      = g++
CXXFLAGS = -Wall -Wextra -std=c++17 # Use C++/17 standard plus add more warnings.
SFMLFLAGS  = -lsfml-graphics -lsfml-window -lsfml-system # Flags for SFML library, we need to link them to the app.

# List of build object files.
OBJS = $(OBJDIR)/main.o

# Build all.
all: $(EXE_NAME)

# Automatic variables:
# $@ → target name (game)
# $^ → all prerequisites (obj/main.o)
# $< → first prerequisite (main.cpp)

# Link.
$(EXE_NAME): $(OBJS)
	$(CXX) -o $@ $^ $(SFMLFLAGS)

# Compile main when main.cpp changes. OBJDIR must exist, but changing its timestamp does not trigger build.
# $< is the first prequisite:
#                    |
# $@ is the target:  |
#         |          |
#  -------------  --------
$(OBJDIR)/main.o: main.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create objdir if it does not exist.
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Clean objects and the exe.
clean:
	rm -rf $(OBJDIR) $(EXE_NAME)


