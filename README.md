# Projekt 122 - fastboot-assistant

## Beschreibung
Programm um das installieren von Custom-ROM und GSIs auf Android-Geräte zu erleichtern.

## Info
- *neue Version ist in Vorbereitung.*
## Versionen
- *Projekt-122-l v.0.3.beta* → für Linux
- *Projekt-122-l v.0.4.beta* → für Linux
- *Projekt-122-l v.0.4.1.beta* → für Linux

  *<https://github.com/NachtsternBuild/fastboot-assistant/releases>*

## Hinweise
- Benutzung auf eigene Gefahr.
- Es kann zu Schäden am Gerät kommen.
- Nicht jedes Gerät unterstützt jede der Funktionen
- Nicht beide Betriebssystem-Varianten haben den selben Funktionsumfang.
- Das Programm befindet sich in der **Testphase**. *Es kann zu Fehlern im Programm kommen.*

## Funktionen
- prüfen der Verbindung ADB/Fastboot
- erstellen eines Arbeitsverzeichnisses
- wechseln in das Arbeitsverzeichnis
- boot in Fastboot-Modus
- Neustart vom Fastboot-Modus
- boot in den Recovery
- öffnen/schleißen des Bootloaders 
- löschen der Nutzerdaten
- umbenennen von Dateien (recovery.img, boot.img, vendor.img, system.img, vbmeta.img)
- Flashen recovery.img, boot.img, vendor.img, system.img, vbmeta.img

## Installation
Es werden für die Ausführung des Programms folgende Tools benötigt. 

*Android Debug Bridge (adb)*, *Fastboot*

- Unter Linux die Tools installieren mit:
```sh
# Debian / Ubuntu:
sudo apt-get update
sudo apt-get install adb
sudo apt-get install fastboot
```
```sh
# Fedora: 
sudo dnf install android-tools
```
```sh
# Arch:
sudo pacman -S android-tools
```
```sh
# openSUSE:
sudo zypper refresh
sudo zypper install android-tools
```
```sh
# Fedora/SUSE
sudo yum install android-tools
```
 Um diese Tool auszuführen starten sie es vom Desktop.

## Entfernen von Projekt 122
1. Terminal öffnen
2. folgenden Befehl ausführen:
```sh
    rm ~/.local/share/applications/Projekt-122-l.desktop
```
3. Das Verzeichnis wo Projekt-122 liegt löschen.

*Entweder über den Dateimanager oder via:*
```sh
rm -r ~/Downloads/Projekt-122
```

## Build

- **nur unter Linux gibt es eine Anleitung**

1. Laden sie den Quellcode herunter:
```sh
git clone https://github.com/NachtsternBuild/Projekt-122.git
```
2. bearbeiten sie diesen nach ihren Vorstellungen. *Beachten sie, dass das Makefile auch bei Namensänderungen geändert werden muss*
3. Nutzen von der ***build.sh*** via:
```sh
bash build.sh
```

*oder manuell:*

1. Installieren sie GCC, ADB/Fastboot, desktop-file-utils :

```sh
# Debian / Ubuntu:
sudo apt update
sudo apt install build-essential
sudo apt-get install adb
sudo apt-get install fastboot
sudo apt-get install -y desktop-file-utils
```
```sh
# Fedora:
sudo dnf install gcc
sudo dnf install -y android-tools
sudo dnf install -y desktop-file-utils
```
```sh
# Arch:
sudo pacman -Syyu
sudo pacman -S gcc
sudo pacman -S --noconfirm android-tools
sudo pacman -S --noconfirm desktop-file-utils
```
```sh
# Open SUSE:
sudo zypper refresh
sudo zypper install gcc
sudo zypper install android-tools
sudo zypper install desktop-file-utils
```
```sh
# Fedora/SUSE
sudo yum install gcc
sudo yum install android-tools
sudo yum install -y desktop-file-utils
```

2. Kompilieren sie den Code indem sie das Makefile ausführen:
```sh
make
```
3. Ausführbar machen mit:
```sh
chmod +x Projekt-122-l-meineVersion
```
oder mit:
```sh
sudo chmod +x Projekt-122-l-meineVersion
```
4. Aufräumen:
```sh
make clean
```

## Eigentümer
- *Elias Mörz*
## Info
ADB (Android Debug Bridge) ermöglicht die Kommunikation zwischen einem Computer und einem Android-Gerät für Debugging und Dateiübertragung. Fastboot ist ein Befehlszeilenwerkzeug für den Bootloader-Modus von Android-Geräten, um Systemabbilder zu flashen und benutzerdefinierte Firmware zu installieren. Beide sind wichtige Tools für Entwickler und fortgeschrittene Nutzer zur Modifikation und Diagnose von Android-Geräten über eine USB-Verbindung. 

GSI (Generic System Image) ist ein standardisiertes Android-Systemabbild, das auf verschiedenen Geräten laufen kann. Custom-ROMs sind modifizierte Android-Betriebssystemversionen, die von der Standard-Software abweichen und von Entwicklern erstellt werden, um zusätzliche Funktionen oder Anpassungen anzubieten. Beide ermöglichen Nutzern die Anpassung ihrer Android-Geräte über Installationen von alternativen Betriebssystemversionen.

 A/B Partitionsschema verwendet zwei Systempartitionen, um nahtlose Updates zu ermöglichen, indem es zwischen ihnen wechselt. Das only-A Partitionsschema hat nur eine Systempartition und erfordert einen Neustart für Updates. A/B bietet redundante Sicherheit und ermöglicht ein kontinuierliches Betriebssystem, während Only-A einfachere Verwaltung erfordert. 

Project Treble ist eine Android-Initiative von Google, die die Trennung von Betriebssystem- und Hardwarekomponenten ermöglicht. Dies erleichtert Herstellern die Bereitstellung von Android-Updates, indem das Betriebssystem unabhängig von den spezifischen Treibern für den Chipsatz ist.

## Bei Fehlern
- Keine Scheu, einfach meckern. 
- Oder es besser machen (*siehe Build*) 
