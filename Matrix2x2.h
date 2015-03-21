#ifndef MATRIX2x2_H
#define MATRIX2x2_H

#include "Vector2D.h"
#include "math.h"

#pragma pack(push, 1) // exact fit - no padding

struct Matrix2x2
{
	double a00, a01, a10, a11;

	Matrix2x2(double a00 = 1, double a01 = 0, double a10 = 0, double a11 = 1)
	{
		Set(a00, a01, a10, a11);
	}

	void Set(double a00, double a01, double a10, double a11)
	{
		this -> a00 = a00;
		this -> a01 = a01;
		this -> a10 = a10;
		this -> a11 = a11;
	}

	void MakeRotationMatrix(double alpha_rad)
	{
		a00 = cos(alpha_rad);
		a01 = sin(alpha_rad);
		a10 =-sin(alpha_rad);
		a11 = cos(alpha_rad);
	}

	Vector2D operator * (const Vector2D & other) const
	{
		Vector2D result;

		result.x = a00 * other.x + a01 * other.y;
		result.y = a10 * other.x + a11 * other.y;

		return result;
	}
};

#pragma pack(pop) //back to whatever the previous packing mode was

#endif
