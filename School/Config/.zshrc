# Log tracker
echo "1" > ~/git42/School/logs/$(hostname -s).txt

# Node
NPM_PACKAGES="${HOME}/.npm-packages"
export PATH="${HOME}/.brew/bin:$NPM_PACKAGES/bin:$PATH"
unset MANPATH # delete if you already modified MANPATH elsewhere" in your config
export MANPATH="$NPM_PACKAGES/share/man:$(manpath)"

# Set Homebrew cache
export HOMEBREW_CACHE=${HOME}/Library/Caches/Homebrew
export PATH=$PATH:"${HOME}/.brew/opt/go/libexec/bin"

# Go
# export GOPATH="${HOME}/go"

# SBCL
export SBCL_HOME="$HOME/.sbcl/lib/sbcl"
export PATH="$PATH:$HOME/.sbcl/bin"

alias sbcl="sbcl --noinform"
alias sbcl.compile="$HOME/git/42/Rushes/carnifex/sbcl.compile"
alias sbcl.run="$HOME/git/42/Rushes/carnifex/sbcl.run"
