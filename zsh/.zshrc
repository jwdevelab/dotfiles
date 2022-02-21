# Enable Powerlevel10k instant prompt. Should stay close to the top of ~/.config/zsh/.zshrc.
# Initialization code that may require console input (password prompts, [y/n]
# confirmations, etc.) must go above this block; everything else may go below.
neofetch

if [[ -r "${XDG_CONFIG_HOME:-$HOME/.config}/zi/init.zsh" ]]; then
  source "${XDG_CONFIG_HOME:-$HOME/.config}/zi/init.zsh" && zzinit
fi

if [[ -r "${XDG_CACHE_HOME:-$HOME/.cache}/p10k-instant-prompt-${(%):-%n}.zsh" ]]; then
  source "${XDG_CACHE_HOME:-$HOME/.cache}/p10k-instant-prompt-${(%):-%n}.zsh"
fi

if [[ ! -f $HOME/.config/zsh/.zi/bin/zi.zsh ]]; then
  print -P "%F{33}▓▒░ %F{160}Installing (%F{33}z-shell/zi%F{160})…%f"
  command mkdir -p "$HOME/.config/zsh/.zi" && command chmod g-rwX "$HOME/.config/zsh/.zi"
  command git clone -q --depth=1 --branch "main" https://github.com/z-shell/zi "$HOME/.config/zsh/.zi/bin" && \
    print -P "%F{33}▓▒░ %F{34}Installation successful.%f%b" || \
    print -P "%F{160}▓▒░ The clone has failed.%f%b"
fi
source "$HOME/.config/zsh/.zi/bin/zi.zsh"
autoload -Uz _zi
(( ${+_comps} )) && _comps[zi]=_zi

zi light-mode for OMZL::git.zsh OMZL::completion.zsh \
    OMZL::compfix.zsh OMZL::prompt_info_functions.zsh \
    OMZL::spectrum.zsh OMZL::clipboard.zsh OMZL::functions.zsh \
    OMZL::termsupport.zsh OMZL::directories.zsh

zi light-mode for \
    OMZP::sudo OMZP::encode64 atload"unalias grv g" OMZP::git OMZP::extract

zi light-mode for z-shell/z-a-meta-plugins @annexes \
    skip'fzy' @fuzzy skip'tig' @console-tools skip'F-Sy-H' @z-shell

zi light-mode for \
    birdhackor/zsh-exa-ls-plugin \
    MichaelAquilina/zsh-you-should-use @zsh-users+fast @romkatv

zicompinit

# To customize prompt, run `p10k configure` or edit ~/.config/zsh/.p10k.zsh.
[[ ! -f ~/.config/zsh/.p10k.zsh ]] || source ~/.config/zsh/.p10k.zsh

alias s="source ~/.zshrc"
alias v="nvim"
alias :q="exit"
alias ç="ranger"
alias mdwm="cd ~/.config/dwm & sudo make clean install"
alias ttyc="tty-clock -c -C 7 -b -D"

bindkey    '\e^?' backward-delete-word

typeset -g HISTSIZE=290000 SAVEHIST=290000 HISTFILE=~/.zhistory
