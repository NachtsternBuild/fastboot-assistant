#!/bin/bash
# rename.sh

# function to check imagetyp
check_img_type() {
    img_file="$1"
    file_type=$(file "$img_file")
    file_size=$(stat -c %s "$img_file") # get filesize

    # check imagetyp and filesize
    if [[ $file_type == *"page size: 2048"* ]]; then
        echo "$img_file ist ein boot.img."
        # rename file
        mv $img_file boot.img
        
    elif [[ $file_type == *"page size: 4096"* ]]; then 
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

# get dir from user
read -p "Bitte geben Sie den Pfad zum Verzeichnis ein, wo die Image-Dateien umbenannt werden soll: " directory

# check for dir
if [ ! -d "$directory" ]; then
    echo "Das Verzeichnis $directory existiert nicht oder ist kein Verzeichnis."
    exit 1
fi

# cd to user  dir
cd "$directory" || exit

# check .img in dir
echo "Überprüfe .img-Dateien in $directory:"
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

