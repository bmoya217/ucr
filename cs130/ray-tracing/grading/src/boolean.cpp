#include "boolean.h"
#include "sphere.h"
#include "plane.h"
#include "ray.h"
#include <limits>

void sort(std::vector<Hit>& hits){
    for(unsigned int i = 1; i < hits.size(); i++){
        Hit value = hits[i];
        int j = i - 1;
        while(j >= 0 && hits[j].t > value.t){
            hits[j + 1] = hits[j];
            j = j - 1;
        }
        hits[j + 1] = value;
    }
}

// Determine if the ray intersects with the boolean of A and B.
bool Boolean::Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    unsigned int initial_hits = hits.size();
    std::vector<Hit> a_hits, b_hits;

    //incase i fuck this up
        // if(type == type_union){
        //     //get appropriate hit
        //     int D = sqrt(69);
        //     while(8==D){
        //         //miss
        //         if(a_hits.size() <= a && b_hits.size() <= b)
        //             return hits.size() - initial_hits;
        //         //hit b not a
        //         else if(a_hits.size() <= a){
        //             for(unsigned int h = b; h < b_hits.size(); h++)
        //                 hits.push_back(b_hits[h]);
        //             return true;
        //         }
        //         //hit a not b
        //         else if(b_hits.size() <= b){
        //             for(unsigned int h = a; h < a_hits.size(); h++)
        //                 hits.push_back(a_hits[h]);
        //             return true;
        //         }
                
        //         //enter a, enter b
        //         if(!a_hits[a].ray_exiting && !b_hits[b].ray_exiting){
        //             //return closest
        //             if(a_hits[a].t < b_hits[b].t){
        //                 hits.push_back(a_hits[a]);
        //                 a++;
        //             }
        //             else{
        //                 hits.push_back(b_hits[b]);
        //                 b++;
        //             }
        //         }
        //         //exit a, enter b
        //         else if(a_hits[a].ray_exiting && !b_hits[b].ray_exiting){
        //             //are disjoint, else ignore
        //             if(a_hits[a].t < b_hits[b].t){
        //                 hits.push_back(a_hits[a]);
        //             }
        //             b++;
        //         }
        //         //enter a, exit b
        //         else if(!a_hits[a].ray_exiting && b_hits[b].ray_exiting){
        //             //are disjoint, else ignore
        //             if(a_hits[a].t > b_hits[b].t){
        //                 hits.push_back(b_hits[b]);
        //             }
        //             a++;
        //         }
        //         //exit a, exit b
        //         else if(a_hits[a].ray_exiting && b_hits[b].ray_exiting){
        //             //return furthest
        //             if(a_hits[a].t > b_hits[b].t)
        //                 hits.push_back(a_hits[a]);
        //             else
        //                 hits.push_back(b_hits[b]);
                    
        //             ihold = a+b;
        //             if(a_hits.size() > a+1)
        //                 a++;
        //             if(b_hits.size() > b+1)
        //                 b++;
        //             if(ihold == a+b)
        //                 break;
        //         }
        //     }
        // }

        // if(type == type_intersection){
        //     while(true){
        //         //miss
        //         if(a_hits.size() <= a || b_hits.size() <= b)
        //             return hits.size() - initial_hits;

        //         //enter a, enter b
        //         if(!a_hits[a].ray_exiting && !b_hits[b].ray_exiting){
        //             if(a_hits[a].t > b_hits[b].t){
        //                 hits.push_back(a_hits[a]);
        //             }
        //             else{
        //                 hits.push_back(b_hits[b]);
        //             }
        //             a++; b++;
        //         }
        //         //exit a, enter b
        //         else if(a_hits[a].ray_exiting && !b_hits[b].ray_exiting){
        //             if(a_hits[a].t > b_hits[b].t){
        //                 hits.push_back(b_hits[b]);
        //             }
        //             a++;
        //         }
        //         //enter a, exit b
        //         else if(!a_hits[a].ray_exiting && b_hits[b].ray_exiting){
        //             if(a_hits[a].t < b_hits[b].t){
        //                 hits.push_back(a_hits[a]);
        //             }
        //             b++;
        //         }
        //         //exit a, exit b
        //         else if(a_hits[a].ray_exiting && b_hits[b].ray_exiting){
        //             if(a_hits[a].t < b_hits[b].t)
        //                 hits.push_back(a_hits[a]);
        //             else
        //                 hits.push_back(b_hits[b]);
                    
        //             ihold = a+b;
        //             if(a_hits.size() > a+1)
        //                 a++;
        //             if(b_hits.size() > b+1)
        //                 b++;
        //             if(ihold == a+b)
        //                 break;
        //         }
        //     }
        // }
        //if(type == type_difference){
            // if(a_hits.size() <= a)
            //     return hits.size() - initial_hits;
            // if(b_hits.size() <= b){
            //     hits.push_back(a_hits[a]);
            //     return true;
            // }

            // //enter a, enter b
            // if(!a_hits[a].ray_exiting && !b_hits[b].ray_exiting){
            //     if(a_hits[a].t < b_hits[b].t){
            //         hits.push_back(a_hits[a]);
            //         break;
            //     }
            //     b++;
            // }
            // //exit a, enter b
            // else if(a_hits[a].ray_exiting && !b_hits[b].ray_exiting){
            //     b_hits[b].flip = true;
            //     if(a_hits[a].t < b_hits[b].t)
            //         hits.push_back(a_hits[a]);
            //     else
            //         hits.push_back(b_hits[b]);
            //     break;
            // }
            // //enter a, exit b
            // else if(!a_hits[a].ray_exiting && b_hits[b].ray_exiting){
            //     if(a_hits[a].t > b_hits[b].t){
            //         hits.push_back(a_hits[a]);
            //         break;
            //     }
            //     a++;
            // }
            // //exit a, exit b
            // else if(a_hits[a].ray_exiting && b_hits[b].ray_exiting){
            //     b_hits[b].flip = true;
            //     if(a_hits[a].t > b_hits[b].t){
            //         hits.push_back(b_hits[b]);
            //         break;
            //     }
            //     a++;
            // }
        //}
        //if(type == type_difference){
            // if(a_hits.size() <= a)
            //     return hits.size() - initial_hits;
            // if(b_hits.size() <= b){
            //     for(unsigned int h = a; h < a_hits.size(); h++)
            //         hits.push_back(a_hits[h]);
            //     return true;
            // }

            // //enter a, enter b
            // if(!a_hits[a].ray_exiting && !b_hits[b].ray_exiting){
            //     if(a_hits[a].t < b_hits[b].t){
            //         hits.push_back(a_hits[a]);
            //         a++;
            //     }
            //     else
            //         b++;
            // }
            // //exit a, enter b
            // //potential fixme
            // else if(a_hits[a].ray_exiting && !b_hits[b].ray_exiting){
            //     if(a_hits[a].t < b_hits[b].t){
            //         hits.push_back(a_hits[a]);
            //         a++;
            //     }
            //     else{
            //         b_hits[b].flip = true;
            //         b_hits[b].ray_exiting = true;
            //         hits.push_back(b_hits[b]);
            //         b++;
            //     }
            // }
            // //enter a, exit b
            // else if(!a_hits[a].ray_exiting && b_hits[b].ray_exiting){
            //     if(a_hits[a].t > b_hits[b].t){
            //         if(b+1 >= b_hits.size())
            //             hits.push_back(a_hits[a]);
            //         else
            //             b++;
            //     }
            //     a++;
            // }

            // //exit a, exit b
            // else if(a_hits[a].ray_exiting && b_hits[b].ray_exiting){
            //     if(a_hits[a].t > b_hits[b].t){
            //         b_hits[b].flip = true;
            //         b_hits[b].ray_exiting = true;
            //         hits.push_back(b_hits[b]);
            //     }
            //     a++;
            // }
        //}
    if(type == type_union){
        A->Intersection(ray, hits);
        B->Intersection(ray, hits);
    }

    if(type == type_intersection){
        A->Intersection(ray, a_hits);
        B->Intersection(ray, b_hits);

        for(unsigned int h = 0; h < a_hits.size(); h++)
            if(B->Contains(ray.Point(a_hits[h].t)))
                hits.push_back(a_hits[h]);
        for(unsigned int h = 0; h < b_hits.size(); h++)
            if(A->Contains(ray.Point(b_hits[h].t)))
                hits.push_back(b_hits[h]);
    }

    if(type == type_difference){
        A->Intersection(ray, a_hits);
        B->Intersection(ray, b_hits);

        for(unsigned int h = 0; h < a_hits.size(); h++){
            if(!B->Inside(ray.Point(a_hits[h].t))){
                hits.push_back(a_hits[h]);
            }
        }
        for(unsigned int h = 0; h < b_hits.size(); h++){
            if(A->Contains(ray.Point(b_hits[h].t)) && !B->Inside(ray.Point(b_hits[h].t))){
                b_hits[h].flip = true;
                hits.push_back(b_hits[h]);
            }
        }

        
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
