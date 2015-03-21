#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <math.h>

#pragma pack(push, 1) // exact fit - no padding

struct Vector2D
{
    Vector2D() : x(0), y(0)
    {
    }

    Vector2D(const Vector2D& other)
    {
        *this = other;
    }

    Vector2D(double x, double y)
    {
        this -> x = x;
        this -> y = y;
    }

    double Length()
    {
        return sqrt(x * x + y * y);
    }

    void Normalize()
    {
        double length = Length();
        if ( length != 0.0 ) // do not divide is length is really small
        {
            x /= length;
            y /= length;
        }
    }

    void Set( double x, double y )
    {
        this -> x = x;
        this -> y = y;
    }

    void operator - ( void )
    {
        x = -x;
        y = -y;
    }

    void operator *= ( double scalar )
    {
        x *= scalar;
        y *= scalar;
    }

    void operator /= ( double scalar )
    {
        x /= scalar;
        y /= scalar;
    }

    Vector2D operator * ( double scalar ) const
    {
        Vector2D result;

        result.x = x * scalar;
        result.y = y * scalar;

        return result ;
    }

    Vector2D operator + ( const Vector2D& other ) const
    {
        Vector2D result;

        result.x = x + other.x;
        result.y = y + other.y;

        return result ;
    }

    Vector2D operator - ( const Vector2D& other ) const
    {
        Vector2D result;

        result.x = x - other.x;
        result.y = y - other.y;

        return result ;
    }

    void operator += ( const Vector2D& other )
    {
        x += other.x;
        y += other.y;
    }

    void operator -= ( const Vector2D& other )
    {
        x -= other.x;
        y -= other.y;
    }

    double operator * ( const Vector2D& other ) const
    {
        double dot_product = 0.0;

        dot_product = x * other.x + y * other.y;

        return dot_product;
    }

    bool operator == ( const Vector2D& other ) const
    {
        bool result = x == other.x && y == other.y;

        return result;
    }

    bool operator != ( const Vector2D& other ) const
    {
        return !(*this == other);
    }

	double x, y;
};

#pragma pack(pop) //back to whatever the previous packing mode was

#endif
