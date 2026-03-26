#include "minirt.h"

bool hit_plane(t_ray ray, t_plane pl, t_hit *hit)
{
    double  denom;
    double  t;
    t_vec3  p0l0; // Vettore tra origine raggio e punto sul piano

    // 1. Calcoliamo il denominatore (prodotto scalare tra direzione raggio e normale piano)
    // Se il prodotto scalare è 0, il raggio è perfettamente parallelo al piano.
    denom = vec3_dot(pl.normal, ray.dir);

    // Usiamo EPSILON per evitare divisioni per zero o colpi quasi paralleli
    if (fabs(denom) < EPSILON)
        return (false);

    // 2. Calcoliamo la distanza t
    // Formula: t = ((PuntoPiano - OrigineRaggio) . Normale) / (DirezioneRaggio . Normale)
    p0l0 = vec3_sub(pl.point, ray.origin);
    t = vec3_dot(p0l0, pl.normal) / denom;

    // 3. Verifichiamo se l'impatto è davanti alla camera
    if (t < EPSILON)
        return (false);

    // 4. Se siamo qui, abbiamo colpito il piano! Riempiamo la struct hit
    hit->t = t;
    hit->phit = vec3_add(ray.origin, vec3_mult(ray.dir, t));
    
    // La normale del piano è fissa (quella del parser), ma dobbiamo assicurarci
    // che punti "contro" il raggio (per l'illuminazione)
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

bool	hit_cylinder(t_ray ray, t_cylinder cy, t_hit *hit)
{
	double	abc[3];
	double	t;
	double	disc;
	double	h;

	get_cy_abc(ray, cy, abc);
	disc = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (disc < 0)
		return (false);
	t = (-abc[1] - sqrt(disc)) / (2.0 * abc[0]);
	if (t < EPSILON)
		t = (-abc[1] + sqrt(disc)) / (2.0 * abc[0]);
	hit->phit = vec3_add(ray.origin, vec3_mult(ray.dir, t));
	h = vec3_dot(vec3_sub(hit->phit, cy.center), cy.axis);
	if (t < EPSILON || h < -cy.height / 2.0 || h > cy.height / 2.0)
		return (false);
	hit->t = (float)t;
	hit->nhit = vec3_normalize(vec3_sub(hit->phit, vec3_add(cy.center,
					vec3_mult(cy.axis, h))));
	hit->color = cy.color;
	return (true);
}

/*
** Möller–Trumbore: intersezione raggio-triangolo.
** Usa i lati (edge) e la normale pre-calcolati dal parser.
** u e v sono le coordinate baricentriche: se u >= 0, v >= 0
** e u + v <= 1, il punto di impatto cade dentro il triangolo.
** params[0] = 1/determinante, params[1] = u, params[2] = v
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