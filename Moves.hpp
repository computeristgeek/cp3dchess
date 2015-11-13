#ifndef __MOVES_HPP__
#define __MOVES_HPP__
#include "Constants.hpp"
extern bool turn;
extern int **Board; //Chars.hpp
extern bool flipped; //Chars.hpp
extern int *charsPosition; //Chars.hpp
extern bool Debug; //Debug.hpp
int Max(int num1,int num2);
int Min(int num1,int num2);
void swap(int *num1,int *num2);
bool kingProtected(int from, int to);
bool inFront(int i1, int j1, int i2, int j2);
bool movePiece(int pieceName, int from, int to);
bool whiteChar(int character); //Chars.hpp
#endif //__MOVES_HPP__
