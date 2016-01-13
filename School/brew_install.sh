#!/bin/sh

rm -rf ~/.brew && mkdir ~/.brew && curl -L https://github.com/Homebrew/homebrew/tarball/master | tar xz --strip 1 -C ~/.brew && mkdir -p ~/Library/Caches/Homebrew
export PATH="$HOME/.brew/bin:$PATH" >> ~/.zshrc
brew install valgrind
