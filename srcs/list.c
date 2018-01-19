#include <filler.h>

int	create_point(t_p **points, int x, int y)
{
	t_p *tmp;

	if (!(*points))
	{
		if (!(*points = (t_p *)malloc(sizeof(t_p))))
			return (0);
		tmp = *points;
	}
	else
	{
		tmp = *points;
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = (t_p *)malloc(sizeof(t_p))))
			return (0);
		tmp = tmp->next;
	}
	tmp->x = x;
	tmp->y = y;
	tmp->distance = -1;
	tmp->next = NULL;
	return (1);
}

int		us_between(t_d *data, t_p *us, t_p *enemy)
{
	int	x;
	int	y;
	int maxx;
	int maxy;

	if (us->x != enemy->x && us->y != enemy->y)
	{
		dprintf(data->debug_fd, "non standard position in us_between. returning 0 from %d-%d an %d-%d\n", us->x, us->y, enemy->x, enemy->y);
		return (0);
	}
	x = us->x < enemy->x ? us->x : enemy->x;
	y = us->y < enemy->y ? us->y : enemy->y;
	maxx = us->x > enemy->x ? us->x : enemy->x;
	maxy = us->y > enemy->y ? us->y : enemy->y;
	while (x < maxx || y < maxy)
	{
		if (data->board[x][y] == data->us_max)
		{
			dprintf(data->debug_fd, "Our piece was found between %d-%d and %d-%d\n", us->x, us->y, enemy->x, enemy->y);
			return (1);
		}
		if (x < maxx)
			x++;
		if (y < maxy)
			y++;
	}
	dprintf(data->debug_fd, "no point found in us_between. returning 0 from %d-%d an %d-%d\n", us->x, us->y, enemy->x, enemy->y);
	return (0);
}

int		diagonal_piece(t_d *data, t_p *point, t_p *enemy)
{
	int x;
	int y;
}

int		calculate_distance
(t_d *data, t_p *point)
{
	int	min;
	t_p	*tmp;

	tmp = data->enemy_points;
	min = -1;
	while (tmp)
	{
		if (min == -1 || (point->x - tmp->x) * (point->x - tmp->x) + (point->y - tmp->y) * (point->y - tmp->y) < min)
		{
			min = (point->x - tmp->x) * (point->x - tmp->x) + (point->y - tmp->y) * (point->y - tmp->y);
			if (us_between(data, point, tmp))
				min += 100;
				min *= min;
		}
		tmp = tmp->next;
	}
	return (min);
}
