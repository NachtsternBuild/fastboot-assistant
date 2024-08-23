#!/bin/bash
# build-fastboot-assistant.sh
# this is a modified version of the bash script, for Debian package and the RPM building from linux-assistant

VERSION="$(cat Build/version.txt)"

# Directory paths
home_dir="$HOME"
source_dir="$home_dir/fastboot-assistant/Anwendung"
# source_dir="$home_dir/Dokumente/Schule/Bell/Projekt_122/Master/Projekt_122_GUI/v_0_5"
header_dir="${source_dir}/header"
config_dir="${source_dir}/config_projekt"
reboot_dir="${source_dir}/reboot"
flash_dir="${source_dir}/flash"
preflash_dir="${source_dir}/preflash"
instructions_dir="${source_dir}/instructions"
target_dir="${source_dir}/build_project"
output_dir="${source_dir}/output"
build_dir="${source_dir}/Build"
# some path for the build for Windows
windows_dir="${source_dir}/Windows"
config_dir_win="${windows_dir}/config_projekt"
preflash_dir_win="${windows_dir}/preflash"
header_dir_win="${windows_dir}/header"

# define the name of the zip-file for windows
zip_name="fastboot-assistant.zip"
# some files that are not needed for the Windows part
# need some work later
unused_files=(
    "mkdir.c"
    "remove_old.c"
    "backup_root.c"
    "unxz_files.c"
    "header_set_main_dir_with_wsl.c"
)

# file that needed in the zip-file
zip_files=(
    "WSL_install.bat"
    "Enable_WSL.bat"
    "README.md"
    "fastboot-assistant.deb"
)


# build the program for linux
build_program_linux() {
	echo "Starting Build for Linux..."
	# Copy files
	echo "Copy all files to $target_dir..."
	for dir in "$source_dir" "$build_dir" "$header_dir" "$config_dir" "$reboot_dir" "$flash_dir" "$preflash_dir" "$instructions_dir"; do
    	find "$dir" -maxdepth 1 -type f -exec cp {} "$target_dir" \;
	done

	echo "Copied all files to $target_dir."

	# Build
	echo "Starting build..."
	chmod a+x "$target_dir"
	echo "cd $target_dir"
	cd "$target_dir" || { echo "Error with changing to $target_dir"; exit 1; }
	if make; then
    	echo "Build successful."
	else
    	echo "Error in the build process."
    	exit 1
	fi
	
	echo "Finish build."
	echo "Start after build processes..."

	# Copy output to output-dir
	rm -rf "$output_dir"
	mkdir -p "$output_dir"
	cp fastboot-assistant "$output_dir"
	chmod a+x "$output_dir"
	echo "The application are ready in the $output_dir."

	# Cleanup prompt
	while true; do
    	read -p "Do you want cleaning old files? (j/n)/(y/n): " answer
    	case "$answer" in
        	j|J|y|Y )
            	echo "Start make clean..."
            	make clean
            	rm -rf "$target_dir"
            	echo "Cleaning successful."
            	break
            	;;
        	n|N )
            	echo "No cleaning."
            	break
            	;;
        	* )
            	echo "Please use 'j' 'y' or 'n'."
            	;;
    	esac
	done
}

# build the program for windows
# this is not a native Windows version but only via WSL
build_program_windows() {
	echo "Build for Windows."
	echo "this is not a native Windows version but only via WSL."
	echo "Starting Build for Windows..."
	# Copy files to the target dir
	echo "Copy all files to $target_dir..."
	for dir in "$source_dir" "$build_dir" "$header_dir" "$config_dir" "$reboot_dir" "$flash_dir" "$preflash_dir" "$instructions_dir"; do
    	find "$dir" -maxdepth 1 -type f -exec cp {} "$target_dir" \;
	done

	echo "Copied all files to $target_dir."
	echo "Removing the linux specific files in the $target_dir..."

	# remove unused files
	for unused_files in "${unused_files[@]}"; do
    	unused="$target_dir/$unused_files"
    	if [ -f "$unused" ]; then
        	rm -rf "$unused"
        	echo "Removed $unused"
    	else
        	echo "Files not found: $unused"
    	fi
	done
	
	# Copy all windows specific files to the target dir
	echo "Copy windows specific files to $target_dir..."
	for dir in "$windows_dir" "$config_dir_win" "$preflash_dir_win"; do
    	find "$dir" -maxdepth 1 -type f -exec cp {} "$target_dir" \;
	done
	echo "Copied all files to $target_dir."
	
	# Build
	echo "Starting build..."
	chmod a+x "$target_dir"
	echo "cd $target_dir"
	cd "$target_dir" || { echo "Error with changing to $target_dir"; exit 1; }
	if make; then
    	echo "Build successful."
	else
    	echo "Error in the build process."
    	exit 1
	fi
	
	echo "Finish build."
	echo "Start after build processes..."

	# Copy output to output-dir
	rm -rf "$output_dir"
	mkdir -p "$output_dir"
	cp fastboot-assistant "$output_dir"
	chmod a+x "$output_dir"
	echo "The application are ready in the $output_dir."

	# Cleanup prompt
	while true; do
    	read -p "Do you want cleaning old files? (j/n)/(y/n): " answer
    	case "$answer" in
        	j|J|y|Y )
            	echo "Start make clean..."
            	make clean
            	rm -rf "$target_dir"
            	echo "Cleaning successful."
            	break
            	;;
        	n|N )
            	echo "No cleaning."
            	break
            	;;
        	* )
            	echo "Please use 'j' or 'y' or 'n'."
            	;;
    	esac
	done
}

# function to build the debian package
debian_package_build() {
	echo "Start Debian package build..."
	echo "Changing to build directory."
	cd "$source_dir" || { echo "Error with changing to $source_dir"; exit 1; }
	# Remove files from previous build
	echo "Delete old build files."
	rm -r deb/usr/

	# Prepare deb files for packaging
	echo "Start building..."
	echo "Create required directories..."
	mkdir -p deb/usr/bin/fastboot-assistant
	mkdir -p deb/usr/share/icons/hicolor/256x256/apps/
	mkdir -p deb/usr/share/applications/
	echo "Copy all files to deb/usr/bin..."
	cp -r  "$output_dir/fastboot-assistant" deb/usr/bin/fastboot-assistant/
	cp "$build_dir/sweet_unix.png" deb/usr/share/icons/hicolor/256x256/apps/
	cp "$build_dir/fastboot-assistant.desktop" deb/usr/share/applications/

	# set authorisations with 'chmod'
	echo "Set authorisations..."
	chmod a+x deb/usr/bin/fastboot-assistant
	chmod 755 deb/DEBIAN

	# Build deb package
	echo "Build package..."
	echo "Set version..."
	sed -i "2s/.*/Version: $VERSION/" deb/DEBIAN/control
	echo "Build DEBIAN package..."
	dpkg-deb --build -Zxz --root-owner-group deb
	mv deb.deb fastboot-assistant.deb
	echo "Package ready."
}

rpm_build() {
	# Prepare rpm files for packaging
	echo "Changing to build directory."
	cd "$source_dir" || { echo "Error with changing to $source_dir"; exit 1; }
	echo "Remove old build files..."
	rm -rf rpmbuild/SOURCES
	
	echo "Create required directories..."
	mkdir -p rpmbuild/SOURCES/fastboot-assistant-$VERSION
	echo "Copy files..."
	cp -r "$output_dir/fastboot-assistant" rpmbuild/SOURCES/fastboot-assistant-$VERSION/fastboot-assistant
	chmod a+x rpmbuild/SOURCES/fastboot-assistant-$VERSION/fastboot-assistant

	# Check if files exist before copying
	if [ -f "$build_dir/fastboot-assistant.desktop" ]; then
    	cp "$build_dir/fastboot-assistant.desktop" rpmbuild/SOURCES/fastboot-assistant-$VERSION/
	fi

	if [ -f "$build_dir/sweet_unix.png" ]; then
	    cp "$build_dir/sweet_unix.png" rpmbuild/SOURCES/fastboot-assistant-$VERSION/
	fi

	echo "Build RPM..."
	echo "Changing directory..."
	cd rpmbuild/SOURCES/
	echo "Create Tar..."
	tar -czvf fastboot-assistant-$VERSION.tar.gz fastboot-assistant-$VERSION
	cd ../../
	echo "Copy everything to $HOME"
	cp -r rpmbuild "$HOME/"
	echo "Set version..."
	sed -i "2s/.*/Version:        $VERSION/" ./rpmbuild/SPECS/fastboot-assistant.spec
	echo "Build package..."
	rpmbuild -ba ./rpmbuild/SPECS/fastboot-assistant.spec --without debuginfo
}

windows_zip_build() {
	echo "Start building zip-file..."
	echo "Changing to $windows_dir"
	cd "$windows_dir"
	echo "Copy files..."
	cp "$source_dir/fastboot-assistant.deb" "$windows_dir"
	# create zip-file
	echo "Build zip-file..."
	zip -r "$zip_name" "${zip_files[@]}"
	echo "Files were successfully packed in $zip_name."
}

#
# start from the main program
#
echo "--------------------------------"
echo "fastboot-assistant build script."
echo "--------------------------------"

echo "All files are built in the folder 'build-project'."
# Check if target directory exists
while true; do
	read -p "Must build-project be created? (j/n) (y/n): " answer
	case "$answer" in 
		j|J|y|Y)
			echo "Create Directory..."
        	rm -rf "$target_dir"
        	mkdir "$target_dir"
        	echo "Ready."
			break
			;;
		n|N)
			echo "Not created."
			break
			;;
		* )
			echo "Please use 'j' or 'y' or 'n'."
			;;
	esac
done

# choose between the build for linux or windows
echo "For which operating system (OS) should the fastboot-assistant be built?"
while true; do
	read -p "Linux (l) / Windows via WSL (w) / or not (n): " answer
	case "$answer" in 
		l|L)
        	build_program_linux
        	echo "Build finished."
			break
			;;
		w|W)
			build_program_windows
			echo "Build finished."
			break
			;;
		n|N)
			echo "No building."
			break
			;;
		* )
			echo "Please use 'l' or 'w' or 'n'."
			;;
	esac
done

# choose between Debian package, RPM build or neither.
echo "As which package should the fastboot-assistant be built?"
while true; do
	read -p "Debian package (d) / RPM (r) / the Zip-file for Windows (w) / nothing (n): " answer
	case "$answer" in 
		d|D)
        	debian_package_build
        	echo "Build finished."
  			echo "The package are at the $source_dir"
			break
			;;
		r|R)
			rpm_build
			echo "Build finished."
  			echo "The package are at $HOME/rpmbuild/RPMS/"
			break
			;;
		w|W)
			debian_package_build
			echo "Build finished."
  			echo "The package are at the $source_dir"
  			windows_zip_build
  			echo "Build finished."
  			echo "The package are at the $source_dir"
  			break
  			;;
		* )
			echo "No package building."
			break
			;;
	esac
done

# change to the source_dir
cd "$source_dir"

# choose between Debian package, RPM build or neither.
echo "Should another package be built??"
while true; do
	read -p "Debian package (d) / RPM (r) / the Zip-file for Windows (w) / nothing (n): " answer
	case "$answer" in 
		d|D)
        	echo "Cleaning..."
        	rm -rf "$output_dir"
        	rm -rf "$target_dir"
        	
        	# start another loop to run make
        	while true; do
        		read -p "Must the program be built beforehand? (j/n) (y/n): " answer
        		case "$answer" in
        			j|J|y|Y)
        				build_program_linux
        				echo "Build finished."
        				break
        				;;
        			* )
        				echo "No building."
        				break
        				;;
        		esac
        	done
        	# start package build
  			echo "Ready."
        	debian_package_build
        	echo "Build finished."
  			echo "The package are at the $source_dir"
			break
			;;
		r|R)
			echo "Cleaning..."
        	rm -rf "$output_dir"
        	rm -rf "$target_dir"
        	
        	# start another loop to run make
        	while true; do
        		read -p "Must the program be built beforehand? (j/n) (y/n): " answer
        		case "$answer" in
        			j|J|y|Y)
        				build_program_linux
        				echo "Build finished."
        				break
        				;;
        			* )
        				echo "No building."
        				break
        				;;
        		esac
        	done
        	# start package building
  			echo "Ready."
			rpm_build
			echo "Build finished."
  			echo "The package are at $HOME/rpmbuild/RPMS/"
			break
			;;
		w|W)
			echo "Cleaning..."
        	rm -rf "$output_dir"
        	rm -rf "$target_dir"
  			echo "Ready."
  			
  			# start another loop to run make
        	while true; do
        		read -p "Must the program be built beforehand? (j/n) (y/n): " answer
        		case "$answer" in
        			j|J|y|Y)
        				build_program_windows
        				echo "Build finished."
        				break
        				;;
        			* )
        				echo "No building."
        				break
        				;;
        		esac
        	done
        	# start package building
			debian_package_build
			echo "Build finished."
  			echo "The package are at the $source_dir"
  			windows_zip_build
  			echo "Build finished."
  			echo "The package are at the $source_dir"
  			break
  			;;
		* )
			echo "No package building."
			break
			;;
	esac
done


cd "$source_dir"
while true; do
	read -p "Should the output directory be deleted? (j/n) (y/n): " answer
	case "$answer" in 
		j|J|y|Y)
        	echo "Cleaning..."
        	rm -rf "$output_dir"
  			echo "Ready."
  			break
			;;
		* )
			echo "No cleaning."
			break
			;;
	esac
done

echo "------------------------------------------------"
echo "Build script of the fastboot-assistant finished!"
echo "------------------------------------------------"
