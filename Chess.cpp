#include <GL/glut.h>
#include <cstdio>
#include <iostream>
#include "Chess.hpp"
using namespace std;
#define PICK_TOL 1
#define PICK_BUFFER_SIZE 256
unsigned int PickBuffer[PICK_BUFFER_SIZE];

bool firstTime=true;
int chosen=-1;
float Xmouse=0, Ymouse=0;
char message[]={'\0','\0','\0','\0','\0','\0','\0','\0'};

int RenderMode=GL_RENDER;
void draw()
{
  	glMatrixMode(GL_PROJECTION);	
	glLoadIdentity();
	float width=glutGet(GLUT_WINDOW_WIDTH),height=glutGet(GLUT_WINDOW_HEIGHT);

	if(RenderMode==GL_SELECT)
	{
		int viewport[4];
		glGetIntegerv(GL_VIEWPORT,viewport);
		gluPickMatrix(Xmouse,(height-Ymouse),PICK_TOL,PICK_TOL,viewport);
	}
 	
	gluPerspective(12.0f,width/height,0.1f,100.0f);		// Calculate The Aspect Ratio Of The Window
  	glMatrixMode(GL_MODELVIEW);
	
	if(RenderMode==GL_SELECT)
	{
		glInitNames();
		glPushName(0xffffffff);
	}

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glColor3f(1,1,1);	
	if(firstTime){glTranslatef(0.0f,0.0f,-10);glRotatef(15,1,0,0);}

	drawBoard(chosen);
	drawChars(firstTime,chosen);
	
	firstTime=false;

	if(RenderMode==GL_RENDER)
	{
		glutSwapBuffers();
		glFlush();
	}
}

void mouse(int button, int state, int x, int y)
{
	//scroll down=button3, scroll up=button4
	if(state==GLUT_UP && (button==3 || button==4))
	{
		int angle;
		if(button==3) angle=5;
		else angle=-5;
		glRotatef(angle,1,0,0);
	}
	//right click=button2
	if(state==GLUT_UP && button==2)
	{
		glRotatef(-5,0,1,0);
	}
	//left click=button0
	if(state==GLUT_UP && button==0)
	{
		int prevChosen=chosen;
		Xmouse=x;Ymouse=y;
		RenderMode = GL_SELECT;
		glRenderMode(GL_SELECT);
		draw();
		RenderMode=GL_RENDER;
		int Nhits=glRenderMode(GL_RENDER);
		for(int i=0,index=0;i<Nhits;i++)
		{
			int nitems=PickBuffer[index++];
			index+=2;//skip zmin and zmax
			for(int j=0;j<nitems;j++)
				chosen=PickBuffer[index++];
		}
		if(chosen==prevChosen || chosen==-1)
		{
			if(chosen==-1)glRotatef(5,0,1,0);
			chosen=-1;
		}
		else
		{
			int newPosition=charsPosition[chosen],i=newPosition/8,ip=charsPosition[prevChosen]/8;
			if(chosen>31)
			{
				newPosition=chosen-32;
				i=newPosition/8;		//chosen=8*i+j+32 in function drawBoard in Chars.cpp, by this equation, j is removed
				//if the tiles were chosen, choose the object in that place
				chosen=Board[i][newPosition-i*8];
			}
			//if the place chosen was empty and an object was chosen previously and it's allowed to move in its place, move it and change the turn
			//if the place chosen wasn't empty, if the object chosen was chosen when it wasn't its turn and the previous object is allowed to move in its place
			if((chosen==-1 || (chosen!=-1 && whiteChar(chosen)!=turn)) && (prevChosen<=31 && prevChosen!=-1) && (freee || movePiece(prevChosen,charsPosition[prevChosen],newPosition))) 
			{	//charsPosition[label]=i*8+j dividing by 8 and receiving in integer, i remains, then removing i*8=j
				Board[ip][charsPosition[prevChosen]-ip*8]=-1;
				Board[i][newPosition-i*8]=prevChosen;
				charsPosition[prevChosen]=newPosition;
				turn=!turn;
			}
		}
	}
	glutPostRedisplay();
}

void skb(int button, int x, int y)
{
	if(button==GLUT_KEY_UP) glRotatef(-5,1,0,0);
	else if(button==GLUT_KEY_DOWN) glRotatef(5,1,0,0);
	else if(button==GLUT_KEY_LEFT) glRotatef(-5,0,1,0);
	else if(button==GLUT_KEY_RIGHT) glRotatef(5,0,1,0);
	glutPostRedisplay();
}

void kb(unsigned char button, int x, int y)
{
	if((button>='a' && button<='z') || (button>='0' && button<='9'))
	{
		for(int i=1;i<8;i++)
			message[i-1]=message[i];
		message[7]=button;
		if(Debug)cout<<message<<endl;
		if(fullDebugMode(message))
		{
			flipBoard(Board);
			glutPostRedisplay();
		}
	}
}

void initialize()
{
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(640, 480);  
	glutInitWindowPosition(300, 300);  
	glutCreateWindow("3D Chess"); 

	glSelectBuffer(PICK_BUFFER_SIZE, PickBuffer);

	LoadGLTextures();							// Load the textures
	glEnable(GL_TEXTURE_2D);						// Enable texture mapping
	RenderMode = GL_RENDER;
	glClearColor(0.91f, 0.8f, 0.4f, 0.0f);					// This Will Clear The Background Color To Black
	glDepthFunc(GL_LESS);							// The Type Of Depth Test To Do
 	glEnable(GL_DEPTH_TEST);						// Enables Depth Testing
  	glShadeModel(GL_SMOOTH);						// Enables Smooth Color Shading
}

int main(int argc,char** argv)
{
	glutInit(&argc, argv);  
	initialize();
	glutDisplayFunc(draw); 
	glutSpecialFunc(skb);
	glutMouseFunc(mouse);
	glutKeyboardFunc(kb);
	glutMainLoop();  
	return 1;	
}
