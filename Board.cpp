#include "Board.h"

Board::Board()
{
	// Set up board
	mBoard = new int* [BOARDSIZE];
	for( int ROW = 0; ROW < BOARDSIZE; ROW++ )
	{
		mBoard[ROW] = new int[BOARDSIZE];
	}
	for( int ROW = 0; ROW < BOARDSIZE; ROW++ )
	{
		for( int COL = 0; COL < BOARDSIZE; COL++ )
		{
			mBoard[ROW][COL] = 0;
		}
	}

	// Set redCar params. 
	// X = -1 indicates redCar position has not been set.
	Car redCar;
	redCar.ccol = -1;
	redCar.crow = RROW;
	redCar.clen = RLENGTH;
	redCar.cvert = RVERT;
	redCar.cID = 1;

	mCars.push_back( redCar );
}

Board::Board(const Board & rhs)
{
	// Set up board
	mBoard = new int* [BOARDSIZE];
	for( int ROW = 0; ROW < BOARDSIZE; ROW++ )
	{
		mBoard[ROW] = new int[BOARDSIZE];
	}
	for( int ROW = 0; ROW < BOARDSIZE; ROW++ )
	{
		for( int COL = 0; COL < BOARDSIZE; COL++ )
		{
			mBoard[ROW][COL] = rhs.mBoard[ROW][COL];
		}
	}

	for( vector<Car>::size_type i = 0; i < rhs.mCars.size(); i++ )
	{
		mCars.push_back( rhs.mCars[i] );
	}
}

bool Board::addRed( int col )
{
	bool carAdded = 1;

	// Check to see if the redCar has previously been placed
	if( mCars[0].ccol != -1 )
		return !carAdded;

	// Check to see that the col is valid
	if( col < 0 || col > BOARDSIZE - RLENGTH )
	       return !carAdded;

	// Check whether the space on the board is free	
	for( int i = 0; i < RLENGTH; i++ )
	{
		if( mBoard[RROW][col + i] != 0 )
			return !carAdded;
	}

	// Set the redCar's col
	mCars[0].ccol = col;

	// Set board spaces to the redCar id, 1
	for( int i = 0; i < RLENGTH; i ++ )
	{
		mBoard[RROW][col + i] = 1;
	}

	return carAdded;
}

bool Board::moveRed( int col )
{
	bool carMoved = 1;
	
	// Check whether the redCar has not yet been placed
	// or if the redCar is already where we wish to move it
	if( mCars[0].ccol == -1 || mCars[0].ccol == col )
		return !carMoved;

	// Check to see that the new col is valid
	if( col < 0 || col > BOARDSIZE - RLENGTH )
		return !carMoved;

	// Check to see that the new spaces are free or already occupied by the redCar
	for( int i = 0; i < RLENGTH; i++ )
	{
		if( mBoard[RROW][col + i] != 0 && mBoard[RROW][col + i] != 1 )
			return !carMoved;
	}

	// Empty the old spaces
	for( int i = 0; i < RLENGTH; i++ )
	{
		mBoard[RROW][mCars[0].ccol + i] = 0;
	}
	
	// Set the new col for the redCar
	mCars[0].ccol = col;

	// Set board spaces to the redCar id, 1
	for( int i = 0; i < RLENGTH; i++ )
	{
		mBoard[RROW][col + i] = 1;
	}
	
	return carMoved;
}

bool Board::addCar( int row, int col, int len, bool vert )
{
	bool carAdded = 1;

	// Check for valid length
	if( len <= 0 || len > BOARDSIZE )
		return !carAdded;

	// Check for valid row and col.
	if( vert == 0 )
	{
		// Car is horizontal
		if( row < 0 || row >= BOARDSIZE ||
		    col < 0 || col > BOARDSIZE - len )
			return !carAdded;
	}
	else
	{
		// Car is vertical
		if( row < 0 || row > BOARDSIZE - len ||
		    col < 0 || col >= BOARDSIZE )
			return !carAdded;
	}

	// Check for vacant board positions
	if( vert == 0 )
	{
		// Car is horizontal
		for( int i = 0; i < len; i++ )
		{
			if( mBoard[row][col + i] != 0 )
				return !carAdded;
		}
	}
	else
	{
		// Car is vertical
		for( int i = 0; i < len; i++ )
		{
			if( mBoard[row + i][col] != 0 )
				return !carAdded;
		}
	}

	// Create Car object and add to mCars
	Car newCar;
	newCar.crow = row;
	newCar.ccol = col;
	newCar.clen = len;
	newCar.cvert = vert;
	newCar.cID = mCars.size() + 1;
	
	mCars.push_back( newCar );

	// Set board positions to car id
	if( vert == 0 )
	{
		// Car is horizontal
		for( int i = 0; i < len; i++ )
		{
			mBoard[row][col + i] = mCars.size();
		}
	}
	else
	{
		// Car is vertical
		for( int i = 0; i < len; i++ )
		{
			mBoard[row + i][col] = mCars.size();
		}
	}
	
	return carAdded;
}

bool Board::moveCar( int ID, int rowcol )
{
	bool carMoved = 1;

	// Check valid ID
	if( ID < 1 || ID > mCars.size() ) 
		return !carMoved;

	Car cc = mCars[ID - 1];

	// Check valid rowcol
	if( rowcol < 0 || rowcol > BOARDSIZE - cc.clen )
		return !carMoved;

	// Check for vacant board positions
	if( cc.cvert == 0 )
	{
		// Car is horizontal
		for( int i = 0; i < cc.clen; i++ )
		{
			if( mBoard[cc.crow][rowcol + i] != 0 && 
			    mBoard[cc.crow][rowcol + i] != ID)
				return !carMoved;
		}
	}
	else
	{
		// Car is vertical
		for( int i = 0; i < cc.clen; i++ )
		{
			if( mBoard[rowcol + i][cc.ccol] != 0 && 
			    mBoard[rowcol + i][cc.ccol] != ID )
				return !carMoved;
		}
	}
	// Set board positions to 0
	if( cc.cvert == 0 )
	{
		// Car is horizontal
		for( int i = 0; i < cc.clen; i++ )
		{
			mBoard[cc.crow][cc.ccol + i] = 0;
		}
	}
	else
	{
		// Car is vertical
		for( int i = 0; i < cc.clen; i++ )
		{
			mBoard[cc.crow + i][cc.ccol] = 0; 
		}
	}

	// Set new location for the car
	if( mCars[ID - 1].cvert == 0 )
	{
		// Car is horizontal
		mCars[ID - 1].ccol = rowcol;
	}
	else
	{
		// Car is vertical
		mCars[ID - 1].crow = rowcol;
	}

	// Set new board positions to car id
	if( mCars[ID - 1].cvert == 0 )
	{
		// Car is horizontal
		for( int i = 0; i < cc.clen; i++ )
		{
			mBoard[mCars[ID - 1].crow][mCars[ID - 1].ccol + i] = ID;
		}
	}
	else
	{
		// Car is vertical
		for( int i = 0; i < cc.clen; i++ )
		{
			mBoard[mCars[ID - 1].crow + i][mCars[ID - 1].ccol] = ID;
		}
	}	

	return carMoved;
}

bool Board::stepCar( int ID, bool upright )
{
	// Check for valid ID
	if( ID < 1 || ID > mCars.size() ) 
		return 0; 
	
	Car cc = mCars[ID - 1];

	// Call moveCar function to move car one step 
	if( cc.cvert == 0 )
	{
		// Car is horizontal
		if( upright == 0 )
		{
			// Move one to the left
			return this->moveCar( ID, cc.ccol - 1 );
		}
		else
		{
			// Move one to the right
		        return this->moveCar( ID, cc.ccol + 1);
		}
	}
	else
	{
		// Car is vertical
		if( upright == 0 )
		{
			// Move one step down 
			return this->moveCar( ID, cc.crow + 1 );
		}
		else
		{
			// Move one step up 
			return this->moveCar( ID, cc.crow - 1 );
		}
	}

	return 0;
}

bool Board::stepRed( bool right )
{
	if( right == 0 )
	{
		// Move one to the left
		return this->moveRed( mCars[0].ccol - 1 );
	}
	else
	{
		return this->moveRed( mCars[0].ccol + 1 );
	}

	return 0;
}

bool Board::isSolution()
{
	bool isSolution = 1;

	for( int i = mCars[0].ccol + RLENGTH; i < BOARDSIZE; i++ ) 
	{
		if( mBoard[RROW][i] != 0 )
			return !isSolution;
	}

	return isSolution;
}

Board & Board::operator=( const Board & rhs )
{
	for( int ROW = 0; ROW < BOARDSIZE; ROW++ )
	{
		for( int COL = 0; COL < BOARDSIZE; COL++ )
		{
			mBoard[ROW][COL] = rhs.mBoard[ROW][COL];
		}
	}

	mCars.clear();

	for( vector<Car>::size_type i = 0; i < rhs.mCars.size(); i++ )
	{
		mCars.push_back( rhs.mCars[i] );
	}

	return *this;
}

bool operator==( const Board & lhs, const Board & rhs )
{
	bool isEqual = 1;
	
	if( &lhs == &rhs )
		return isEqual;

	if( lhs.mCars.size() != rhs.mCars.size() )
		return !isEqual;

	for( vector<Car>::size_type i = 0; i < lhs.mCars.size(); i++ )
	{
		if( lhs.mCars[i].crow != rhs.mCars[i].crow ||
		    lhs.mCars[i].ccol != rhs.mCars[i].ccol ||
		    lhs.mCars[i].clen != rhs.mCars[i].clen ||
		    lhs.mCars[i].cvert != rhs.mCars[i].cvert )
			return !isEqual;
	}

	return isEqual;
}

void Board::print()
{
	for( int ROW = 0; ROW < BOARDSIZE; ROW++ )
	{
		for( int COL = 0; COL < BOARDSIZE; COL++ )
		{
			cout << this->id( mBoard[ROW][COL] ) << "  ";
			if( COL % BOARDSIZE == BOARDSIZE - 1 )
				cout << endl;
		}
	}
	cout << endl;
}

Board::~Board()
{
	for( int ROW = 0; ROW < BOARDSIZE; ROW++ )
	{
		if( mBoard[ROW] != NULL )
			delete [] mBoard[ROW];
	}

	if( mBoard != NULL )
		delete [] mBoard;
}

char Board::id( int i )
{
	char out;
	switch( i )
	{
		case 0:
			out = '*';
			break;
		case 1:
			out = 'R';
			break;
		case 2:
			out = 'A';
			break;
		case 3:
			out = 'B';
			break;
		case 4:
			out = 'C';
			break;
		case 5:
			out = 'D';
			break;
		case 6:
			out = 'E';
			break;
		case 7:
			out = 'F';
			break;
		case 8:
			out = 'G';
			break;
		case 9:
			out = 'H';
			break;
		case 10:
			out = 'I';
			break;
		case 11:
			out = 'J';
			break;
		case 12:
			out = 'K';
			break;
		case 13:
			out = 'L';
			break;
		case 14:
			out = 'M';
			break;
		case 15:
			out = 'N';
			break;
		case 16:
			out = 'O';
			break;
		case 17:
			out = 'P';
			break;
		case 18:
			out = 'Q';
			break;
	}

	return out;
}
