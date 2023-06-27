# Define the link target.
linkTarget = program

# Define the libraries that we need.
LIBS = -lSDL2 -lSDL2_image -lglfw -lGL -lGLU

# Define any flags.
CFLAGS = -std=c++17 -Ofast -g

# Define the object files that we need to use.
objects = main.o \
			ray.o \
			camera.o \
			$(patsubst %.cpp,%.o,$(wildcard ./BRDFs/*.cpp)) \
			$(patsubst %.cpp,%.o,$(wildcard ./Materials/*.cpp)) \
			$(patsubst %.cpp,%.o,$(wildcard ./Scene/*.cpp)) \
			$(patsubst %.cpp,%.o,$(wildcard ./Tracers/*.cpp)) \
			$(patsubst %.cpp,%.o,$(wildcard ./Samplers/*.cpp)) \
			$(patsubst %.cpp,%.o,$(wildcard ./Objects/*.cpp)) \
			$(patsubst %.cpp,%.o,$(wildcard ./Lights/*.cpp))
					
# Define the rebuildables.
rebuildables = $(objects) $(linkTarget)

# Rule to actually perform the build.
$(linkTarget): $(objects)
	g++ -g -o $(linkTarget) $(objects) $(LIBS) $(CFLAGS)
	
# Rule to create the .o (object) files.
%.o: %.cpp
	g++ -o $@ -c $< $(CFLAGS)
	
.PHONEY:
clean:
	rm $(rebuildables)