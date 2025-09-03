#!/bin/bash
# build-os.sh
# ╔═══════════════════════════════════════════════╗
# ║              Fastboot-Assistant               ║
# ║               Build Environment               ║
# ╚═══════════════════════════════════════════════╝
# ╔═══════════════════════════════════════════════╗
# ║                                               ║
# ║                   License:                    ║ 
# ║          GNU GENERAL PUBLIC LICENSE           ║
# ║                  Version 3                    ║
# ║                                               ║
# ╚═══════════════════════════════════════════════╝
# 
# build skript for:
# - object file of the fastboot-assistant
# - Debian package
# 	- simple mode
# 	- debuild
# - Snap
# - Flatpak
# this is a modified version of the bash script, for Debian package and the RPM building from the linux-assistant

# build the program for linux
build_program_linux() {
	echo "[⧗] Build for Linux..."
	prompt_user "$(tr compile)"
	read -p " " answer
	if [ "$answer" == "j" ] || [ "$answer" == "J" ] || [ "$answer" == "y" ] || [ "$answer" == "Y" ]; 
 	then
    	echo "[⧗] Start Build for Linux..."
    	echo "[⧗] Copy all files to $target_dir..."
    	for dir in "$source_dir" "$build_dir" "$header_dir" "$config_dir" "$reboot_dir" "$flash_dir" "$preflash_dir" "$instructions_dir" "$h_flash_dir" "$h_UI_dir" "$h_commands_dir" "$h_config_dir" "$h_directory_dir" "$h_message_dir" "$h_spinner_dir" "$h_theme_dir" "$h_partition_dir" "$h_language_dir" "$f_others_dir" "$p_backup_dir" "$p_prepare_dir" "$updater_dir" "$main_dir" "$po_dir"; do
        	# find "$dir" -maxdepth 1 -type f -exec cp {} "$target_dir" \;
        	rsync -av --update --exclude '.git/' --exclude='*/' --exclude='*.md' "$dir/" "$target_dir/"
    	done
		echo "[✓] Copied all files to $target_dir."
		
		building
    else 
    	echo "[x] No compilation."
    fi
    
    # loop for package build
    while true; do
    	prompt_user "$(tr build_package)"
    	echo ""
    	prompt_user "╭────────────── $(tr select_os) ──────────────╮"
    	echo -e "${RED}│            (d) Debian                  │${NC}"
    	echo -e "${CYAN}|            (s) Snap                    |${NC}"
    	echo -e "${GREEN}|            (f) Flatpak                 |${NC}"
    	echo -e "${RED}|               $(tr select_exit)               |${NC}"
    	prompt_user "╰────────────────────────────────────────╯"
    	read -n1 -s answer
   		echo ""
    	case "$answer" in 
        	d|D)
        	    debian_package_build
        	    prompt_user "[✓] End packagebuild."
        	    ;;
        	s|S)
        	    build_snap
        	    echo "[✓] End Snap build."
        	    ;;
        	f|F)
        	    build_flatpak
        	    echo "[✓] End Flatpak build."
        	    ;;
        	b|B|n|N)
        	    echo "[✓] End package build script."
        	    break
        	    ;;
        	* )
        	    build_info "$(tr invalid_input)"
        	    ;;
    	esac
	done
}

# build the program for Windows
build_program_windows() {
    echo "[⧗] Build für Windows (WSL)..."
    build_info "$(tr build_wsl_info)"
    echo "[⧗] Start Build for Windows (WSL)..."
    echo "[⧗] Copy all files to $target_dir..."
    for dir in "$source_dir" "$build_dir" "$header_dir" "$config_dir" "$reboot_dir" "$flash_dir" "$preflash_dir" "$instructions_dir" "$h_flash_dir" "$h_UI_dir" "$h_commands_dir" "$h_config_dir" "$h_directory_dir" "$h_message_dir" "$h_spinner_dir" "$h_theme_dir" "$h_partition_dir" "$f_others_dir" "$h_language_dir" "$p_backup_dir" "$p_prepare_dir" "$updater_dir" "$main_dir" "$po_dir"; do
        # find "$dir" -maxdepth 1 -type f -exec cp {} "$target_dir" \;
        rsync -av --update --exclude '.git/' --exclude='*/' --exclude='*.md' "$dir/" "$target_dir/"
    done

    echo "[✓] Copied all files to $target_dir."
    echo "[⧗] Remove Linux spezific files $target_dir..."

    # remove unused files
    for unused in "${unused_files[@]}"; do
        unused_path="$target_dir/$unused"
        if [ -f "$unused_path" ]; then
            rm -rf "$unused_path"
            echo "[⧗] Remove $unused_path..."
        else
            echo "[⚠] Cannot found: $unused_path"
        fi
    done
    
    prompt_user "$(tr compile)"
	read -p " " answer
	if [ "$answer" == "j" ] || [ "$answer" == "J" ] || [ "$answer" == "y" ] || [ "$answer" == "Y" ]; 
 	then
    	echo "[⧗] Start Build for WSL..."
    	echo "[⧗] Copy all files to $target_dir..."
    	for dir in "$preflash_dir_win" "$header_dir_win" "$windows_dir" "$other_dir_win"; do
        	# find "$dir" -maxdepth 1 -type f -exec cp {} "$target_dir" \;
        	rsync -av --update --exclude '.git/' --exclude='*.md' "$dir/" "$target_dir/"
    	done
		echo "[✓] Copied all files to $target_dir."
		
		building
    else 
    	echo "[x] No compilation."
    fi
 	
 	prompt_user "$(tr package_wsl)"
 	read -n1 -s answer
 	if [ "$answer" == "j" ] || [ "$answer" == "J" ] || [ "$answer" == "y" ] || [ "$answer" == "Y" ]; 
 	then
  		debian_package_build_simple
		echo "[✓] Build finished."
  		prompt_user "[✓] The package are at the $source_dir"
  		windows_zip_build
  		echo "[✓] Build finished."
  		prompt_user "[✓] The package are at the $source_dir"
	else
  		prompt_user "[x] No package build."
	fi
}
