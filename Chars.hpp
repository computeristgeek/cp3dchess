#ifndef __CHARS_HPP__
#define __CHARS_HPP__
#include "Constants.hpp"

extern int **Board,*charsPosition;
extern bool flipped;
extern int RenderMode; //Chess.hpp
extern GLuint *texture; //Texture.hpp

bool whiteChar(int character);
void drawBoard(int chosen);
void drawAskari(float x, float y, float z, bool blackWhite, bool chosen);
void drawWazeer(float x, float y, float z, bool blackWhite, bool chosen);
void drawMalek(float x, float y, float z, bool blackWhite, bool chosen);
void drawTabya(float x, float y, float z, bool blackWhite, bool chosen);
void drawHosan(float x, float y, float z, bool blackWhite, bool chosen);
void drawFeel(float x, float y, float z, bool blackWhite, bool chosen);
void drawChars(bool initialize, int choice);

#endif //__CHARS_HPP__
