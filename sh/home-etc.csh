#!/bin/csh

if ( -r $HOME/.home_etc ) then
    set HOME_ETC = `cat $HOME/.home_etc | head -n1`
    if ( `echo $HOME_ETC | cut -b1` == '#' ) then
	unset HOME_ETC
	unsetenv HOME_ETC
    else
	if ( `echo $HOME_ETC | cut -b1` != '/' ) then
	    set HOME_ETC = "$HOME/$HOME_ETC"
	endif
	setenv HOME_ETC
    endif
endif

echo "HOME_ETC=$HOME_ETC"
