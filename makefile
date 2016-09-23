# Example 6
ASSIGN=hw3

# Main target
all: $(ASSIGN)

#  MinGW
ifeq "$(OS)" "Windows_NT"
CFLG=-O3 -Wall
LIBS=-lglut32cu -lglu32 -lopengl32
CLEAN=del *.exe *.o *.a
else
#  OSX
ifeq "$(shell uname)" "Darwin"
CFLG=-O3 -Wall -Wno-deprecated-declarations
LIBS=-framework GLUT -framework OpenGL
#  Linux/Unix/Solaris
else
CFLG=-O3 -Wall
LIBS=-lglut -lGLU -lGL -lm
endif
#  OSX/Linux/Unix/Solaris
CLEAN=rm -f $(ASSIGN1) *.o *.a
endif

#Dependencies
hw3.o: hw3.c 


# Compile rules
#Preceding dot means that target is not a valid default target: more needs to be done once it's made
#These targets use suffix rules
.c.o:
	gcc -c $(CFLG) $<
.cpp.o:
	g++ -c $(CFLG) $<

#  Link
hw3: hw3.o 
	gcc -O3 -o $@ $^   $(LIBS)

#  Clean
clean:
	$(CLEAN)
