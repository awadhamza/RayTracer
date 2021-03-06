#include "reflective_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 Reflective_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color;
	if(recursion_depth <= world.recursion_depth_limit){
            color = shader->Shade_Surface(ray, intersection_point, normal, recursion_depth);
	    vec3 reflected_dir = (ray.direction * -1) * (2 * (dot(ray.direction, normal)) * normal);
	    Ray  reflected_ray(intersection_point, reflected_dir);
	    return color = (1 - reflectivity) * color + reflectivity * world.Cast_Ray(reflected_ray, recursion_depth+1);
	}
	//TODO; // determine the color
    return color;
}
