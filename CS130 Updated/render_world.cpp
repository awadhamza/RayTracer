#include "render_world.h"
#include "flat_shader.h"
#include "object.h"
#include "light.h"
#include "ray.h"

#include <limits>
#include <iostream>

using namespace std;


extern bool disable_hierarchy;

Render_World::Render_World()
    :background_shader(0),ambient_intensity(0),enable_shadows(true),
    recursion_depth_limit(3)
{}

Render_World::~Render_World()
{
    delete background_shader;
    for(size_t i=0;i<objects.size();i++) delete objects[i];
    for(size_t i=0;i<lights.size();i++) delete lights[i];
}

// Find and return the Hit structure for the closest intersection.  Be careful
// to ensure that hit.dist>=small_t.
Hit Render_World::Closest_Intersection(const Ray& ray)
{
    //Set min_t to a large int value
    int min_t = std::numeric_limits<int>::max();
    
    //Initialize empty Hit object
    Hit closest = {NULL, 0, 0};
    

    //For every object in the world
    for(unsigned i = 0; i < objects.size(); i++){
        //Set a temporary hit struct to the result of a intersection function
        Hit temp = objects[i]->Intersection(ray, -1);
        
        //If that temporary hit on object[i] is the closest intersection thus far
        // and its intersection distance is greater than small_t, then rewrite
        // the closest Hit struct to point to object[i] and replace min_t
        if(temp.dist < min_t && temp.dist > small_t){
            closest = temp;
            closest.object = temp.object;
            min_t = closest.dist;
        }
    }
    
    //Return the closest intersection as Hit
    return closest;
}

// set up the initial view ray and call
void Render_World::Render_Pixel(const ivec2& pixel_index)
{
    // set up the initial view ray here
    
    //According to ray formula, we need to fetch an endpoint and a direction point
    // to form a ray going from the endpoint towards the direction point
    vec3 EP = camera.position;
    vec3 dir_point = camera.World_Position(pixel_index);
    
    /*if(pixel_index[0] == 450 && pixel_index[1] == 160){
		cout << "Endpoint: " << EP << endl;
		cout << "Direction: " << (dir_point - EP).normalized() << endl;
    }*/

    //Now, we calculate the direction vector and normalize it
    vec3 dir_norm = (dir_point - EP).normalized();
    
    //Ray created using endpoint and direction vector
    Ray ray(EP, dir_norm);
    
    
    vec3 color=Cast_Ray(ray,1);
    camera.Set_Pixel(pixel_index,Pixel_Color(color));
}

void Render_World::Render()
{
    if(!disable_hierarchy)
        Initialize_Hierarchy();

    for(int j=0;j<camera.number_pixels[1];j++)
        for(int i=0;i<camera.number_pixels[0];i++)
            Render_Pixel(ivec2(i,j));
}

// cast ray and return the color of the closest intersected surface point,
// or the background color if there is no object intersection
vec3 Render_World::Cast_Ray(const Ray& ray,int recursion_depth)
{
    vec3 color;
    // determine the color here
    
    //Get closest intersection
    Hit temp = Closest_Intersection(ray);

    //If an intersection exists
    if (temp.object != NULL){
        //R(t) = E + ut
        vec3 IP = ray.endpoint + (ray.direction * temp.dist);

        //Get normal at intersection point
        vec3 norm = temp.object->Normal(IP, temp.part);

        //Determine color using Shade_Surface function
        color = temp.object->material_shader->Shade_Surface(ray, IP, norm, recursion_depth);   
    }
    //Applying background color because of no object intersection
    else {
        color = this->background_shader->Shade_Surface(ray, vec3(0,0,0), vec3(0,0,0), recursion_depth);
    }
    
    return color;
}

void Render_World::Initialize_Hierarchy()
{
    TODO; // Fill in hierarchy.entries; there should be one entry for
    // each part of each object.

    hierarchy.Reorder_Entries();
    hierarchy.Build_Tree();
}
