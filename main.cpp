#include <iostream>
#include <fstream>
#include <cmath>
#include "hitable.h"
#include "sphere.h"
#include "ray.h"
#include "hittable_list.h"
#include "camera.h"
#include "material.h"
const int MAX_D = 50;
const vec3 color(const ray& r, hitable *world, int depth = 0) {
    hit_record rec;
    if(world->hit(r, 0.001, MAXFLOAT, rec)){
        ray scat;
        vec3 att;
        if(depth < MAX_D and rec.mat_ptr->scatter(r, rec, att, scat)){
            return att*color(scat, world, depth+1);
        }
        else return vec3(0,0,0);
    }
    vec3 unit_direction = unit_vec(r.dir());
    float t = 0.5*(unit_direction[1] + 1.0);
    return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
}

hitable *random_scene() {
    int n = 500;
    hitable **list = new hitable*[n+1];
    list[0] = new sphere(vec3(0, -1000, 0), 1000, new lambertian(vec3(0.5, 0.5, 0.5)));
    int i = 1;
    for(int a = -11; a < 11; ++a) {
        for(int b = -11; b < 11; ++b){
            float choose_mat = drand48();
            vec3 center(a + 0.9 * drand48(), 0.2, b + 0.9 * drand48());
            if ((center - vec3(4, 0.2, 0)).length() > 0.9) {
                if (choose_mat < 0.8) {
                    list[i++] = new sphere(center, 0.2, 
                    new lambertian(vec3(drand48()*drand48(), drand48()*drand48(), drand48()*drand48())));
                }
                else if (choose_mat < 0.95) {
                    list[i++] = new sphere(center, 0.2, 
                    new metal(vec3(0.5 * (1 + drand48()), 0.5 * (1 + drand48()), 0.5 * (1 + drand48())), 0.5 * drand48()));
                }
                else {
                    list[i++] = new sphere(center, 0.2, new dielectric(1.5));
                }
            }
        }
    }
    list[i++] = new sphere(vec3(0, 1, 0), 1.0, new dielectric(1.5));
    list[i++] = new sphere(vec3(-4, 1, 0), 1.0, new metal(vec3(0.7, 0.6, 0.5), 0.0));
    list[i++] = new sphere(vec3(4, 1, 0), 1.0, new lambertian(vec3(0.4, 0.2, 0.1)));
    return new hittable_list(list, i);
}

int main() {
    std::ofstream cout("img.ppm");
    int nx = 1920, ny = 1080, ns = 20;
    // int nx = 400, ny = 300, ns = 20;
    cout << "P3\n" << nx << " " << ny << "\n255\n";
    vec3 lookfrom(3, 3, 2);
    vec3 lookat(0, 0, -1);
    float dist_focus = (lookfrom - lookat).length();
    float aperture = 1.0;
    // camera cm(lookfrom, lookat, vec3(0, 1, 0), M_PI / 2, float(nx) / ny);
    camera cm(lookfrom, lookat, vec3(0, 1, 0), M_PI / 9, float(nx) / ny, aperture, dist_focus);
    // const int num_obj = 5;
    // hitable *list[num_obj];
    // list[0] = new sphere(vec3(0,0,-1), 0.5, new lambertian(vec3(0.8, 0.3, 0.3)));
    // list[1] = new sphere(vec3(0,-100.5,-1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
    // list[2] = new sphere(vec3(1,0,-1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0.4));
    // list[3] = new sphere(vec3(-1,0,-1), 0.5,new dielectric(1.5)); 
    // list[4] = new sphere(vec3(-1,0,-1), -0.49,new dielectric(1.5)); 
    // hitable *world = new hittable_list(list, num_obj);
    hitable *world = random_scene();

    for (int j = ny-1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            vec3 col(0, 0, 0);
            for(int s = 0; s<ns; ++s) {
                float u = float(i+drand48()) / float(nx);
                float v = float(j+drand48()) / float(ny);
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
    delete world;
}