#include "Board.h"
#include "BoardQ.h"

void bfs( Board root );

int main()
{
	Board test;

	test.addRed( 2 );
	test.addCar( 1, 0, 2, 1 );
    	test.addCar( 4, 1, 2, 1 );
	test.addCar( 3, 2, 2, 1 );
	test.addCar( 0, 3, 2, 1 );
	test.addCar( 0, 4, 3, 1 );
	test.addCar( 0, 5, 3, 1 );
	test.addCar( 0, 0, 3, 0 );
	test.addCar( 1, 1, 2, 0 );
	test.addCar( 3, 0, 2, 0 );
	test.addCar( 4, 4, 2, 0 );
	test.addCar( 5, 2, 2, 0 );
	test.addCar( 5, 4, 2, 0 );
	test.print();
	
    	bfs( test );

	return 0;	
}
