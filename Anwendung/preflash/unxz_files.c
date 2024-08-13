#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <sys/stat.h>
#include <sys/types.h>

#define OUTPUT_DIR_ENV "HOME" // home dir
#define TARGET_DIR "Downloads/ROM-Install" // target dir

void unxz_files(const char *xz_filename) 
{
    // get home dir
    const char *home_dir = getenv(OUTPUT_DIR_ENV);
    if (home_dir == NULL) 
    {
        fprintf(stderr, "Fehler: Home-Verzeichnis nicht gefunden.\n");
        exit(EXIT_FAILURE);
    }

    // make full path
    char output_dir_xz[512];
    snprintf(output_dir_xz, sizeof(output_dir_xz), "%s/%s", home_dir, TARGET_DIR);
    

    // remove .xz from the output
    char output_xz_filename[512];
    const char *dot_xz = strrchr(xz_filename, '.');
    if (dot_xz && strcmp(dot_xz, ".xz") == 0) 
    {
        size_t base_length = dot_xz - xz_filename;
        strncpy(output_xz_filename, xz_filename, base_length);
        output_xz_filename[base_length] = '\0';
    } 
    
    else 
    {
        strncpy(output_xz_filename, xz_filename, sizeof(output_xz_filename));
        g_print("Keine xz-komprimierte Datei!\n");
    }
    
    // make full path to outout file
    char output_file_xz[512];
    snprintf(output_file_xz, sizeof(output_file_xz), "%s", output_xz_filename);

    // create unxz command
    char command[1024];
    snprintf(command, sizeof(command), "unxz -c %s > %s", xz_filename, output_file_xz);

    // output of the command
    g_print("Führe Befehl aus: %s\n", command);

    // run command
    int result = system(command);
    if (result != 0) 
    {
        g_fprintf(stderr, "Fehler beim Ausführen des Befehls\n");
        exit(EXIT_FAILURE);
    }
}
