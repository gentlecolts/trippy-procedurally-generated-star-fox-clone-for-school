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
#include "vec4d.h"
//TODO: make this 4x4 so I can represent translations


class Matrix {
private:
	Vec4d *v;
public:
	Matrix();
	Matrix(Vec4d x, Vec4d y, Vec4d z, Vec4d w);
	Matrix(Vec4d angles);
	
	Vec4d &operator[](int index);
	Vec4d operator[](int index) const;
	
	Matrix operator*(double scale) const;
	Matrix operator/(double scale) const;
	Matrix operator+(const Matrix &other) const;
	Matrix operator-(const Matrix &other) const;
	Matrix operator-() const;
	
	Vec4d operator*(Vec4d vect) const;
	Matrix operator*(Matrix mat) const;
	
	const Matrix &operator*=(double scale);
	const Matrix &operator*=(Matrix mat);
	const Matrix &operator/=(double scale);
	const Matrix &operator+=(const Matrix &other);
	const Matrix &operator-=(const Matrix &other);
};

#endif /* defined(__HelloSDL__Matrix__) */
