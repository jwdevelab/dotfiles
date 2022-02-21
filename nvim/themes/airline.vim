" Switch to your current theme
let g:airline_theme='gruvbox_material'

" enable tabline
let g:airline#extensions#tabline#enabled = 1
let g:airline#extensions#tabline#left_sep = ''
let g:airline#extensions#tabline#left_alt_sep = ''
let g:airline#extensions#tabline#right_sep = ''
let g:airline#extensions#tabline#right_alt_sep = ''
let g:airline#extensions#tabline#enabled = 0
set showtabline=0

" enable powerline fonts
let g:airline_powerline_fonts = 1
let g:airline_left_sep = ''
let g:airline_right_sep = ''

" Always show tabs

" We don't need to see things like -- INSERT -- anymore
set noshowmode


"Disable vim-airline integration:
let g:airline#extensions#coc#enabled = 1

"Change error symbol:
let airline#extensions#coc#error_symbol = 'Error:'

"Change warning symbol:
let airline#extensions#coc#warning_symbol = 'Warning:'

"Change error format:
let airline#extensions#coc#stl_format_err = '%E{[%e(#%fe)]}'

"Change warning format:
let airline#extensions#coc#stl_format_warn = '%W{[%w(#%fw)]}'

