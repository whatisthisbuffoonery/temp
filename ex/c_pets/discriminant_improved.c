/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   discriminant_improved.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 23:00:50 by dthoo             #+#    #+#             */
/*   Updated: 2026/10/27 23:00:53 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minirt.h"
#define IDEAL_LINEAR_RANGE 900
#define IDEAL_QUADRATIC_RANGE 500

int	linear_target(double ac)
{
	int	abs_ac

	abs_ac = (abs(ac) - IDEAL_LINEAR_RANGE) / 2;
	if (ac >= 0)
		return (abs_ac + (ac > 0 && ac % 2));
	return (abs_ac - (ac < 0 && ac % 2));
}

//for target[0], up = (probably -ve) exponent + range
//shift if up < 0
//up = -target[0]
//for target[1], down = (probably +ve) exponent - range
//shift if down > 0
//down = target[1]
static void	find_tolerance(int *tol, int *target, t_dot_math *m)
{
	int ea;
	int eb;
	int ec;
	int ac;
	int	b_target;

	frexp(m->a, &ea);
	frexp(m->b, &eb);
	frexp(m->c, &ec);
	ac = ea + ec + 2;//2 accounts for * 4.0
	tol[0] = (DBL_MIN_EXP - 1) - min3_exp(ea, eb, ec);//check shift >= tol[0]
	tol[1] = (DBL_MAX_EXP - 1) - max3_exp(ea, eb, ec);//check shift <= tol[1]
	if (m->a && m->c)
		target[(ac >= 0)] = linear_target(ac);//if <= 0, no shift needed
	b_target = 0;
	if (m->b)
		b_target = abs(eb) - IDEAL_QUADRATIC_RANGE;
	if (b_target > target[(eb >= 0)])
		target[(eb >= 0)] = b_target;
	if (!target[0])
		target[0] = target[1];
	if (!target[1])
		target[1] = target[0];
}

//if down is a +ve shift and up was 0, we are fucked
static void	shift_all(t_dot_math *m, int *tol, int *target)
{
	int	shift;
	int	down;
	int	up;

	down = target[1];
	up = -target[0];
	if (down > up)
		return ;
	shift = 0;
	if (shift < down)
		shift = down;
	if (shift > up)
		shift = up;
	shift = -shift;//dont add back the one
	if (shift < tol[0] || shift > tol[1])
		return ;
	m->a = scalbn(m->a, shift);
	m->b = scalbn(m->b, shift);
	m->c = scalbn(m->c, shift);
}

static int	count_roots(t_dot_math *m)
{
	double	disc;
	double	a;
	double	c;

	a = m->a;
	c = m->c;
	if (fabs(a) > fabs(c))
	{
		a = m->c;
		c = m->a;
	}
	disc = diff_products(m->b, m->b, a * 4.0, c);
	m->disc = disc;
	if (!isfinite(disc))
		return (-1);
	return ((disc >= 0.0) + (disc > 0.0));
}

int	grab_disc_improved(t_dot_math *m)
{
	int	tol[2];
	int	target[2];

	target[0] = 0;
	target[1] = 0;
	find_tolerance(tol, target, m);
	shift_all(m, tol, target);
	return (count_roots(m));
}
