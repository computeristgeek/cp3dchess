#ifndef __DEBUG_HPP__
#define __DEBUG_HPP__
extern bool Debug, freee;
extern bool flipped; //Chars.hpp
extern int *charsPosition; //Chars.hpp

void flipBoard(int **Board);
bool fullDebugMode(char* message);
#endif //__DEBUG_HPP__
