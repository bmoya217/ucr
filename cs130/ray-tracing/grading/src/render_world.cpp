#include "render_world.h"
#include "flat_shader.h"
#include "object.h"
#include "light.h"
#include "ray.h"
#include <limits>

using namespace std;

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

// Find the closest object of intersection and return the object that was
// intersected.  Record the Hit structure in hit.  If no intersection occurred,
// return NULL.  Note that in the case of a Boolean, the object returned will be
// the Boolean, but the object stored in hit will be the underlying primitive.
// Any intersection with t<=small_t should be ignored.
Object* Render_World::Closest_Intersection(const Ray& ray, Hit& hit)
{   
    Object* closest = NULL;
    double min_t = numeric_limits<double>::max();

    for(unsigned int o = 0; o < objects.size(); o++){
        vector<Hit> hits;

        if(objects[o]->Intersection(ray, hits)){
            for(unsigned int h = 0; h < hits.size(); h++){
                if(hits[h].t <= min_t && hits[h].t > small_t){
                    min_t = hits[h].t;
                    closest = objects[o];
                    hit = hits[h];
                }
            }
        }
    }

    return closest;
}

// set up the initial view ray and call
void Render_World::Render_Pixel(const ivec2& pixel_index)
{   
    Ray ray;
    ray.endpoint = camera.position;
    ray.direction = camera.World_Position(pixel_index) - ray.endpoint;
    ray.direction = ray.direction.normalized();
    vec3 color=Cast_Ray(ray,1);
    camera.Set_Pixel(pixel_index,Pixel_Color(color));
}

void Render_World::Render()
{
    for(int j=0;j<camera.number_pixels[1];j++)
        for(int i=0;i<camera.number_pixels[0];i++)
            Render_Pixel(ivec2(i,j));
}

// cast ray and return the color of the closest intersected surface point,
// or the background color if there is no object intersection
vec3 Render_World::Cast_Ray(const Ray& ray,int recursion_depth)
{
    Hit hit;
    vec3 color;
    double flip = 1.0;

    Object* closest = Closest_Intersection(ray, hit);

    if(hit.flip){
        flip = -1.0;
    }
    if(closest != NULL && recursion_depth <= recursion_depth_limit)
        color = closest->material_shader->Shade_Surface(ray, ray.Point(hit.t), hit.object->Normal(ray.Point(hit.t))*flip, 1);
    else
        color = background_shader->Shade_Surface(ray, color, color, 1);

    return color;
}
 