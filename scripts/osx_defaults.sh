#!/bin/bash

## read more at
## https://jonlabelle.com/snippets/view/shell/mac-os-x-defaults

# `-g` and `NSGlobalDomain` are equivalent

#osascript -e "tell application \"System Preferences\" to quit"

# Disable "natural" scrolling
defaults write -g com.apple.swipescrolldirection -bool false
defaults -currentHost write -g com.apple.swipescrolldirection -bool false

# Set Initial key repeat to very fast -- settings minimum is 15 (225ms)
defaults write -g InitialKeyRepeat -int 95
defaults -currentHost write -g InitialKeyRepeat -int 95

# Set key repeat to very fast -- settings minimum is 2 (30ms)
defaults write -g KeyRepeat -int 5
defaults -currentHost write -g KeyRepeat -int 5

# Set mouse speed to very fast (min: 1.0, max: 5.0)
defaults write -g com.apple.mouse.scaling 1.0
defaults -currentHost write -g com.apple.mouse.scaling 1.0

# Require password immediatly after sleep or screen saver
defaults write com.apple.screensaver askForPassword -int 1
defaults write com.apple.screensaver askForPasswordDelay -int 0

#launchctl stop com.apple.syncdefaultsd && launchctl start com.apple.syncdefaultsd

#find ~/Library/Application\ Support/Dock -name "*.db" -maxdepth 1 -delete

#for app in "Activity Monitor" "Address Book" "Calendar" "Contacts" "cfprefsd" \
#  "Dock" "Finder" "Mail" "Messages" "Safari" "SystemUIServer" \
#  "Terminal" "Transmission"; do
#  killall "${app}" > /dev/null 2>&1
#done

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
