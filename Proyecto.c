#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 50
#define MAX_USERS 100

struct User
{
    char nombredeusuario[MAX_LENGTH];
    char contraseña[MAX_LENGTH];
};

void agregarUsuario(const char *nombredeusuario, const char *contraseña)
{
    /* fopen nos permite abrir el archivo "usuarios.txt" en modo de escritura ("a" indica que se añadirá al final del archivo) */
    FILE *Archivo = fopen("usuarios.txt", "a");

    if (Archivo == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return;
    }

    /* Se escribe el nuevo usuario y contraseña en el archivo */
    fprintf(Archivo, "%s %s\n", nombredeusuario, contraseña);

    /* Se cierra el archivo */
    fclose(Archivo);
}

int leerUsuarios(struct User *usuarios)
{
    /* Se abre el archivo "usuarios.txt" en modo de lectura */
    FILE *Archivo = fopen("usuarios.txt", "r");

    if (Archivo == NULL)
    {
        printf("El archivo de usuarios no existe. Creando archivo...\n");
        /* Si el archivo no existe, se crea */
        fclose(fopen("usuarios.txt", "w"));
        return 0;
    }

    int num_usuarios = 0;

    /* Se lee cada usuario y contraseña del archivo */
    while (fscanf(Archivo, "%s %s", usuarios[num_usuarios].nombredeusuario, usuarios[num_usuarios].contraseña) != EOF)
    {
        num_usuarios++;
    }

    /* Se cierra el archivo */
    fclose(Archivo);
    return num_usuarios;
}
