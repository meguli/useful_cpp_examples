/* 
    This file explains the idea of a regular type and also
    gives an example called singleton<T> which can be used as
    a blueprint for our own regular types. This is explained
    in Alexander Stepanov's lectures titled "Efficient Programming
    with Components"
*/

#ifndef SINGLETON_H
#define SINGLETON_H

/* 
    By the below code, requirements on T is that it should be
    semi-regular OR regular OR totally-ordered. This is called
    a disjunctive concept. The reason it works is that templates
    are not instantiated unless they are used and singleton<T>
    will not generate, say operator==, if T is semi-regular 
    because no one will call its operator==. It is a compile-time
    error if one does anyways. 
*/
template <typename T>
struct singleton
{
    T value;
    typedef T value_type;
    
    /*
        Implicit conversions need to be avoided because they might lead
        to hard to decipher code. A function expectiong singleton<T>
        might be called with T if we make this non-explicit. 
    */

    // conversions and constructors
    explicit singleton(const T& x) : value(x) {}
    explicit operator T() const { return T; } // Since C++11

    // Maybe you would like to convert from singleton<int> to
    // singleton<double>? This is how you do it.
    template <typename U>
    singleton(const singleton<U>& x) : value(x.value) {}

    /* 
        semiregular types require copy const, default const, and
        assignment operator. This allows us to exchange T a(b) with
        T a; a = b; and T a = b; which is natural way we expect
        types to work
    */
    singleton(const singleton& x) : value(x.value) {}
    singleton() {}
    ~singleton() {}
    singleton& operator=(const singleton& x)
    {
        value = x.value;
        return *this;
    }

    // regular types also add operator== and != for comparison
    friend bool operator==(const singleton& x, const singleton& y)
    {
        return x.value == y.value;
    }

    friend bool operator!=(const singleton& x, const singleton& y)
    {
        return !(x == y);
    }

    /* 
        we will make this into a totally ordered type by providing
        operator<, >, <=, >=. Most of the algorithms in STL requires
        T to be a totally ordered type. Note how we define everything
        in terms of operator< so that they are semantically consistent
    */
    friend bool operator<(const singleton& x, const singleton& y)
    {
        return x.value < y.value;
    }

    friend bool operator>(const singleton& x, const singleton& y)
    {
        return y < x;
    }

    friend bool operator<=(const singleton& x, const singleton& y)
    {
        return !(y < x);
    }

    friend bool operator>=(const singleton& x, const singleton& y)
    {
        return !(x < y);
    }
};

#endif