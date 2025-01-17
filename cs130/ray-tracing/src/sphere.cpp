#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
bool Sphere::Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    // center to endpoint
    vec3 L = center - ray.endpoint;
    double len_L = sqrt(dot(L,L));

    // center projected on to the ray
    vec3 center_proj_ray = dot(L, ray.direction)*ray.direction;
    double len_cpr = sqrt(dot(center_proj_ray, center_proj_ray));

    // distance from the center to the ray
    double d = sqrt(len_L*len_L - len_cpr*len_cpr);
    if(d > radius)
        return false;

    // the length between the two points that hit the circle
    double dt = sqrt(radius*radius - d*d);

    Hit hit1;
    hit1.object = this;
    hit1.t = len_cpr - dt;
    hit1.ray_exiting = false;

    Hit hit2;
    hit2.object = this;
    hit2.t = len_cpr + dt;
    hit2.ray_exiting = true;
    
    if(hit1.t < 0 && hit2.t < 0)
        return false;
    if(hit1.t > hit2.t){
        double dhold = hit1.t;
        hit1.t = hit2.t;
        hit2.t = dhold;
    }
    if(hit1.t < 0)
        hit1.t = 0;

    hits.push_back(hit1);
    hits.push_back(hit2);
    return true;
}

vec3 Sphere::Normal(const vec3& point) const
{
    vec3 normal = point-center;
    normal = normal.normalized();
    return normal;
}

bool Sphere::Contains(const vec3& point) const
{
    double distance_from_center = sqrt(dot(point-center,point-center));
    if(distance_from_center - .00001 < radius)
        return true;
    return false;
}
bool Sphere::Inside(const vec3& point) const
{
    double distance_from_center = sqrt(dot(point-center,point-center));
    if(distance_from_center + .00001 < radius)
        return true;
    return false;
}
