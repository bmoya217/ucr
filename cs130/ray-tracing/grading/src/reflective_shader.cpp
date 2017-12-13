#include "reflective_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 Reflective_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& same_side_normal,int recursion_depth) const
{
	vec3 shader_color = shader->Shade_Surface(ray, intersection_point, same_side_normal, recursion_depth);
	vec3 reflection = 2 * dot(same_side_normal,ray.direction*-1) * same_side_normal - (ray.direction*-1);
	
	Ray next_ray;
	next_ray.direction = reflection.normalized();
	next_ray.endpoint = intersection_point;
	vec3 reflected_color = world.Cast_Ray(next_ray, recursion_depth+1);

	return (1-reflectivity)*shader_color + reflectivity*reflected_color;
}
