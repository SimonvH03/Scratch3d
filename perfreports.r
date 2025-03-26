> perf record -g ./cub3d scenes/cub/test.cub
> perf report --no-children

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
{
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
}

##################### STILL 1Minute test.cub[E] ###########27.02.2025_0########

- 42.74%	cub3d							[.] __memmove_avx_unaligned_erms
	- 42.52% __memmove_avx_unaligned_erms
		- 29.37% 0x75916e79f8da
			mlx_render_images
			mlx_loop
			main
		- % 0x75916e10bed4
			mlx_render_images
			mlx_loop
			main
- 19.79%	cub3d							[.] draw_texture_column
	18.71% draw_texture_column
	0.96% raycast
- 13.37%	cub3d							[.] reset_image
	- 13.36% reset_image
		13.35% 0x3f80000000000000
- 7.54%	cub3d								[.] sample_wall
	7.15% sample_wall
- 1.62%	cub3d								[.] update_minimap
	1.59% update_minimap
		0x3f80000000000000
- 1.18%	cub3d								[.] image_iteration
	1.10% sample_wall
- 0.99%	cub3d								[.] raycast
	0.90% draw_texture_column

##################### STILL 1Minute test.cub[E] ###########27.02.2025_1########

- 43.38%	cub3d							[.] __memmove_avx_unaligned_erms
	- 43.10% __memmove_avx_unaligned_erms
		- 29.92% 0x75916e79f8da
			mlx_render_images
			mlx_loop
			main
		- 13.18% 0x75916e10bed4
			mlx_render_images
			mlx_loop
			main
- 19.76%	cub3d							[.] draw_texture_column
	18.36% draw_texture_column
	1.35% raycast
- 12.82%	cub3d							[.] reset_image
	- 12.80% reset_image
		12.80% 0x3f80000000000000
- 7.67%	cub3d								[.] sample_wall
	7.28% sample_wall
- 1.62%	cub3d								[.] update_minimap
	1.61% update_minimap
		0x3f80000000000000
- 1.27%	cub3d								[.] image_iteration
	1.18% sample_wall
- 1.01%	cub3d								[.] raycast
	0.88% draw_texture_column

##################### STILL 1Minute test.cub[E] ###########27.02.2025_2########

- 42.77%	cub3d							[.] __memmove_avx_unaligned_erms
	- 42.55% __memmove_avx_unaligned_erms
		- 31.76% 0x75916e79f8da
			mlx_render_images
			mlx_loop
			main
		- 10.80% 0x75916e10bed4
			mlx_render_images
			mlx_loop
			main
- 20.25%	cub3d							[.] draw_texture_column
	19.15% draw_texture_column
	0.97% raycast
- 12.82%	cub3d							[.] reset_image
	- 12.80% reset_image
		12.80% 0x3f80000000000000
- 7.62%	cub3d								[.] sample_wall
	7.25% sample_wall
- 1.69%	cub3d								[.] update_minimap
	1.69% update_minimap
		0x3f80000000000000
- 1.28%	cub3d								[.] image_iteration
	1.21% sample_wall
- 0.99%	cub3d								[.] raycast
	0.89% draw_texture_column

##################### STILL 1Minute test.cub[E] ###########27.02.2025_3########
# reset_image() set full pixel to 0, not only A component ((uint8_t *)dest)[3]
# performance equivalent to using ft_bzero() on pixelbuffer
- 43.61%	cub3d							[.] __memmove_avx_unaligned_erms
	- 43.45% __memmove_avx_unaligned_erms
		- 32.71% 0x75916e79f8da
			mlx_render_images
			mlx_loop
			main
		- 10.74% 0x75916e10bed4
			mlx_render_images
			mlx_loop
			main
- 20.98%	cub3d							[.] draw_texture_column
	19.78% draw_texture_column
	1.05% raycast
- 10.43%	cub3d							[.] reset_image
	- 10.39% reset_image
		10.30% 0x3f80000000000000
- 8.22%	cub3d								[.] sample_wall
	7.83% sample_wall
- 1.88%	cub3d								[.] update_minimap
	1.88% update_minimap
		0x3f80000000000000
- 1.39%	cub3d								[.] image_iteration
	1.31% sample_wall
- 1.05%	cub3d								[.] raycast
	0.92% draw_texture_column