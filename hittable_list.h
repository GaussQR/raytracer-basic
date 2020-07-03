#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H
#include "hitable.h"
struct hittable_list: public hitable {
	hittable_list() {}
	hittable_list(hitable** l, int n) {list = l; list_size = n; }
	virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const{
		hit_record temp_rec;
		bool hit_anything = false;
		double closest_so_far = tmax;
		for (int i = 0; i < list_size; i++) {
			if (list[i]->hit(r, tmin, closest_so_far, temp_rec)) {
				hit_anything = true;
				closest_so_far = temp_rec.t;
				rec = temp_rec;
			}
		}
		return hit_anything;
	}
	hitable **list;
	int list_size;
	~hittable_list() {
		for (int i = 0; i < list_size; ++i)
			delete list[i];
	}
};
#endif