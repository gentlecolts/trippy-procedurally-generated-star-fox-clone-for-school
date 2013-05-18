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

using namespace std;

bool logMat=false;

Matrix::Matrix() {
	v=new Vec4d[4];
	v[0]=Vec4d(1, 0, 0, 0);
	v[1]=Vec4d(0, 1, 0, 0);
	v[2]=Vec4d(0, 0, 1, 0);
	v[3]=Vec4d(0, 0, 0, 1);
}

Matrix::Matrix(Vec4d x, Vec4d y, Vec4d z, Vec4d w) {
	v=new Vec4d[4];
	v[0] = x;
	v[1] = y;
	v[2] = z;
	v[3] = w;
	
//	cout<<"z: "<<z<<endl;
}

Matrix::Matrix(Vec4d angles) {
	//angles=-angles;
	
	Matrix yRotMat=Matrix(
		Vec4d(cos(radians(angles[1])), 0, sin(radians(angles[1])), 0),
		Vec4d(0, 1, 0, 0),
		Vec4d(-sin(radians(angles[1])), 0, cos(radians(angles[1])), 0),
		Vec4d(0, 0, 0, 1)
	);
	
	Matrix xRotMat=Matrix(
						  Vec4d(1, 0, 0, 0),
						  Vec4d(0, cos(radians(angles[0])), -sin(radians(angles[0])), 0),
						  Vec4d(0, sin(radians(angles[0])), cos(radians(angles[0])), 0),
						  Vec4d(0, 0, 0, 1)
						  );
	
	Matrix zRotMat=Matrix(
						  Vec4d(cos(radians(angles[2])), -sin(radians(angles[2])), 0, 0),
						  Vec4d(sin(radians(angles[2])), cos(radians(angles[2])), 0, 0),
						  Vec4d(0, 0, 1, 0),
						  Vec4d(0, 0, 0, 1)
						  );
	
	Matrix comb=yRotMat*xRotMat*zRotMat;
	
	v=comb.v;
}

Vec4d &Matrix::operator[](int index) {
	return v[index];
}

Vec4d Matrix::operator[](int index) const {
	return v[index];
}

Matrix Matrix::operator*(double scale) const {
	return Matrix(v[0] * scale, v[1] * scale, v[2] * scale, v[3] * scale);
}

Matrix Matrix::operator/(double scale) const {
	return Matrix(v[0] / scale, v[1] / scale, v[2] / scale, v[3] / scale);
}

Matrix Matrix::operator+(const Matrix &other) const {
	return Matrix(v[0] + other.v[0], v[1] + other.v[1], v[2] + other.v[2], v[3] + other.v[3]);
}

Matrix Matrix::operator-(const Matrix &other) const {
	return Matrix(v[0] - other.v[0], v[1] - other.v[1], v[2] - other.v[2], v[3] - other.v[3]);
}

Matrix Matrix::operator-() const {
	return Matrix(-v[0], -v[1], -v[2], -v[3]);
}

Vec4d Matrix::operator*(Vec4d vect) const {
	return Vec4d(v[0][0]*vect[0]+v[0][1]*vect[1]+v[0][2]*vect[2]+v[0][3]*vect[3],
				 v[1][0]*vect[0]+v[1][1]*vect[1]+v[1][2]*vect[2]+v[1][3]*vect[3],
				 v[2][0]*vect[0]+v[2][1]*vect[1]+v[2][2]*vect[2]+v[2][3]*vect[3],
				 v[3][0]*vect[0]+v[3][1]*vect[1]+v[3][2]*vect[2]+v[3][3]*vect[3]
	);
}

Matrix Matrix::operator*(Matrix mat) const {
	Matrix comb;
	
	for(int i=0;i<4;i++) {
		for(int j=0;j<4;j++) {
			Vec4d columnVec=Vec4d(mat[0][j],mat[1][j],mat[2][j], mat[3][j]);
//			if(logMat)
//				cout<<"("<<i<<","<<j<<") column: "<<columnVec<<" row: "<<v[i]<<"result: "<<columnVec.dot(v[i])<<endl;
			comb[i][j]=columnVec.dot(v[i]);
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
	v[3] *= scale;
	return *this;
}

const Matrix &Matrix::operator/=(double scale) {
	v[0] /= scale;
	v[1] /= scale;
	v[2] /= scale;
	v[3] /= scale;
	return *this;
}

const Matrix &Matrix::operator+=(const Matrix &other) {
	v[0] += other.v[0];
	v[1] += other.v[1];
	v[2] += other.v[2];
	v[3] += other.v[3];
	return *this;
}

const Matrix &Matrix::operator-=(const Matrix &other) {
	v[0] -= other.v[0];
	v[1] -= other.v[1];
	v[2] -= other.v[2];
	v[3] -= other.v[3];
	return *this;
}

ostream &operator<<(ostream &output, const Matrix &m) {
	cout << '[' << m[0] << "\n\t" << m[1] << "\n\t" << m[2] << "\n\t" << m[3] << ']';
	return output;
}