#!/bin/bash
# build-language.sh
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


language_build() {
	echo "[⧗] Starting building the language files..."
	prompt_user "$(tr create_po)"
	while true; do
    	read -n1 -s answer_po
    	case "$answer_po" in
       		j|J|y|Y)
       			echo "[⧗] Creating pot files..."
       			generate_pot
       			echo "[⧗] Creating po files..."
       			generate_po
       			echo "[⧗] Building language files..."
				build_translations
				break
				;;
			n|N)
				echo "[⧗] Build language files..."
				prompt_user "$(tr manuell_po)"
				while true; do
    				read -n1 -s answer_manuell_po
    				case "$answer_manuell_po" in
						j|J|y|Y)
							echo "[⧗] Manuell building of language files..."
							prompt_user "$(tr use_po)"
							prompt_user "╭────────────── Language  ──────────────╮"
    						echo -e "${GREEN}│         (d) Deutsch            |${NC}"
    						echo -e "${GREEN}│         (e) English            │${NC}"
    						echo -e "${GREEN}│         (r) Русский            │${NC}"
    						echo -e "${GREEN}│         (s) Español            │${NC}"
			    			echo -e "${GREEN}│         (p) Português            │${NC}"
			    			echo -e "${GREEN}│         (f) Français            │${NC}"
			    			echo -e "${RED}│          $(tr select_exit)            │${NC}"
			    			prompt_user "╰────────────────────────────────────────╯"
							while true; do
								read -n1 -s answer_use_po
								case "$answer_use_po" in
									d|D|de|De|DE|g|G)
										echo "[⧗] Build language file for German..."
										build_translation_single de
			    						break
			    						;;
			    					e|E|en|EN)
			    						echo "[⧗] Build language file for English..."
										build_translation_single en
			    						break
			    						;;
			    					r|R|ru|RU)
										echo "[⧗] Build language file for Russian..."
										build_translation_single ru
			    						break
			    						;;
			    					s|S|es|ES)
										echo "[⧗] Build language file for Spanish..."
										build_translation_single es
			    						break
			    						;;
			    					p|P|pt|PT)
										echo "[⧗] Build language file for Portuguese..."
										build_translation_single pt
			    						break
			    						;;
			    					f|F|fr|FR)
			    						echo "[⧗] Build language file for French..."
										build_translation_single fr
			    						break
			    						;;
			    					* )
			    						build_info "$(tr invalid_input)"
			    						;;
    							esac
    						done
    						break
    						;;
    					n|N)
    						echo "[⧗] Build language files..."
    						build_translations
    						break
    						;;
    					* )
    						build_info "$(tr invalid_input)"
    						;;
    				esac
    			done
    			break
    			;;		
    		* )
    			 build_info "$(tr invalid_input)"
    			 ;;
    	esac
	done
}
