@echo off
REM This script installs WSL, sets WSL 2 as the default version, and installs Ubuntu.

echo Enable WSL
dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart
dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart

echo Please restart your device.
pause
