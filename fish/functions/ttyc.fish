# Defined in - @ line 1
function ttyc --wraps='tty-clock -c -C 7 -b -D' --description 'alias ttyc tty-clock -c -C 7 -b -D'
  tty-clock -c -C 7 -b -D $argv;
end
