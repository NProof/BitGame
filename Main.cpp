#include <iostream>
#include "Board.h"
#include "Chess.h"

using namespace std;

int main(int argc, char *argv[])
{
	cout << sizeof(Board) << endl;
	cout << sizeof(Chess) << endl;
	cout << sizeof(Move) << endl;
	return 0;
}
