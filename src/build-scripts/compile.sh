#!/bin/bash
# compile.sh
#
# (C) Copyright 2025 @NachtsternBuild
#
# License: GNU GENERAL PUBLIC LICENSE Version 3
# 
# build skript for:
# - object file of the fastboot-assistant
# - Debian package
# 	- simple mode
# 	- debuild
# - Snap
# - Flatpak
# this is a modified version of the bash script, for Debian package and the RPM building from the linux-assistant

compile() {
	prompt_user "$(tr compile)"
	while true; do
		read -n1 -s answer	
   		case "$answer" in 
   			j|J|y|Y)
    	    	make
    	    	chmod +x "${source_dir}/fastboot-assistant"
    	       	build_info "[✓] Completed."
    	       	break
    	       	;;
    	    * )
    	       	build_info "$(tr invalid_input)"
    	        ;;
    	esac
	done
}
