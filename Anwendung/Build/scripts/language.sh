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
    echo "[⧗] Generating POT file..."
    make -C "$source_dir" "$PO_FILE_DIR/$TARGET.pot"
    echo "[✓] POT file created at $PO_FILE_DIR/$TARGET.pot"
}

# initialize .po files
generate_po() {
    echo "[⧗] Initializing PO files..."
    for lang in "${SUPPORTED_LANGS[@]}"; do
        if [ ! -f "$po_dir/$lang.po" ]; then
            msginit --no-translator --input="$PO_FILE_DIR/$TARGET.pot" \
                --locale="$lang" --output-file="$po_dir/$lang.po"
            echo "[✓] Created $po_dir/$lang.po"
        else
            echo "[i] $po_dir/$lang.po already exists, skipped."
        fi
    done
}

# update existing .po files
update_po() {
    local lang="${1:-}"  
    if [ -n "$lang" ]; then
        # single language
        if [ -f "$po_dir/$lang.po" ]; then
            msgmerge --update --backup=none "$po_dir/$lang.po" "$PO_FILE_DIR/$TARGET.pot"
            echo "[✓] Updated $po_dir/$lang.po"
        else
            echo "[!] $po_dir/$lang.po missing, run generate_po first."
        fi
    else
        # all languages
        for l in "${SUPPORTED_LANGS[@]}"; do
            if [ -f "$po_dir/$l.po" ]; then
                msgmerge --update --backup=none "$po_dir/$l.po" "$PO_FILE_DIR/$TARGET.pot"
                echo "[✓] Updated $po_dir/$l.po"
            else
                echo "[!] $po_dir/$l.po missing, run generate_po first."
            fi
        done
    fi
}

# compile .po → .mo
compile_mo() {
    local lang="${1:-}"
    local langs=()
    if [ -n "$lang" ]; then
        langs=("$lang")
    else
        langs=("${SUPPORTED_LANGS[@]}")
    fi

    echo "[⧗] Compiling MO files..."
    for l in "${langs[@]}"; do
        local out_dir="$output_dir/locale/$l/LC_MESSAGES"
        mkdir -p "$out_dir"
        msgfmt "$po_dir/$l.po" -o "$out_dir/$TARGET.mo"
        echo "[✓] Compiled $out_dir/$TARGET.mo"
    done
}

# ------------------------
# Build translations
# ------------------------
build_translations() {
    generate_pot
    generate_po
    update_po
    compile_mo
    echo "[✓] All translations built in $output_dir"
}

build_translation_single() {
    local lang="$1"
    generate_pot
    generate_po
    update_po "$lang"
    compile_mo "$lang"
    echo "[✓] Translation built at $output_dir for $lang"
}

