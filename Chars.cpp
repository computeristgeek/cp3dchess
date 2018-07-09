#include <GL/glut.h>
#include <cstdio>
#include <iostream>
using namespace std;
#include "Chars.hpp"

int **Board=new int*[8],*charsPosition=new int[32];
bool flipped=false;

bool whiteChar(int character)
{
	return ((character<=whiteAskari7 && character>=whiteAskari0)?true:((character<=blackAskari7)?false:((character<=whiteFeel1)?true:((character<=blackFeel1)?false:((character<=whiteHosan1)?true:((character<=blackHosan1)?false:((character<=whiteTabya1)?true:((character<=blackTabya1)?false:((character==whiteMalek)?true:((character<=blackMalek)?false:((character<=whiteWazeer)?true:false)))))))))));
}
/*
	This function draws the chess board
*/
void drawBoard(int chosen)
{
	if(RenderMode==GL_SELECT)
	for(int i=0;i<8;i++)for(int j=0;j<8;j++)
	{
		int num=8*i+j+32;
		glLoadName(num);
		glPushMatrix();
		glTranslatef(0.25*j,DIV32/4.0,0.25*i);
		glBegin(GL_QUADS);
		glVertex3f(-1,  0.125, -1);
		glVertex3f(-1,  0.125,  -1+0.25);
		glVertex3f(-1+0.25,  0.125,  -1+0.25);
		glVertex3f( -1+0.25,  0.125, -1);
		glEnd();
		glPopMatrix();
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

	glPushMatrix();
	glTranslatef(x,y,z);		// draw in required position
	if(blackWhite)glRotatef(180,0,1,0);
		if(RenderMode==GL_RENDER)
		{
			//base
			glPushMatrix();
			glTranslatef(0,-0.0625,0);
				glRotatef(90,1,0,0);		
					glutSolidTorus(DIV16-0.05,DIV16,64,64);
			glPopMatrix();
			glPushMatrix();
			glTranslatef(0,-0.033,0);
				glRotatef(90,1,0,0);		
					glutSolidTorus(DIV16-0.05,DIV16,64,64);
			glPopMatrix();
		}
		//objects
		GLUquadricObj *AskariSphere=gluNewQuadric(),*AskariCylinder=gluNewQuadric(),*AskariCone=gluNewQuadric();
		//activate Texture
		gluQuadricTexture(AskariSphere,true);gluQuadricTexture(AskariCylinder,true);gluQuadricTexture(AskariCone,true);
		
		//head
		glPushMatrix();
		glTranslatef(0,DIV8,0);
		gluSphere(AskariSphere,DIV16-0.02,64,64);
		//body
		glPushMatrix();
		glRotatef(90,1,0,0);
		gluCylinder(AskariCone,DIV32,DIV16,DIV8,64,64);
		glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glRotatef(90,1,0,0);
		gluCylinder(AskariCylinder,DIV16,DIV16,DIV16,64,64);
		glPopMatrix();
	glPopMatrix();
}

void drawWazeer(float x, float y, float z, bool blackWhite, bool chosen)
{
	glBindTexture(GL_TEXTURE_2D, texture[((blackWhite)?((chosen)?WHITE_WOOD_C:WHITE_WOOD):((chosen)?BLACK_WOOD_C:BLACK_WOOD))]);
	glPushMatrix();
	glTranslatef(x,y,z);		// draw in required position
	if(blackWhite)glRotatef(180,0,1,0);
		GLUquadricObj *WazeerSphere=gluNewQuadric(),*WazeerCylinder=gluNewQuadric(),*WazeerCone=gluNewQuadric();
		gluQuadricTexture(WazeerSphere,true);gluQuadricTexture(WazeerCylinder,true);gluQuadricTexture(WazeerCone,true);
		if(RenderMode==GL_RENDER)
		{
			//base
			glPushMatrix();
			glTranslatef(0,-0.0625,0);
					glRotatef(90,1,0,0);		
						glutSolidTorus(DIV16-0.1,DIV16,64,64);
			glPopMatrix();
			glPushMatrix();
			glTranslatef(0,-0.033,0);
					glRotatef(90,1,0,0);		
						glutSolidTorus(DIV16-0.1,DIV16,64,64);
			glPopMatrix();

			glDisable(GL_TEXTURE_2D);
			glPushMatrix();
			glTranslatef(0,DIV4+0.07125,0);
				glRotatef(90,1,0,0);
					glPushMatrix();
					glTranslatef(0,0.04,0);
						gluCylinder(WazeerCylinder,0,DIV32/4.0,DIV32,64,64);
					glPopMatrix();
					glPushMatrix();
					glTranslatef(0.04,0,0);
						gluCylinder(WazeerCylinder,0,DIV32/4.0,DIV32,64,64);
					glPopMatrix();
					glPushMatrix();
					glTranslatef(0.03,0.03,0);
						gluCylinder(WazeerCylinder,0,DIV32/4.0,DIV32,64,64);
					glPopMatrix();
					glPushMatrix();
					glTranslatef(0,-0.04,0);
						gluCylinder(WazeerCylinder,0,DIV32/4.0,DIV32,64,64);
					glPopMatrix();
					glPushMatrix();
					glTranslatef(-0.04,0,0);
						gluCylinder(WazeerCylinder,0,DIV32/4.0,DIV32,64,64);
					glPopMatrix();
					glPushMatrix();
					glTranslatef(-0.03,-0.03,0);
						gluCylinder(WazeerCylinder,0,DIV32/4.0,DIV32,64,64);
					glPopMatrix();
					glPushMatrix();
					glTranslatef(0.03,-0.03,0);
						gluCylinder(WazeerCylinder,0,DIV32/4.0,DIV32,64,64);
					glPopMatrix();
					glPushMatrix();
					glTranslatef(-0.03,0.03,0);
						gluCylinder(WazeerCylinder,0,DIV32/4.0,DIV32,64,64);	
					glPopMatrix();
			//glutSolidTorus(DIV32-0.001,DIV16-0.01,4,4);
			glPopMatrix();
			glEnable(GL_TEXTURE_2D);
		}
		glPushMatrix();
		glTranslatef(0,DIV4,0);
			gluSphere(WazeerSphere,DIV16,64,64);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0,DIV4,0);
			glRotatef(90,1,0,0);
				gluCylinder(WazeerCone,DIV32,DIV16,DIV4,64,64);
		glPopMatrix();
		glPushMatrix();
		glRotatef(90,1,0,0);
			gluCylinder(WazeerCylinder,DIV16,DIV16,DIV8,64,64);
		glPopMatrix();
	glPopMatrix();
}

void drawMalek(float x, float y, float z, bool blackWhite, bool chosen)
{
	glBindTexture(GL_TEXTURE_2D, texture[((blackWhite)?((chosen)?WHITE_WOOD_C:WHITE_WOOD):((chosen)?BLACK_WOOD_C:BLACK_WOOD))]);
	glPushMatrix();
	glTranslatef(x,y,z);		// draw in required position
	if(blackWhite)glRotatef(180,0,1,0);
		GLUquadricObj *WazeerSphere=gluNewQuadric(),*WazeerCylinder=gluNewQuadric(),*WazeerCone=gluNewQuadric();
		gluQuadricTexture(WazeerSphere,true);gluQuadricTexture(WazeerCylinder,true);gluQuadricTexture(WazeerCone,true);
		if(RenderMode==GL_RENDER)
		{
			//base
			glPushMatrix();
			glTranslatef(0,-0.0625,0);
					glRotatef(90,1,0,0);		
						glutSolidTorus(DIV8-0.1,DIV8,64,64);
			glPopMatrix();
			glPushMatrix();
			glTranslatef(0,-0.033,0);
					glRotatef(90,1,0,0);		
						glutSolidTorus(DIV8-0.1,DIV8,64,64);
			glPopMatrix();
			//crown spikes
			glDisable(GL_TEXTURE_2D);
			glPushMatrix();
			glTranslatef(0,DIV4+0.06125,0);
				glRotatef(90,1,0,0);
					glPushMatrix();
					glTranslatef(0,0.04,0);
						gluCylinder(WazeerCylinder,DIV32/4.0,DIV32/4.0,DIV32,64,64);
					glPopMatrix();
					glPushMatrix();
					glTranslatef(0.04,0,0);
						gluCylinder(WazeerCylinder,DIV32/4.0,DIV32/4.0,DIV32,64,64);
					glPopMatrix();
					glPushMatrix();
					glTranslatef(0.03,0.03,0);
						gluCylinder(WazeerCylinder,DIV32/4.0,DIV32/4.0,DIV32,64,64);
					glPopMatrix();
					glPushMatrix();
					glTranslatef(0,-0.04,0);
						gluCylinder(WazeerCylinder,DIV32/4.0,DIV32/4.0,DIV32,64,64);
					glPopMatrix();
					glPushMatrix();
					glTranslatef(-0.04,0,0);
						gluCylinder(WazeerCylinder,DIV32/4.0,DIV32/4.0,DIV32,64,64);
					glPopMatrix();
					glPushMatrix();
					glTranslatef(-0.03,-0.03,0);
						gluCylinder(WazeerCylinder,DIV32/4.0,DIV32/4.0,DIV32,64,64);
					glPopMatrix();
					glPushMatrix();
					glTranslatef(0.03,-0.03,0);
						gluCylinder(WazeerCylinder,DIV32/4.0,DIV32/4.0,DIV32,64,64);
					glPopMatrix();
					glPushMatrix();
					glTranslatef(-0.03,0.03,0);
						gluCylinder(WazeerCylinder,DIV32/4.0,DIV32/4.0,DIV32,64,64);	
					glPopMatrix();
			glPopMatrix();
			glEnable(GL_TEXTURE_2D);

		}

		glPushMatrix();
		glTranslatef(0,DIV4,0);
			gluSphere(WazeerSphere,DIV16,64,64);
			glPushMatrix();
			glRotatef(90,1,0,0);
				gluCylinder(WazeerCone,DIV32,DIV8,DIV4,64,64);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glRotatef(90,1,0,0);
			gluCylinder(WazeerCylinder,DIV8,DIV8,DIV8,64,64);
		glPopMatrix();
	glPopMatrix();
}


void drawTabya(float x, float y, float z, bool blackWhite, bool chosen)
{
	glBindTexture(GL_TEXTURE_2D, texture[((blackWhite)?((chosen)?WHITE_WOOD_C:WHITE_WOOD):((chosen)?BLACK_WOOD_C:BLACK_WOOD))]);
	glPushMatrix();
	glTranslatef(x,y,z);		// draw in required position
	if(blackWhite)glRotatef(180,0,1,0);
		if(RenderMode==GL_RENDER)
		{
			//base
			glPushMatrix();
			glTranslatef(0,-0.0625,0);
					glRotatef(90,1,0,0);		
						glutSolidTorus(/*DIV16-0.05*/DIV32,DIV16,64,64);
			glPopMatrix();
			glPushMatrix();
			glTranslatef(0,-0.033,0);
					glRotatef(90,1,0,0);		
						glutSolidTorus(DIV16-0.05,DIV16,64,64);
			glPopMatrix();
		}
		GLUquadricObj *AskariSphere=gluNewQuadric(),*AskariCylinder=gluNewQuadric(),*AskariCone=gluNewQuadric();
		gluQuadricTexture(AskariSphere,true);gluQuadricTexture(AskariCylinder,true);gluQuadricTexture(AskariCone,true);


		glPushMatrix();
		glTranslatef(0,DIV8,0);
			glRotatef(90,1,0,0);
				gluCylinder(AskariCone,DIV16-0.01,DIV16,DIV8,64,64);
				glPushMatrix();
				glTranslatef(0,0,-DIV16);
					gluDisk(AskariSphere,0,DIV16,64,64);
					gluCylinder(AskariSphere,DIV16,DIV16,DIV16,64,64);
				glPopMatrix();
				gluDisk(AskariSphere,0,DIV16,64,64);
		glPopMatrix();

		glPushMatrix();
		glRotatef(90,1,0,0);
			gluCylinder(AskariCylinder,DIV16,DIV16,DIV16,64,64);
		glPopMatrix();
	glPopMatrix();
}

void drawHosan(float x, float y, float z, bool blackWhite, bool chosen)
{
	glBindTexture(GL_TEXTURE_2D, texture[((blackWhite)?((chosen)?WHITE_WOOD_C:WHITE_WOOD):((chosen)?BLACK_WOOD_C:BLACK_WOOD))]);
	glPushMatrix();
	glTranslatef(x,y,z);		// draw in required position
	if(flipped ^ blackWhite)glRotatef(180,0,1,0);
		if(RenderMode==GL_RENDER)
		{
			//base
			glPushMatrix();
			glTranslatef(0,-0.0625,0);
					glRotatef(90,1,0,0);		
						glutSolidTorus(/*DIV16-0.05*/DIV32,DIV16,64,64);
			glPopMatrix();
			glPushMatrix();
			glTranslatef(0,-0.033,0);
					glRotatef(90,1,0,0);		
						glutSolidTorus(DIV16-0.05,DIV16,64,64);
			glPopMatrix();
		}

		GLUquadricObj *AskariSphere=gluNewQuadric(),*AskariCylinder=gluNewQuadric(),*AskariCone=gluNewQuadric();
		gluQuadricTexture(AskariSphere,true);gluQuadricTexture(AskariCylinder,true);gluQuadricTexture(AskariCone,true);

	//neck
		glPushMatrix();
		glTranslatef(0,DIV8,0);
			glPushMatrix();
			glRotatef(90,1,0,0);
				glPushMatrix();
				glRotatef(15,0,1,0);
					glTranslatef(0,0,-DIV8);
							gluCylinder(AskariSphere,0,DIV16-0.01,DIV8,64,64);
				glPopMatrix();
				glPushMatrix();
				glRotatef(-15,0,1,0);
					glTranslatef(0,0,-DIV8);
							gluCylinder(AskariSphere,0,DIV16-0.01,DIV8,64,64);
				glPopMatrix();
			glPopMatrix();
			//eyes
			glDisable(GL_TEXTURE_2D);
				glPushMatrix();
				glTranslatef(DIV32,DIV32,DIV32+0.01);
					gluSphere(AskariSphere,DIV32/4.0,64,64);
				glPopMatrix();
				glPushMatrix();
				glTranslatef(-DIV32,DIV32,DIV32+0.01);
					gluSphere(AskariSphere,DIV32/4.0,64,64);
				glPopMatrix();
			glEnable(GL_TEXTURE_2D);

			//end of mouth
			glPushMatrix();
			glTranslatef(0,-DIV32-0.01,DIV8-0.01);
				gluSphere(AskariSphere,DIV32,64,64);
			glPopMatrix();

			//face
			glPushMatrix();
			glRotatef(200,1,0,0);
				glTranslatef(0,0,-DIV8);
						gluCylinder(AskariSphere,DIV32,DIV16-0.01,DIV8,64,64);
			glPopMatrix();

			glPushMatrix();
			glRotatef(90,1,0,0);
				gluCylinder(AskariCone,DIV16-0.01,DIV16,DIV8,64,64);
			glPopMatrix();
		glPopMatrix();
		glPushMatrix();
			glRotatef(90,1,0,0);
				gluCylinder(AskariCylinder,DIV16,DIV16,DIV16,64,64);
		glPopMatrix();
	glPopMatrix();
}

void drawFeel(float x, float y, float z, bool blackWhite, bool chosen)
{
	glBindTexture(GL_TEXTURE_2D, texture[((blackWhite)?((chosen)?WHITE_WOOD_C:WHITE_WOOD):((chosen)?BLACK_WOOD_C:BLACK_WOOD))]);
	glPushMatrix();
	glTranslatef(x,y,z);		// draw in required position
	if(blackWhite)glRotatef(180,0,1,0);
		if(RenderMode==GL_RENDER)
		{
			//base
			glPushMatrix();
			glTranslatef(0,-0.0625,0);
					glRotatef(90,1,0,0);		
						glutSolidTorus(DIV16-0.1,DIV16,64,64);
			glPopMatrix();
			glPushMatrix();
			glTranslatef(0,-0.033,0);
					glRotatef(90,1,0,0);		
						glutSolidTorus(DIV16-0.1,DIV16,64,64);
			glPopMatrix();
		}

		GLUquadricObj *WazeerSphere=gluNewQuadric(),*WazeerCylinder=gluNewQuadric(),*WazeerCone=gluNewQuadric();
		gluQuadricTexture(WazeerSphere,true);gluQuadricTexture(WazeerCylinder,true);gluQuadricTexture(WazeerCone,true);

		glPushMatrix();
		glTranslatef(0,DIV4-0.02,0);
			gluSphere(WazeerSphere,DIV16-0.02,64,64);
			glPushMatrix();
			glRotatef(90,1,0,0);
				gluCylinder(WazeerCone,DIV32,DIV16,DIV4-0.02,64,64);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glRotatef(90,1,0,0);
			gluCylinder(WazeerCylinder,DIV16,DIV16,DIV8-0.02,64,64);
		glPopMatrix();
	glPopMatrix();
}

void drawChars(bool initialize, int choice)
{
	float XX=-1+0.125,YY=0.25-DIV16,ZZ=-1+0.125;
	if(initialize)
	{
		for(int i=0;i<8;i++) Board[i]=new int[8];
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
