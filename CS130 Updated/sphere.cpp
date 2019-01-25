#include "sphere.h"
#include "ray.h"
#include <math.h>
#include <iostream>

using namespace std;

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
    
    
    double a = dot(ray.direction, ray.direction);
    double b = 2 * dot((ray.endpoint - this->center), ray.direction);
    double c = dot((ray.endpoint - this->center), (ray.endpoint - this->center)) - (this->radius * this->radius);
    
    double squareRT = (b * b) - 4*a*c;
    
    if(squareRT < 0){
		return {NULL, 0, 0};
	}
    
    squareRT = sqrt(squareRT);
    
    
    
    double plusNB = -b + squareRT;
    double minusNB = -b - squareRT;
    
    double t2 = plusNB /(2 * a);
    double t1 = minusNB /(2 * a);
    
    	if(squareRT == 0){ //one intersection
		double t3 = -b /(2 * a);
	
		if(t3 > 0){
			return {this, t3, part};
		} else {
			return {NULL, 0, 0};
		}
	
	}
	
	else if(squareRT > 0){ //more than one intersection
    
		if(t1 > small_t){
			return {this, t1, part};
		} else if (t2 > small_t){
			return {this, t1, part};
		} else {
			return {NULL, 0, 0};
		}
	
	}
   return {NULL, 0, 0}; 
}

vec3 Sphere::Normal(const vec3& point, int part) const
{
    vec3 normal;
    TODO; // compute the normal direction
    return normal;
}

Box Sphere::Bounding_Box(int part) const
{
    Box box;
    TODO; // calculate bounding box
    return box;
}
