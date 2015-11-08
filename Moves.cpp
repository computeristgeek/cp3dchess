#include "Chars.cpp"
#include "Debug.cpp"
#include <cmath>

int Max(int num1,int num2)
{
	return num1>num2?num1:num2;
}
int Min(int num1,int num2)
{
	return num1<num2?num1:num2;
}
void swap(int *num1,int *num2)
{
	int temp=*num1;
	*num1=*num2;
	*num2=temp;
}

bool turn=true;

bool kingProtected(int from, int to)
{
	if(Debug)return true;
	int ifrom=from/8,jfrom=from-8*ifrom;
	int ito=to/8,jto=to-8*ito;
	int simulateBoard[8][8],simcharsPosition[32];
	bool white=true;
	for(int i=0;i<8;i++)
	for(int j=0;j<8;j++)
		simulateBoard[i][j]=Board[i][j];
	for(int i=0;i<32;i++)
		simcharsPosition[i]=charsPosition[i];
	int test=simulateBoard[ito][jto];
	simulateBoard[ito][jto]=simulateBoard[ifrom][jfrom];
	if(test!=-1) simcharsPosition[test]=-1;
	simcharsPosition[simulateBoard[ifrom][jfrom]]=ito*8+jto;
	simulateBoard[ifrom][jfrom]=-1;
	if(!whiteChar(simulateBoard[ito][jto])) white=false;

	
	//convert constants from blackPieces to whitePieces, c0 for Askari, c1 and c2 for types that have 1 piece or 2 pieces, respectively
	int c0=(white?0:-8),c1=(white?0:-1),c2=(white?0:-2);

	int Askari0=blackAskari0+c0,Askari7=blackAskari7+c0;
	int Wazeer=blackWazeer+c1,Malek=blackMalek+c1;
	int Feel0=blackFeel0+c2,Feel1=blackFeel1+c2,Hosan0=blackHosan0+c2,Hosan1=blackHosan1+c2,Tabya0=blackTabya0+c2,Tabya1=blackTabya1+c2;

	int Mali=simcharsPosition[white?whiteMalek:blackMalek]/8,Malj=simcharsPosition[white?whiteMalek:blackMalek]-Mali*8;

	//check for hosan in (-2,-1) (-1,-2) (+1,-2) (-2,+1) (+2,+1) (+1,+2) (-1,+2) (+2,-1)
	for(int i=0,inci=-2,incj=-1;i<8;i++)
	{
		int tempi=Mali+inci,tempj=Malj+incj;
		if(tempi<8 && tempj<8 && tempi+tempj==abs(tempi)+abs(tempj) && simulateBoard[tempi][tempj]==Hosan0 || simulateBoard[tempi][tempj]==Hosan1)
			return false; //king not protected
		if(i%2==0)swap(&inci,&incj);
		else inci=-inci;
	}

	{
		int otherMali=simcharsPosition[Malek]/8,otherMalj=simcharsPosition[Malek]-otherMali*8;
		if(abs(otherMali-Mali)<=1 && abs(otherMalj-Malj)<=1) return false;//king not protected
	}

	int begin=(white?1:6);
	if(flipped) begin=(white?6:1);
	//check for any part around the malek (+1,+1) (-1,-1) (+1,-1) (-1,+1) that can have a askari
	if((begin==6 && Mali+1<8) || (begin==1 && Mali-1>-1))
	{
		if(Malj+1<8)
		{
			test=simulateBoard[Mali+(begin==6?1:-1)][Malj+1];
			if(test<=Askari7 && test>=Askari0) return false;//king not protected
		}
		if(Malj-1>-1)
		{
			test=simulateBoard[Mali+(begin==6?1:-1)][Malj-1];
			if(test<=Askari7 && test>=Askari0) return false;//king not protected
		}
	}


	//check diagonal for any wazeer or feel
	//a tabya needs to be in places (+i,+0) (+0,+i) (-i,+0) (+0,-i) or wazeer
	//a feel needs to be in places (+i,+i) (-i,-i) (+i,-i) (-i,+i) or wazeer
	bool testing[]={true,true,true,true,true,true,true,true};
	for(int i=1;i<8;i++)
	{
		if(testing[0] && Mali+i<8)
		{
			test=simulateBoard[Mali+i][Malj];
			if(test==Wazeer || test==Tabya0 || test==Tabya1) return false;//king not protected
			else if(test!=-1) testing[0]=false;
		}
		if(testing[1] && Malj+i<8)
		{
			test=simulateBoard[Mali][Malj+i];
			if(test==Wazeer || test==Tabya0 || test==Tabya1) return false;//king not protected
			else if(test!=-1) testing[1]=false;
		}
		if(testing[2] && Mali-i>-1)
		{
			test=simulateBoard[Mali-i][Malj];
			if(test==Wazeer || test==Tabya0 || test==Tabya1) return false;//king not protected
			else if(test!=-1) testing[2]=false;
		}
		if(testing[3] && Malj-i>-1)
		{
			test=simulateBoard[Mali][Malj-i];
			if(test==Wazeer || test==Tabya0 || test==Tabya1) return false;//king not protected
			else if(test!=-1) testing[3]=false;
		}
		if(testing[4] && Mali+i<8 && Malj+i<8)
		{
			test=simulateBoard[Mali+i][Malj+i];
			if(test==Wazeer || test==Feel0 || test==Feel1) return false;//king not protected
			else if(test!=-1) testing[4]=false;
		}
		if(testing[5] && Mali+i<8 && Malj-i>-1)
		{
			test=simulateBoard[Mali+i][Malj-i];
			if(test==Wazeer || test==Feel0 || test==Feel1) return false;//king not protected
			else if(test!=-1) testing[5]=false;
		}
		if(testing[6] && Mali-i>-1 && Malj-i>-1)
		{
			test=simulateBoard[Mali-i][Malj-i];
			if(test==Wazeer || test==Feel0 || test==Feel1) return false;//king not protected
			else if(test!=-1) testing[6]=false;
		}
		if(testing[7] && Mali-i>-1 && Malj+i<8)
		{
			test=simulateBoard[Mali-i][Malj+i];
			if(test==Wazeer || test==Feel0 || test==Feel1) return false;//king not protected
			else if(test!=-1) testing[7]=false;
		}
	}

	return true;
}

//place infront of it is empty
bool inFront(int i1, int j1, int i2, int j2)
{
	if(j1==j2)
	{
		for(int i=Min(i1,i2)+1;i<Max(i1,i2);i++)
			if(Board[i][j1]!=-1) return true;
	}
	else
	{
		if(i1==i2)
		{
			for(int j=Min(i1,i2);j<Max(i1,i2);j++)
				if(Board[i1][j]!=-1) return true;
		}
		else if(abs(i1-i2)==abs(j1-j2))
		{
			int inc=(i1<i2)?j1:j2;
			inc=(inc==Min(j1,j2))?1:-1;
			for(int i=Min(i1,i2)+1,j=((i1<i2)?j1:j2)+inc;i<Max(i1,i2);i++)
			{
				if(Board[i][j]!=-1) return true;
				j+=inc;
			}
		}
	}
	return false;
}

bool movePiece(int pieceName, int from, int to)
{

	int ifrom=from/8,jfrom=from-8*ifrom;
	int ito=to/8,jto=to-8*ito;
	if(pieceName<=blackAskari7)
	{
		int begin=(turn?6:1);
		if(flipped) begin=(turn?1:6);
		//if it's the side's turn
		if(!(pieceName<=whiteAskari7 ^ turn))
		{
			bool onlyOneMoveForward=(begin==1)?(ito-ifrom==1):(ito-ifrom==-1);
			bool twoMovesForward=(begin==1)?(ito-ifrom==2):(ito-ifrom==-2);
			if(
				(
					(// and the move is allowed and nothing exists infront of it and when moved the king is still protected, allow moving
						jto==jfrom
						&& (
							onlyOneMoveForward || (ifrom==begin && twoMovesForward)
						)
						&& !inFront(ifrom, jfrom, ito+((begin==1)?1:-1), jto)
					)
					|| (
						Board[ito][jto]!=-1
						&& (whiteChar(Board[ito][jto])^turn)
						&& onlyOneMoveForward
						&& abs(jto-jfrom)==1
					)
				)// and when moved the king is still protected, allow moving
				&& kingProtected(from,to)
			)
			return true;
		}
		else
			return false;
	}
	else
	{
		if(pieceName>=whiteHosan0 && pieceName<=blackHosan1)
		{
			//if it's the side's turn
			if(!(pieceName<=whiteHosan1 ^ turn) 
				&& (// and the move is allowed
					(abs(ito-ifrom)==2 && abs(jto-jfrom)==1) 
					|| (abs(ito-ifrom)==1 && abs(jto-jfrom)==2)
				)// and when moved the king is still protected, allow moving
			 	&& kingProtected(from,to)
			)
				return true;
			else
				return false;
		}
		else
		{
			if(pieceName==whiteWazeer || pieceName==blackWazeer)
			{
				//if it's the side's turn
				if(!(pieceName==whiteWazeer ^ turn)
					// and the move is allowed
					&& (ito==ifrom || jto==jfrom || abs(ito-ifrom)==abs(jto-jfrom))
					// and nothing exists infront of it
					&& !inFront(ifrom, jfrom, ito, jto)
					// and when moved the king is still protected, allow moving
					&& kingProtected(from,to)
				)
					return true;
				else
					return false;
			}
			else
			{
				if(pieceName>=whiteFeel0 && pieceName<=blackFeel1)
				{
					//if it's the side's turn
					if(!(pieceName<=whiteFeel1 ^ turn)
						// and the move is allowed
						&& (abs(ito-ifrom)==abs(jto-jfrom))
						// and nothing exists infront of it
						&& !inFront(ifrom, jfrom, ito, jto)
						// and when moved the king is still protected, allow moving
						&& kingProtected(from,to)
					)
						return true;
					else
						return false;
				}
				else
				{
					if(pieceName>=whiteTabya0 && pieceName<=blackTabya1)
					{
						//if it's the side's turn
						if(!(pieceName<=whiteTabya1 ^ turn)
							// and the move is allowed
							&& (ito==ifrom || jto==jfrom)
							// and nothing exists infront of it
							&& !inFront(ifrom, jfrom, ito, jto)
							// and when moved the king is still protected, allow moving
							&& kingProtected(from,to)
						)
							return true;
						else
							return false;
					}
					else if(pieceName==whiteMalek || pieceName==blackMalek)
					{
						//if it's the side's turn
						if(!(pieceName==whiteMalek ^ turn)
							// and the move is allowed
							&& (abs(ito-ifrom)<=1 && abs(jto-jfrom)<=1)
							// and when moved the king is still protected, allow moving
							&& kingProtected(from,to)
						)
							return true;
						else
							return false;
					}
				}
			}
		}
	}
}
