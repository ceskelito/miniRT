#include "minirt.h"

//serve per da interruttore per gestire l'oggetto giusto
bool intersect(t_ray ray, t_object *obj, t_hit *hit)
{
    if (obj->type == SPHERE)
        return (hit_sphere(ray, obj->data.sp, hit));
    else if (obj->type == PLANE)
        return (hit_plane(ray, obj->data.pl, hit));
    else if (obj->type == CYLINDER)
        return (hit_cylinder(ray, obj->data.cy, hit));
    else if (obj->type == CONE)
        return (hit_cone(ray, obj->data.co, hit)); // Bonus
    else if (obj->type == TRIANGLE)
        return (hit_triangle(ray, obj->data.tr, hit)); // Bonus
    else if (obj->type == TORUS)
        return (hit_torus(ray, obj->data.to, hit)); // Bonus
    return (false);
}

//funzione per il calcolo dei parametri del clilndro 
static void	get_cy_abc(t_ray ray, t_cylinder cy, double *abc)
{
	t_vec3	oc;

	oc = vec3_sub(ray.origin, cy.center);
	abc[0] = vec3_dot(ray.dir, ray.dir) - pow(vec3_dot(ray.dir, cy.axis), 2);
	abc[1] = 2 * (vec3_dot(ray.dir, oc) - (vec3_dot(ray.dir, cy.axis)
				* vec3_dot(oc, cy.axis)));
	abc[2] = vec3_dot(oc, oc) - pow(vec3_dot(oc, cy.axis), 2)
		- pow(cy.diameter / 2, 2);
}

