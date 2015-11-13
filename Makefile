# compiler to use, storing in a variable
# in case you want to change it easily
CC=g++
# along with its FLAGS/options
CFLAGS=-g -c -Wall

#all the program depends on cp3c
all: cp3c

#cp3c depends on these object files
cp3c: Debug.o Texture.o Moves.o Chars.o Chess.o 
	# compile using compiler in CC variable
	# using all the dependencies "$^"
	# and output the name of the dependent "$@"
	$(CC) $^ -o $@ -lglut -lGL -lGLU -lGLEW

Debug.o: Debug.cpp Debug.hpp Types.hpp
	$(CC) $(CFLAGS) Debug.cpp

Texture.o: Texture.cpp Texture.hpp Constants.hpp wood.bmp woodBottom.bmp Wwood.bmp WwoodChoice.bmp Bwood.bmp BwoodChoice.bmp BWTop.bmp
	$(CC) $(CFLAGS) Texture.cpp

Moves.o: Moves.cpp Moves.hpp Constants.hpp
	$(CC) $(CFLAGS) Moves.cpp

Chars.o: Chars.cpp Chars.hpp Constants.hpp
	$(CC) $(CFLAGS) Chars.cpp

Chess.o: Chess.cpp Chess.hpp Constants.hpp Types.hpp
	$(CC) $(CFLAGS) Chess.cpp

clean:
	rm *.o cp3c
