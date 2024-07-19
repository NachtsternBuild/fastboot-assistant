#!/bin/bash
# backup_root.sh
# path for the backup
BACKUP_DIR="$HOME/Downloads/ROM-Install/Backup"

echo "Sicherung aller auf dem verfügbaren Partitionen nach $BACKUP_DIR."
# connect device with adb and wait for it
adb wait-for-device

# get all partitions by-name via root
PARTITIONS=$(adb shell su -c "ls /dev/block/bootdevice/by-name/" | tr -d '\r')

# backup partitions
for PARTITION in $PARTITIONS; do
    # check if the device has a/b-partitions
    if adb shell su -c "ls /dev/block/bootdevice/by-name/${PARTITION}_a" >/dev/null 2>&1; then
        for SLOT in "a" "b"; do
        	# loop for backup all partitions on a/b-devices
            FILE_NAME="${PARTITION}_${SLOT}.img"
            echo "Sichere ${PARTITION} (Slot ${SLOT}) nach ${BACKUP_DIR}/${FILE_NAME}"
            adb shell su -c "dd if=/dev/block/bootdevice/by-name/${PARTITION}_${SLOT}" | dd of="${BACKUP_DIR}/${FILE_NAME}"
        done
    else
    	# backup for only-a-devices
        FILE_NAME="${PARTITION}.img"
        echo "Sichere ${PARTITION} nach ${BACKUP_DIR}/${FILE_NAME}"
        adb shell su -c "dd if=/dev/block/bootdevice/by-name/${PARTITION}" | dd of="${BACKUP_DIR}/${FILE_NAME}"
    fi
done

echo "Sicherung abgeschlossen. Dateien befinden sich in $BACKUP_DIR"

