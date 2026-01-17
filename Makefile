# Mark all and clean as phony, so make does not get confused if we ever create files called all and clean.
.PHONY: all clean 

#Variables
EXE_NAME = game
OBJDIR   = obj
CXX      = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Wpedantic -MMD -MP # Use C++/20 standard plus add more warnings and handle header file dependencies.
LDLIBS  = -lsfml-graphics -lsfml-window -lsfml-system # Flags for SFML library, we need to link them to the app.
INCLUDES = -ILogging -IConfiguration 

# All source files
SRCS = \
	main.cpp \
	Logging/logger_base.cpp \
	Logging/console_logger.cpp \
	Logging/multi_logger.cpp \
	Logging/logger.cpp \
	Logging/logging.cpp \
	Logging/file_logger.cpp \
	Configuration/toml_config.cpp \
	Configuration/configuration.cpp

# Convert src paths to obj paths
OBJS = $(SRCS:%.cpp=$(OBJDIR)/%.o)

# Build all.
all: $(EXE_NAME)

# Automatic variables:
# $@ → target name (game)
# $^ → all prerequisites (obj/main.o, obj/Logging/logger.o ...)
# $< → first prerequisite (e.g. main.cpp)

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

# Depency mapping stuff, related to CXXFLAGS = -MMD -MP.
-include $(OBJS:.o=.d)