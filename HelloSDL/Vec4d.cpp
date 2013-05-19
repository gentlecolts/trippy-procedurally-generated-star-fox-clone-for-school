//
//  Vec4d.cpp
//  HelloSDL
//
//  Created by Jonah Chazan on 5/4/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#include "Vec4d.h"
#include "../vec3d.h"

using namespace std;

Vec4d::Vec4d() {

}

Vec4d::Vec4d(double x, double y, double z, double w) {
	v[0] = x;
	v[1] = y;
	v[2] = z;
	v[3] = w;
}

double &Vec4d::operator[](int index) {
	return v[index];
}

double Vec4d::operator[](int index) const {
	return v[index];
}

Vec4d Vec4d::operator*(double scale) const {
	return Vec4d(v[0] * scale, v[1] * scale, v[2] * scale, v[3] * scale);
}

Vec4d Vec4d::operator/(double scale) const {
	return Vec4d(v[0] / scale, v[1] / scale, v[2] / scale, v[3] / scale);
}

Vec4d Vec4d::operator+(const Vec4d &other) const {
	return Vec4d(v[0] + other.v[0], v[1] + other.v[1], v[2] + other.v[2], v[3]);
}

Vec4d Vec4d::operator-(const Vec4d &other) const {
	return Vec4d(v[0] - other.v[0], v[1] - other.v[1], v[2] - other.v[2], v[3]);
}

Vec4d Vec4d::operator-() const {
	return Vec4d(-v[0], -v[1], -v[2], v[3]);
}

const Vec4d &Vec4d::operator*=(double scale) {
	v[0] *= scale;
	v[1] *= scale;
	v[2] *= scale;
	return *this;
}

const Vec4d &Vec4d::operator/=(double scale) {
	v[0] /= scale;
	v[1] /= scale;
	v[2] /= scale;
	return *this;
}

const Vec4d &Vec4d::operator+=(const Vec4d &other) {
	v[0] += other.v[0];
	v[1] += other.v[1];
	v[2] += other.v[2];
	return *this;
}

const Vec4d &Vec4d::operator-=(const Vec4d &other) {
	v[0] -= other.v[0];
	v[1] -= other.v[1];
	v[2] -= other.v[2];
	return *this;
}

double Vec4d::dot(const Vec4d &other) const {
	return v[0] * other.v[0] + v[1] * other.v[1] + v[2] * other.v[2] + v[3] * other.v[3];
}

Vec4d operator*(double scale, const Vec4d &v) {
	return v * scale;
}

Vec4d::operator Vec3d() {
	if(v[3]==0)
		return Vec3d(0, 0, 0);
	return Vec3d(v[0]/v[3], v[1]/v[3], v[2]/v[3]);
}

ostream &operator<<(ostream &output, const Vec4d &v) {
	cout << '(' << v[0] << ", " << v[1] << ", " << v[2] << ", " << v[3] << ')';
	return output;
}
