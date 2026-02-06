#include "minirt.h"
#include "objects.h"
#include "parser.h"

t_vec3 v_add(t_vec3 a, t_vec3 b)
{
    return((t_vec3){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_vec3 v_sub(t_vec3 a, t_vec3 b)
{
    return((t_vec3){a.x - b.x, a.y - b.y, a.z - b.z});
}

t_vec3 v_mult(t_vec3 a, double scalar)
{
    return((t_vec3){a.x * scalar, a.y * scalar, a.z * scalar});
}

double v_dot(t_vec3 a, t_vec3 b) //(Prodotto scalare)
{
    return(a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3 v_normalize(t_vec3 a)
{

}

double v_length(t_vec3 a)
{
    return (sqrt(v_dot(a, a)));
}