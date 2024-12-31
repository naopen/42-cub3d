/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 21:11:37 by nkannan           #+#    #+#             */
/*   Updated: 2024/12/31 21:12:57 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	move_forward(t_game *game)
{
	double	nx;
	double	ny;

	nx = game->player.x + game->player.dir_x * game->player.move_speed;
	ny = game->player.y + game->player.dir_y * game->player.move_speed;
	// 壁衝突などをチェックしたければここでマップを確認し、1 でなければ進む
	if (game->map.grid[(int)ny][(int)nx] != '1')
	{
		game->player.x = nx;
		game->player.y = ny;
	}
}

static void	move_backward(t_game *game)
{
	double	nx;
	double	ny;

	nx = game->player.x - game->player.dir_x * game->player.move_speed;
	ny = game->player.y - game->player.dir_y * game->player.move_speed;
	if (game->map.grid[(int)ny][(int)nx] != '1')
	{
		game->player.x = nx;
		game->player.y = ny;
	}
}

static void	rotate_left(t_game *game)
{
	double	oldDirX;
	double	oldPlaneX;
	double	rot;

	oldDirX = game->player.dir_x;
	oldPlaneX = game->player.plane_x;
	rot = game->player.rot_speed;
	game->player.dir_x = game->player.dir_x * cos(rot) - game->player.dir_y
		* sin(rot);
	game->player.dir_y = oldDirX * sin(rot) + game->player.dir_y * cos(rot);
	game->player.plane_x = game->player.plane_x * cos(rot)
		- game->player.plane_y * sin(rot);
	game->player.plane_y = oldPlaneX * sin(rot) + game->player.plane_y
		* cos(rot);
}

static void	rotate_right(t_game *game)
{
	double	oldDirX;
	double	oldPlaneX;
	double	rot;

	oldDirX = game->player.dir_x;
	oldPlaneX = game->player.plane_x;
	rot = -game->player.rot_speed;
	game->player.dir_x = game->player.dir_x * cos(rot) - game->player.dir_y
		* sin(rot);
	game->player.dir_y = oldDirX * sin(rot) + game->player.dir_y * cos(rot);
	game->player.plane_x = game->player.plane_x * cos(rot)
		- game->player.plane_y * sin(rot);
	game->player.plane_y = oldPlaneX * sin(rot) + game->player.plane_y
		* cos(rot);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_window(game);
	else if (keycode == KEY_W)
		move_forward(game);
	else if (keycode == KEY_S)
		move_backward(game);
	else if (keycode == KEY_A)
	{
		// 斜め移動にしたり、ストレーフにしたり、自由に実装可能
	}
	else if (keycode == KEY_D)
	{
		// 斜め移動にしたり、ストレーフにしたり...
	}
	else if (keycode == KEY_LEFT)
		rotate_left(game);
	else if (keycode == KEY_RIGHT)
		rotate_right(game);
	return (0);
}

int	close_window(t_game *game)
{
	// 後処理 (mlx_destroy_window, free map, etc.)
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
	return (0);
}