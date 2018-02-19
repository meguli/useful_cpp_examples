#include <vector>
#include <iostream>

using std::vector;
using std::cout;

/*
	Additional reading
	https://www.cs.indiana.edu/pub/techreports/TR542.pdf
*/

/*	
	CRTP stands for Curiously Recurring Template Pattern. We'll use this
	technique to parametrize an implementation of a virtual function using
	templates and still expose a polymorphic behaviour.

	struct Shape
	{
		virtual Shape* Clone() = 0;
		virtual ~Shape() = default;
	};

	struct Square : public Shape
	{
		virtual Square* Clone() override
		{
			// Cloning is handled by default copy constructor
			return new Square(*this);
		}
	
		int x = 1;
	};

	struct Rectangle : public Shape
	{
		virtual Rectangle* Clone() override
		{
			// Cloning is handled by default copy constructor
			return new Rectangle(*this);
		}

		int x = 5;
		int y = 3;
	};

	The above Clone function has the polymorphic behaviour we want but the
	implementation is really the same. We would be duplicating this code
	for each new Shape if we don't make it a template function. But where 
	to put the templated version? Putting it onto base class will not work
	as you can see in the following video:
	https://youtu.be/7-nHdQjSRe0
*/

struct Shape
{
	virtual Shape* Clone() = 0;
	virtual ~Shape() = default;
};

/* 
	Since ShapeCRTP is a Shape, all that inherit from it
	will still be a Shape and we can manage them through
	a Shape*
*/
template <typename T>
struct ShapeCRTP : public Shape
{
	
	virtual Shape* Clone() override
	{
		// Cloning is handled by default copy constructor
		return new T(*static_cast<T*>(this));

		// this pointer will point to ShapeCRTP but when we come to Clone
		// we know that it is either a Square or Rectangle object so this
		// can be statically casted into T* and this is needed to call T's
		// copy constructor
	}

};

// Templated on our type itself, this is the
// curious recurrence pattern on the template type
struct Square : public ShapeCRTP<Square>
{
	int x = 1;
};

struct Rectangle : public ShapeCRTP<Rectangle>
{
	int x = 5;
	int y = 3;
};

bool CRTP_test()
{
	vector<Shape*> v;

	v.push_back(new Square);
	v.push_back(new Rectangle);

	for (auto s : v)
	{
		// Examine to see that c has members of
		// square and rectangle copied
		Shape* c = s->Clone();
	}
	return true;
}

/*
int main()
{
	bool b = CRTP_test();
	if (b)
		cout << "Tests passed";
	else
		cout << "Tests failed";

	return 0;
}
*/