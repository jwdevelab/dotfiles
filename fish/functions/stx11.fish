# Defined in - @ line 1
function stx11 --wraps='cd ~/.config/stx11 && sudo make clean install' --description 'alias stx11 cd ~/.config/stx11 && sudo make clean install'
  cd ~/.config/stx11 && sudo make clean install $argv;
end
