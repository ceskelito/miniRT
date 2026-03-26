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

}

double vec3_length(t_vec3 a)
{
    return (sqrt(vec3_dot(a, a)));
}
