#ifndef HITTABLEH
#define HITTABLEH
#include "ray.h"

struct material;

struct hit_record {
	float t;
	vec3 p, normal;
	material* mat_ptr;
};

struct material{
	virtual bool scatter(const ray &r, const hit_record &rec, vec3 &attenuation, ray &scattered) const = 0;
};

struct hitable {
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif