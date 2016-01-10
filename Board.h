#ifndef BOARD_H
#define BOARD_H

#include<vector>
#include<iostream>

using std::vector;
using std::cout;
using std::endl;

struct Car
{
	int crow;
	int ccol;
	int clen;
	bool cvert;
	int cID;
};

class Board
{
	private:
		// All boards are 6x6. The red car is always horizontal, 
		// has length 2, and is in the 3rd row (index 2). 
		static const int  BOARDSIZE = 6;
		static const int  RROW = 2;	  // Red car row
		static const int  RLENGTH = 2;    // Red car length
		static const bool RVERT = 0;	  // Red car is horizontal
		
		vector<Car> mCars;
		int ** mBoard;

		char id( int );
	public:
		Board();
		Board( const Board & );
		bool addCar( int row, int col, int len, bool vert );
		bool addRed( int col );
		bool isSolution();

		int numCars(){ return mCars.size(); }
		int boardSize(){ return BOARDSIZE; }

		bool moveCar( int ID, int rowcol );
		bool moveRed( int col );

		bool stepCar( int ID, bool upright );
		bool stepRed( bool right );
		
		void print();

		Board &operator=( const Board & rhs );
		friend bool operator==(const Board & lhs, const Board & rhs);
		friend bool operator!=(const Board & lhs, const Board & rhs) { return !( lhs == rhs ); }

		~Board();
};

#endif
