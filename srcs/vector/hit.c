#include "minirt.h"

// Finds the closest object to the camera so only the frontmost hit is rendered
t_color trace_ray(t_scene *scene, t_ray ray)
{
    t_hit   closest_hit;
    t_hit   current_hit;
    t_object *obj;

    closest_hit.t = INFINITY; // Start from infinity
    obj = scene->objects;

    while (obj)
    {
        if (intersect(ray, obj, &current_hit)) // Intersection dispatcher by object type
        {
            if (current_hit.t < closest_hit.t)
                closest_hit = current_hit;
        }
        obj = obj->next;
    }

    if (closest_hit.t == INFINITY)
        return (t_color){0, 0, 0}; // Black background

    return (calculate_lighting(scene, &closest_hit));
}
