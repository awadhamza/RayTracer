#include "plane.h"
#include "ray.h"
#include <cfloat>
#include <limits>

// Intersect with the half space defined by the plane.  The plane's normal
// points outside.  If the ray starts on the "inside" side of the plane, be sure
// to record a hit with t=0 as the first entry in hits.
Hit Plane::Intersection(const Ray& ray, int part) const
{
    
    double numerator = 0;
    double denominator = dot(ray.direction, this->normal);
    
    /*
    // Check if ray direction vector is parallel to plane
    if((denominator) == 0){
		return {0, -1, 0};
	}
	
	// If ray eventually intersects plane, calculate ray scalar for intersection
	else {
		// endpoint dot normal
		numerator = dot(ray.endpoint, this->normal);
		
		// Q - (double)
		vec3 numeratorSub = this->x1;
		for(unsigned i = 0; i < 3; i++){
			numeratorSub[i] = numeratorSub[i] - numerator;
		}
		
	}
    
    // Divide numerator by denominator
    for(unsigned i = 0; i < 3; i++){
		numeratorSub[i] = numeratorSub[i] / denominator;
	}
    
    double tScalar = numeratorSub;
    */
    
    // Check if ray direction vector is parallel to plane
    if((denominator) == 0){
		return {NULL, -1, 0};
	}
	
	// If ray eventually intersects plane, calculate ray scalar for intersection
	else {
		numerator = dot((this->x1 - ray.endpoint), this->normal);
	}
        
    double tScalar = numerator / denominator;
    
    //If tScalar is less than small_t, return failure
    if(tScalar < small_t){
		return {NULL, -1, 0};
	}
    
    // Return plane hit, distance to hit, and part hit
    return {this , tScalar, 0};
}

vec3 Plane::Normal(const vec3& point, int part) const
{
    return normal;
}

// There is not a good answer for the bounding box of an infinite object.
// The safe thing to do is to return a box that contains everything.
Box Plane::Bounding_Box(int part) const
{
    Box b;
    b.hi.fill(std::numeric_limits<double>::max());
    b.lo=-b.hi;
    return b;
}
