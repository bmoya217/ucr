#include "boolean.h"
#include "sphere.h"
#include "plane.h"
#include "ray.h"
#include <limits>

// Determine if the ray intersects with the boolean of A and B.
bool Boolean::Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    unsigned int initial_hits = hits.size();
    std::vector<Hit> a_hits, b_hits;
    A->Intersection(ray, a_hits);
    B->Intersection(ray, b_hits);

    if(type == type_union){
        for(unsigned int h = 0; h < a_hits.size(); h++)
            if(!B->Inside(ray.Point(a_hits[h].t)))
                hits.push_back(a_hits[h]);
        for(unsigned int h = 0; h < b_hits.size(); h++)
            if(!A->Inside(ray.Point(b_hits[h].t)))
                hits.push_back(b_hits[h]);
    }

    else if(type == type_intersection){
        for(unsigned int h = 0; h < a_hits.size(); h++)
            if(B->Contains(ray.Point(a_hits[h].t)))
                hits.push_back(a_hits[h]);
        for(unsigned int h = 0; h < b_hits.size(); h++)
            if(A->Contains(ray.Point(b_hits[h].t)))
                hits.push_back(b_hits[h]);
    }

    else if(type == type_difference){
        for(unsigned int h = 0; h < a_hits.size(); h++)
            if(!B->Inside(ray.Point(a_hits[h].t)))
                hits.push_back(a_hits[h]);
        for(unsigned int h = 0; h < b_hits.size(); h++)
            if(A->Contains(ray.Point(b_hits[h].t)) && !B->Inside(ray.Point(b_hits[h].t)))
                hits.push_back(b_hits[h]);   
    }

    if(initial_hits == hits.size())
        return false;
    return true;
}

// This should never be called.
vec3 Boolean::Normal(const vec3& point) const
{
    assert(false);
    return vec3();
}

bool Boolean::Contains(const vec3& point) const{
    if(type == type_union)
        return (A->Contains(point) || B->Contains(point));
    if(type == type_intersection)
        return (A->Contains(point) && B->Contains(point));
    if(type == type_difference)
        return (A->Contains(point) && !B->Inside(point));
    return false;
}

bool Boolean::Inside(const vec3& point) const{
    if(type == type_union)
        return (A->Inside(point) || B->Inside(point));
    if(type == type_intersection)
        return (A->Inside(point) && B->Inside(point));
    if(type == type_difference)
        return (A->Inside(point) && !B->Contains(point));
    return false;
}
