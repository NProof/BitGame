#ifndef CHESS_H
#define CHESS_H

#include <cctype>

typedef __UINT8_TYPE__ U8;

class Chess
{
	public:
		/** Default constructor */
		Chess();
		/** Default destructor */
		~Chess();

		bool isC();
		bool isRed();
		bool isEmp();
		bool isMove(U8);

		unsigned char Gettype() { return type; }
		void Settype(unsigned char val) { type = val; }
		unsigned char Getup() { return up; }
		void Setup(unsigned char val) { up = val; }
		unsigned char Getdown() { return down; }
		void Setdown(unsigned char val) { down = val; }
		unsigned char Getleft() { return left; }
		void Setleft(unsigned char val) { left = val; }
		unsigned char Getright() { return right; }
		void Setright(unsigned char val) { right = val; }
		unsigned char GetLright() { return Lright; }
		void SetLright(unsigned char val) { Lright = val; }
		unsigned char GetLleft() { return Lleft; }
		void SetLleft(unsigned char val) { Lleft = val; }
		unsigned char GetLdown() { return Ldown; }
		void SetLdown(unsigned char val) { Ldown = val; }
		unsigned char GetLup() { return Lup; }
		void SetLup(unsigned char val) { Lup = val; }

	protected:

	private:
		unsigned char type:4; //!< Member variable "type"
		unsigned char Lright:2; //!< Member variable "Lright"
		unsigned char Lleft:2; //!< Member variable "Lleft"
		unsigned char Ldown:3; //!< Member variable "Ldown"
		unsigned char Lup:3; //!< Member variable "Lup"
		unsigned char right:2; //!< Member variable "right"
		unsigned char left:2; //!< Member variable "left"
		unsigned char down:3; //!< Member variable "down"
		unsigned char up:3; //!< Member variable "up"
};

#endif // CHESS_H
