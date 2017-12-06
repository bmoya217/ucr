#include "boolean.h"

// Determine if the ray intersects with the boolean of A and B.
bool Boolean::Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    int a = 0, b = 0;
    std::vector<Hit> a_hits, b_hits;
    A->Intersection(ray, a_hits);
    B->Intersection(ray, b_hits);

    if(a_hits.size() > 0)
        if(a_hits[a].t <= 0.0001)
            a++;
    if(b_hits.size() > 0)
        if(b_hits[b].t <= 0.0001)
            b++;

    if(type == type_union){
        if(a_hits.size() == 0 && b_hits.size() == 0)
            return false;
        else if(a_hits.size() == 0)
            return B->Intersection(ray, hits);
        else if(b_hits.size() == 0)
            return A->Intersection(ray, hits);
        
        if(!a_hits[a].ray_exiting && !b_hits[b].ray_exiting){
            hits.push_back(a_hits[a]);
            hits.push_back(b_hits[b]);
        }
        else if(a_hits[a].ray_exiting && !b_hits[b].ray_exiting){
            b++;
            hits.push_back(a_hits[a]);
            hits.push_back(b_hits[b]);

        }
        else if(!a_hits[a].ray_exiting && b_hits[b].ray_exiting){
            a++;
            hits.push_back(a_hits[a]);
            hits.push_back(b_hits[b]);
        }
        else if(a_hits[a].ray_exiting && b_hits[b].ray_exiting){
            // return furthest
            if(a_hits[a].t > b_hits[b].t)
                hits.push_back(a_hits[a]);
            else
                hits.push_back(b_hits[b]);
        }
        return true;
    }

    if(type == type_intersection){
        if(a_hits.size() == 0 || b_hits.size() == 0)
            return false;

        if(!a_hits[a].ray_exiting && !b_hits[b].ray_exiting){
            // return furthest
            if(a_hits[a].t > b_hits[b].t)
                hits.push_back(a_hits[a]);
            else
                hits.push_back(b_hits[b]);
        }
        else if(a_hits[a].ray_exiting && !b_hits[b].ray_exiting){
            a++;
            // return closest 
            hits.push_back(a_hits[a]);
            hits.push_back(b_hits[b]);

        }
        else if(!a_hits[a].ray_exiting && b_hits[b].ray_exiting){
            b++;
            // return closest 
            hits.push_back(a_hits[a]);
            hits.push_back(b_hits[b]);
        }
        else if(a_hits[a].ray_exiting && b_hits[b].ray_exiting){
            // return closest 
            hits.push_back(a_hits[a]);
            hits.push_back(b_hits[b]);
        }
        return true;
    }

    if(type == type_difference){
        if(a_hits.size() == 0)
            return false;
        if(b_hits.size() == 0){
            return A->Intersection(ray, hits);
        }

        if(!a_hits[a].ray_exiting && !b_hits[b].ray_exiting){
            b++;
            // return closest 
            hits.push_back(a_hits[a]);
            hits.push_back(b_hits[b]);
        }
        else if(a_hits[a].ray_exiting && !b_hits[b].ray_exiting){
            a_hits[a].flip = true;
            // return closest 
            hits.push_back(a_hits[a]);
            hits.push_back(b_hits[b]);
        }
        else if(!a_hits[a].ray_exiting && b_hits[b].ray_exiting){
            a++;
            a_hits[a].flip = true;
            // return furthest
            if(a_hits[a].t > b_hits[b].t)
                hits.push_back(a_hits[a]);
            else
                hits.push_back(b_hits[b]);
        }
        else if(a_hits[a].ray_exiting && b_hits[b].ray_exiting){
            a++;
            // return closest
            hits.push_back(a_hits[a]);
            hits.push_back(b_hits[b]);
        }
        return true;
    }

    return false;
}

// This should never be called.
vec3 Boolean::Normal(const vec3& point) const
{
    assert(false);
    return vec3();
}
