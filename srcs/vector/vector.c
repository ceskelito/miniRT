#include <math.h>
#include "vec3.h"

t_vec3 vec3_add(t_vec3 a, t_vec3 b)
{
    return((t_vec3){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_vec3 vec3_sub(t_vec3 a, t_vec3 b)
{
    return((t_vec3){a.x - b.x, a.y - b.y, a.z - b.z});
}

t_vec3 vec3_mult(t_vec3 a, double scalar)
{
    return((t_vec3){a.x * scalar, a.y * scalar, a.z * scalar});
}

double vec3_dot(t_vec3 a, t_vec3 b) // Scalar Product
{
    return(a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3 vec3_normalize(t_vec3 a)
{
	double	len;

	len = vec3_length(a);
	if (len == 0)
		return ((t_vec3){0, 0, 0});
	return (vec3_mult(a, 1.0 / len));
}

double vec3_length(t_vec3 a)
{
    return (sqrt(vec3_dot(a, a)));
}

t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	});
}