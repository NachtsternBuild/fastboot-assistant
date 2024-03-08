# Projekt 122

## Beschreibung
Programm um das installieren von Custom-ROM und GSIs auf Android-Geräte zu erleichtern.

## Versionen
- *Projekt-122-l-v.0.3.beta* → für Linux Debian/Ubuntu
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
sudo apt update
sudo apt install android-tools-adb android-tools-fastboot
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
sudo zypper install android-tools
```
 Um diese Tool auszuführen führen sie im Terminal folgendes aus:
```sh
./Projekt-122-l-v_0_3
```

- *Für Windows-Nutzer:*
**Nutzung von WSL um die Anwendung auszuführen.**

## Build

- **nur unter Linux gibt es eine Anleitung**

1. Laden sie den Quellcode herunter 
2. bearbeiten sie diesen nach ihren Vorstellungen. *Beachten sie, dass das Makefile auch bei Namensänderungen geändert werden muss*
3. Installieren sie GCC:

```sh
# Debian / Ubuntu:
sudo apt update
sudo apt install build-essential
```
```sh
# Fedora:
sudo dnf install gcc
```
```sh
# Arch:
sudo pacman -Syu
sudo pacman -S gcc
```
```sh
# Open SUSE:
sudo zypper install gcc
```

4. Kompilieren sie den Code indem sie das Makefile ausführen:
```sh
make
```
5. Ausführbar machen mit:
```sh
chmod a+w Projekt-122-l-meineVersion
```
oder mit:
```sh
sudo chmod a+w Projekt-122-l-meineVersion
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
