#ifndef __CHESS_HPP__
#define __CHESS_HPP__
#include "Constants.hpp"
#include "Types.hpp"
extern int RenderMode;
extern bool Debug; //Debug.hpp
extern bool freee; //Debug.hpp
extern int **Board; //Chars.hpp
extern bool turn; //Chars.hpp
extern int *charsPosition; //Chars.hpp

void draw();
void mouse(int button, int state, int x, int y);
void skb(int button, int x, int y);
void kb(unsigned char button, int x, int y);
void initialize();
//extern functions from Texture.hpp
int ImageLoad(const char *filename, Image *image);
void LoadGLTextures();
//extern functions from Debug.hpp
void flipBoard(int **Board);
bool fullDebugMode(char* message);
//extern functions from Moves.hpp
bool movePiece(int pieceName, int from, int to);
//extern functions from Chars.hpp
void drawBoard(int chosen);
void drawChars(bool initialize, int choice);
bool whiteChar(int character);
#endif //__CHESS_HPP__
