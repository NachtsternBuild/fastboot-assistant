# Install the fastboot-assistant WSL
## Preparation
1. Check whether the Windows Subsystem for Linux (WSL) is installed and activated under Windows.
2. Check whether the installed distribution is *Ubuntu*.
3. Check whether a user is set up for the *Ubuntu*.
- **If yes, then start Ubuntu and install the package:**
```sh
cd /mnt/c/Users/UserName/Downloads/Path/to/unpacked/Zipfile
sudo apt update && sudo apt upgrade
sudo dpkg -i fastboot-assistant.deb
```

- **If not, open a command line as administrator.** 
- Navigate to the location where the zip file was unpacked.
- Execute this command:
```bat
Enable_WSL.bat
```
- When the script has run, restart your system and execute the following command:
```bat
WSL_install.bat
```
- Then define the users and run:
```sh
sudo apt update && sudo apt upgrade
```
- Execute the following commands:
```sh
cd /mnt/c/Users/UserName/Downloads/Path/to/unpack/Zipfile
sudo dpkg -i fastboot-assistant.deb
```

## Remove fastboot-assistant
1. Start WSL and run:
```sh
sudo dpkg -r --force-all Fastboot-Assistant
```
