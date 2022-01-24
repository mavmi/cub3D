/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_ray_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaryjo <pmaryjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 19:21:30 by pmaryjo           #+#    #+#             */
/*   Updated: 2022/01/24 18:20:21 by pmaryjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/painting.h"

static void	test_print_point(t_point *point)
{
	printf("{x = %d, y = %d, z = %d}\n", point->x, point->y, point->z);
}

static void	test_print_vector(t_vector *vector)
{
	printf("[\n");
	printf("\tbegin: ");
	test_print_point(vector->begin);
	printf("\tend: ");
	test_print_point(vector->end);
	printf("]\n");
}

// *************************************************** //

static int	paint_is_wall(t_painting *painting, int pixel_x, int pixel_y, int quarter)
{
	//printf("\t{x = %d, y = %d}\n", pixel_x, pixel_y);
	/*
	if (quarter == 1)
	{
		if (pixel_x % PIXEL_SIZE != 0)
			pixel_x -= pixel_x % PIXEL_SIZE;
		
		if (pixel_y % PIXEL_SIZE != 0)
			pixel_y -= pixel_y % PIXEL_SIZE;
		else
			pixel_y -= PIXEL_SIZE;
	}
	
	
	else if (quarter == 2)
	{
		if (pixel_y % PIXEL_SIZE)
			pixel_y -= pixel_y % PIXEL_SIZE;
		else
			pixel_x -= pixel_x % PIXEL_SIZE;
	}
	

	else if (quarter == 3)
	{
		if (pixel_x % PIXEL_SIZE)
			pixel_x -= pixel_x % PIXEL_SIZE;
		else if (pixel_x % PIXEL_SIZE == 0)
		{
			if (pixel_y % PIXEL_SIZE)
				pixel_y = pixel_y - pixel_y % PIXEL_SIZE;
			else
				pixel_y -= PIXEL_SIZE;
			pixel_x -= PIXEL_SIZE;
		}
	}


	else
	{
		if (pixel_x % PIXEL_SIZE)
		{
			pixel_x -= pixel_x % PIXEL_SIZE;
			pixel_y -= PIXEL_SIZE;
		}
		else
		{
			pixel_x -= PIXEL_SIZE;
			pixel_y -= pixel_y % PIXEL_SIZE;
		}
	}
	*/

	(void)quarter;
	pixel_x -= pixel_x % PIXEL_SIZE;
	pixel_y -= pixel_y % PIXEL_SIZE;
	pixel_x /= PIXEL_SIZE;
	pixel_y /= PIXEL_SIZE;
	//printf("\t{x = %d, y = %d}\n", pixel_x, pixel_y);
	if (painting->map->lines[pixel_y]->line[pixel_x]->type == WALL)
		return (1);
	return (0);
}

static t_vector	*paint_get_ray_vector(t_painting *painting, t_ray *ray)
{
	(void)test_print_point; (void)test_print_vector;
	
	int			delta;
	double		corner_angle;
	t_point		*begin;
	t_point		*end;
	t_vector	*corner_vector;
	t_vector	*ray_vector;

	// Инициализация точек вектора луча
	if (!painting || !ray)
		return (NULL);
	begin = geom_init_point(painting->map->player->pos->x * PIXEL_SIZE,
				painting->map->player->pos->y * PIXEL_SIZE, 0);
	end = geom_init_point(painting->map->player->pos->x * PIXEL_SIZE,
				painting->map->player->pos->y * PIXEL_SIZE, 0);
	if (!begin || !end)
	{
		geom_destroy_point(begin);
		geom_destroy_point(end);
		return (NULL);
	}
	printf("quarter: %d\n", ray->quarter);

	// Обновление точки конца вектора, двигаясь по границам квадратов
	while (1)
	{
		
//printf("\t====================\n");
//printf("quarter: %d\n", ray->quarter);
//printf("angle: %d\n", ray->quarter_angle);

		// Берем вектор, направленный в угол из текущей точки end
		corner_vector = paint_get_corner_vector(end, ray->quarter);
		if (!corner_vector)
		{
			geom_destroy_point(begin);
			geom_destroy_point(end);
			return (NULL);
		}

//printf("\n");
//printf("to corner: ");
//test_print_point(end);
//printf("corner vector: ");
//test_print_vector(corner_vector);

		// Берем угол между угловым и вертикальным векторамии
		corner_angle = geom_get_angle(ray->orient_vert, corner_vector);
		if (corner_angle > 90.0)
			corner_angle -= 90.0;

		// В зависимости от угла расчитываем сдвиг под одной из осей
		if (ray->quarter_angle <= corner_angle)
			delta = (int)sqrt(pow(corner_vector->begin->y - corner_vector->end->y, 2))
					* tan(ray->quarter_angle * M_PI / 180.0);
		else
			delta = (int)sqrt(pow(corner_vector->begin->x - corner_vector->end->x, 2))
					* tan((90 - ray->quarter_angle) * M_PI / 180.0);
		geom_destroy_vector(corner_vector);
		
//printf("\n");
//printf("angle: %f\n", corner_angle);
//printf("quarter angle: %d\n", ray->quarter_angle);
//printf("delta: %d\n", delta);
//printf("angle: %d\n", ray->quarter_angle);

		// Сдвиг точки конца
		if (ray->quarter == 1 && ray->quarter_angle <= corner_angle)
		{
			end->x += delta;
			if (end->y % PIXEL_SIZE)
				end->y = end->y - end->y % PIXEL_SIZE - 1;
			else
				end->y = end->y - PIXEL_SIZE - 1;
		}
		else if (ray->quarter == 1 && ray->quarter_angle > corner_angle)
		{
			if (end->x % PIXEL_SIZE)
				end->x = end->x - end->x % PIXEL_SIZE + PIXEL_SIZE;
			else
				end->x += PIXEL_SIZE;
			end->y -= delta;
		}
		
		
		else if (ray->quarter == 2 && ray->quarter_angle <= corner_angle)
		{
			end->x += delta;
			if (end->y % PIXEL_SIZE)
				end->y = end->y - end->y % PIXEL_SIZE + PIXEL_SIZE;
			else
				end->y += PIXEL_SIZE;
		}
		else if (ray->quarter == 2 && ray->quarter_angle > corner_angle)
		{
			if (end->x % PIXEL_SIZE)
				end->x = end->x - end->x % PIXEL_SIZE + PIXEL_SIZE;
			else
				end->x = end->x + PIXEL_SIZE;
			end->y += delta;
		}
		

		else if (ray->quarter == 3 && ray->quarter_angle <= corner_angle)
		{
			end->x -= delta;
			if (end->y % PIXEL_SIZE)
				end->y = end->y - end->y % PIXEL_SIZE + PIXEL_SIZE;
			else
				end->y += PIXEL_SIZE;
		}
		else if (ray->quarter == 3 && ray->quarter_angle > corner_angle)
		{
			if (end->x % PIXEL_SIZE)
				end->x = end->x - end->x % PIXEL_SIZE - 1;
			else
				end->x = end->x - PIXEL_SIZE - 1;
			end->y += delta;
		}

		
		else if (ray->quarter == 4 && ray->quarter_angle <= corner_angle)
		{
			end->x -= delta;
			if (end->y % PIXEL_SIZE)
				end->y = end->y - end->y % PIXEL_SIZE - 1;
			else
				end->y = end->y - PIXEL_SIZE - 1;
		}
		else if (ray->quarter == 4 && ray->quarter_angle > corner_angle)
		{
			if (end->x % PIXEL_SIZE)
				end->x = end->x - end->x % PIXEL_SIZE - 1;
			else
				end->x = end->x - PIXEL_SIZE - 1;
			end->y -= delta;
		}
			
//printf("begin: ");
//test_print_point(begin);
//printf("end: ");
//test_print_point(end);
//printf("\n");


		if (paint_is_wall(painting, end->x, end->y, ray->quarter))
		{
			break ;
		}
		
//test_print_vector(ray_vector);
//ray_vector = geom_init_vector(begin, end);
//paint_draw_vector(painting, ray_vector, COLOR_PLAYER);

//sleep(1); 
	}
		
	ray_vector = geom_init_vector(begin, end);
	if (ray_vector)
		return (ray_vector);
	geom_destroy_point(begin);
	geom_destroy_point(end);
	return (NULL);
}

void	paint_print_ray(t_painting *painting)
{
	t_ray		*ray_info;
	static t_vector	*ray_vector = NULL;
	static t_vector	*ray_vector_prev = NULL;

	if (!painting)
		return ;
	ray_info = paint_get_ray_info(painting);
	if (!ray_info)
		return ;
	ray_vector = paint_get_ray_vector(painting, ray_info);
	if (!ray_vector)
	{
		paint_destroy_ray_info(ray_info);
		return ;	
	}
	paint_erase_vector(painting, ray_vector_prev);
	paint_draw_vector(painting, ray_vector);
	ray_vector_prev = ray_vector;
	paint_destroy_ray_info(ray_info);
}
