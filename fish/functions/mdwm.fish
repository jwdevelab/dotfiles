# Defined in - @ line 1
function mdwm --wraps='cd ~/.config/dwm & sudo make clean install' --description 'alias mdwm cd ~/.config/dwm & sudo make clean install'
  cd ~/.config/dwm & sudo make clean install $argv;
end
