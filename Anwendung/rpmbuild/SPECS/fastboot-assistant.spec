Name:           fastboot-assistant
Version:        0.5.3
Release:        1%{?dist}
Summary:        Program to facilitate the installation of custom ROMs and GSIs on Android devices.
License:        Apache License Version 2.0
Source0:        %{name}-%{version}.tar.gz
%if 0%{?suse_version}
Requires:       adb fastboot glibc >= 2.15 gtk3 >= 3.0.0 xz wget unzip heimdall-flash heimdall-flash-frontend
%else
Requires:       adb fastboot glibc >= 2.15 gtk3 >= 3.0.0 xz wget unzip heimdall-flash heimdall-flash-frontend
%endif

%description
Program to facilitate the installation of custom ROMs and GSIs on Android devices.

%prep
%setup -q

%build

#%install
#rm -rf %{buildroot}
#mkdir -p %{buildroot}/%{_bindir}
#mkdir -p %{buildroot}/%{_libdir}/%{name}
#mkdir -p %{buildroot}/%{_datadir}/icons/hicolor/256x256/apps/
#mkdir -p %{buildroot}/%{_datadir}/applications/

# Kopieren Sie die Dateien in das Buildroot-Verzeichnis
#cp %{_libdir}/%{name}/%{name} %{buildroot}/%{_bindir}/%{name}
#cp %{_libdir}/%{name}/sweet_unix.png %{buildroot}/%{_datadir}/icons/hicolor/256x256/apps/
#cp %{_libdir}/%{name}/fastboot-assistant.desktop %{buildroot}/%{_datadir}/applications/

%install
rm -rf %{buildroot}
mkdir -p %{buildroot}/usr/bin
mkdir -p %{buildroot}/usr/lib64/fastboot-assistant
mkdir -p %{buildroot}/usr/share/icons/hicolor/256x256/apps/
mkdir -p %{buildroot}/usr/share/applications/

# Copy the binary and other necessary files
cp %{_builddir}/fastboot-assistant-0.5.3/fastboot-assistant %{buildroot}/usr/lib64/fastboot-assistant/
ln -s /usr/lib64/fastboot-assistant/Projekt-122-l %{buildroot}/usr/bin/fastboot-assistant
cp %{_libdir}/%{name}/sweet_unix.png %{buildroot}/%{_datadir}/icons/hicolor/256x256/apps/
cp %{_libdir}/%{name}/fastboot-assistant.desktop %{buildroot}/%{_datadir}/applications/

%clean
rm -rf %{buildroot}

%files
%{_bindir}/%{name}
%{_datadir}/applications/fastboot-assistant.desktop
%{_datadir}/icons/hicolor/256x256/apps/sweet_unix.png

%changelog
