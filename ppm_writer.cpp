#include <iostream>
#include <fstream>
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "hitable_list.h"
#include "float.h"
#include "camera.h"
#include <random>

std::uniform_real_distribution<float> unirandomreal(0, 1);
std::random_device e;

vec3 random_in_unit_sphere() {
	vec3 p;
	do {
		p = 2.0 * vec3(unirandomreal(e), unirandomreal(e), unirandomreal(e))
			- vec3(1, 1, 1);
	} while (p.squared_length() >= 1.0);
	return p;
}

vec3 color(const ray& r, hitable *world) {
	hit_record rec;
	if (world->hit(r, 0.0, FLT_MAX, rec)) {
		vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		return 0.5*color(ray(rec.p, target - rec.p), world);
	}
	vec3 unit_direction = unit_vector(r.direction());
	float t = 0.5f * (unit_direction.y() + 1.0f);
	//std::cout << "iteration t: " << t <<"\n";
	return (1.0f - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}



int main(int argc, char** argv) {
	int nx = 200;
	int ny = 100;
	int ns = 100;
	std::ofstream f("test.ppm", std::ios_base::out
		| std::ios_base::binary
		| std::ios_base::trunc
	);

	f << "P3\n" << nx << " " << ny << "\n255\n";
	vec3 lower_left_corner(-2.0, -1.0, -1.0);
	vec3 horizontal(4.0, 0.0, 0.0);
	vec3 vertical(0.0, 2.0, 0.0);
	vec3 origin(0.0, 0.0, 0.0);
	hitable* list[2];
	list[0] = new sphere(vec3(0, 0, -1), 0.5);
	list[1] = new sphere(vec3(0, -100.5, -1), 100);
	hitable* world = new hitable_list(list, 2);
	camera cam;
	
	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			vec3 col(0, 0, 0);
			for (int s = 0; s < ns; s++) {
				float u = float(i + unirandomreal(e)) / float(nx);
				float v = float(j + unirandomreal(e)) / float(ny);
				ray r = cam.get_ray(u, v);
				col += color(r, world);
			}
			
			col /= float(ns);
			int ir = int(255.9 * col[0]);
			int ig = int(255.9 * col[1]);
			int ib = int(255.9 * col[2]);
			f << ir << " " << ig << " " << ib << "\n";
		}
	}
	return 0;
}