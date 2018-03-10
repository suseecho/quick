set number
set relativenumber
set hlsearch
set ts=4
set ai
"set cindent
set history=100
set showcmd
filetype off
set rtp+=~/.vim/bundle/vundle/
call vundle#rc()
Bundle 'The-NERD-tree'
Bundle 'taglist.vim'
Bundle 'SrcExpl'

set tags=/home/echo/src/linux-2.6.30.4/tags
set csprg=/usr/bin/cscope
set csto=0
set cst
set nocsverb
cs add /home/echo/src/linux-2.6.30.4/cscope.out	/home/echo/src/linux-2.6.30.4
set csverb


"Tap List 环境设置
"--------------------------------------------------"
filetype on
nmap <F7> :TlistToggle<CR>
let Tlist_Ctags_Cmd = "/usr/bin/ctags"
let Tlist_Inc_Winwidth = 0
let Tlist_Exit_OnlyWindow = 0
let Tlist_Auto_Open = 0
let Tlist_Use_Right_Window = 1
"--------------------------------------------------"
"Source Explorer 环境设置
"--------------------------------------------------"
nmap <F8> :SrcExplToggle<CR>
nmap <C-H> <C-W>h
nmap <C-J> <C-W>j
nmap <C-K> <C-W>k
nmap <C-L> <C-W>l
let g:SrcExpl_winHeight = 8
let g:SrcExpl_refreshTime = 100
let g:SrcExpl_jumpKey = "<ENTER>"
let g:SrcExpl_gobackKey = "<SPACE>"
let g:SrcExpl_isUpdateTags = 0
"--------------------------------------------------"
"NERD Tree 环境设置
"--------------------------------------------------"
let NERDTreeWinPos = "left"
nmap <F9> :NERDTreeToggle<CR>
