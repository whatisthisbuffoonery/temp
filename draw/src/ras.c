/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ras.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 13:04:48 by dthoo             #+#    #+#             */
/*   Updated: 2026/03/20 03:20:04 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_mlx.h"

void	scale_init(t_pt *pt, int size, t_data *data, float *f)
{
	int		i;
	float	bw;
	float	bh;
	t_view	*view;

	i = 0;
	view = &data->param.view;
	while (i < size)
	{
		if (pt[i].fx > f[2])
			f[2] = pt[i].fx;
		if (pt[i].fy > f[3])
			f[3] = pt[i].fy;
		if (pt[i].fx < f[0])
			f[0] = pt[i].fx;
		if (pt[i].fy < f[1])
			f[1] = pt[i].fy;
		i ++;
	}
	bw = fmaxf(f[2] - f[0], 1.0f);
	bh = fmaxf(f[3] - f[1], 1.0f);
	view->scale = (fminf(WIDTH / bw, HEIGHT / bh)) * 0.5;
	// while (i < size)
	// {
	// 	pt[i].fx = (pt[i].fx * view->scale) + data->cx;
	// 	pt[i].fy = (pt[i].fy * view->scale) + data->cy;
	// 	i ++;
	// }
}

void	center_init(t_data *data, int size)
{
	t_pt	*pt;
	int		i;
	int		z_min;
	int		z_max;

	pt = data->param.pt;
	i = 0;
	z_min = INT_MAX;
	z_max = INT_MIN;
	while (i < size)
	{
		if (pt[i].z > z_max)
			z_max = pt[i].z;
		if (pt[i].z < z_min)
			z_min = pt[i].z;
		i ++;
	}
	data->cx = (float) (data->x) * 0.5f;
	data->cy = (float) (data->y) * 0.5f;
	data->cz = (z_min + z_max) * 0.5f;
}

void	view_init(t_pt *pt, int size, char **v, t_data *data)
{
	int		i;
	t_view	view;
	t_trig	t;
	float	z;

	view = angle_init(v);
	center_init(data, size);
	i = 0;
	while (i < size)
	{
		t.x = pt[i].x - data->cx;
		t.y = pt[i].y - data->cy;
		t.z = pt[i].z - data->cz;
		pt[i].fx = (t.x * view.cosz) - (t.y * view.sinz);
		pt[i].fy = (t.x * view.sinz) + (t.y * view.cosz);
		z = -(pt[i].fx * view.siny) + (t.z * view.cosy);
		pt[i].fx = ((pt[i].fx * view.cosy) + (t.z * view.siny)) + data->cx;
		pt[i].fy = ((pt[i].fy * view.cosx) + (z * view.sinx)) + data->cy;
		i ++;
	}
	data->param.view = view;
	scale_init(pt, size, data, (float []){FLT_MAX, FLT_MAX, -FLT_MAX, -FLT_MAX});
}

void	rasterise(t_pt *pt, t_view view, int size, t_data *data)
{
	t_trig	t;
	t_trig	r;
	int		i;

	i = 0;
	while (i < size)
	{
		t.x = pt[i].x - data->cx;
		t.y = pt[i].y - data->cy;
		t.z = pt[i].z - data->cz;
		pt[i].fx = (t.x * view.cosz) - (t.y * view.sinz);
		pt[i].fy = (t.x * view.sinz) + (t.y * view.cosz);
		r.z = -(pt[i].fx * view.siny) + (t.z * view.cosy);
		r.x = (pt[i].fx * view.cosy) + (t.z * view.siny);
		r.y = (pt[i].fy * view.cosx) + (r.z * view.sinx);
		r.z *= view.scale;
		r.y *= view.scale;
		r.x *= view.scale;
		pt[i].fx = r.x + (((float)WIDTH) * 0.5f) + data->offset_x;
		pt[i].fy = r.y + (((float)HEIGHT) * 0.5f) + data->offset_y;
		pt[i].fz = r.z;
		i ++;
	}
}
