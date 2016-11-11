#!/bin/bash

## read more at
## https://jonlabelle.com/snippets/view/shell/mac-os-x-defaults

# `-g` and `NSGlobalDomain` are equivalent

# Disable "natural" scrolling
defaults -currentHost write -g com.apple.swipescrolldirection -bool false

# Set Initial key repeat to very fast -- settings minimum is 15 (225ms)
defaults write -g InitialKeyRepeat -int 10

# Set key repeat to very fast -- settings minimum is 2 (30ms)
defaults write -g KeyRepeat -int 4

# Set mouse speed to very fast (min: 1.0, max: 5.0)
defaults -currentHost write -g com.apple.mouse.scaling 1.0

# Require password immediatly after sleep or screen saver
defaults write com.apple.screensaver askForPassword -int 1
defaults write com.apple.screensaver askForPasswordDelay -int 0


###############################################################################
# Terminal                                                                    #
###############################################################################
 
# Only use UTF-8 in Terminal.app
#defaults write com.apple.terminal StringEncodings -array 4
 
# Use a modified version of the Pro theme by default in Terminal.app
#open "$HOME/init/Mathias.terminal"
#sleep 1 # Wait a bit "o make sure the theme is loaded
#defaults write com.apple.terminal "Default Window Settings" -string "Mathias"
#defaults write com.apple.terminal "Startup Wndow Settings" -string "Mathias"
 
# Enable "focus follows mouse" for Terminal.app and all X11 apps
# i.e. hover over a window and start typing in it without clicking first
#defaults write com.apple.terminal FocusFollowsMouse -bool true
#defaults write org.x.X11 wm_ffm -bool true
