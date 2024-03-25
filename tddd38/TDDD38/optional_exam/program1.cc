#include <iostream>
#include <cassert>
#include <sstream>
#include "stack.h"

// Originally taken from: 2022-03-17 Assignment #4
// Modified so that it doesn't requqire type converting operators.

int main()
{
    {
	Stack<int> st { 6, 5, 4 };

	// 4 should be at the top of the stack
	assert( st == 4 );
	
	// pushing 3, 2 and 1 to the stack
	st << 3 << 2 << 1;

	// now 1 should be at the top
	assert( st == 1 );

	std::ostringstream oss { };
	oss << st;
	
	assert( oss.str() == "1 2 3 4 5 6 ");

	// popping into a, b and c as a chained operator call.
	int a, b, c;
	st >> a >> b >> c;

	assert( a == 1 );
	assert( b == 2 );
	assert( c == 3 );

	// pop the values one by one
	int i { 4 };
	while (st.is_empty())
	{
	    int x;
	    st >> x;

	    assert(x == i);
	    ++i;
	}
    }

	enum {
		PONTUS,
		GORILLA

	};

	enum struct P{
		PONTUS=-1
	};

	//auto test = P::PONTUS;

	int const test = 1;
	int const test2 = 2;
	int hej = test + test2;
	int test3 = test ! test2;

	int const& x;
}
