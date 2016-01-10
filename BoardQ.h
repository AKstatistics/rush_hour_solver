#ifndef BOARDQ_H
#define BOARDQ_H

#include "Board.h"
#include <vector>
#include <deque>
#include <iostream>
using std::cout;
using std::endl;

using std::vector;
using std::deque;

class BoardQ
{
	private:
		vector<Board> searchQ;
		vector<Board> parents;
		int index;
	public:
		BoardQ();
		BoardQ( Board first );
		bool addNode( Board node, Board parent);
		Board fifo();
		bool isEmpty();
		deque<Board> getPath( Board from, Board to );
};

#endif
