let $USER = 'tdefresn'
let $MAIL = $USER . '@student.42.fr'

syn on
set nu

filetype plugin indent on
inoremap ( () <Esc>i
inoremap { {} <Esc>i
set ruler

highlight ExtraWhitespace ctermbg=red guibg=red
match ExtraWhitespace / \( \|\n\)/

set backupdir=~/.vim/.backup//,.,/tmp
set directory=~/.vim/.swp//,.,/tmp
set undodir=~/vim/.undo//,.,/tmp
