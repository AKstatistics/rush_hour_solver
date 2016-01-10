// NOTE: The Q object will automatically not add nodes to the queue which are already queued or have been once dequeued (already searched).

#include "Board.h"
#include "BoardQ.h"
#include <iostream>
#include <vector>
#include <deque>
using std::cout;
using std::endl;
using std::vector;
using std::deque;

void bfs( Board root )
{
	Board node;
	Board child;
	bool upright = 1;
	int nCars = 0;
	int depth = 0;
	int i = 0;
	BoardQ search( root );		// Stores the queue to be searched 
	deque<int> searchDepth;	// Stores the depth of the queued node.
	deque<Board> path;	// Stores the path to the current node being search.
	searchDepth.push_back(0);
	
	while( !search.isEmpty() )
	{
		node = search.fifo();	// Pop out the next node to search for the stack

		depth = searchDepth[0];		// Now save the depth of the current node
		searchDepth.pop_front();	// and remove that from the depth list.
		
		std::cout << i++ << ". Depth: " << depth << std::endl;
		node.print();

		if( node.isSolution() ) break;	// If we found our goal, quit.

		nCars = node.numCars();
		child = node;

		for( int ii = 0; ii <= nCars; ii++ )
		{
			if( child.stepCar( ii, !upright) )
			{
				if( search.addNode( child, node ) )
				{
					searchDepth.push_back( depth + 1 );
				}
				child = node;
			}
			if( child.stepCar( ii, upright) )
			{
				if( search.addNode( child, node ) )
				{
					searchDepth.push_back( depth + 1 );
				}
				child = node;	
			}
		}
	}	

	path = search.getPath( root, node );

	if( node.isSolution() )
	{
		while( node.stepCar( 1, 1 ) )
		{
			path.push_back( node );
		}

		cout << "Path found: " << endl;
		for( deque<Board>::size_type i = 0; i < path.size(); i++ )
		{
			cout << i << ". " << endl;
			path[i].print();
		}

		cout << "Solution found after " << i << " board states. " << endl;
	}
	else
	{
		cout << "No solution found. " << i << " board states searched. " << endl;
	}
}
