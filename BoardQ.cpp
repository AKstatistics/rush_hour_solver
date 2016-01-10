#include "BoardQ.h"

BoardQ::BoardQ() { index = 0; }

BoardQ::BoardQ( Board first )
{
	index = 0;
	searchQ.push_back(first);
	parents.push_back(first);
}

bool BoardQ::addNode( Board node, Board parent )
{
	bool nodeAdded = 1;

	for( vector<Board>::size_type i = 0; i < searchQ.size(); i++ )
	{
		if( searchQ[i] == node )
			return !nodeAdded;
	}

	searchQ.push_back( node );
	parents.push_back( parent );
	return nodeAdded;
}

Board BoardQ::fifo()
{
	if( this->isEmpty() )
		return searchQ[index - 1];

	index++;
	return searchQ[index - 1];
}

bool BoardQ::isEmpty()
{
	return (index == searchQ.size());
}

deque<Board> BoardQ::getPath(Board from, Board to)
{
	deque<Board> path;
	Board node;
	Board parent;

	node = to;

	while( node != from )
	{
		for( int i = searchQ.size() - 1; i >= 0; i-- )
		{
			if( node == searchQ[i] )
			{
				path.push_front( node );
				node = parents[i];
			}
		}
	}

	return path;
}
