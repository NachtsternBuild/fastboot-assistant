# fastboot-assistant
## Beschreibung
Programm um das installieren von Custom-ROM und GSIs auf Android-Geräte zu erleichtern. Basierend auf GTK und Shell.
## Funktionen
- prüfen der Verbindung ADB/Fastboot
- erstellen eines Arbeitsverzeichnisses
- wechseln in das Arbeitsverzeichnis
- boot in Fastboot-Modus
- Neustart vom Fastboot-Modus
- Neustart in Download-Modus
- boot in den Recovery
- öffnen/schleißen des Bootloaders 
- löschen der Nutzerdaten
- umbenennen von Dateien (recovery.img, boot.img, vendor.img, system.img, vbmeta.img)
- Flashen recovery.img, boot.img, init_boot.img, vendor_boot.img, vendor.img, system.img, vbmeta.img, dtbo.img, preloader.img, preloader.bin, super.img und viele andere

## Versionen
 *<https://github.com/NachtsternBuild/fastboot-assistant/releases>*
- ***siehe Changelog.md für alle Änderungen oder halt GitHub.***

### Versionshinweis
- **dev** - noch in Arbeit, aber einiges funktioniert schon
- **beta** - das meiste funktioniert, aber einige Fehler
- **Projekt-122-l** - alte Versionen oder Entwicklungsversionen
  
### Sweet Unix v.0.5.x
- **fastboot-assistant (noch Projekt-122-l) v.0.5.1.dev** → Linux (Ubuntu/Debian) / *Windows über WSL (ist noch experimentell)*

### Sprudelnde PC-Kühlung v.0.4.x
- *Projekt-122-l v.0.4.1.beta* → Linux
- *Projekt-122-l v.0.4.beta* → Linux
### Funkelnde Datenkristalle v.0.3.x
- *Projekt-122-l v.0.3.beta* → für Linux Debian/Ubuntu
## Hinweise
- Benutzung auf eigene Gefahr.
- Es kann zu Schäden am Gerät kommen.
- Nicht jedes Gerät unterstützt jede der Funktionen
- Nicht alle Betriebssystem-Varianten haben den selben Funktionsumfang.
- Das Programm befindet sich in der **Testphase**. *Es kann zu Fehlern im Programm kommen.*

## Installation
Es werden für die Ausführung des Programms folgende Tools benötigt. 
- *Android Debug Bridge (adb)* 
- *Fastboot*
- *xz-utils*
- *unzip*
- *wget*
- *heimdall*

Diese werden automatisch mit dem Debian-Paket installiert.
*Zur Installation werden Root-Rechte benötigt.*
- **Debian-Paket im Terminal installieren mit:**
```sh
sudo apt-get install /PFAD/ZUM/fastboot-assistant.deb 
```
***oder über eine grafische Benutzeroberfläche.***

## Entfernen von Projekt 122
1. Terminal öffnen
2. folgenden Befehl ausführen:
```sh
sudo dpkg -r --force-all Projekt-122-l
```

## weitere Infos
- siehe Anleitungen in der Anwendungen selbst

## Bei Fehlern
- Keine Scheu, einfach meckern. 
- Oder es besser machen (*siehe Build*)
- und gerne bei Issues eintragen 
## Build
*siehe <https://github.com/NachtsternBuild/fastboot-assistant/tree/main/Anwendung>*
