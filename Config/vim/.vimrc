let $USER = 'tdefresn'
let $MAIL = $USER . '@student.42.fr'

syn on
set nu

function g:MatchCursorCharacter (c, bs)
	let l:tt = col('.') + 1
	let l:test = matchstr(getline('.'), '\%' . l:tt . 'c.') == a:c
	if l:test
		if a:bs == '1'
			call feedkeys("\<Backspace>\<Right>")
		endif
		call feedkeys("\<Del>")
	endif
endfunction

filetype plugin indent on
inoremap ( ()<Esc>i
inoremap ) <Esc>:call g:MatchCursorCharacter(')', '0')<CR>i<Right>)
inoremap { {}<Esc>i
inoremap } <Esc>:call g:MatchCursorCharacter('}', '0')<CR>i<Right>}
inoremap [ []<Esc>i
inoremap ] <Esc>:call g:MatchCursorCharacter(']', '0')<CR>i<Right>]
inoremap " <Esc>:call g:MatchCursorCharacter('"', '1')<CR>i<Right>""<Left>
inoremap ' <Esc>:call g:MatchCursorCharacter("'", '1')<CR>i<Right>''<Left>
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
