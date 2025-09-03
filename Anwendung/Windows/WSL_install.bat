@echo off
REM This script installs WSL, sets WSL 2 as the default version, and installs Ubuntu.

echo Setting WSL 2 as the default version...
wsl -l -v
wsl --set-default-version 2
wsl --update
wsl --list --online

echo Installing Ubuntu on WSL...
wsl --install -d Ubuntu

REM Launch Ubuntu to complete the installation
echo Please setup your Linux user info.
echo Launching Ubuntu to complete the installation...
ubuntu

echo WSL and Ubuntu installation complete.
pause

