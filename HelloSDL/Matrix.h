//
//  Matrix.h
//  HelloSDL
//
//  Created by Jonah Chazan on 5/4/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#ifndef __HelloSDL__Matrix__
#define __HelloSDL__Matrix__

#include <iostream>
#include "vec3d.h"
//TODO: make this 4x4 so I can represent translations


class Matrix {
private:
	Vec3d v[3];
public:
	Matrix();
	Matrix(Vec3d x, Vec3d y, Vec3d z);
	Matrix(Vec3d angles);
	
	Vec3d &operator[](int index);
	Vec3d operator[](int index) const;
	
	Matrix operator*(double scale) const;
	Matrix operator/(double scale) const;
	Matrix operator+(const Matrix &other) const;
	Matrix operator-(const Matrix &other) const;
	Matrix operator-() const;
	
	Vec3d operator*(Vec3d vect) const;
	Matrix operator*(Matrix mat) const;
	
	const Matrix &operator*=(double scale);
	const Matrix &operator*=(Matrix mat);
	const Matrix &operator/=(double scale);
	const Matrix &operator+=(const Matrix &other);
	const Matrix &operator-=(const Matrix &other);
};

#endif /* defined(__HelloSDL__Matrix__) */
