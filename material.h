#ifndef MATERIALH
#define MATERIALH
#include "hitable.h"

struct lambertian: public material{
	vec3 albedo;
	lambertian(const vec3 &v){ albedo = v; }
	virtual bool scatter(const ray &r, const hit_record &rec, vec3 &attenuation, ray &scattered) const {
		vec3 tg = rec.p + rec.normal + random_unit_sphere();
		scattered = ray(rec.p, tg - rec.p);
		attenuation = albedo;
		return true;
	}
};

struct metal: public material{
	vec3 albedo;
	metal(const vec3 &v){ albedo = v; }
	virtual bool scatter(const ray &r, const hit_record &rec, vec3 &attenuation, ray &scattered) const {
		vec3 reflected = reflect(unit_vec(r.dir()), rec.normal);
		scattered = ray(rec.p, reflected);
		attenuation = albedo;
		return dot(scattered.dir(), rec.normal) > 0;
	}
};

#endif