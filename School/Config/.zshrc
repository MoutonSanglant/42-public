export SBCL_HOME="$HOME/.sbcl/lib/sbcl"
export PATH="$PATH:$HOME/.sbcl/bin"

echo "1" > ~/git/42/School/logs/$(hostname -s).txt

alias sbcl="sbcl --noinform"
alias sbcl.compile="$HOME/git/42/Rushes/carnifex/sbcl.compile"
alias sbcl.run="$HOME/git/42/Rushes/carnifex/sbcl.run"
alias valgrind=~/.brew/Cellar/valgrind/3.11.0/bin/valgrind
