#ifndef CAMERAH
#define CAMERAH

#include "ray.h"

struct camera {
	camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect) {
		float half_height = tan(vfov / 2);
		float half_width = aspect * half_height;
		origin = lookfrom;
        w = unit_vec(lookfrom - lookat);
        u = cross(vup, w);
        v = cross(w, u);
        lower_left_corner = origin - half_height * v - half_width * u - w;
        horizontal = 2 * half_width * u;
        vertical = 2 * half_height * v;
	}
	camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect, float aperture, float focus_dist) {
		lens_radius = aperture / 2;
        float half_height = tan(vfov / 2);
		float half_width = aspect * half_height;
		origin = lookfrom;
        w = unit_vec(lookfrom - lookat);
        u = cross(vup, w);
        v = cross(w, u);
        lower_left_corner = origin - half_height * focus_dist * v - half_width * focus_dist * u - focus_dist * w;
        horizontal = 2 * half_width * focus_dist * u;
        vertical = 2 * half_height * focus_dist * v;
	}
	ray get_ray(float s, float t) {
        vec3 rd = lens_radius * random_unit_disk();
		vec3 offset = u * rd[0] + v * rd[1];
		return ray(origin + offset, lower_left_corner + s*horizontal + t*vertical - origin - offset);
	}
	vec3 u, v, w;
	vec3 origin;
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
	float lens_radius;
};
#endif