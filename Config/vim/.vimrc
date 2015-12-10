let $USER = 'tdefresn'
let $MAIL = $USER . '@student.42.fr'

syn on
set nu

filetype plugin indent on
inoremap ( ()<Esc>i
inoremap { {}<Esc>i
set ruler

"set filetype	=c
"let c_space_errors = 1

set colorcolumn	=80
highlight ColorColumn ctermbg=grey guibg=grey
highlight LineNr ctermfg=red ctermbg=DarkGrey guibg=#ffffff

highlight FtHeader ctermfg=yellow ctermbg=black guibg=black
highlight ExtraWhitespace ctermbg=red guibg=red
" highlight extra whitespace
match ExtraWhitespace /\(^\t*\ \+\| \_s\+\)/
" remove header highlighting
"2match FtHeader /\(\_^\/\*.*\)\{0,1\}\*\/\_s/
2match FtHeader /\(\_^\/\* .*\)\{0,1\}\n/

set backupdir	=~/.vim/.backup//,.,/tmp
set directory	=~/.vim/.swp//,.,/tmp
set undodir	=~/vim/.undo//,.,/tmp
