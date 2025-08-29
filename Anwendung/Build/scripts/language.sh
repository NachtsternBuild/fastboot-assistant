#!/bin/bash
# language.sh
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


# generate .pot file
generate_pot() {
    echo "[⧗] Generating POT file via Makefile..."
    make init-po      
    echo "[✓] POT file created at $PO_FILE_DIR/fastboot-assistant.pot"
}

# generate .po files
generate_po() {
    local lang="${1:-}"
	mkdir -p "$po_dir"
	mkdir -p "$OUTPUT_DIR_PO"
	
    if [ -n "$lang" ]; then
        echo "[⧗] Creating PO file for $lang..."
        make po-"$lang"
        echo "[✓] PO file $lang.po ready."
        cp "$PO_FILE_DIR"/* "$OUTPUT_DIR_PO/"
        cp "$PO_FILE_DIR"/* "$po_dir/"
    else
        echo "[⧗] Creating PO files for all languages..."
        for lang in "${SUPPORTED_LANGS[@]}"; do
            #make po-"$lang"
            make init-po
            echo "[✓] PO file $lang.po ready."
            cp -r "$PO_FILE_DIR"/* "$OUTPUT_DIR_PO/"
            cp -r "$PO_FILE_DIR"/* "$po_dir/"
        done
    fi
    echo "[✓] All PO files ready at $OUTPUT_DIR_PO and $po_dir."
}

# update the .po files for all languages or a single on
update_po() {
    local lang="${1:-}"
	mkdir -p "$po_dir"
	mkdir -p "$OUTPUT_DIR_PO"
	
    if [ -n "$lang" ]; then
        echo "[⧗] Updating PO file for $lang..."
        make update-po
        echo "[✓] PO file $lang.po updated."
        cp "$PO_FILE_DIR"/* "$OUTPUT_DIR_PO/"
        cp "$PO_FILE_DIR"/* "$po_dir/"
    else
        echo "[⧗] Updating PO files for all languages..."
        make update-po
        for lang in "${SUPPORTED_LANGS[@]}"; do
            cp -r "$PO_FILE_DIR"/* "$OUTPUT_DIR_PO/"
            cp -r "$PO_FILE_DIR"/* "$po_dir/"
        done
        echo "[✓] All PO files updated at $OUTPUT_DIR_PO and $po_dir."
    fi
}

# compile the .po files to .mo files
compile_mo() {
    local lang="${1:-}"
    local langs=()
    mkdir -p "$MO_DIR"
	
    if [ -n "$lang" ]; then
        langs=("$lang")
    else
        langs=("${SUPPORTED_LANGS[@]}")
    fi

    echo "[⧗] Compiling MO files..."
    for lang in "${langs[@]}"; do
        mkdir -p "$OUTPUT_DIR_PO/locale/$lang/LC_MESSAGES"
        make mo-all
        cp -r "$MO_DIR"/* "$OUTPUT_DIR_PO/locale/$lang/LC_MESSAGES/"
        echo "[✓] Compiled $OUTPUT_DIR_PO/locale/$lang/LC_MESSAGES/$lang.mo"
    done
}

# build the language files
build_translations() {
    mkdir -p "$OUTPUT_DIR_PO" "$po_dir"
    generate_pot
    generate_po
    update_po
    compile_mo
    echo "[✓] All translations built in $OUTPUT_DIR_PO"
}

# build a single language file
build_translation_single() {
    mkdir -p "$OUTPUT_DIR_PO" "$po_dir"
    local lang="${1:-}"
    generate_pot
    generate_po "$lang"
    update_po "$lang"
    compile_mo "$lang"
    echo "[✓] Translation built at $OUTPUT_DIR_PO for $lang"
}
