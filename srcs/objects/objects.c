#include "minirt.h"

bool hit_plane(t_ray ray, t_plane pl, t_hit *hit)
{
    double  denom;
    double  t;
	t_vec3  p0l0; // Vector between ray origin and a point on the plane

	// 1. Compute the denominator (dot product between ray direction and plane normal)
	// If the dot product is 0, the ray is perfectly parallel to the plane.
    denom = vec3_dot(pl.normal, ray.dir);

	// Use EPSILON to avoid divisions by zero or nearly parallel hits
    if (fabs(denom) < EPSILON)
        return (false);

	// 2. Compute distance t
	// Formula: t = ((PlanePoint - RayOrigin) . Normal) / (RayDirection . Normal)
    p0l0 = vec3_sub(pl.point, ray.origin);
    t = vec3_dot(p0l0, pl.normal) / denom;

	// 3. Check whether the intersection is in front of the camera
    if (t < EPSILON)
        return (false);

	// 4. If we get here, the plane was hit. Fill the hit struct
    hit->t = t;
    hit->phit = vec3_add(ray.origin, vec3_mult(ray.dir, t));
    
	// The plane normal is fixed (from parsing), but it must point
	// against the ray direction for consistent lighting
    if (denom > 0)
        hit->nhit = vec3_mult(pl.normal, -1.0);
    else
        hit->nhit = pl.normal;
        
    hit->color = pl.color;
    return (true);
}

bool	hit_sphere(t_ray ray, t_sphere sp, t_hit *hit)
{
	t_vec3	oc;
	double	abc[3];
	double	disc;
	double	t;

	oc = vec3_sub(ray.origin, sp.center);
	abc[0] = vec3_dot(ray.dir, ray.dir);
	abc[1] = 2.0 * vec3_dot(oc, ray.dir);
	abc[2] = vec3_dot(oc, oc) - pow(sp.diameter / 2.0, 2);
	disc = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (disc < 0)
		return (false);
	t = (-abc[1] - sqrt(disc)) / (2.0 * abc[0]);
	if (t < EPSILON)
		t = (-abc[1] + sqrt(disc)) / (2.0 * abc[0]);
	if (t < EPSILON)
		return (false);
	hit->t = (float)t;
	hit->phit = vec3_add(ray.origin, vec3_mult(ray.dir, t));
	hit->nhit = vec3_normalize(vec3_sub(hit->phit, sp.center));
	hit->color = sp.color;
	return (true);
}

/* Computes quadratic coefficients for the infinite cylinder equation.
** Moved here from objects_utils.c so hit_cylinder can call it as static. */
static void	get_cy_abc(t_ray ray, t_cylinder cy, double *abc)
{
	t_vec3	oc;

	oc = vec3_sub(ray.origin, cy.center);
	abc[0] = vec3_dot(ray.dir, ray.dir)
		- pow(vec3_dot(ray.dir, cy.axis), 2);
	abc[1] = 2 * (vec3_dot(ray.dir, oc)
			- (vec3_dot(ray.dir, cy.axis) * vec3_dot(oc, cy.axis)));
	abc[2] = vec3_dot(oc, oc) - pow(vec3_dot(oc, cy.axis), 2)
		- pow(cy.diameter / 2, 2);
}

/*
** Validates a single cylinder root: checks that t is positive and that the
** hit point lies within the finite height of the cylinder.
** Extracted so hit_cylinder can test both roots independently.
*/
static bool	cy_check_root(t_ray ray, t_cylinder cy, double t, t_hit *hit)
{
	double	h;

	if (t < EPSILON)
		return (false);
	hit->phit = vec3_add(ray.origin, vec3_mult(ray.dir, t));
	h = vec3_dot(vec3_sub(hit->phit, cy.center), cy.axis);
	if (h < -cy.height / 2.0 || h > cy.height / 2.0)
		return (false);
	hit->t = (float)t;
	hit->nhit = vec3_normalize(vec3_sub(hit->phit,
				vec3_add(cy.center, vec3_mult(cy.axis, h))));
	hit->color = cy.color;
	return (true);
}

/*
** Ray-cylinder intersection.  Tries the nearest root first; if its hit point
** falls outside the finite height, falls back to the farther root.
*/
bool	hit_cylinder(t_ray ray, t_cylinder cy, t_hit *hit)
{
	double	abc[3];
	double	disc;
	double	t1;
	double	t2;

	get_cy_abc(ray, cy, abc);
	disc = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (disc < 0)
		return (false);
	t1 = (-abc[1] - sqrt(disc)) / (2.0 * abc[0]);
	t2 = (-abc[1] + sqrt(disc)) / (2.0 * abc[0]);
	/* Try nearest root first; fall back to farther root if height check fails */
	if (cy_check_root(ray, cy, t1, hit))
		return (true);
	return (cy_check_root(ray, cy, t2, hit));
}

/*
** Moller-Trumbore ray-triangle intersection.
** Uses precomputed edges and normal from the parser.
** u and v are barycentric coordinates: if u >= 0, v >= 0,
** and u + v <= 1, the hit point lies inside the triangle.
** params[0] = 1/determinant, params[1] = u, params[2] = v
*/
bool	hit_triangle(t_ray ray, t_triangle tr, t_hit *hit)
{
	t_vec3	hvec;
	t_vec3	svec;
	t_vec3	qvec;
	double	params[3];
	double	t;

	hvec = vec3_cross(ray.dir, tr.edge[1]);
	params[0] = vec3_dot(tr.edge[0], hvec);
	if (fabs(params[0]) < EPSILON)
		return (false);
	params[0] = 1.0 / params[0];
	svec = vec3_sub(ray.origin, tr.c[0]);
	params[1] = params[0] * vec3_dot(svec, hvec);
	if (params[1] < 0.0 || params[1] > 1.0)
		return (false);
	qvec = vec3_cross(svec, tr.edge[0]);
	params[2] = params[0] * vec3_dot(ray.dir, qvec);
	if (params[2] < 0.0 || params[1] + params[2] > 1.0)
		return (false);
	t = params[0] * vec3_dot(tr.edge[1], qvec);
	if (t < EPSILON)
		return (false);
	hit->t = t;
	hit->phit = vec3_add(ray.origin, vec3_mult(ray.dir, t));
	if (vec3_dot(tr.n, ray.dir) > 0)
		hit->nhit = vec3_mult(tr.n, -1.0);
	else
		hit->nhit = tr.n;
	hit->color = tr.color;
	return (true);
}