#include "Board.h"

Board::Board()
{
	//ctor
}

Board::~Board()
{
	//dtor
}

U32 Board::GetDarks()
{
	return darks;
}

Pieces Board::GetPiecesDark()
{
	Pieces piecesDark;
	piecesDark.g = g;
	piecesDark.m = m;
	piecesDark.r = r;
	piecesDark.n = n;
	piecesDark.c = c;
	piecesDark.p = p;
	piecesDark.G = G;
	piecesDark.M = M;
	piecesDark.R = R;
	piecesDark.N = N;
	piecesDark.C = C;
	piecesDark.P = P;
	piecesDark.k = k;
	piecesDark.K = K;
	return piecesDark;
}

int index32[32] = {31,0,1,5,2,16,27,6,3,14,17,19,28,11,7,21,30,4,15,26,13,18,10,20,29,25,12,9,24,8,23,22};

int BitsHash(U32 x)
{
	return (x * 0x08ED2BE6) >> 27;
}

int GetIndex(U32 mask)
{
	return index32[BitsHash(mask)];
}

std::vector<Move> Board::genMove()
{
	std::vector<Move> ret;
	if(turn == 0){}
	else if(turn == 1 || turn == 2) // 1: red, 2: black
	{
		U32 p = (turn & 0x1) ? red : black;
		Move tmp;
		while(p)
		{
			U32 mask = p & (-p);
			p ^= mask;
			signed char dirs[] = {-4, -1, 4, 1};
			U8 (Chess::*fp[4])() = {Chess::Getup, Chess::Getright, Chess::Getdown, Chess::Getleft};
			U8 (Chess::*limitFp[4])() = {Chess::GetLup, Chess::GetLright, Chess::GetLdown, Chess::GetLleft};
			for(U8 dir = 0; dir < 4; dir++)
			{
				U8 len = (cheese[GetIndex(mask)].*fp[dir])();
				if(len > 1 || len == 0 && (cheese[GetIndex(mask)].*limitFp[dir])())
				{
					tmp.type = 1;
					tmp.src = GetIndex(mask);
					tmp.dir = dir;
					tmp.len = 1;
					tmp.chess = 0;
					ret.push_back(Move(tmp));
				}
				if(cheese[GetIndex(mask)].isC())
				{
					if(len)
						len = (cheese[GetIndex(mask)+dirs[dir]*len].*fp[dir])();
					if(len && cheese[GetIndex(mask)+dirs[dir]*len].isRed() ^ (turn & 0x1))
					{
						tmp.type = 3;
						tmp.src = GetIndex(mask);
						tmp.dir = dir;
						tmp.len = len;
						tmp.chess = cheese[GetIndex(mask)+dirs[dir]*len].Gettype();
						ret.push_back(Move(tmp));
					}
				}
				else
				{
					U8 type = cheese[GetIndex(mask)+dirs[dir]].Gettype();
					if(len == 1 && cheese[GetIndex(mask)].isMove(type))
					{
						tmp.type = 2;
						tmp.src = GetIndex(mask);
						tmp.dir = dir;
						tmp.len = 1;
						tmp.chess = type;
						ret.push_back(Move(tmp));
					}
				}
			}
		}
		turn ^= 3;
	}
	else{}
	return ret;
}

U8 Board::mov(Move iMov)
{
	if(iMov.type == 0)
	{
		darks ^= ( 0x1 << iMov.src);
		return ins(iMov.src, iMov.chess);
	}
	else
	{
		signed char idir[] = {-4, -1, 4, 1};
		return ins(iMov.src + idir[iMov.dir] * iMov.len, rem(iMov.src));
	}
}

U8 Board::ins(U8 index, U8 type)
{
	U8 ret = cheese[index].Gettype();
	cheese[index].Settype(type);

	U8 flag, len;
	flag = index / 4;
	len = 0;
	while(flag - len > 0 && cheese[flag - 4 * len].Gettype())
		len ++;
	cheese[index].Setup(len);
	cheese[flag - 4 * len].Setdown(len);

	len = 0;
	while(flag + len < 7 && cheese[flag + 4 * len].Gettype())
		len ++;
	cheese[index].Setdown(len);
	cheese[flag + 4 * len].Setup(len);

	flag = index % 4;
	len = 0;
	while(flag - len > 0 && cheese[flag - len].Gettype())
		len ++;
	cheese[index].Setright(len);
	cheese[flag - len].Setleft(len);

	len = 0;
	while(flag + len < 3 && cheese[flag + len].Gettype())
		len ++;
	cheese[index].Setleft(len);
	cheese[flag + len].Setright(len);
	return ret;
}

U8 Board::rem(U8 index)
{
	U8 type = cheese[index].Gettype();
	cheese[index].Settype(0);
	if(cheese[index].Getdown() && cheese[index].Getup())
	{
		U8 ext = cheese[index].Getdown() + cheese[index].Getup() + 1;
		cheese[index + 4 * cheese[index].Getdown()].Setup(ext);
		cheese[index - 4 * cheese[index].Getup()].Setdown(ext);
	}
	else if(cheese[index].Getdown())
		cheese[index + 4 * cheese[index].Getdown()].Setup(0);
	else if(cheese[index].Getup())
		cheese[index - 4 * cheese[index].Getup()].Setdown(0);

	if(cheese[index].Getleft() && cheese[index].Getright())
	{
		U8 ext = cheese[index].Getleft() + cheese[index].Getright() + 1;
		cheese[index + cheese[index].Getleft()].Setright(ext);
		cheese[index - cheese[index].Getright()].Setleft(ext);
	}
	else if(cheese[index].Getleft())
		cheese[index + cheese[index].Getleft()].Setright(0);
	else if(cheese[index].Getright())
		cheese[index - cheese[index].Getright()].Setleft(0);
	return type;
}
