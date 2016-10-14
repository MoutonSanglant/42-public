#!/bin/sh

rm -rf ~/.brew && mkdir ~/.brew && curl -L https://github.com/Homebrew/homebrew/tarball/master | tar xz --strip 1 -C ~/.brew && mkdir -p ~/Library/Caches/Homebrew

source ~/.zshrc

brew update
brew install valgrind
#brew install node

alias valgrind="~/.brew/bin/valgrind"
