#include <GL/glut.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#define DIV4 0.25
#define DIV8 0.125
#define DIV16 0.0625
#define DIV32 0.03125
using namespace std;
#include "Texture.cpp"
	#define whiteAskari0	0
	#define whiteAskari1	1
	#define whiteAskari2	2
	#define whiteAskari3	3
	#define whiteAskari4	4
	#define whiteAskari5	5
	#define whiteAskari6	6
	#define whiteAskari7	7
	#define blackAskari0	8
	#define blackAskari1	9
	#define blackAskari2	10
	#define blackAskari3	11
	#define blackAskari4	12
	#define blackAskari5	13
	#define blackAskari6	14
	#define blackAskari7	15
	#define whiteFeel0	16
	#define whiteFeel1	17
	#define blackFeel0	18
	#define blackFeel1	19
	#define whiteHosan0	20
	#define whiteHosan1	21
	#define blackHosan0	22
	#define blackHosan1	23
	#define whiteTabya0	24
	#define whiteTabya1	25
	#define blackTabya0	26
	#define blackTabya1	27
	#define whiteMalek	28
	#define blackMalek	29
	#define whiteWazeer	30
	#define blackWazeer	31
#define PICK_TOL 1
#define PICK_BUFFER_SIZE 256
unsigned int PickBuffer[PICK_BUFFER_SIZE];

int Board[8][8],RenderMode,charsPosition[32];

void drawBoard(int chosen)
{
	if(RenderMode==GL_SELECT)
	for(int i=0;i<8;i++)for(int j=0;j<8;j++)
	{
		int num=8*i+j+32;
		glLoadName(num);
		//if(chosen==num && Board[i][j]!=-1) chosen=Board[i][j];//glColor3f(0,0,1);//glBindTexture(GL_TEXTURE_2D,texture[WHITE_WOOD_C]);
		//else if((num+i)%2==0)glColor3f(1,1,1);else glColor3f(0,0,0);//glBindTexture(GL_TEXTURE_2D,texture[BOTTOM_WOOD]);//if num%2==0 && i%2==0
		//glDisable(GL_TEXTURE_2D);
		glTranslatef(0.25*j,DIV32/4.0,0.25*i);
		glBegin(GL_QUADS);
		glVertex3f(-1,  0.125, -1);
		glVertex3f(-1,  0.125,  -1+0.25);
		glVertex3f(-1+0.25,  0.125,  -1+0.25);
		glVertex3f( -1+0.25,  0.125, -1);
		glEnd();
		glTranslatef(-0.25*j,-DIV32/4.0,-0.25*i);
		//glEnable(GL_TEXTURE_2D);
	}
	if(RenderMode==GL_RENDER)
	{
		glBindTexture(GL_TEXTURE_2D, texture[SIDE_WOOD]);
		glBegin(GL_QUADS);
			// Front Face (note that the texture's corners have to match the quad's corners)
			glNormal3f( 0.0f, 0.0f, 1.0f);					// front face points out of the screen on z.
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -0.125f,  1.0f);	// Bottom Left Of The Texture and Quad
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -0.125f,  1.0f);	// Bottom Right Of The Texture and Quad
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  0.125f,  1.0f);	// Top Right Of The Texture and Quad
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  0.125f,  1.0f);	// Top Left Of The Texture and Quad
		glEnd();

		glBindTexture(GL_TEXTURE_2D, texture[SIDE_WOOD]);
		glBegin(GL_QUADS);  
			// Back Face
			glNormal3f( 0.0f, 0.0f,-1.0f);					// back face points into the screen on z.
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -0.125f, -1.0f);	// Bottom Right Of The Texture and Quad
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  0.125f, -1.0f);	// Top Right Of The Texture and Quad
			glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  0.125f, -1.0f);	// Top Left Of The Texture and Quad
			glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -0.125f, -1.0f);	// Bottom Left Of The Texture and Quad
		glEnd();

		glBindTexture(GL_TEXTURE_2D, texture[CHESS_BOARD]);
		glBegin(GL_QUADS);	
			// Top Face
			//glNormal3f( 0.0f, 1.0f, 0.0f);					// top face points up on y.
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  0.125f, -1.0f);	// Top Left Of The Texture and Quad
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  0.125f,  1.0f);	// Bottom Left Of The Texture and Quad
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  0.125f,  1.0f);	// Bottom Right Of The Texture and Quad
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  0.125f, -1.0f);	// Top Right Of The Texture and Quad
		glEnd();

		glBindTexture(GL_TEXTURE_2D, texture[BOTTOM_WOOD]);
		glBegin(GL_QUADS);
			// Bottom Face       
			glNormal3f( 0.0f, -1.0f, 0.0f);					// bottom face points down on y. 
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -0.125f, -1.0f);	// Top Right Of The Texture and Quad
			glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -0.125f, -1.0f);	// Top Left Of The Texture and Quad
			glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -0.125f,  1.0f);	// Bottom Left Of The Texture and Quad
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -0.125f,  1.0f);	// Bottom Right Of The Texture and Quad
		glEnd();

		glBindTexture(GL_TEXTURE_2D, texture[SIDE_WOOD]);
		glBegin(GL_QUADS); 
			// Right face
			glNormal3f( 1.0f, 0.0f, 0.0f);					// right face points right on x.
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -0.125f, -1.0f);	// Bottom Right Of The Texture and Quad
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  0.125f, -1.0f);	// Top Right Of The Texture and Quad
			glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  0.125f,  1.0f);	// Top Left Of The Texture and Quad
			glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -0.125f,  1.0f);	// Bottom Left Of The Texture and Quad
		  
			// Left Face
			glNormal3f(-1.0f, 0.0f, 0.0f);					// left face points left on x.
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -0.125f, -1.0f);	// Bottom Left Of The Texture and Quad
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -0.125f,  1.0f);	// Bottom Right Of The Texture and Quad
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  0.125f,  1.0f);	// Top Right Of The Texture and Quad
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  0.125f, -1.0f);	// Top Left Of The Texture and Quad
		  
		glEnd();
	}
}

void drawAskari(float x, float y, float z, bool blackWhite, bool chosen)
{
	glBindTexture(GL_TEXTURE_2D, texture[((blackWhite)?((chosen)?WHITE_WOOD_C:WHITE_WOOD):((chosen)?BLACK_WOOD_C:BLACK_WOOD))]);

	glTranslatef(x,y,z);		// draw in required position
	if(blackWhite)glRotatef(180,0,1,0);
		if(RenderMode==GL_RENDER)
		{
			//base
			glTranslatef(0,-0.0625,0);
				glRotatef(90,1,0,0);		
					glutSolidTorus(DIV16-0.05,DIV16,64,64);
				glRotatef(-90,1,0,0);
			glTranslatef(0,0.0625,0);
			glTranslatef(0,-0.033,0);
				glRotatef(90,1,0,0);		
					glutSolidTorus(DIV16-0.05,DIV16,64,64);
				glRotatef(-90,1,0,0);
			glTranslatef(0,0.033,0);
		}
		//objects
		GLUquadricObj *AskariSphere=gluNewQuadric(),*AskariCylinder=gluNewQuadric(),*AskariCone=gluNewQuadric();
		//activate Texture
		gluQuadricTexture(AskariSphere,true);gluQuadricTexture(AskariCylinder,true);gluQuadricTexture(AskariCone,true);
		
		//head
		glTranslatef(0,DIV8,0);
		gluSphere(AskariSphere,DIV16-0.02,64,64);
		glTranslatef(0,-DIV8,0);
		//body
		glTranslatef(0,DIV8,0);
		glRotatef(90,1,0,0);
		gluCylinder(AskariCone,DIV32,DIV16,DIV8,64,64);
		glRotatef(-90,1,0,0);
		glTranslatef(0,-DIV8,0);


		glRotatef(90,1,0,0);
		gluCylinder(AskariCylinder,DIV16,DIV16,DIV16,64,64);
		glRotatef(-90,1,0,0);
	if(blackWhite)glRotatef(-180,0,1,0);
	glTranslatef(0-x,0-y,0-z);
}

void drawWazeer(float x, float y, float z, bool blackWhite, bool chosen)
{
	glBindTexture(GL_TEXTURE_2D, texture[((blackWhite)?((chosen)?WHITE_WOOD_C:WHITE_WOOD):((chosen)?BLACK_WOOD_C:BLACK_WOOD))]);
	glTranslatef(x,y,z);		// draw in required position
	if(blackWhite)glRotatef(180,0,1,0);
		GLUquadricObj *WazeerSphere=gluNewQuadric(),*WazeerCylinder=gluNewQuadric(),*WazeerCone=gluNewQuadric();
		gluQuadricTexture(WazeerSphere,true);gluQuadricTexture(WazeerCylinder,true);gluQuadricTexture(WazeerCone,true);
		if(RenderMode==GL_RENDER)
		{
			//base
			glTranslatef(0,-0.0625,0);
					glRotatef(90,1,0,0);		
						glutSolidTorus(DIV16-0.1,DIV16,64,64);
					glRotatef(-90,1,0,0);
			glTranslatef(0,0.0625,0);
			glTranslatef(0,-0.033,0);
					glRotatef(90,1,0,0);		
						glutSolidTorus(DIV16-0.1,DIV16,64,64);
					glRotatef(-90,1,0,0);
			glTranslatef(0,0.033,0);

			glDisable(GL_TEXTURE_2D);
			glTranslatef(0,DIV4+0.07125,0);
				glRotatef(90,1,0,0);
					glTranslatef(0,0.04,0);
						gluCylinder(WazeerCylinder,0,DIV32/4.0,DIV32,64,64);
					glTranslatef(0,-0.04,0);
					glTranslatef(0.04,0,0);
						gluCylinder(WazeerCylinder,0,DIV32/4.0,DIV32,64,64);
					glTranslatef(-0.04,0,0);
					glTranslatef(0.03,0.03,0);
						gluCylinder(WazeerCylinder,0,DIV32/4.0,DIV32,64,64);
					glTranslatef(-0.03,-0.03,0);
					glTranslatef(0,-0.04,0);
						gluCylinder(WazeerCylinder,0,DIV32/4.0,DIV32,64,64);
					glTranslatef(0,0.04,0);
					glTranslatef(-0.04,0,0);
						gluCylinder(WazeerCylinder,0,DIV32/4.0,DIV32,64,64);
					glTranslatef(0.04,0,0);
					glTranslatef(-0.03,-0.03,0);
						gluCylinder(WazeerCylinder,0,DIV32/4.0,DIV32,64,64);
					glTranslatef(0.03,0.03,0);
					glTranslatef(0.03,-0.03,0);
						gluCylinder(WazeerCylinder,0,DIV32/4.0,DIV32,64,64);
					glTranslatef(-0.03,0.03,0);
					glTranslatef(-0.03,0.03,0);
						gluCylinder(WazeerCylinder,0,DIV32/4.0,DIV32,64,64);	
					glTranslatef(0.03,-0.03,0);
			//glutSolidTorus(DIV32-0.001,DIV16-0.01,4,4);
				glRotatef(-90,1,0,0);
			glTranslatef(0,-DIV4-0.07125,0);
			glEnable(GL_TEXTURE_2D);
		}
		glTranslatef(0,DIV4,0);
			gluSphere(WazeerSphere,DIV16,64,64);
		glTranslatef(0,-DIV4,0);

		glTranslatef(0,DIV4,0);
			glRotatef(90,1,0,0);
				gluCylinder(WazeerCone,DIV32,DIV16,DIV4,64,64);
			glRotatef(-90,1,0,0);
		glTranslatef(0,-DIV4,0);

		glRotatef(90,1,0,0);
			gluCylinder(WazeerCylinder,DIV16,DIV16,DIV8,64,64);
		glRotatef(-90,1,0,0);
	if(blackWhite)glRotatef(-180,0,1,0);
	glTranslatef(0-x,0-y,0-z);
}

void drawMalek(float x, float y, float z, bool blackWhite, bool chosen)
{
	glBindTexture(GL_TEXTURE_2D, texture[((blackWhite)?((chosen)?WHITE_WOOD_C:WHITE_WOOD):((chosen)?BLACK_WOOD_C:BLACK_WOOD))]);
	glTranslatef(x,y,z);		// draw in required position
	if(blackWhite)glRotatef(180,0,1,0);
		GLUquadricObj *WazeerSphere=gluNewQuadric(),*WazeerCylinder=gluNewQuadric(),*WazeerCone=gluNewQuadric();
		gluQuadricTexture(WazeerSphere,true);gluQuadricTexture(WazeerCylinder,true);gluQuadricTexture(WazeerCone,true);
		if(RenderMode==GL_RENDER)
		{
			//base
			glTranslatef(0,-0.0625,0);
					glRotatef(90,1,0,0);		
						glutSolidTorus(DIV8-0.1,DIV8,64,64);
					glRotatef(-90,1,0,0);
			glTranslatef(0,0.0625,0);
			glTranslatef(0,-0.033,0);
					glRotatef(90,1,0,0);		
						glutSolidTorus(DIV8-0.1,DIV8,64,64);
					glRotatef(-90,1,0,0);
			glTranslatef(0,0.033,0);

			//crown spikes
			glDisable(GL_TEXTURE_2D);
			glTranslatef(0,DIV4+0.06125,0);
				glRotatef(90,1,0,0);
					glTranslatef(0,0.04,0);
						gluCylinder(WazeerCylinder,DIV32/4.0,DIV32/4.0,DIV32,64,64);
					glTranslatef(0,-0.04,0);
					glTranslatef(0.04,0,0);
						gluCylinder(WazeerCylinder,DIV32/4.0,DIV32/4.0,DIV32,64,64);
					glTranslatef(-0.04,0,0);
					glTranslatef(0.03,0.03,0);
						gluCylinder(WazeerCylinder,DIV32/4.0,DIV32/4.0,DIV32,64,64);
					glTranslatef(-0.03,-0.03,0);
					glTranslatef(0,-0.04,0);
						gluCylinder(WazeerCylinder,DIV32/4.0,DIV32/4.0,DIV32,64,64);
					glTranslatef(0,0.04,0);
					glTranslatef(-0.04,0,0);
						gluCylinder(WazeerCylinder,DIV32/4.0,DIV32/4.0,DIV32,64,64);
					glTranslatef(0.04,0,0);
					glTranslatef(-0.03,-0.03,0);
						gluCylinder(WazeerCylinder,DIV32/4.0,DIV32/4.0,DIV32,64,64);
					glTranslatef(0.03,0.03,0);
					glTranslatef(0.03,-0.03,0);
						gluCylinder(WazeerCylinder,DIV32/4.0,DIV32/4.0,DIV32,64,64);
					glTranslatef(-0.03,0.03,0);
					glTranslatef(-0.03,0.03,0);
						gluCylinder(WazeerCylinder,DIV32/4.0,DIV32/4.0,DIV32,64,64);	
					glTranslatef(0.03,-0.03,0);
				glRotatef(-90,1,0,0);
			glTranslatef(0,-DIV4-0.06125,0);
			glEnable(GL_TEXTURE_2D);

		}

		glTranslatef(0,DIV4,0);
			gluSphere(WazeerSphere,DIV16,64,64);
		glTranslatef(0,-DIV4,0);

		glTranslatef(0,DIV4,0);
			glRotatef(90,1,0,0);
				gluCylinder(WazeerCone,DIV32,DIV8,DIV4,64,64);
			glRotatef(-90,1,0,0);
		glTranslatef(0,-DIV4,0);

		glRotatef(90,1,0,0);
			gluCylinder(WazeerCylinder,DIV8,DIV8,DIV8,64,64);
		glRotatef(-90,1,0,0);
	if(blackWhite)glRotatef(-180,0,1,0);
	glTranslatef(0-x,0-y,0-z);
}


void drawTabya(float x, float y, float z, bool blackWhite, bool chosen)
{
	glBindTexture(GL_TEXTURE_2D, texture[((blackWhite)?((chosen)?WHITE_WOOD_C:WHITE_WOOD):((chosen)?BLACK_WOOD_C:BLACK_WOOD))]);
	glTranslatef(x,y,z);		// draw in required position
	if(blackWhite)glRotatef(180,0,1,0);
		if(RenderMode==GL_RENDER)
		{
			//base
			glTranslatef(0,-0.0625,0);
					glRotatef(90,1,0,0);		
						glutSolidTorus(/*DIV16-0.05*/DIV32,DIV16,64,64);
					glRotatef(-90,1,0,0);
			glTranslatef(0,0.0625,0);
			glTranslatef(0,-0.033,0);
					glRotatef(90,1,0,0);		
						glutSolidTorus(DIV16-0.05,DIV16,64,64);
					glRotatef(-90,1,0,0);
			glTranslatef(0,0.033,0);
		}
		GLUquadricObj *AskariSphere=gluNewQuadric(),*AskariCylinder=gluNewQuadric(),*AskariCone=gluNewQuadric();
		gluQuadricTexture(AskariSphere,true);gluQuadricTexture(AskariCylinder,true);gluQuadricTexture(AskariCone,true);


		glTranslatef(0,DIV8,0);
			glRotatef(90,1,0,0);
				gluCylinder(AskariCone,DIV16-0.01,DIV16,DIV8,64,64);
				glTranslatef(0,0,-DIV16);
					gluDisk(AskariSphere,0,DIV16,64,64);
					gluCylinder(AskariSphere,DIV16,DIV16,DIV16,64,64);
				glTranslatef(0,0,DIV16);
				gluDisk(AskariSphere,0,DIV16,64,64);
			glRotatef(-90,1,0,0);
		glTranslatef(0,-DIV8,0);


		glRotatef(90,1,0,0);
			gluCylinder(AskariCylinder,DIV16,DIV16,DIV16,64,64);
		glRotatef(-90,1,0,0);
	if(blackWhite)glRotatef(-180,0,1,0);
	glTranslatef(0-x,0-y,0-z);
}

void drawHosan(float x, float y, float z, bool blackWhite, bool chosen)
{
	glBindTexture(GL_TEXTURE_2D, texture[((blackWhite)?((chosen)?WHITE_WOOD_C:WHITE_WOOD):((chosen)?BLACK_WOOD_C:BLACK_WOOD))]);
	glTranslatef(x,y,z);		// draw in required position
	if(blackWhite)glRotatef(180,0,1,0);
		if(RenderMode==GL_RENDER)
		{
			//base
			glTranslatef(0,-0.0625,0);
					glRotatef(90,1,0,0);		
						glutSolidTorus(/*DIV16-0.05*/DIV32,DIV16,64,64);
					glRotatef(-90,1,0,0);
			glTranslatef(0,0.0625,0);
			glTranslatef(0,-0.033,0);
					glRotatef(90,1,0,0);		
						glutSolidTorus(DIV16-0.05,DIV16,64,64);
					glRotatef(-90,1,0,0);
			glTranslatef(0,0.033,0);
		}

		GLUquadricObj *AskariSphere=gluNewQuadric(),*AskariCylinder=gluNewQuadric(),*AskariCone=gluNewQuadric();
		gluQuadricTexture(AskariSphere,true);gluQuadricTexture(AskariCylinder,true);gluQuadricTexture(AskariCone,true);

	//neck
		glTranslatef(0,DIV8,0);
			glRotatef(90,1,0,0);
				glRotatef(15,0,1,0);

					glTranslatef(0,0,-DIV8);
							gluCylinder(AskariSphere,0,DIV16-0.01,DIV8,64,64);
					glTranslatef(0,0,DIV8);
				glRotatef(-15,0,1,0);

				glRotatef(-15,0,1,0);
				
					glTranslatef(0,0,-DIV8);
							gluCylinder(AskariSphere,0,DIV16-0.01,DIV8,64,64);
					glTranslatef(0,0,DIV8);
				glRotatef(15,0,1,0);
			glRotatef(-90,1,0,0);

			//eyes
			glDisable(GL_TEXTURE_2D);
						glTranslatef(DIV32,DIV32,DIV32+0.01);
							gluSphere(AskariSphere,DIV32/4.0,64,64);
						glTranslatef(-DIV32,-DIV16,-DIV32-0.01);
						glTranslatef(-DIV32,DIV16,DIV32+0.01);
							gluSphere(AskariSphere,DIV32/4.0,64,64);
						glTranslatef(DIV32,-DIV32,-DIV32-0.01);
			glEnable(GL_TEXTURE_2D);

			//end of mouth
			glTranslatef(0,-DIV32-0.01,DIV8-0.01);
				gluSphere(AskariSphere,DIV32,64,64);
			glTranslatef(0,DIV32+0.01,-DIV8+0.01);

			//face
			glRotatef(200,1,0,0);
				glTranslatef(0,0,-DIV8);
						gluCylinder(AskariSphere,DIV32,DIV16-0.01,DIV8,64,64);
				glTranslatef(0,0,DIV8);
			glRotatef(-200,1,0,0);

			glRotatef(90,1,0,0);
				gluCylinder(AskariCone,DIV16-0.01,DIV16,DIV8,64,64);
			glRotatef(-90,1,0,0);
		glTranslatef(0,-DIV8,0);

		glRotatef(90,1,0,0);
		gluCylinder(AskariCylinder,DIV16,DIV16,DIV16,64,64);
		glRotatef(-90,1,0,0);
	if(blackWhite)glRotatef(-180,0,1,0);
	glTranslatef(0-x,0-y,0-z);

}

void drawFeel(float x, float y, float z, bool blackWhite, bool chosen)
{
	glBindTexture(GL_TEXTURE_2D, texture[((blackWhite)?((chosen)?WHITE_WOOD_C:WHITE_WOOD):((chosen)?BLACK_WOOD_C:BLACK_WOOD))]);
	glTranslatef(x,y,z);		// draw in required position
	if(blackWhite)glRotatef(180,0,1,0);
		if(RenderMode==GL_RENDER)
		{
			//base
			glTranslatef(0,-0.0625,0);
					glRotatef(90,1,0,0);		
						glutSolidTorus(DIV16-0.1,DIV16,64,64);
					glRotatef(-90,1,0,0);
			glTranslatef(0,0.0625,0);
			glTranslatef(0,-0.033,0);
					glRotatef(90,1,0,0);		
						glutSolidTorus(DIV16-0.1,DIV16,64,64);
					glRotatef(-90,1,0,0);
			glTranslatef(0,0.033,0);
		}

		GLUquadricObj *WazeerSphere=gluNewQuadric(),*WazeerCylinder=gluNewQuadric(),*WazeerCone=gluNewQuadric();
		gluQuadricTexture(WazeerSphere,true);gluQuadricTexture(WazeerCylinder,true);gluQuadricTexture(WazeerCone,true);

		glTranslatef(0,DIV4-0.02,0);
			gluSphere(WazeerSphere,DIV16-0.02,64,64);
		glTranslatef(0,-DIV4+0.02,0);

		glTranslatef(0,DIV4-0.02,0);
			glRotatef(90,1,0,0);
				gluCylinder(WazeerCone,DIV32,DIV16,DIV4-0.02,64,64);
			glRotatef(-90,1,0,0);
		glTranslatef(0,-DIV4+0.02,0);

		glRotatef(90,1,0,0);
			gluCylinder(WazeerCylinder,DIV16,DIV16,DIV8-0.02,64,64);
		glRotatef(-90,1,0,0);
	if(blackWhite)glRotatef(-180,0,1,0);
	glTranslatef(0-x,0-y,0-z);
}

void drawChars(bool initialize, int choice)
{
	float XX=-1+0.125,YY=0.25-DIV16,ZZ=-1+0.125;
	if(initialize)
	{
		Board[7][4]=whiteMalek;charsPosition[whiteMalek]=60;
		Board[0][4]=blackMalek;charsPosition[blackMalek]=4;
		Board[7][3]=whiteWazeer;charsPosition[whiteWazeer]=59;
		Board[0][3]=blackWazeer;charsPosition[blackWazeer]=3;
		Board[7][2]=whiteFeel0;charsPosition[whiteFeel0]=58;Board[7][5]=whiteFeel1;charsPosition[whiteFeel1]=61;
		Board[0][2]=blackFeel0;charsPosition[blackFeel0]=2;Board[0][5]=blackFeel1;charsPosition[blackFeel1]=5;
		Board[7][1]=whiteHosan0;charsPosition[whiteHosan0]=57;Board[7][6]=whiteHosan1;charsPosition[whiteHosan1]=62;
		Board[0][1]=blackHosan0;charsPosition[blackHosan0]=1;Board[0][6]=blackHosan1;charsPosition[blackHosan1]=6;
		Board[7][0]=whiteTabya0;charsPosition[whiteTabya0]=56;Board[7][7]=whiteTabya1;charsPosition[whiteTabya1]=63;
		Board[0][0]=blackTabya0;charsPosition[blackTabya0]=0;Board[0][7]=blackTabya1;charsPosition[blackTabya1]=7;
		for(int i=0;i<8;i++)
		{
			Board[6][i]=i;charsPosition[whiteAskari0+i]=6*8+i;
			Board[1][i]=i+8;charsPosition[blackAskari0+i]=1*8+i;
		}
		for(int i=2;i<6;i++)
			for(int j=0;j<8;j++)
				Board[i][j]=-1;
	}
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++)
		{
			if(Board[i][j]==-1)continue;
			glLoadName(Board[i][j]);
			if(Board[i][j]<16)	drawAskari(0.25*j+XX,YY,0.25*i+ZZ,(Board[i][j]<8),(choice==Board[i][j]));
			else if(Board[i][j]<20)	drawFeel(0.25*j+XX,YY,0.25*i+ZZ,(Board[i][j]<18),(choice==Board[i][j]));
			else if(Board[i][j]<24)	drawHosan(0.25*j+XX,YY,0.25*i+ZZ,(Board[i][j]<22),(choice==Board[i][j]));
			else if(Board[i][j]<28)	drawTabya(0.25*j+XX,YY,0.25*i+ZZ,(Board[i][j]<26),(choice==Board[i][j]));
			else if(Board[i][j]<30)	drawMalek(0.25*j+XX,YY,0.25*i+ZZ,(Board[i][j]==28),(choice==Board[i][j]));
			else if(Board[i][j]<32)	drawWazeer(0.25*j+XX,YY,0.25*i+ZZ,(Board[i][j]==30),(choice==Board[i][j]));
		}
}
