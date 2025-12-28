.PHONY: all clean # Mark all and clean as phony, so make does not get confused if we ever create files called all and clean.

#Variables
EXE_NAME = game
OBJDIR   = obj
CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -MMD -MP # Use C++/17 standard plus add more warnings and handle header file dependencies.
LDLIBS  = -lsfml-graphics -lsfml-window -lsfml-system # Flags for SFML library, we need to link them to the app.
INCLUDES = -ILogging

# All source files
SRCS = \
	main.cpp \
	Logging/logger_base.cpp \
	Logging/console_logger.cpp \
	Logging/multi_logger.cpp

# Convert src paths to obj paths
OBJS = $(SRCS:%.cpp=$(OBJDIR)/%.o)

# Build all.
all: $(EXE_NAME)

# Automatic variables:
# $@ → target name (game)
# $^ → all prerequisites (obj/main.o)
# $< → first prerequisite (main.cpp)

# Link.
$(EXE_NAME): $(OBJS)
	$(CXX) -o $@ $^ $(LDLIBS)
	
# Pattern rule for compiling any .cpp file in OBJDIR folder.
$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@


# Clean objects and the exe.
clean:
	rm -rf $(OBJDIR) $(EXE_NAME)


-include $(OBJS:.o=.d)