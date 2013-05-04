//
//  Matrix.cpp
//  HelloSDL
//
//  Created by Jonah Chazan on 5/4/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#include "Matrix.h"
#include "vec3d.h"
#include "math.h"
#include "imports.h"

Matrix::Matrix() {
	v=new Vec3d[3];
	v[0]=new Vec3d;
	v[1]=new Vec3d;
	v[2]=new Vec3d;
}

Matrix::Matrix(Vec3d x, Vec3d y, Vec3d z) {
	v[0] = x;
	v[1] = y;
	v[2] = z;
}

Matrix::Matrix(Vec3d angles) {
	Matrix yRotMat=Matrix(
		Vec3d(cos(radians(angles[1])), 0, sin(radians(angles[1]))),
		Vec3d(0, 1, 0),
		Vec3d(-sin(radians(angles[1])), 0, cos(radians(angles[1])))
	);
	
	Matrix xRotMat=Matrix(
						  Vec3d(1, 0, 0),
						  Vec3d(0, cos(radians(angles[0])), -sin(radians(angles[0]))),
						  Vec3d(0, sin(radians(angles[0])), cos(radians(angles[0])))
						  );
	
	Matrix zRotMat=Matrix(
						  Vec3d(cos(radians(angles[2])), -sin(radians(angles[2])), 0),
						  Vec3d(sin(radians(angles[2])), cos(radians(angles[2])), 0),
						  Vec3d(0, 0, 1)
						  );
	
	Matrix comb=yRotMat*xRotMat*zRotMat;
	
	v=comb.v;
}

Vec3d &Matrix::operator[](int index) {
	return v[index];
}

Vec3d Matrix::operator[](int index) const {
	return v[index];
}

Matrix Matrix::operator*(double scale) const {
	return Matrix(v[0] * scale, v[1] * scale, v[2] * scale);
}

Matrix Matrix::operator/(double scale) const {
	return Matrix(v[0] / scale, v[1] / scale, v[2] / scale);
}

Matrix Matrix::operator+(const Matrix &other) const {
	return Matrix(v[0] + other.v[0], v[1] + other.v[1], v[2] + other.v[2]);
}

Matrix Matrix::operator-(const Matrix &other) const {
	return Matrix(v[0] - other.v[0], v[1] - other.v[1], v[2] - other.v[2]);
}

Matrix Matrix::operator-() const {
	return Matrix(-v[0], -v[1], -v[2]);
}

Vec3d Matrix::operator*(Vec3d vect) const {
	return Vec3d(v[0][0]*vect[0]+v[0][1]*vect[1]+v[0][2]*vect[2],
				 v[1][0]*vect[0]+v[1][1]*vect[1]+v[1][2]*vect[2],
				 v[2][0]*vect[0]+v[2][1]*vect[1]+v[2][2]*vect[2]
	);
}

Matrix Matrix::operator*(Matrix mat) const {
	Matrix comb;
	
	for(int i=0;i<3;i++) {
		for(int j=0;j<3;j++) {
			Vec3d columnVec=Vec3d(v[0][i],v[1][i],v[2][i]);
			comb[i][j]=columnVec.dot(mat[j]);
		}
	}
	
	return comb;
}

const Matrix &Matrix::operator*=(Matrix mat) {
	Matrix comb=*this*mat;
	
	v=comb.v;

	return *this;
}

const Matrix &Matrix::operator*=(double scale) {
	v[0] *= scale;
	v[1] *= scale;
	v[2] *= scale;
	return *this;
}

const Matrix &Matrix::operator/=(double scale) {
	v[0] /= scale;
	v[1] /= scale;
	v[2] /= scale;
	return *this;
}

const Matrix &Matrix::operator+=(const Matrix &other) {
	v[0] += other.v[0];
	v[1] += other.v[1];
	v[2] += other.v[2];
	return *this;
}

const Matrix &Matrix::operator-=(const Matrix &other) {
	v[0] -= other.v[0];
	v[1] -= other.v[1];
	v[2] -= other.v[2];
	return *this;
}