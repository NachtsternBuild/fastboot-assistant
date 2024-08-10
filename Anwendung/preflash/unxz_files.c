#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#define OUTPUT_DIR_ENV "HOME" // Name der Umgebungsvariable für das Home-Verzeichnis
#define TARGET_DIR "Downloads/ROM-Install" // Zielverzeichnis unter dem Home-Verzeichnis

void unxz_files(const char *xz_filename) 
{
    // Erhalte das Home-Verzeichnis aus der Umgebungsvariable
    const char *home_dir = getenv(OUTPUT_DIR_ENV);
    if (home_dir == NULL) 
    {
        g_fprintf(stderr, "Fehler: Home-Verzeichnis nicht gefunden.\n");
        exit(EXIT_FAILURE);
    }

    // Erstelle das vollständige Zielverzeichnis
    char output_dir_xz[512];
    snprintf(output_dir_xz, sizeof(output_dir_xz), "%s/%s", home_dir, TARGET_DIR);
    

    // Entferne die .xz Endung für den Namen der Ausgabedatei
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
        g_printf("Keine xz-komprimierte Datei!\n");
    }
    
    // Erstelle den vollständigen Pfad zur Ausgabedatei
    char output_file_xz[512];
    snprintf(output_file_xz, sizeof(output_file_xz), "%s", output_xz_filename);

    // Erstelle den Befehl für unxz
    char command[1024];
    snprintf(command, sizeof(command), "unxz -c %s > %s", xz_filename, output_file_xz);

    // Ausgabe des Befehls
    g_printf("Führe Befehl aus: %s\n", command);

    // Führe den Befehl aus
    int result = system(command);
    if (result != 0) 
    {
        g_fprintf(stderr, "Fehler beim Ausführen des Befehls\n");
        exit(EXIT_FAILURE);
    }
}
