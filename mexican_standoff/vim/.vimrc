filetype plugin indent on
inoremap ( () <Esc>i
inoremap { {} <Esc>i
set ruler

highlight ExtraWhitespace ctermbg=red guibg=red
match ExtraWhitespace /\s(\s\|\n\)/

set backupdir=~/.vim/.backup//,.,/tmp
set directory=~/.vim/.swp//,.,/tmp
set undodir=~/vim/.undo//,.,/tmp
