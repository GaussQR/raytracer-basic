#include <iostream>
#include <fstream>
#include <cmath>
#include "hitable.h"
#include "sphere.h"
#include "ray.h"
#include "hittable_list.h"
#include "camera.h"
#include "random.h"
#include "material.h"
const int MAX_D = 50;
const vec3 color(const ray& r, hitable *world, int depth = 0) {
	hit_record rec;
	if(world->hit(r, 0.01, MAXFLOAT, rec)){
		ray scat;
		vec3 att;
		if(depth < MAX_D and rec.mat_ptr->scatter(r, rec, att, scat)){
			return att*color(scat, world, depth+1);
		}
		return vec3(0, 0, 0);
	}
	vec3 unit_direction = unit_vec(r.dir());
	float t = 0.5*(unit_direction[2] + 1.0);
	return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
}
int main() {
	std::ofstream cout("img.ppm");
	int nx = 400, ny = 200, ns = 10;
	cout << "P3\n" << nx << " " << ny << "\n255\n";
	camera cm;
	hitable *list[4];
	list[0] = new sphere(vec3(0,0,-1), 0.5, new lambertian(vec3(0.8, 0.3, 0.3)));
	list[1] = new sphere(vec3(0,-100.5,-1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
	list[2] = new sphere(vec3(1,0,-1), 0.5, new metal(vec3(0.8, 0.6, 0.2)));
	list[3] = new sphere(vec3(-1,0,-1), 0.5, new metal(vec3(0.8, 0.8, 0.8)));
	hitable *world = new hittable_list(list,4);
	for (int j = ny-1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			vec3 col(0, 0, 0);
			for(int s = 0; s<ns; ++s){
				float u = float(i+random_double()) / float(nx);
				float v = float(j+random_double()) / float(ny);
				ray r = cm.get_ray(u, v);
				col += color(r, world);
			}
			col /= float(ns);
			col = vec3(sqrt(col[0]),sqrt(col[1]),sqrt(col[2])); //gamma correction.
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);
			cout << ir << " " << ig << " " << ib << "\n";
		}
	}
	for(int i = 0; i<4; ++i) delete list[i];
	delete world;
	// delete[] list;
}