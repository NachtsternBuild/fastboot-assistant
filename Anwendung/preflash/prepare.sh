#!/bin/bash
# prepare.sh

# function to check imagetyp
check_img_type() {
    img_file="$1"
    file_type=$(file "$img_file")
    file_size=$(stat -c %s "$img_file") # get filesize

    # check imagetyp and filesize
    if [[ $file_type == *"Android bootimg"* && $file_size -gt 2048 && $file_size -le 199999999]]; then
        echo "$img_file ist ein boot.img."
        # rename file
        mv $img_file boot.img
        
    elif [[ $file_type == *"Android bootimg"* && $file_size -gt 4096 && $file_size -le 199999999]]; then 
        echo "$img_file ist ein recovery.img."
        # rename file
        mv $img_file recovery.img
        
    elif [[ $file_type == *"Linux rev 1.0 ext2 filesystem data"* && $file_size -gt 200000000 && $file_size -le 900000000 ]]; then
        echo "$img_file ist ein vendor.img."
        # rename file
        mv $img_file vendor.img
        
    elif [[ $file_type == *"Linux rev 1.0 ext2 filesystem data"* && $file_size -gt 3000000000 && $file_size -le 7500000000 ]]; then
        echo "$img_file ist ein system.img."
        # rename file 
        mv $img_file system.img
    else
        echo "Unbekannter Dateityp für $img_file."
    fi
}

# main programm
# decompress files
DIRECTORY= ~/Downloads/ROM-Install

# check for xz
if ! command -v xz &> /dev/null
then
    echo "xz ist nicht installiert. Bitte installiere es zuerst."
    exit 1
fi

# get the dir
if [ ! -d "$DIRECTORY" ]; then
    echo "Das angegebene Verzeichnis existiert nicht."
    exit 1
fi

# cd to user  dir
cd "$DIRECTORY" || exit

# search for all files in the dir
for file in "$DIRECTORY"/*
do
    # check if the files are compresses with xz
    if [[ "$file" == *.xz ]]; then
        echo "Dekomprimieren von $file..."
        xz -d "$file"
        if [ $? -eq 0 ]; then
            echo "$file erfolgreich dekomprimiert."
        else
            echo "Fehler beim Dekomprimieren von $file."
        fi
    fi
done

echo "Überprüfung und Dekomprimierung abgeschlossen."

# rename files
# check .img files in dir
echo "Überprüfe .img-Dateien in $DIRECTORY:"
for img_file in *.img; do
    if [ -f "$img_file" ]; then
    	echo "------------------------------------------------------------------------"
        echo "Datei: $img_file"
        check_img_type "$img_file"
        echo "------------------------------------------------------------------------"
    fi
done

echo "Überprüfung abgeschlossen."
echo "Dateien umbenannt!"
echo "------------------------------------------------------------------------"
echo "Nun kann weiter gearbeitet werden!"
echo "------------------------------------------------------------------------"

