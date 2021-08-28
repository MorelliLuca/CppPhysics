//VectorAlgebra.hpp - Libraries for vector algerba
//Written by Luca Morelli 2021 

#ifndef VECTORALGEBRA_HPP
#define VECTORALGEBRA_HPP

#include <math.h>
#include <iostream>

namespace VA{
struct Const{
    inline double static epsilon{1E-5};
    double static constexpr G{6.678E-11},Pi{M_PI},K_e{8.988e9};

};

//Template struct to create vectors in 3d space
template <typename T>
struct Vector3{
T x{0};
T y{0};
T z{0};

//Overload @= operators
template <typename S>
Vector3<T> const& operator+=(Vector3<S> const& lhs)
{
    x+=lhs.x;
    y+=lhs.y;
    z+=lhs.z;
    return *this;
}

Vector3<T> const& operator*=(T lhs)
{
    x*=lhs;
    y*=lhs;
    z*=lhs;
    return *this;
}
template <typename S>
Vector3<T> const& operator-=(Vector3<S> const& lhs)
{
    x-=lhs.x;
    y-=lhs.y;
    z-=lhs.z;
    return *this;
}

Vector3<T> const& operator/=(T lhs)
{
    x/=lhs;
    y/=lhs;
    z/=lhs;
    return *this;
}

template <typename S>
T operator*=(Vector3<S> const& lhs)
{
    
    return x*lhs.x+y*lhs.y+z*lhs.z;
}

//Conversion between types
template <typename S>
operator Vector3<S>() const
{
    return Vector3<S>{x,y,z};
}

};

//Overload of the other operators
template <typename T, typename S>
inline bool operator==(Vector3<T> const& rhs, Vector3<S> const& lhs)
{
    return (rhs.x==lhs.x&&rhs.y==lhs.y&&rhs.z==lhs.z);
}

template <typename T, typename S>
inline bool operator!=(Vector3<T> const& rhs, Vector3<S> const& lhs)
{
    return !(lhs==rhs);
}

template <typename T, typename S>
inline auto operator+(Vector3<T> rhs, Vector3<S> const& lhs)
{
    return rhs+=lhs;
}

template <typename T, typename S>
inline auto operator-(Vector3<T> rhs, Vector3<S> const& lhs)
{
    return rhs-=lhs;
}

template <typename S>
inline auto operator-(Vector3<S> const& lhs)
{
    Vector3<S> zero{0,0,0};
    return zero-=lhs;
}

template <typename T>
inline auto operator*(Vector3<T> rhs,double const& lhs)
{
    return rhs*=lhs;
}

template <typename T>
inline auto operator*(double const&  rhs,Vector3<T> lhs)
{
    return lhs*=rhs;
}

template <typename T>
inline auto operator/(Vector3<T> rhs,double const& lhs)
{
    return rhs/=lhs;
}

template <typename T, typename S>
inline auto operator*(Vector3<T> rhs, Vector3<S> const& lhs)
{
    return rhs*=lhs;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, Vector3<T> const& v)
{
    os<<v.x<<"i+"<<v.y<<"j+"<<v.z<<"k";
    return os;
}

//Vector based function

//Returns the magnetude of a vector
template <typename T>
inline double mod(Vector3<T> arg) 
{
    return sqrt(arg*arg);
}

//Returns the versor v_hat given v
template <typename T>
inline auto hat(Vector3<T> arg)
{
  return arg/mod(arg);
}

//Cross product
template <typename T, typename S>
inline Vector3<T> crossP(Vector3<T> rhs, Vector3<S> const& lhs)
{
    return Vector3<T>{rhs.y*lhs.z-lhs.y*rhs.z,rhs.z*lhs.x-rhs.x*lhs.z,rhs.x*lhs.y-rhs.y*lhs.x};
}

//Resturns the angle enclosed between two vectors
template <typename T, typename S>
inline double betweenAngle(Vector3<T> rhs, Vector3<S> const& lhs)
{
    return asin(mod(crossP(rhs,lhs))/(mod(lhs)*mod(rhs)));
}




//Aliases
using Vector3d =  Vector3<double>;
using Vector3f =  Vector3<float>;
using Vector3i =  Vector3<int>;
     
}

#endif