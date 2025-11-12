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

// define option for debug mode
bool debug_mode = false;
bool debug_snap = false;
bool debug_mock = false;

#define APP_VERSION "0.9.1.dev"

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

/* main function */
int main(int argc, char *argv[]) 
{
	// check arguments 
    for (int i = 1; i < argc; i++) 
    {
        if (strcmp(argv[i], "-debug") == 0 || strcmp(argv[i], "--debug") == 0) 
        {
            debug_mode = true;
            continue;
        }

        if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0) 
        {
            printf("Fastboot-Assistant Version %s\n", APP_VERSION);
            return 0;
        }

        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) 
        {
            printf("Verwendung: %s [Optionen]\n\n", argv[0]);
            printf("Optionen:\n");
            printf("  -debug [Flags]      Debugmodus aktivieren (z.B. -snp, -mock)\n");
            printf("  -v, --version       Versionsnummer anzeigen\n");
            printf("  -h, --help          Diese Hilfe anzeigen\n");
            return 0;
        }

        // Debug-Unteroptionen nur gültig, wenn -debug aktiv
        if (debug_mode) 
        {
            if (strcmp(argv[i], "-snp") == 0) 
            {
                debug_snap = true;
                setenv("SNAP", "/tmp/snap-debug", 1);
                g_print("[DEBUG] SNAP-Umgebung simuliert: $SNAP=%s\n", getenv("SNAP"));
                continue;
            }
            
            else if (strcmp(argv[i], "-flp") == 0) 
            {
                debug_mock = true;
                g_print("[DEBUG] Mock-Modus aktiviert.\n");
                continue;
            }
        } 
        
        else 
        {
            // Falls jemand versucht, Debug-Unterflags ohne -debug zu setzen
            if (strncmp(argv[i], "-", 1) == 0) 
            {
                fprintf(stderr, "Warnung: '%s' kann nur mit -debug verwendet werden.\n", argv[i]);
            }
        }
    }
	
	g_autoptr(AdwApplication) app = NULL;

    app = adw_application_new("io.github.nachtsternbuild.Fastboot-Assistant", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK (activate_fastboot_assistant), NULL);

    return g_application_run(G_APPLICATION (app), argc, argv);
}
