#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"
#include <algorithm>


vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& same_side_normal,int recursion_depth) const
{
    vec3 ambient = color_ambient*world.ambient_intensity*world.ambient_color, diffuse = {0,0,0}, specular = {0,0,0};

    for(unsigned int l = 0; l < world.lights.size(); l++){
    	vec3 point_to_light = world.lights[l]->position - intersection_point;
    	double len_ptl = sqrt(dot(point_to_light,point_to_light));
    	vec3 point_to_camera = world.camera.position - intersection_point;
    	vec3 reflection = 2 * dot(same_side_normal,point_to_light.normalized()) * same_side_normal - point_to_light.normalized();
    	
    	Hit hit;
    	Ray ray_of_light;
    	ray_of_light.endpoint = world.lights[l]->position;
    	ray_of_light.direction = -point_to_light.normalized();
    	world.Closest_Intersection(ray_of_light, hit);
    	if(hit.t+small_t > len_ptl || !world.enable_shadows){
	    	diffuse += std::max(dot(same_side_normal, point_to_light.normalized()),0.0) * color_diffuse * world.lights[l]->Emitted_Light(ray)/(len_ptl*len_ptl);
    		specular += std::pow(std::max(dot(reflection.normalized(), point_to_camera.normalized()),0.0),specular_power) * color_specular * world.lights[l]->Emitted_Light(ray)/(len_ptl*len_ptl);
    	}
    }

	return ambient + diffuse + specular;
}
