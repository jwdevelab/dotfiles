# Defined in - @ line 1
function mst --wraps='cd ~/.config/st & sudo make clean install' --description 'alias mst cd ~/.config/st & sudo make clean install'
  cd ~/.config/st & sudo make clean install $argv;
end
