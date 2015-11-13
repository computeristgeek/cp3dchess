#ifndef __TEXTURE_HPP__
#define __TEXTURE_HPP__
#include "Constants.hpp"

extern GLuint	*texture;		// Storage for 3 textures.
#include "Types.hpp"
int ImageLoad(const char *filename, Image *image);
void LoadGLTexture(const char *filename, int textNum);
void LoadGLTextures();
#endif //__TEXTURE_HPP__
