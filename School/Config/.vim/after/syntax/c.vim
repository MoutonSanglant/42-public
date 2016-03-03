syn keyword MyTypes t_mask t_vert t_vec2 t_vec2f t_vec2ui32 t_vec3 t_vec3f t_vec4f t_mat4x4 t_tri
syn keyword GNLTypes t_parser
syn keyword MLXTypes t_mlx_sess t_image t_color
syn keyword FDFTypes t_camera t_grid t_bresenham
highlight MyTypes ctermfg=yellow
highlight GNLTypes ctermfg=yellow
highlight MLXTypes ctermfg=yellow
highlight FDFTypes ctermfg=yellow

syn keyword ForbidenFunc malloc free opendir readdir closedir stat lstat getpwuid getgrgid listxattr getxattr time ctime readlink open close read write perror stderror exit printf
highlight ForbidenFunc ctermfg=white ctermbg=red
