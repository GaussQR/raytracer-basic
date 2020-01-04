#ifndef RAY_H
#define RAY_H
#include "vec3.h"
struct ray
{
	vec3 A, B;
	ray(){}
	ray(vec3 a, vec3 b){
		A = a, B = b;
	}
	vec3 origin() const{
		return A;
	}
	vec3 dir() const{
		return B;
	}
	vec3 point_at_parameter(float t) const{
		return A + B*t;
	}
};
#endif