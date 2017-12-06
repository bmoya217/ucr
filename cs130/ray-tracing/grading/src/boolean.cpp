#include "boolean.h"
#include "ray.h"

// Determine if the ray intersects with the boolean of A and B.
bool Boolean::Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    // double t_total = 0.0;
    // Ray new_ray;
    // new_ray.direction = ray.direction;
    // new_ray.endpoint = ray.endpoint;
    // for(unsigned int h = 0; h < hits.size(); h++){
    //     t_total += hits[h].t;
    // }
    // if(hits.size() > 0){
    //     new_ray.endpoint = ray.Point(t_total+.0001);
    // }

    unsigned int a = 0, b = 0;
    std::vector<Hit> a_hits, b_hits;
    A->Intersection(ray, a_hits);
    B->Intersection(ray, b_hits);

    // make sure the hits are relevant
    while(a_hits.size() > a){
        if(a_hits[a].t <= 0.0001)
            a++;
        else
            break;
    }
    while(b_hits.size() > b){
        if(b_hits[b].t <= 0.0001)
            b++;
        else
            break;
    }

    // get first hit
    while(true){
        if(type == type_union){
            if(a_hits.size() <= a && b_hits.size() <= b)
                return false;
            else if(a_hits.size() <= a){
                hits.push_back(b_hits[b]);
                return true;
            }
            else if(b_hits.size() <= b){
                hits.push_back(a_hits[a]);
                return true;
            }
            
            if(!a_hits[a].ray_exiting && !b_hits[b].ray_exiting){
                if(a_hits[a].t < b_hits[b].t)
                    hits.push_back(a_hits[a]);
                else
                    hits.push_back(b_hits[b]);
                break;
            }
            else if(a_hits[a].ray_exiting && !b_hits[b].ray_exiting){
                if(a_hits[a].t < b_hits[b].t){
                    hits.push_back(a_hits[a]);
                    break;
                }
                b++;
            }
            else if(!a_hits[a].ray_exiting && b_hits[b].ray_exiting){
                if(a_hits[a].t > b_hits[b].t){
                    hits.push_back(b_hits[b]);
                    break;
                }
                a++;
            }
            else if(a_hits[a].ray_exiting && b_hits[b].ray_exiting){
                if(a_hits[a].t > b_hits[b].t)
                    hits.push_back(a_hits[a]);
                else
                    hits.push_back(b_hits[b]);
                break;
            }
        }

        if(type == type_intersection){
            if(a_hits.size() <= a || b_hits.size() <= b)
                return false;

            if(!a_hits[a].ray_exiting && !b_hits[b].ray_exiting){
                if(a_hits[a].t > b_hits[b].t)
                    hits.push_back(a_hits[a]);
                else
                    hits.push_back(b_hits[b]);
                break;
            }
            else if(a_hits[a].ray_exiting && !b_hits[b].ray_exiting){
                if(a_hits[a].t > b_hits[b].t){
                    hits.push_back(b_hits[b]);
                    break;
                }
                a++;
            }
            else if(!a_hits[a].ray_exiting && b_hits[b].ray_exiting){
                if(a_hits[a].t < b_hits[b].t){
                    hits.push_back(a_hits[a]);
                    break;
                }
                b++;
            }
            else if(a_hits[a].ray_exiting && b_hits[b].ray_exiting){
                if(a_hits[a].t < b_hits[b].t)
                    hits.push_back(a_hits[a]);
                else
                    hits.push_back(b_hits[b]);
                break;
            }
        }

        if(type == type_difference){
            if(a_hits.size() <= a)
                return false;
            if(b_hits.size() <= b){
                hits.push_back(a_hits[a]);
                return true;
            }

            if(!a_hits[a].ray_exiting && !b_hits[b].ray_exiting){
                if(a_hits[a].t < b_hits[b].t){
                    hits.push_back(a_hits[a]);
                    break;
                }
                b++;
            }
            else if(a_hits[a].ray_exiting && !b_hits[b].ray_exiting){
                b_hits[b].flip = true;
                if(a_hits[a].t < b_hits[b].t)
                    hits.push_back(a_hits[a]);
                else
                    hits.push_back(b_hits[b]);
                break;
            }
            else if(!a_hits[a].ray_exiting && b_hits[b].ray_exiting){
                if(a_hits[a].t > b_hits[b].t){
                    hits.push_back(a_hits[a]);
                    break;
                }
                a++;
            }
            else if(a_hits[a].ray_exiting && b_hits[b].ray_exiting){
                b_hits[b].flip = true;
                if(a_hits[a].t > b_hits[b].t){
                    hits.push_back(b_hits[b]);
                    break;
                }
                a++;
            }
        }
    }

    //get (potential) second hit
    // if(Intersection(ray, hits))
    //     hits[hits.size()-1].t += hits[hits.size()-2].t;

    return true;
}

// This should never be called.
vec3 Boolean::Normal(const vec3& point) const
{
    assert(false);
    return vec3();
}
