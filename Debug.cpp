#include <cstring>

bool Debug=false,freee=false;

void flipBoard(int Board[][8])
{
	for(int i=0;i<4;i++)
	for(int j=0;j<8;j++)
	{
		int swap=Board[7-i][7-j];
		Board[7-i][7-j]=Board[i][j];
		charsPosition[swap]=8*i+j;
		Board[i][j]=swap;
		charsPosition[Board[7-i][7-j]]=8*(7-i)+7-j;
	}
}

bool fullDebugMode(char* message)
{
	if(strcmp(message,"c3cdebug")==0)
		Debug=!Debug;
	else if(strcmp(message,"c3cfreee")==0)
		freee=!freee;
	else if(strcmp(message,"c3cflipp")==0)
	{		
		flipped=!flipped;
		return true;
	}
	return false;
}
