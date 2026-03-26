#ifndef VEC3_H
# define VEC3_H

typedef struct s_vec3
{
	double				x;
	double				y;
	double				z;
}						t_vec3;

t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_sub(t_vec3 a, t_vec3 b);
t_vec3	vec3_mult(t_vec3 a, double scalar);
t_vec3	vec3_normalize(t_vec3 a);
double	vec3_dot(t_vec3 a, t_vec3 b); // Scalar Product
double	vec3_length(t_vec3 a);

#endif
