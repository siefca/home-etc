
if [ -r $HOME/.home_etc ]; then
    HOME_ETC=`cat $HOME/.home_etc | head -n1`
    if [  "x`echo $HOME_ETC | cut -b1`" = "x#" ]; then
	unset HOME_ETC
    else
	if [ "x`echo $HOME_ETC | cut -b1`" != "x/" ]; then
	    HOME_ETC="$HOME/$HOME_ETC"
	fi
	export HOME_ETC
    fi
fi

