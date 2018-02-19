#ifndef INSTRUMENTED_H
#define INSTRUMENTED_H
#include <cstddef>

enum operations
{
    constructor = 0,
    default_const = 1,
    copy_const = 2,
    destructor = 3,
    assignment = 4,
    equality = 5,
    comparison = 6,
};

template <typename T>
struct instrumented
{
    T value;
    typedef T real_type;
    static size_t counts[7];

    // conversions and constructors
    explicit instrumented(const T& x) : value(x) { ++counts[operations::constructor]; }

    instrumented(const instrumented& x) : value(x.value) { ++counts[operations::copy_const]; }
    instrumented() { ++counts[operations::default_const]; }
    ~instrumented() { ++counts[operations::destructor]; }
    instrumented& operator=(const instrumented& x)
    {
        ++counts[operations::assignment];
        value = x.value;
        return *this;
    }

    friend bool operator==(const instrumented& x, const instrumented& y)
    {
        ++counts[operations::equality];
        return x.value == y.value;
    }

    friend bool operator!=(const instrumented& x, const instrumented& y)
    {
        return !(x == y);
    }

    friend bool operator<(const instrumented& x, const instrumented& y)
    {
        ++counts[operations::comparison];
        return x.value < y.value;
    }

    friend bool operator>(const instrumented& x, const instrumented& y)
    {
        return y < x;
    }

    friend bool operator<=(const instrumented& x, const instrumented& y)
    {
        return !(y < x);
    }

    friend bool operator>=(const instrumented& x, const instrumented& y)
    {
        return !(x < y);
    }
    
    static size_t constructor_count() { return instrumented<T>::counts[operations::constructor]; }
    static size_t default_const_count() { return instrumented<T>::counts[operations::default_const]; }
    static size_t copy_const_count() { return instrumented<T>::counts[operations::copy_const]; }
    static size_t destructor_count() { return instrumented<T>::counts[operations::destructor]; }
    static size_t assignment_count() { return instrumented<T>::counts[operations::assignment]; }
    static size_t equality_count() { return instrumented<T>::counts[operations::equality]; }
    static size_t comparison_count() { return instrumented<T>::counts[operations::comparison]; }
};

#endif