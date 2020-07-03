#ifndef MATERIALH
#define MATERIALH
#include "hitable.h"

vec3 reflect(const vec3 &v, const vec3 &n){
	return v - 2*dot(v, n)*n;
}

float schlick(float cosine, float ref_idx) {
	float r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow(1 - cosine, 5);
}

bool refract(const vec3 &v, const vec3 &n, float ni_over_nt, vec3 &refracted) {
	vec3 uv = unit_vec(v);
	float dt = dot(uv, n);
	float discriminant = 1.0 - ni_over_nt*ni_over_nt*(1 - dt*dt);
	if (discriminant > 0) {
		refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
		return true;
	}
	return false;
}

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
	float fuzz;
	metal(const vec3 &v, float f){ 
		albedo = v; 
		fuzz = (f > 1)?1:f;
	}
	virtual bool scatter(const ray &r, const hit_record &rec, vec3 &attenuation, ray &scattered) const {
		vec3 reflected = reflect(unit_vec(r.dir()), rec.normal);
		scattered = ray(rec.p, reflected);
		attenuation = albedo;
		return dot(scattered.dir(), rec.normal) > 0;
	}
};

struct dielectric: public material {
	float ref_idx;
	dielectric(float ri) : ref_idx(ri) {}
	virtual bool scatter(const ray &r, const hit_record &rec, vec3 &attenuation, ray &scattered) const {
		vec3 outward_normal;
		vec3 reflected = reflect(r.dir(), rec.normal);
		float ni_over_nt;
		vec3 refracted;
		attenuation = vec3(1, 1, 1);
		float reflec_prob;
		float cosine;
		if (dot(r.dir(), rec.normal) > 0) {
			outward_normal = -1 * rec.normal;
			ni_over_nt = ref_idx;
			cosine = ref_idx * dot(r.dir(), rec.normal) / r.dir().length(); 
		}
		else {
			outward_normal = rec.normal;
			ni_over_nt = 1 / ref_idx;
			cosine = -1 * dot(r.dir(), rec.normal) / r.dir().length(); 
		}
		if (refract(r.dir(), outward_normal, ni_over_nt, refracted)) {
			reflec_prob = schlick(cosine, ref_idx);
		}
		else{
			scattered = ray(rec.p, reflected);
			reflec_prob = 1;
		}
		if (drand48() >= reflec_prob) {
			scattered = ray(rec.p, refracted);
		}
		else scattered = ray(rec.p, reflected);
		return true;
	}
};
#endif