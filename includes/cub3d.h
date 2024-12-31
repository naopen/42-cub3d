/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:05:30 by nkannan           #+#    #+#             */
/*   Updated: 2024/12/31 21:14:47 by nkannan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
// miniLibX (パスは環境に合わせて)
# include "mlx.h"

// ---- 定数・マクロ ----
# define WIN_WIDTH 800
# define WIN_HEIGHT 600

# define KEY_ESC 53 // macOS例: ESC
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124

// ---- 構造体 定義例 ----

// テクスチャなどの設定を保持
typedef struct s_texture
{
	void		*img;
	int			*addr;
	int			width;
	int			height;
	int			bpp;
	int			line_length;
	int			endian;
}				t_texture;

// マップやプレイヤー情報
typedef struct s_map
{
	char **grid; // 2次元マップ (0,1,N,S,E,W)
	int			width;
	int			height;
}				t_map;

// プレイヤーやレイキャストに必要な情報
typedef struct s_player
{
	double x; // 座標 (マップ上)
	double		y;
	double dir_x; // 向き (ベクトル)
	double		dir_y;
	double plane_x; // カメラ平面のベクトル
	double		plane_y;
	double		move_speed;
	double		rot_speed;
}				t_player;

// 色情報
typedef struct s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

// 全体管理構造体
typedef struct s_game
{
	void		*mlx;
	void		*win;

	t_map		map;
	t_player	player;

	// テクスチャ (N, S, E, W) のパスや読み込んだ画像
	t_texture	tex_n;
	t_texture	tex_s;
	t_texture	tex_e;
	t_texture	tex_w;

	// 床と天井の色
	t_color		floor_color;
	t_color		ceiling_color;

	// バッファ描画用イメージ
	void		*img;
	int			*addr;
	int			bpp;
	int			line_len;
	int			endian;

	// mlx 関連のエラーが発生したかどうかを示すフラグ
	int			mlx_error;

}				t_game;

// ---- 関数プロトタイプ ----

// parse_config.c
int				parse_config(t_game *game, const char *cub_file);
// parse_map.c
int				parse_map(t_game *game);
// init.c
int				init_game(t_game *game);
// hooks.c
int				key_press(int keycode, t_game *game);
int				close_window(t_game *game);
// raycast.c
void			render_frame(t_game *game);
// draw.c
void			draw_background(t_game *game);
void			draw_walls(t_game *game);
// utils.c
void			put_pixel(t_game *game, int x, int y, int color);
int				create_trgb(int t, int r, int g, int b);

#endif