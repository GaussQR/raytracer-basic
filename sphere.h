#ifndef SPHEREH
#define SPHEREH
#include "hitable.h"

struct sphere: public hitable  {
	sphere() {}
	sphere(vec3 cen, float r, material* mat) : center(cen), radius(r), mat_ptr(mat)  {};
	vec3 center;
	float radius;
	material *mat_ptr;
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
		vec3 oc = r.origin() - center;
		float a = dot(r.dir(), r.dir());
		float b = dot(oc, r.dir());
		float c = dot(oc, oc) - radius*radius;
		float discriminant = b*b - a*c;
		if (discriminant > 0) {
			float temp = (-b - sqrt(discriminant))/a;
			if (temp < t_max && temp > t_min) {
				rec.t = temp;
				rec.p = r.point_at_parameter(rec.t);
				rec.normal = (rec.p - center) / radius;
				rec.mat_ptr = mat_ptr;
				return true;
			}
			temp = (-b + sqrt(discriminant)) / a;
			if (temp < t_max && temp > t_min) {
				rec.t = temp;
				rec.p = r.point_at_parameter(rec.t);
				rec.normal = (rec.p - center) / radius;
				rec.mat_ptr = mat_ptr;
				return true;
			}
		}
		return false;
	}
	~sphere() {
		delete mat_ptr;
	}
};
#endif