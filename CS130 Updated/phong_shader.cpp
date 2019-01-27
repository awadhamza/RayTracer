#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color;
    TODO; //determine the color

    //Add ambient component
    vec3 Iambient = world.ambient_intensity * world.ambient_color * this.color_ambient;

    for(unsigned i = 0; i < lights.size(); i++){
        
        Ray shadow_ray(intersection_point, (lights.at(i)->position - intersection_point));   // shadow_ray points from intersection point towards light

        double maxDistance = (lights.at(i)->position - intersection_point)/(shadow_ray.direction)    // max Ray's intersection distance, t

        
        Hit tempHit = Closest_Intersection(shadow_ray); // Finding closest intersectionf or shadow_ray


        if(tempHit.object != NULL && (tempHit.dist != 0 || tempHit.dist > maxDistance){    // If shadow_ray doesn't intersect any object between initial point and light
            //Compute diffuse and specular
            vec3 Idiffuse = Emitted_Light(shadow_ray) * max(dot(normal, shadow_ray.normalized()), 0);
            

            vec3 v = -ray.direction;
            vec3 r = v - 2 * dot(v, normal) * normal;

            vec3 Ispecular = Emitted_Light(shadow_ray) * max(dot(v, r), 0); 

            color += Idiffuse + Ispecular;
            
        }

        

    }
    
    color += Iambient;

    return color;
}
