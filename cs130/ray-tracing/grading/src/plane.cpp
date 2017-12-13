#include "plane.h"
#include "ray.h"
#include <cfloat>


// Intersect with the half space defined by the plane.  The plane's normal
// points outside.  If the ray starts on the "inside" side of the plane, be sure
// to record a hit with t=0 as the first entry in hits.
bool Plane::
Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
	if(dot(ray.endpoint-x1, normal) < 0){
		Hit hit;
	    hit.object = this;
	    hit.t = 0;
	    hit.ray_exiting = false;
	    hits.push_back(hit);
	}

    Hit hit;
    hit.object = this;
    hit.t = dot(x1-ray.endpoint, normal) / dot(ray.direction,normal);
    hit.ray_exiting = true;

    hits.push_back(hit);

    return true;
}

vec3 Plane::
Normal(const vec3& point) const
{
    return normal;
}

bool Plane::Contains(const vec3& point) const
{
	if(dot(normal, point-x1)-.0001 > 0)
		return false;
	return true;
}
bool Plane::Inside(const vec3& point) const
{
	if(dot(normal, point-x1)+.0001 > 0)
		return false;
	return true;
}
