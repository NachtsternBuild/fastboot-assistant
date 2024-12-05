Name:           fastboot-assistant
Version:        0.6.2
Release:        1%{?dist}
Summary:        Program to facilitate the installation of custom ROMs and GSIs on Android devices.
License:        Apache License Version 2.0
Source0:        %{name}-%{version}.tar.gz
%if 0%{?suse_version}
Requires:       adb fastboot glibc >= 2.15 curl, pkexec, gtk4 >= 4.0.0 xz wget unzip coreutils curl
%else
Requires:       adb fastboot glibc >= 2.15 curl, pkexec, gtk4 >= 4.0.0 xz wget unzip coreutils curl
%endif

%description
Program to facilitate the installation of custom ROMs and GSIs on Android devices.

%prep
%setup -q

%install
rm -rf %{buildroot}
mkdir -p %{buildroot}/usr/bin/fastboot-assistant
mkdir -p %{buildroot}/usr/share/icons/hicolor/256x256/apps
mkdir -p %{buildroot}/usr/share/applications

# Copy the binary and other necessary files
cp %{_builddir}/fastboot-assistant-%{version}/fastboot-assistant %{buildroot}/usr/bin/fastboot-assistant/fastboot-assistant
cp %{_builddir}/fastboot-assistant-%{version}/sweet_unix.png %{buildroot}/usr/share/icons/hicolor/256x256/apps/sweet_unix.png
cp %{_builddir}/fastboot-assistant-%{version}/fastboot-assistant.desktop %{buildroot}/usr/share/applications/fastboot-assistant.desktop

%clean
rm -rf %{buildroot}

%files
%{_bindir}/fastboot-assistant/fastboot-assistant
%{_datadir}/applications/fastboot-assistant.desktop
%{_datadir}/icons/hicolor/256x256/apps/sweet_unix.png

%changelog
* Tue Aug 13 2024 Elias Mörz<elias.moerz@mail.de> - 0.5.4
- Initial package
