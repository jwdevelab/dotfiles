function update --wraps='sudo pacman -Syy' --description 'alias update sudo pacman -Syy'
  sudo pacman -Syy $argv; 
end
