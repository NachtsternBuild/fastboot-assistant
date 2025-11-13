/**
* fastboot_assistant.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
* Usage:
* fastboot-assistant
* fastboot-assistant -debug
* fastboot-assistant -v
* fastboot-assistant -help
*/
#include "fastboot_assistant.h"

#define MAX_BUFFER_SIZE 256
#define SEARCH_STRING "fastboot-assistant" 
#define SOURCES_DIR "/etc/apt/sources.list.d"

// define option for debug mode
bool debug_mode = false;
bool debug_snap = false;
bool debug_mock = false;

// define the local domain
const char *LOCALE_DOMAIN = "fastboot-assistant";
// define the filter file
const char *DEFAULT_FILTER = "/etc/fastboot-assistant/filter.conf";
// define the local dir
const char *LOCALEDIR_PATH = "local/";

// define about infos
const char *app_icon = "/usr/share/icons/hicolor/256x256/apps/sweet_unix.png";
const char *app_name = "Fastboot-Assistant";
const char *developer_name = "NachtsternBuild";
const char *version = "0.9.1.dev";
const char *release_notes_version = "0.9.1";
const char *release_notes = "\
<p>\
  This release adds this features:\
</p>\
<ul>\
  <li>Switch UI to ATL UIBase.</li>\
  <li>Rework project structure.</li>\
  <li>Add support for flatpak.</li>\
  <li>Improve support for libadwaita.</li>\
  <li>Bug fixes and performance improvements.</li>\
  <li>Translation updates.</li>\
</ul>\
  ";
const char *comments = " The Fastboot Assistant facilitates the installation of Custom-ROMs and GSIs on Android devices. It offers a user-friendly GTK4/Libadwaita interface and integrates tools such as adb, fastboot, and heimdall.";
const char *website = "https://nachtsternbuild.github.io/fastboot-assistant/";
const char *issue_url = "https://github.com/NachtsternBuild/fastboot-assistant/issues";
const char *support_url = "https://github.com/NachtsternBuild/fastboot-assistant/discussions";
const char *copyright = "© 2025 NachtsternBuild";
const char *developers[] = {
	"NachtsternBuild",
	NULL
};
const char *artists[] = {
	"GNOME Design Team",
	"NachtsternBuild",
	NULL
};
const char *documentation_url = "https://github.com/NachtsternBuild/fastboot-assistant/wiki";
const char *font_usage = "This application uses font data from <a href='https://example.org'>somewhere</a>.";
const char *special_thanks[] = {
	"Tux",
	NULL
};

// show version info about fastboot-assistant
void version_details() 
{
	const char *env = get_execution_environment();
	char package[20];
		
	// flatpak		
    if (strcmp(env, "flatpak") == 0) 
    {
        snprintf(package, sizeof(package), "Flatpak");
    }
    // snap
    else if (strcmp(env, "snap") == 0) 
    {
        snprintf(package, sizeof(package), "Snap");
    } 
    
    // PPA/DEB
    else 
    {
        int result = search_file_directory(SOURCES_DIR, SEARCH_STRING);
    
    	if (result == -1) 
    	{
        	LOGE("Error check for PPA files");
        	exit(1);
   	 	}
    
    	else if (result == 1) 
    	{
        	snprintf(package, sizeof(package), "Debian Package PPA");
    	} 
    
    	else 
    	{
        	snprintf(package, sizeof(package), "Local Debian Package");
    	}
    }
    
    g_print("Fastboot-Assistant [%s] %s", package, version);  
}

void help()
{
	g_print("Usage: fastboot-assistant <option>\n");
	g_print("Options:\n");
	g_print("   -debug [flags] – Debugging\n");
	g_print("          -snp    – Set snap environment\n");
	g_print("          -flp    – Set flatpak environment\n");
	g_print("   -v, --version  – Show Version Info\n");
	g_print("   -h, --help     – Show this help\n");
	g_print("\n");
	g_print("More Infos:\n");
	g_print("man fastboot-assistant - Only for Debian Package\n");
	g_print("Project Site:\n");
	g_print("https://github.com/NachtsternBuild/fastboot-assistant\n");
	g_print("Wiki:\n");
	g_print("https://github.com/NachtsternBuild/fastboot-assistant/wiki\n");
	g_print("Issues:\n");
	g_print("https://github.com/NachtsternBuild/fastboot-assistant/issues\n");
}

/* main function */
int main(int argc, char *argv[]) 
{
	int new_argc = 0;
	char *new_argv[argc];

	new_argv[new_argc++] = argv[0];
	
	// check arguments 
    for (int i = 1; i < argc; i++) 
    {       
        if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--d") == 0 || strcmp(argv[i], "-debug") == 0 || strcmp(argv[i], "--debug") == 0) 
        {
            debug_mode = true;
            continue;
        }

        if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--v") == 0 || strcmp(argv[i], "--version") == 0 || strcmp(argv[i], "-version") == 0) 
        {
            version_details();
            return 0;
        }

        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) 
        {
            help();
            return 0;
        }

        // use debug mode, if debug mode is active
        if (debug_mode) 
        {
            if (strcmp(argv[i], "-snp") == 0) 
            {
                debug_snap = true;
                setenv("SNAP", "/tmp/snap-debug", 1);
                g_print("[DEBUG] SNAP-Env: $SNAP=%s\n", getenv("SNAP"));
                continue;
            }
            
            else if (strcmp(argv[i], "-flp") == 0) 
            {
                debug_mock = true;
                setenv("FLATPAK_ID", "io.github.nachtsternbuild.Fastboot-Assistant", 1);
                g_print("[DEBUG] Flatpak-End: $FLATPAK_ID=%s\n", getenv("FLATPAK_ID"));
                continue;
            }    
        } 
        
        else 
        {
            // error without debug flag
            if (strncmp(argv[i], "-", 1) == 0)
            {
                fprintf(stderr, "Warning: '%s' can only be used with -debug.\n", argv[i]);
            }
        }
    new_argv[new_argc++] = argv[i];    
    }
	
	g_autoptr(AdwApplication) app = NULL;

    app = adw_application_new("io.github.nachtsternbuild.Fastboot-Assistant", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK (activate_fastboot_assistant), NULL);

    return g_application_run(G_APPLICATION (app), new_argc, new_argv);
}
