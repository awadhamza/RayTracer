#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"
#include <algorithm>
#include <iostream>
#include <math.h>

using namespace std;


double max(double a, double b){
    if(a>b) return a;
    if(a<b) return b;
    return a;
}

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color;
    //determine the color

    //Add ambient component
    vec3 Iambient = world.ambient_intensity * world.ambient_color * this->color_ambient;

    for(unsigned i = 0; i < world.lights.size(); i++){
        vec3 ray_dir = (world.lights.at(i)->position - intersection_point);

        Ray shadow_ray(intersection_point, ray_dir);   // shadow_ray points from intersection point towards light

        double maxDistance = (world.lights.at(i)->position - intersection_point).magnitude();    // max Ray's intersection distance, t

        
        Hit tempHit = world.Closest_Intersection(shadow_ray); // Finding closest intersection of shadow_ray


        if(tempHit.object == NULL || tempHit.dist < small_t  || tempHit.dist > maxDistance){    // If shadow_ray doesn't intersect any object between initial point and light
    										            //Compute diffuse and specular
            
			double Idiffprod = dot(normal, shadow_ray.direction);
	    
            vec3 Idiffuse = this->color_diffuse * world.lights.at(i)->Emitted_Light(ray_dir) * max(Idiffprod, 0);
            if(debug_pixel){
				cout << Idiffuse << endl;
			}

            vec3 v = ray.direction;
            vec3 r = v - (2 * dot(v, normal) * normal);

            vec3 Ispecular = this->color_specular * world.lights.at(i)->Emitted_Light(ray_dir) * pow(max(dot(-v, r), 0), specular_power); 

            color += Idiffuse; 
			color += Ispecular;
            
        }

        

    }
    
    color += Iambient;

    return color;
}
