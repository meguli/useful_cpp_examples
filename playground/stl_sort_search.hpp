/*
	This file contains STL style implementations of basic searching
	and sorting algorithms, using iterators. Most of these are, of
	course, implemented better in STL. These are just for example
	purposes.
*/
#include <iterator>
#include <algorithm>
#include <iostream>
#include <type_traits>
#include <cmath>

// Alias template for iterators having floating types as value type
// SFINAE for specializing on floating point types
template <typename T>
using floating_val_type = std::enable_if_t<std::is_floating_point<typename std::iterator_traits<T>::value_type>::value,
										   typename std::iterator_traits<T>::value_type>;
template <typename T>
using nonfloating_val_type = std::enable_if_t<!std::is_floating_point<typename std::iterator_traits<T>::value_type>::value,
											  typename std::iterator_traits<T>::value_type>;

// If value_type of given Iterator is not a floating point type, this
// template will be deduced
template <typename ForwIt>
ForwIt linear_search(ForwIt begin, ForwIt end,
					 nonfloating_val_type<ForwIt> val)
{
	while (begin != end)
	{
		if (*begin != val)
			begin++;
		else
			break;
	}
	return begin;
}

// If value_type of given Iterator is a floating point type, this
// template will be deduced
template <typename ForwIt>
ForwIt linear_search(ForwIt begin, ForwIt end,
					 floating_val_type<ForwIt> val)
{
	while (begin != end)
	{
		if (fabs(*begin - val) > 0.0001f)
			begin++;
		else
			break;
	}
	return begin;
}

// We require insertion_sort to not invalidate iterators given as parameter
// We require insertion_sort to be stable, but I won't test it
template <typename BiderIt>
void insertion_sort(BiderIt first, BiderIt last)
{
	BiderIt cur = first;
	BiderIt limit = --last;
	while (cur != limit)
	{
		cur++;
		BiderIt inner = cur;
		BiderIt left_of_inner = --cur;
		while (inner != first && *left_of_inner > *inner)
		{
			std::iter_swap(left_of_inner, inner);
			inner--;
			if (left_of_inner == first)
				break;
			else
				left_of_inner--;
		}
		cur++;
	}
}

