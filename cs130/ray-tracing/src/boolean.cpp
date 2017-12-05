#include "boolean.h"


// Determine if the ray intersects with the boolean of A and B.
bool Boolean::Intersection(const Ray& ray, std::vector<Hit>& hits) const
{	
	//typeid()
    if(type == type_intersection)
    	if(A->Intersection(ray, hits) && B->Intersection(ray, hits))
    		return true;

    if(type == type_union)
    	if(A->Intersection(ray, hits) || B->Intersection(ray, hits))
    		return true;

    if(type == type_difference)
    	if(A->Intersection(ray, hits) && !B->Intersection(ray, hits))
    		return true;

    return false;
}

// This should never be called.
vec3 Boolean::Normal(const vec3& point) const
{
    assert(false);
    return vec3();
}
