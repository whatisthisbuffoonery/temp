set number
set title
set showcmd
set wrap
set autoindent
filetype indent on
set shiftwidth=4
set tabstop=4
let &t_SI = "\e[6 q"  " Insert mode: solid vertical bar
let &t_SR = "\e[6 q"  " Replace mode: solid vertical bar
let &t_EI = "\e[6 q"  " Normal mode: solid vertical bar
if has("autocmd")
  au BufReadPost * 
        \ if line("'\"") > 1 && line("'\"") <= line("$") | 
        \   execute "normal! g`\"" | 
        \ endif
endif

