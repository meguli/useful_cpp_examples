#include <type_traits>
#include <iostream>
#include <string>

using std::ostream;
using std::conditional_t;
using std::is_floating_point;
using std::true_type;
using std::false_type;
using std::enable_if_t;
/*
	For more reading about this look at;
	SFINAE Sono Buoni
	http://www.stevedewhurst.com/once_weakly/w02_SFINAE.pdf
	and the stackoverflow question;
	https://stackoverflow.com/questions/3407633/explain-c-sfinae-to-a-non-c-programmer/3408317#3408317
*/

/*
	Let's say we want to write a generic writer for our objects.
	The thing is, we do not control how << mechanism is implemented.
	Some might use os << object by implementing operator<< and some
	might use object.write(os). We might have something like:

	template <class T>
	std::ostream &write_object(T object, std::ostream &os) {
	return os << object;
	}

	template <>
	std::ostream &write_object(special_object object, std::ostream &os) {
	return object.write(os);
	}

	but we can't specialize for every different possible type. We'll 
	use SFINAE to detect if object supports << and use this to handle
	all objects that does not support <<.
*/

/*
	Note that all these functions have no implementation because
	we only care about their return type, due to use of sizeof below,
	and we never call them. We use their return types to construct an
	illformed type when type does not support <<. This way, SFINAE will
	eliminate that resolution and will chose the other.
*/
template<class T> T& ref();
template<class T> T  val();

// has_inserter checks at compile time to see if T supports <<
template<class T>
struct has_inserter
{
	// Use of decltype is a more clear option but read the below
	// part to understand the matter, you can experiment by changing
	// the define below
	#define DECLTYPE_TRICK

	#ifdef DECLTYPE_TRICK
	template<class U>
	static char test(decltype(sizeof(ref<std::ostream>() << val<U>())));
	#endif // DECLTYPE_TRICK

	#ifdef ARRAY_TRICK
	template<class U>
	static char test(char(*)[sizeof(ref<std::ostream>() << val<U>())]);

	/*
	Above part is the magic. When we say something like has_inserter<T>,
	enum below will call "sizeof test<T>(0)". Compiler will try to find the
	matching test template function since sizeof is a compile-time. The
	above test function takes an argument of array of function pointers
	that returns char. During template resolution, sizeof in the above
	test function will eventually try to determine the return type of
	operator<<(ostream, T). When this type fails, we'll see that SFINAE
	will move to the other test function. So the return type of sizeof
	in the enum below will only be char when T supports <<. The trick is
	to use the type that would be returned by the above sizeof in another
	typename so that when that type is erronous, whole above template
	would be erronous and discarded by SFINAE.
	*/
	#endif // ARRAY_TRICK
	
	// The template to be chosen when T does not support <<. Thus,
	// sizeof test<T> will be sizeof long. We used varargs because
	// we really don't care how we call test, as long as we make
	// compiler perform template deduction
	template<class U>
	static long test(...);

	// if value is 1, ie. true, we conclude test returning char
	// is chosen by SFINAE and T supports <<
	enum { value = 1 == sizeof test<T>(0) };
};

template <class T>
enable_if_t<has_inserter<T>::value, ostream>& write_object(T object, ostream &os) {
	return os << object;
}

template <class T>
enable_if_t<!has_inserter<T>::value, ostream>& write_object(T object, ostream &os) {
	return object.write(os);
}

// An object with no << support
struct NoInserter
{
public:
	ostream& write(ostream& os)
	{
		os << data;
	}
private:
	static const int data = 5;
};

bool has_inserter_test()
{
	bool b1 = has_inserter<std::string>::value;
	bool b2 = has_inserter<NoInserter>::value;
	bool b3 = has_inserter<int>::value;
	return b1 && !b2 && b3;
}

/*
int main()
{
	bool b = has_inserter_test();
	if (b)
		std::cout << "Tests passed.";
	else
		std::cout << "Tests failed.";
}
*/