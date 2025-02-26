##################### STILL 1Minute test.cub[E] ###########26.02.2025##########
- 43.80%	cub3d							[.] __memmove_avx_unaligned_erms
	- 43.58% __memmove_avx_unaligned_erms
		- 32.36% 0x7bb7f752264b
			mlx_render_images
			mlx_loop
			main
		- 11.21% 0x7bb7f6e84314
			mlx_render_images
			mlx_loop
			main
- 19.47%	cub3d							[.] draw_texture_column
	18.41% draw_texture_column
	0.90% raycast
- 12.74%	cub3d							[.] reset_image
	12.72% reset_image
	0x3f80000000000000
- 7.70%		cub3d							[.] sample_wall
	7.36% sample_wall
- 1.67%		cub3d							[.] update_minimap
	1.66% update_minimap
	0x3f80000000000000
- 1.31%		cub3d							[.] image_iteration
	1.23% sample_wall
- 1.00%		cub3d							[.] raycast
	0.90% draw_texture_column
	0.42%	cub3d							[.] unfilterScanline
	0.36%	cub3d							[.] lodepng_memcpy
	0.29%	cub3d							[.] lodepng_memset
	0.24%	cub3d							[.] update_adler32
	0.11%	cub3d							[.] __memset_avx2_unaligned_erms
	0.10%	cub3d							[.] __memset_avx2_unaligned_erms
	0.10%	cub3d							[.] ft_abs_float
	0.10%	cub3d							[.] ft_sign_float
	0.04%	cub3d							[.] sample_bigmap
	0.03%	cub3d							[.] mlx_put_pixel
	0.02%	cub3d							[.] sample_scalable
	0.01%	cub3d							[.] draw_scene_background
	0.01%	cub3d							[.] frametime_dependant_variables
	0.01%	cub3d							[.] modlx_put_string
	0.01%	cub3d							[.] mlx_draw_pixel
	0.01%	cub3d							[.] ft_memcpy
	0.01%	cub3d							[.] arrowkey_turn
	0.01%	cub3d							[.] mlx_is_key_down
	0.01%	cub3d							[.] mlx_exec_loop_hooks
	0.00%	cub3d							[.] sample_overlay
	0.00%	cub3d							[.] view_manager
	0.00%	cub3d							[.] wasd_move

###############################################################################