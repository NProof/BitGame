#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <set>
#include <map>
#include "Chess.h"

typedef __UINT32_TYPE__ U32;
typedef __UINT8_TYPE__ U8;

struct Move
{
	U8 type:2, dir:2, chess:4, len:3, src:5;
};

struct Pieces
{
	U8 temp:2,g:2,m:2,r:2,n:2,c:2,p:4,G:2,M:2,R:2,N:2,C:2,P:4,k:1,K:1;
};

class Board
{
	public:
		/** Default constructor */
		Board();
		/** Default destructor */
		~Board();

		U32 GetDarks();
		Pieces GetPiecesDark();
		std::vector<Move> genMove();
		U8 mov(Move iMov);
	protected:

	private:
		U8 ins(U8, U8);
		U8 rem(U8);

		Chess cheese[32];
		unsigned int darks;
		unsigned int red;
		unsigned int black;
		U8 turn:2,g:2,m:2,r:2,n:2,c:2,p:4,G:2,M:2,R:2,N:2,C:2,P:4,k:1,K:1;
};

#endif // BOARD_H
