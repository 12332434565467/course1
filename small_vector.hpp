
#ifndef SMALL_VECTOR_HPP_214E3703_A050_411A_834B_4E55AEEC18B8
#define SMALL_VECTOR_HPP_214E3703_A050_411A_834B_4E55AEEC18B8

#include <cassert>
#include <cmath>
#include <cstddef>

template<std::size_t N, typename T = float>
struct SmallVec
{
    T v[N];

    constexpr T& operator[](std::size_t i) noexcept
    {
        assert(i < N);
        return v[i];
    }

    constexpr T operator[](std::size_t i) const noexcept
    {
        assert(i < N);
        return v[i];
    }

    constexpr T const* data() const noexcept
    {
        return v;
    }
};

template<typename T>
struct SmallVec<2, T>
{
    T x, y;

    constexpr T& operator[](std::size_t i) noexcept
    {
        assert(i < 2);
        return (&x)[i];
    }

    constexpr T operator[](std::size_t i) const noexcept
    {
        assert(i < 2);
        return (&x)[i];
    }

    constexpr T const* data() const noexcept
    {
        return &x;
    }
};

template<typename T>
struct SmallVec<3, T>
{
    T x, y, z;

    constexpr T& operator[](std::size_t i) noexcept
    {
        assert(i < 3);
        return (&x)[i];
    }

    constexpr T operator[](std::size_t i) const noexcept
    {
        assert(i < 3);
        return (&x)[i];
    }

    constexpr T const* data() const noexcept
    {
        return &x;
    }
};

template<typename T>
struct SmallVec<4, T>
{
    T x, y, z, w;

    constexpr T& operator[](std::size_t i) noexcept
    {
        assert(i < 4);
        return (&x)[i];
    }

    constexpr T operator[](std::size_t i) const noexcept
    {
        assert(i < 4);
        return (&x)[i];
    }

    constexpr T const* data() const noexcept
    {
        return &x;
    }
};

template<std::size_t N, typename T>
constexpr std::size_t dimension(SmallVec<N, T>) noexcept
{
    return N;
}

template<std::size_t N, typename T>
constexpr SmallVec<N, T> operator+(SmallVec<N, T> const& a) noexcept
{
    return a;
}

template<std::size_t N, typename T>
constexpr SmallVec<N, T> operator-(SmallVec<N, T> const& a) noexcept
{
    SmallVec<N, T> r{};
    for (std::size_t i = 0; i < N; ++i)
        r[i] = -a[i];
    return r;
}

template<std::size_t N, typename T>
constexpr SmallVec<N, T> operator+(
    SmallVec<N, T> const& a,
    SmallVec<N, T> const& b) noexcept
{
    SmallVec<N, T> r{};
    for (std::size_t i = 0; i < N; ++i)
        r[i] = a[i] + b[i];
    return r;
}

template<std::size_t N, typename T>
constexpr SmallVec<N, T> operator-(
    SmallVec<N, T> const& a,
    SmallVec<N, T> const& b) noexcept
{
    SmallVec<N, T> r{};
    for (std::size_t i = 0; i < N; ++i)
        r[i] = a[i] - b[i];
    return r;
}

template<std::size_t N, typename T>
constexpr SmallVec<N, T> operator*(
    T s, SmallVec<N, T> const& a) noexcept
{
    SmallVec<N, T> r{};
    for (std::size_t i = 0; i < N; ++i)
        r[i] = s * a[i];
    return r;
}

template<std::size_t N, typename T>
constexpr SmallVec<N, T> operator*(
    SmallVec<N, T> const& a, T s) noexcept
{
    return s * a;
}

template<std::size_t N, typename T>
constexpr SmallVec<N, T> operator/(
    SmallVec<N, T> const& a, T s) noexcept
{
    SmallVec<N, T> r{};
    for (std::size_t i = 0; i < N; ++i)
        r[i] = a[i] / s;
    return r;
}

template<std::size_t N, typename T>
constexpr SmallVec<N, T>& operator+=(
    SmallVec<N, T>& a, SmallVec<N, T> const& b) noexcept
{
    for (std::size_t i = 0; i < N; ++i)
        a[i] += b[i];
    return a;
}

template<std::size_t N, typename T>
constexpr SmallVec<N, T>& operator-=(
    SmallVec<N, T>& a, SmallVec<N, T> const& b) noexcept
{
    for (std::size_t i = 0; i < N; ++i)
        a[i] -= b[i];
    return a;
}

template<std::size_t N, typename T>
constexpr SmallVec<N, T>& operator*=(
    SmallVec<N, T>& a, T s) noexcept
{
    for (std::size_t i = 0; i < N; ++i)
        a[i] *= s;
    return a;
}

template<std::size_t N, typename T>
constexpr SmallVec<N, T>& operator/=(
    SmallVec<N, T>& a, T s) noexcept
{
    for (std::size_t i = 0; i < N; ++i)
        a[i] /= s;
    return a;
}

template<std::size_t N, typename T>
constexpr T dot(
    SmallVec<N, T> const& a,
    SmallVec<N, T> const& b) noexcept
{
    T result{};
    for (std::size_t i = 0; i < N; ++i)
        result += a[i] * b[i];
    return result;
}

template<std::size_t N, typename T>
inline T length(SmallVec<N, T> const& a) noexcept
{
    return static_cast<T>(
        std::sqrt(static_cast<double>(dot(a, a))));
}

