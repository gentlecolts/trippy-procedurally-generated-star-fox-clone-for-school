//
//  Vec4d.h
//  HelloSDL
//
//  Created by Jonah Chazan on 5/4/13.
//  Copyright (c) 2013 Student. All rights reserved.
//

#ifndef __HelloSDL__Vec4d__
#define __HelloSDL__Vec4d__

#include <iostream>

class Vec3d;

class Vec4d {
private:
	double v[4];
public:
	Vec4d();
	Vec4d(double x, double y, double z, double w);
	
	double &operator[](int index);
	double operator[](int index) const;
	
	Vec4d operator*(double scale) const;
	Vec4d operator/(double scale) const;
	Vec4d operator+(const Vec4d &other) const;
	Vec4d operator-(const Vec4d &other) const;
	Vec4d operator-() const;
	operator Vec3d();
	
	const Vec4d &operator*=(double scale);
	const Vec4d &operator/=(double scale);
	const Vec4d &operator+=(const Vec4d &other);
	const Vec4d &operator-=(const Vec4d &other);
	
	double dot(const Vec4d &other) const;
};

Vec4d operator*(double scale, const Vec4d &v);
std::ostream &operator<<(std::ostream &output, const Vec4d &v);



#endif /* defined(__HelloSDL__Vec4d__) */
