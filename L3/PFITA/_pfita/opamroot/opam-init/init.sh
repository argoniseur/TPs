# Load the environment variables
. /home/dfl1826a/Github/TPs/L3/PFITA/_pfita/opamroot/opam-init/variables.sh > /dev/null 2> /dev/null || true

# Load the auto-complete scripts
if tty -s >/dev/null 2>&1; then
  . /home/dfl1826a/Github/TPs/L3/PFITA/_pfita/opamroot/opam-init/complete.sh > /dev/null 2> /dev/null || true
fi

# Load the opam-switch-eval script
if tty -s >/dev/null 2>&1; then
  . /home/dfl1826a/Github/TPs/L3/PFITA/_pfita/opamroot/opam-init/switch_eval.sh > /dev/null 2> /dev/null || true
fi

