#include <iostream>
#include <cmath>
struct vec3
{
	float e[3];
	vec3(){}
	vec3(float e0, float e1, float e2){
		e[0] = e0, e[1] = e1, e[2] = e2;
	}
	vec3 operator - (){
		return vec3(-e[0], -e[1], -e[2]);
	}
	float operator[](int i) const {
		return e[i];
	}
	float& operator[](int i) {
		return e[i];
	}
	float sq_length() const {
		return e[0]*e[0]+e[1]*e[1]+e[2]*e[2];
	}
	float length() const {
		return sqrt(sq_length());
	}
	vec3& operator += (const vec3 &oth){
		e[0] += oth[0], e[1] += oth[1], e[2] += oth[2];
		return *this;
	}
	vec3& operator -= (const vec3 &oth){
		e[0] -= oth[0], e[1] -= oth[1], e[2] -= oth[2];
		return *this;
	}
	vec3& operator *= (const vec3 &oth){
		e[0] *= oth[0], e[1] *= oth[1], e[2] *= oth[2];
		return *this;
	}
	vec3& operator /= (const vec3 &oth){
		e[0] /= oth[0], e[1] /= oth[1], e[2] /= oth[2];
		return *this;
	}
	vec3& operator *= (float k){
		e[0] *= k, e[1] *= k, e[2] *= k;
		return *this;
	}
	vec3& operator /= (float k){
		e[0] /= k, e[1] /= k, e[2] /= k;
		return *this;
	}
	void make_univec(){
		(*this) /= length();
	}
};

inline std::istream& operator >>(std::istream &is, vec3 &v){
	is >> v[0] >> v[1] >> v[2];
	return is;
}
inline std::ostream& operator <<(std::ostream &is, const vec3 &v){
	is << v[0] << v[1] << v[2];
	return is;
}
inline vec3 operator + (const vec3 &v1, const vec3 &v2){
	return vec3(v1[0]+v2[0], v1[1]+v2[1], v1[2]+v2[2]);
}
inline vec3 operator - (const vec3 &v1, const vec3 &v2){
	return vec3(v1[0]-v2[0], v1[1]-v2[1], v1[2]-v2[2]);
}
inline vec3 operator * (const vec3 &v1, const vec3 &v2){
	return vec3(v1[0]*v2[0], v1[1]*v2[1], v1[2]*v2[2]);
}
inline vec3 operator / (const vec3 &v1, const vec3 &v2){
	return vec3(v1[0]/v2[0], v1[1]/v2[1], v1[2]/v2[2]);
}
inline vec3 operator * (const vec3 &v1, float k){
	return vec3(v1[0]*k, v1[1]*k, v1[2]*k);
}
inline vec3 operator * (float k, const vec3 &v1){
	return vec3(v1[0]*k, v1[1]*k, v1[2]*k);
}
inline vec3 operator / (const vec3 &v1, float k){
	return vec3(v1[0]/k, v1[1]/k, v1[2]/k);
}
inline vec3 unit_vec(const vec3 &v){
	return v/v.length();
}
inline float dot(const vec3 &v1, const vec3 &v2) {
	return v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2];
}
inline vec3 cross(const vec3 &v1, const vec3 &v2) {
	return vec3(v1[1]*v2[2] - v1[2]*v2[1], v1[2]*v2[0]-v1[0]*v2[2], v1[0]*v2[1]-v1[1]*v2[0]);
}
vec3 random_unit_sphere(){
	vec3 p(1,1,1);
	while(p.sq_length() >= 1.0) p = 2.0*vec3(drand48(), drand48(), drand48()) - vec3(1,1,1);
	return p;
}
vec3 random_unit_disk() {
	vec3 p(1,0,0);
	while (dot(p, p) >= 1.0) {
		p = 2.0 * vec3(drand48(), drand48(), 0.0) - vec3(1, 1, 0);
	}
	return p;
}