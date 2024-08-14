Name:           fastboot-assistant
Version:        0.5.3
Release:        1%{?dist}
Summary:        Program to facilitate the installation of custom ROMs and GSIs on Android devices.
License:        Apache License Version 2.0
Source0:        %{name}-%{version}.tar.gz
%if 0%{?suse_version}
Requires:       adb fastboot glibc >= 2.15 gtk3 >= 3.0.0 xz wget unzip
%else
Requires:       adb fastboot glibc >= 2.15 gtk3 >= 3.0.0 xz wget unzip
%endif

%description
Program to facilitate the installation of custom ROMs and GSIs on Android devices.

%prep
%setup -q

%install
rm -rf %{buildroot}
mkdir -p %{buildroot}/usr/bin/projekt-122
mkdir -p %{buildroot}/usr/share/icons/hicolor/256x256/apps
mkdir -p %{buildroot}/usr/share/applications

# Copy the binary and other necessary files
cp %{_builddir}/fastboot-assistant-0.5.3/Projekt-122-l %{buildroot}/usr/bin/projekt-122/Projekt-122-l
# cp %{_builddir}/fastboot-assistant-0.5.3/sweet_unix.png %RPM_BUILD_ROOT/%{_datadir}/icons/hicolor/256x256/apps/sweet_unix.png
# cp %{_builddir}/fastboot-assistant-0.5.3/fastboot-assistant.desktop %RPM_BUILD_ROOT/%{_datadir}/applications/fastboot-assistant.desktop
cp /home/elias/rpmbuild/BUILD/fastboot-assistant-0.5.3/sweet_unix.png %{buildroot}/usr/share/icons/hicolor/256x256/apps/sweet_unix.png
cp /home/elias/rpmbuild/BUILD/fastboot-assistant-0.5.3/fastboot-assistant.desktop %{buildroot}/usr/share/applications/fastboot-assistant.desktop

%clean
rm -rf %{buildroot}

%files
%{_bindir}/projekt-122/%{name}
%{_datadir}/applications/fastboot-assistant.desktop
%{_datadir}/icons/hicolor/256x256/apps/sweet_unix.png

%changelog
* Tue Aug 13 2024 Elias Mörz<elias.moerz@mail.de> - 0.5.3
- Initial package
