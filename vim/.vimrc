" don't load the match-paren plugin
let loaded_matchparen = 1

" use the nocompatible mode
set nocompatible

" backspace behavior
set backspace=indent,eol,start

" keep backup files, and where to store them
set backup
set backupdir=c:/Users/philip/vimbackup

" tabs and indentation settings
set expandtab
set tabstop=4
set shiftwidth=4
set softtabstop=4
set autoindent

set ruler
set showcmd
set incsearch
syntax on
set hlsearch
set fileformats=unix,dos
set history=50	" keep 50 lines of command line history
set switchbuf=useopen
set clipboard=unnamed
set laststatus=2
set statusline=%f\ %(%w%h%m%r%)%=byte=0x%B,\ row=%l,\ col=%v\ \ \ 
let g:netrw_sort_sequence='[\/]$,\.\(h\|c\|cpp\)$,*,^\.'
let g:netrw_mousemaps=0
set selectmode=

set runtimepath^=c:\code\vim

" use the tab completion menu and only complete as much as necessary
set wildmenu
set wildmode=longest:full

" mappings for moving through windows
map ; <C-w>_
map w <C-w>w;
map W <C-w>W;
map c :q<CR>;

" I like to just press r to redo
map r <C-r>

" this makes the arrow keys act more reasonably on wrapped lines
noremap <Up> g<Up>
noremap <Down> g<Down>
imap <Up> <C-o>g<Up>
imap <Down> <C-o>g<Down>

" moving between tabs
map <Tab> gt
map <S-Tab> gT
map <Backspace> gT

" pasting
vnoremap p p:let @"=@0<CR>

" Here we make a nice way to compile and step through the errors
set shellpipe=2>&1\ \\|\ tee\ %s

" iterate through tags with just t and T
map e :call NextError()<CR>
map E :call PreviousError()<CR>
map <C-z> :call ReloadErrors()<CR>:copen<CR>;G
map t :tn<CR>
map T :tp<CR>

map F :call SplitToFileDirectory()<CR>;
map <C-S-f> :call TabSplitToFileDirectory()<CR>

map <F4> :call OpenErrorAndPreview()<CR>
map g<F7> :call CompileResults()<CR>
map gc :call LastCompileResults()<CR>
map gC :call NextCompileResults()<CR>
map g<S-F7> :call ResetCompile()<CR>

map <F7> :call Compile("", "-s LIBPHIL_TARGETPLAT=\"winvs\"")<CR>
map <M-F7> :call Compile("", "-s LIBPHIL_TARGETPLAT=\"wingcc\"")<CR>

"" ================================================================================================
"" Global variable initializations
"" ================================================================================================
if has('python')
    function! InitGlobal(varname, value)
        if !exists(a:varname)
python << END_OF_PYTHON
import vim, string
varname = vim.eval('a:varname')
value = vim.eval('a:value')
value = string.replace(value, "\\", "\\\\")
cmd = 'let %(varname)s = %(value)s' % { 'varname':varname, 'value':value }
vim.command(cmd)
END_OF_PYTHON
        endif
    endfunction

    call InitGlobal("g:initialized", 0)
    call InitGlobal("g:errornum", -1)
    call InitGlobal("g:errorswrap", 1)
    call InitGlobal("g:errorheight", 5)
    call InitGlobal("g:compileminimized", 0)
    call InitGlobal("g:temppath", "\"" . expand("~") . "\\Local Settings\\Temp\"")
endif

"" ================================================================================================
"" Instead of the default vim behavior of editing one argument at a time, I'll just split
"" them all into different windows
"" ================================================================================================
function! OpenArgsInWindows()
    let c = argc()
    let i = 0
    while i < c
        if i > 0
            sp
        endif
        silent execute "argument! " . (i + 1)
        let i = i + 1
    endwhile
endfunction

if g:initialized != 1
    let g:initialized = 1
    if argc() == 0
        cd $LIBPHIL_BASEDIR/src
    else
        call OpenArgsInWindows()
        execute "normal! \<C-w>W\<C-w>_"
    endif
endif

"" ================================================================================================
"" Basic window / tab utilities
"" ================================================================================================
function! SplitToFileDirectory()
    let dir = expand("%:h")
    if(dir == "")
        let dir = "."
    endif
    silent execute 'sp ' . dir
endfunction

function! TabSplitToFileDirectory()
    let dir = expand("%:h")
    if(dir == "")
        let dir = "."
    endif
    silent execute 'tabe ' . dir
endfunction

"" ================================================================================================
"" Make sure the preview window and error window are ready, and the errorformat is set correctly
"" ================================================================================================
function! OpenErrorAndPreview()
    tabfirst
    copen
    if(g:errorswrap)
        set wrap
    endif
    pclose
    execute "pedit " . g:temppath . "\\new"
    execute "normal! \<C-w>P"
    enew
    execute "normal! \<C-w>_"
endfunction

"" ================================================================================================
"" Sets the errorformat for compiling
"" ================================================================================================
function! SetErrorFormat()
    set errorformat=

    " Normal windows compile error (note : %*\\D matches any number of non-digits)
    set errorformat+=%f(%l)\ :\ %t%*\\D%n:\ %m
    " Indented windows error (for lines like file.h(line) : See definition ...
    set errorformat+=%*[\ ]%f(%l)\ :\ %m

    " Windows link error
    set errorformat+=%+E%*\\S\ :\ %trror%*\\D%n:\ %m
    " Windows link warning
    set errorformat+=%*\\S\ :\ %tarning%*\\D%n:\ %m

    " link error
    set errorformat+=LINK\ :\ fatal\ %trror\ LNK%n:\ %m

    " gcc errors
    set errorformat +=%f:%l:\ %trror:\ %m
    " gcc warnings
    set errorformat +=%f:%l:\ %tarning:\ %m
endfunction

"" ================================================================================================
"" Stepping through errors
"" ================================================================================================
function! ReloadErrors()
    tabfirst
    silent exec "cgetfile " . g:errorfile
endfunction

function! SetErrorHeight(h)
    copen
    execute "resize " . a:h
    execute "normal! \<C-w>p"
endfunction

function! NextErrorNoReload()
    execute "normal! \<C-w>P"
    try
        cr
        if(g:errornum > 0)
            execute "normal! \<C-w>P"
            execute g:errornum . "cn"
        endif
    catch /^Vim\%((\a\+)\)\=:E42/      " No errors
    catch /^Vim\%((\a\+)\)\=:E553/     " No more errors
    endtry

    execute "normal! \<C-w>P"
    try
        cn
        let g:errornum = g:errornum + 1
    catch /^Vim\%((\a\+)\)\=:E42/      " No errors
    catch /^Vim\%((\a\+)\)\=:E553/     " No more errors
        execute "normal! \<C-w>p"
    endtry
    execute "normal! \<C-w>_"
    call SetErrorHeight(g:errorheight)
endfunction

" display the previous error
function! PreviousErrorNoReload()
    execute "normal! \<C-w>P"
    try
        cr
        execute "normal! \<C-w>P"
        execute g:errornum . "cn"
    catch /^Vim\%((\a\+)\)\=:E42/      " No errors
    catch /^Vim\%((\a\+)\)\=:E553/     " No more errors
    endtry

    if(g:errornum <= 1)
        return
    endif

    execute "normal! \<C-w>P"
    try
        cp
        let g:errornum = g:errornum - 1
    catch /^Vim\%((\a\+)\)\=:E42/      " No errors
    catch /^Vim\%((\a\+)\)\=:E553/     " No more errors
        let g:errornum = 1
        execute "normal! \<C-w>p"
    endtry
    execute "normal! \<C-w>_"
    call SetErrorHeight(g:errorheight)
endfunction

" display the next error
function! NextError()
    call ReloadErrors()
    call NextErrorNoReload()
endfunction

" display the previous error
function! PreviousError()
    call ReloadErrors()
    call PreviousErrorNoReload()
endfunction

"" ================================================================================================
"" Quickfix file management
"" ================================================================================================
function! NewQuickfixFile(type)
    let g:errorfile = g:temppath . "\\libphil." . localtime() . "." . a:type . ".output"

    if !exists("g:lasterrorfile_{a:type}_count")
        let g:lasterrorfile_{a:type}_count = 0
    endif

    let i = g:lasterrorfile_{a:type}_count
    while i > 0
        let g:lasterrorfile_{a:type}_{i} = g:lasterrorfile_{a:type}_{i-1}
        let i = i - 1
    endwhile

    let g:lasterrorfile_{a:type}_{0} = g:errorfile
    let g:lasterrorfile_{a:type}_count = g:lasterrorfile_{a:type}_count + 1
    let g:errornum = 0
endfunction

function! LastQuickfixFile(type, index)
    if !exists("g:lasterrorfile_{a:type}_count")
        echo 'Invalid quickfix type'
        return
    endif

    if a:index >= g:lasterrorfile_{a:type}_count
        echo 'Invalid quickfix index'
        return
    endif

    let g:errorfile = g:lasterrorfile_{a:type}_{a:index}
    let g:errornum = 0
    call ReloadErrors()
endfunction

function! ResetQuickfixType(type)
    let g:lasterrorfile_{a:type}_count = 0
endfunction

function! QuickfixTypeCount(type)
    if !exists("g:lasterrorfile_{a:type}_count")
        return 0
    else
        return g:lasterrorfile_{a:type}_count
    endif
endfunction

"" ================================================================================================
"" For saving and reloading tabs
"" ================================================================================================
let g:savetab = 1
function! SaveTab()
    let g:savetab = tabpagenr()
endfunction

function! LoadTab()
    silent execute 'tabn ' . g:savetab
endfunction

"" ================================================================================================
"" Compile the given directory with the given project base
"" ================================================================================================
let g:compileidx = 0
function! Compile(dir, torun)
    " reset quickfix indices
    let g:compileidx = 0

    " save the tab we're in, and move to the first tab for all compile tasks
    call SaveTab()
    tabfirst

    let winnumber = winnr()
    call OpenErrorAndPreview()
    call SetErrorFormat()
    call NewQuickfixFile("compile")

    " clear the error file, so that we don't see old errors
    execute "normal! \<C-w>P"
    silent exec "w! " . g:errorfile
    enew

    let mkcmd = "!start "
    if(g:compileminimized)
        let mkcmd = mkcmd . "/min "
    endif
    let mkcmd = mkcmd . "cmd.exe /c cd c:/code/src/" . a:dir . " && build.bat " . a:torun
    let mkcmd = mkcmd . " 2>&1 | sed -u 's/\\r//' | tee \"" . g:errorfile . "\""
    silent execute mkcmd
    silent exec "cf " . g:errorfile
    let g:errornum = 0

    " Get focus back, and go back to the original window
    call foreground()
    silent execute "normal! " . winnumber . "\<C-w>w\<C-w>_"
    call LoadTab()
endfunction

"" ================================================================================================
"" Dealing with the quickfix list of compile error buffers
"" ================================================================================================
function! LastCompile(index)
    call SetErrorFormat()
    call LastQuickfixFile("compile", a:index)
endfunction

function! ResetCompile()
    let g:compileidx = 0
    call ResetQuickfixType("compile")
endfunction

function! CompileCount()
    return QuickfixTypeCount("compile")
endfunction

function! CompileResults()
    call SaveTab()
    call LastCompile(g:compileidx)
    call LoadTab()
endfunction

function! NextCompileResults()
    if g:compileidx <= 0
        let g:compileidx = 0
    else
        let g:compileidx = g:compileidx - 1
    endif
    call CompileResults()
endfunction

function! LastCompileResults()
    let compilecount = CompileCount()
    if compilecount <= 0
        echo 'No compiles available'
        return
    endif

    let g:compileidx = g:compileidx + 1
    if g:compileidx >= compilecount
        let g:compileidx = compilecount - 1
    endif
    call CompileResults()
endfunction

