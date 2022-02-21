# Defined in - @ line 1
function nconf --wraps='cd ~/.config/nvim' --description 'alias nconf cd ~/.config/nvim'
  cd ~/.config/nvim $argv;
end
