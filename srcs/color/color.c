#include "minirt.h"

// FIXME: This implementation still needs a full review.
t_color calculate_lighting(t_scene *scene, t_hit *hit)
{
    t_color ambient;
    t_color diffuse;
    t_vec3  light_dir;
    double  dot;
    bool    shadowed;

    // 1. AMBIENT LIGHT
    // The object color is tinted by ambient light.
    ambient = color_mult_ratio(hit->color, scene->ambient.color, scene->ambient.ratio);

    // 2. SHADOW TEST (shadow ray)
    // Cast a ray from the hit point toward the light source.
    light_dir = vec3_normalize(vec3_sub(scene->light.light_point, hit->phit));
    shadowed = is_in_shadow(scene, hit->phit, light_dir);

    if (shadowed)
        return (ambient); // In shadow, only ambient light contributes.

    // 3. DIFFUSE LIGHT (Lambert model)
    // Compute the angle between surface normal and light direction.
    dot = vec3_dot(hit->nhit, light_dir);
    
    if (dot > 0)
    {
        // If the point faces the light, compute diffuse intensity.
        double intensity = dot * scene->light.brightness_ratio;
        diffuse = color_mult_ratio(hit->color, scene->light.color, intensity);
        return (color_add(ambient, diffuse));
    }

    return (ambient);
}

bool is_in_shadow(t_scene *scene, t_vec3 point, t_vec3 light_dir)
{
    t_ray   shadow_ray;
    t_hit   hit;
    t_object *obj;
    double  dist_to_light;

    /* Offset origin along light direction to avoid self-intersection (shadow acne).
    ** Using light_dir instead of the uninitialized hit.nhit. */
    shadow_ray.origin = vec3_add(point, vec3_mult(light_dir, EPSILON));
    shadow_ray.dir = light_dir;
    
    dist_to_light = vec3_length(vec3_sub(scene->light.light_point, point));
    obj = scene->objects;

    while (obj)
    {
        // If the shadow ray hits anything before reaching the light...
        if (intersect(shadow_ray, obj, &hit))
        {
            // ...and the hit lies between the point and the light.
            if (hit.t > 0 && hit.t < dist_to_light)
                return (true);
        }
        obj = obj->next;
    }
    return (false);
}

// Applies light color and intensity to the object color.
t_color color_mult_ratio(t_color obj_c, t_color light_c, double ratio)
{
    t_color res;
    res.r = (int)((obj_c.r * (light_c.r / 255.0)) * ratio);
    res.g = (int)((obj_c.g * (light_c.g / 255.0)) * ratio);
    res.b = (int)((obj_c.b * (light_c.b / 255.0)) * ratio);
    return (res);
}

// Adds two colors and clamps each channel to 255.
t_color color_add(t_color a, t_color b)
{
    t_color res;
    res.r = (a.r + b.r > 255) ? 255 : a.r + b.r;
    res.g = (a.g + b.g > 255) ? 255 : a.g + b.g;
    res.b = (a.b + b.b > 255) ? 255 : a.b + b.b;
    return (res);
}