function unins --wraps='sudo pacman -Rns' --description 'alias unins sudo pacman -Rns'
  sudo pacman -Rns $argv; 
end
