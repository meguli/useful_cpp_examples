#include <type_traits>
#include <iostream>
#include <cmath>

using std::conditional_t;
using std::is_floating_point;
using std::true_type;
using std::false_type;
using std::enable_if_t;

/* 
	For additional explanation, watch the video
	https://youtu.be/Vkck4EU2lOU
*/
/* 
	Suppose we want to implement an Equals function that compares two
	objects of same type to see if they are equal. We'll write a templated
	function. You'll see that we can handle the edge cases in two different
	ways: one is tag dispatching and the other is SFINAE. Change the defs
	below to examine each.
*/
#define SFINAE

// This part uses tag dispatching to handle template overload resolution.
#ifdef TAG

template <typename T>
bool Equals(T lhs, T rhs)
{
	return Equals(lhs, rhs,
		conditional_t<is_floating_point<T>::value,
		true_type,
		false_type>{});
	// conditional_t is a shorthand for getting the typename out of
	// conditional<bool, T1, T2>::type
}

// FP arithmetic case
template <typename T>
bool Equals(T lhs, T rhs, true_type)
{
	return fabs(rhs - lhs) < 0.00000000001;
}

// Other cases
template <typename T>
bool Equals(T lhs, T rhs, false_type)
{
	return rhs == lhs;
}
#endif // TAG

// This part uses the SFINAE idiom to handle template overload resolution. 
#ifdef SFINAE

/*
	"API" to utilize SFINAE is the template enable_if<Pred, T> and this returns
	you the type T if your Pred is true. default T returned is void if Pred is
	true and T is ommited. [Note that templates can have default arguments just
	like functions] enable_if_t returns an erronous type if Pred is not true.
	Compiler sees this erronous situation but says, "well, substitution failure
	is not an error, SFINAE. I'll just remove that resolution from possible
	overloads and move on with my other possible resolutions. This is the reason
	why compiler considers the second template when expanding with T = floating"
*/
template <typename T>
enable_if_t<!is_floating_point<T>::value, bool> Equals(T lhs, T rhs)
{
	return rhs == lhs;
}

template <typename T>
enable_if_t<is_floating_point<T>::value, bool> Equals(T lhs, T rhs)
{
	return fabs(lhs - rhs) < 0.00000000001;
}
#endif // SFINAE

bool equals_test()
{
	bool b1 = Equals(4, 4);
	bool b2 = Equals(4.04 - 0.04, 4.0);
	bool b3 = Equals("how", "how");

	return b1 && b2 && b3;
}

/*
int main()
{
	bool b = equals_test();
	if (b)
		std::cout << "Tests passed.";
	else
		std::cout << "Tests failed.";
}
*/