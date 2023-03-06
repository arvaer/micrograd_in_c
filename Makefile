CXX = g++
CXXFLAGS=-std=c++17 -Wall -Wextra -pedantic
# Directories
SRCDIR = src
INCDIR = include
BUILDDIR = build
# Files
EXECUTABLE = main
SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)
INCLUDES = -I $(INCDIR)

# Targets
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: clean

clean:
	rm -f $(BUILDDIR)/*.o $(EXECUTABLE)
