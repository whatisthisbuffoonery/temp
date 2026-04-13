"source $VIMRUNTIME/defaults.vim
set autoindent
filetype indent on
set tabstop=4
set shiftwidth=4
set noexpandtab
set number
set wildmenu
set showcmd
"set showmatch
set ignorecase
set smartcase
set incsearch
"set mouse=a
set title
set wrap
set hlsearch
let &t_SI = "\e[6 q" "insert
let &t_SR = "\e[6 q" "replace
let &t_EI = "\e[6 q" "normal
if has("autocmd")
	au BufReadPost *
				\	if line("'\"") > 1 && line("'\"") <= line("$") |
				\		execute "normal g`\"" |
				\	endif
endif
