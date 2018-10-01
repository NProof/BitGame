#include "Chess.h"

Chess::Chess()
{
	//ctor
}

Chess::~Chess()
{
	//dtor
}

bool Chess::isC()
{
	char tmp = "-kgmrncpKGMRNCPX"[type];
	return tmp == 'c' || tmp == 'C';
}

bool Chess::isRed()
{
	char tmp = "-kgmrncpKGMRNCPX"[type];
	return islower(tmp);
}

bool Chess::isEmp()
{
	return !type;
}

bool Chess::isMove(U8 beType)
{
	return false;
}
