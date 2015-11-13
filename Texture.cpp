#include <GL/glut.h>
#include <iostream>
#include <cstdio>
#include "Texture.hpp"
using namespace std;

GLuint	*texture= new GLuint[max];

int ImageLoad(const char *filename, Image *image)
{
	FILE *file;
	unsigned long size;                 // size of the image in bytes.
	unsigned long i;                    // standard counter.
	unsigned short int planes;          // number of planes in image (must be 1) 
	unsigned short int bpp;             // number of bits per pixel (must be 24)
	char temp;                          // used to convert bgr to rgb color.
	// Make sure the file exists
	if ((file = fopen(filename, "rb"))==NULL)
	{
		printf("File Not Found : %s\n",filename);
		return 0;
	}
	// Skip to bmp header
	fseek(file,18, SEEK_CUR);
	// read width
	if ((i = fread(&image->sizeX, 4, 1, file)) != 1) {
		printf("Error reading width from %s.\n", filename);
		return 0;
	}
	//printf("Width of %s: %lu\n",filename, image->sizeX);
	//read the height
	if ((i = fread(&image->sizeY,4,1,file)) != 1) {
		printf("Error reading height from %s.\n", filename);
		return 0;
	}
	//printf("Height of %s: %lu\n", filename, image->sizeY);
//	image->sizeX=image->sizeY=256;//fixes bug
	// calculate the size (assuming 24 bpp)
	size = image->sizeX * image->sizeY * 3;
	//cout<<image->sizeX<<" "<<image->sizeY<<" "<<endl;
	// read the planes
	if ((fread(&planes, 2, 1, file)) != 1) {
		printf("Error reading planes from %s. \n", filename);
		return 0;
	}
	if (planes != 1) {
		printf("Planes from %s is not 1: %u\n", filename, planes);
		return 0;
	}
	// read the bpp
	if ((i = fread(&bpp, 2, 1, file)) != 1) {
		printf("Error reading bpp from %s. \n", filename);
		return 0;
	}
	if (bpp != 24) {
		printf("Bpp from %s is not 24: %u\n", filename, bpp);
		return 0;
	}
	// seek past the rest of the bitmap header
	fseek(file, 24, SEEK_CUR);
	// Read the data
	image->data = (char *) malloc(size);
	if (image->data == NULL) {
		printf("Error allocating memory for colour-corrected image data");
		return 0;
	}
	if ((i = fread(image->data,size,1,file)) != 1) {
		printf("Error reading image data from %s.\n", filename);
		return 0;
	}
	// reverse all of the colours bgr => rgb)
	for (i=0;i<size;i+=3) {
		temp = image->data[i];
		image->data[i] = image->data[i+2];
		image->data[i+2] = temp;
	}
	return 1;
}

void LoadGLTexture(const char *filename, int textNum)
{
	// Stores the texture
	Image *image1;

	// Allocate space for texture
	image1 = (Image *) malloc(sizeof(Image));
	if (image1 == NULL) {
		cout<<"Error allocating space for image"<<endl;
		exit(0);
	}

	if (!ImageLoad(filename, image1)) {
		exit(1);
	}

	// create Texture
	glGenTextures(1, &texture[textNum]);

	// texture 2 (linear scaling)
	glBindTexture(GL_TEXTURE_2D, texture[textNum]);   // 2d texture (x and y size)
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image1->sizeX, image1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image1->data);
	free(image1);
}


void LoadGLTextures()
{
	LoadGLTexture("BWTop.bmp",CHESS_BOARD);
	LoadGLTexture("woodBottom.bmp",BOTTOM_WOOD);
	LoadGLTexture("wood.bmp",SIDE_WOOD);
	LoadGLTexture("Wwood.bmp",WHITE_WOOD);
	LoadGLTexture("Bwood.bmp",BLACK_WOOD);
	LoadGLTexture("WwoodChoice.bmp",WHITE_WOOD_C);
	LoadGLTexture("BwoodChoice.bmp",BLACK_WOOD_C);
}
