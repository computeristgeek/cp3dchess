#include <GL/glut.h>
#include <unistd.h>
#include <cstdio>
#include "Chars.cpp"
#include <iostream>
using namespace std;

GLUquadricObj *quadratic;
typedef struct Image Image;

int angle=0;bool firstTime=true;int chosen=-1;
float TotalAngle=0;

float Xmouse=0, Ymouse=0;

bool movePiece(int pieceName, int from, int to)
{
	
}

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

void beten()
{
	angle+=5;
	usleep(1000000);
	glutPostRedisplay();
}

void mousie(int button, int state, int x, int y)
{
	if(state==GLUT_UP && (button==3 || button==4))
	{
		if(button==3) angle=5;
		else angle=-5;
		glRotatef(angle,1,0,0);
		TotalAngle+=angle;
		angle=0;
	}
	if(state==GLUT_UP && button==0)
	{
		int prevChosen=chosen;
		bool Debug=false;
		RenderMode = GL_SELECT;
		glRenderMode(GL_SELECT);
		draw();
		RenderMode=GL_RENDER;
		int Nhits=glRenderMode(GL_RENDER);

		if(Debug) fprintf(stderr,"# pick hits = %d\n",Nhits);
		int i,index;
		
		for(i=0,index=0;i<Nhits;i++)
		{
			int nitems=PickBuffer[index++];
			int zmin=PickBuffer[index++];
			int zmax=PickBuffer[index++];
			if(Debug)
			{
				fprintf(stderr,"Hit # %2d: found %2d items on the name stack\n",i,nitems);
				fprintf(stderr,"\tZmin = 0x%0x, Zmax = 0x%0x\n",zmin,zmax);
			}
			for(int j=0;j<nitems;j++)
			{
				int item=PickBuffer[index++];
				chosen=item;
				if(Debug)
				fprintf(stderr,"\t%2d: %6d\n",j,item);
			}
		}
		Xmouse=x;Ymouse=y;

		RenderMode=GL_SELECT;
		glRenderMode(GL_SELECT);
		draw();
		RenderMode=GL_RENDER;
		Nhits=glRenderMode(GL_RENDER);

		for(i=0,index=0;i<Nhits;i++)
		{
			int nitems=PickBuffer[index++];
			int zmin=PickBuffer[index++];
			int zmax=PickBuffer[index++];
			for(int j=0;j<nitems;j++)
			{
				int item=PickBuffer[index++];
				chosen=item;
			}
		}
		if(chosen==prevChosen) chosen=-1;
		Xmouse=x;Ymouse=y;

		if(chosen==-1 && prevChosen==-1)
		glRotatef(5,0,1,0);

		i=(chosen-32)/8;		//chosen=8*i+j+32 in function drawBoard in Chars.cpp, by this equation, j is removed
		int ip=charsPosition[prevChosen]/8;
	
		if(chosen>31 && Board[i][chosen-32-i*8]!=-1) chosen=Board[i][chosen-32-i*8];
		else if(Board[i][chosen-32-i*8]==-1 && (prevChosen<=31 && prevChosen!=-1)) 
		{	//charsPosition[label]=i*8+j dividing by 8 and receiving in integer, i remains, then removing i*8=j
			Board[ip][charsPosition[prevChosen]-ip*8]=-1;
			Board[i][chosen-32-i*8]=prevChosen;
			charsPosition[prevChosen]=chosen-32;
		}
	}
	if(state==GLUT_UP && button==2)
	{
		glRotatef(-5,0,1,0);
	}
	glutPostRedisplay();
}

void skb(int button, int x, int y)
{
	glutPostRedisplay();
}

int main(int argc,char** argv)
{
	
	glutInit(&argc, argv);  
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(640, 480);  
	glutInitWindowPosition(300, 300);  
	glutCreateWindow("3D Chess"); 

	glSelectBuffer(PICK_BUFFER_SIZE, PickBuffer);

	LoadGLTextures();							// Load the textures
	glEnable(GL_TEXTURE_2D);						// Enable texture mapping
	RenderMode = GL_RENDER;
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);					// This Will Clear The Background Color To Black
	glDepthFunc(GL_LESS);							// The Type Of Depth Test To Do
 	glEnable(GL_DEPTH_TEST);						// Enables Depth Testing
  	glShadeModel(GL_SMOOTH);						// Enables Smooth Color Shading
	glutDisplayFunc(draw); glutSpecialFunc(skb);glutMouseFunc(mousie);	//glutIdleFunc(beten); 
	glutMainLoop();  

  return 1;
		
}
