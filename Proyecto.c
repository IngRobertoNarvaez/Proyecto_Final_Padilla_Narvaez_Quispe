#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 50
#define MAX_USERS 100
#define MAX_PRODUCTOS 100

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
struct Producto
{
    char codigo[20];
    char nombre[50];
    float precioCompra;
    int cantidad;
};

float calcularUtilidad(struct Producto producto)
{
    /* Se calcula la utilidad como el 10% del precio de compra */
    float utilidad = 0.1 * producto.precioCompra;
    return utilidad;
}

void guardarInventario(struct Producto inventario[], int numProductos)
{
    /* Se abre el archivo "inventario.txt" en modo de escritura */
    FILE *archivost;
    archivost = fopen("inventario.txt", "w");
    if (archivost == NULL)
    {
        printf("Error al abrir el archivo.");
        return;
    }

    /* Se escribe cada producto en el archivo */
    for (int i = 0; i < numProductos; i++)
    {
        fprintf(archivost, "%s %s %.2f %d\n", inventario[i].codigo, inventario[i].nombre, inventario[i].precioCompra, inventario[i].cantidad);
    }

    /* Se cierra el archivo */
    fclose(archivost);
}

int cargarInventario(struct Producto inventario[])
{
    /* Se abre el archivo "inventario.txt" en modo de lectura */
    FILE *archivost;
    archivost = fopen("inventario.txt", "r");
    if (archivost == NULL)
    {
        printf("Error al abrir el archivo.");
        return 0;
    }

    int numProductos = 0;
    /* Se lee cada producto del archivo */
    while (fscanf(archivost, "%s %s %f %d", inventario[numProductos].codigo, inventario[numProductos].nombre, &inventario[numProductos].precioCompra, &inventario[numProductos].cantidad) == 4)
    {
        numProductos++;
    }

    /* Se cierra el archivo */
    fclose(archivost);
    return numProductos;
}

int ingresarProducto(struct Producto inventario[], int numProductos)
{
    printf("\nIngrese los datos para el nuevo producto:\n");
    printf("Codigo: ");
    scanf("%s", inventario[numProductos].codigo);
    printf("Nombre: ");
    scanf("%s", inventario[numProductos].nombre);
    printf("Precio de compra: ");
    scanf("%f", &inventario[numProductos].precioCompra);
    printf("Cantidad: ");
    scanf("%d", &inventario[numProductos].cantidad);

    /* Se guarda el inventario después de ingresar un nuevo producto */
    guardarInventario(inventario, numProductos + 1);

    return numProductos + 1;
}

void buscarProducto(struct Producto inventario[], int numProductos)
{
    char codigoBuscado[20];
    printf("\nIngrese el codigo del producto a buscar: ");
    scanf("%s", codigoBuscado);

    /* Se busca el producto por su código */
    for (int i = 0; i < numProductos; i++)
    {
        if (strcmp(inventario[i].codigo, codigoBuscado) == 0)
        {
            /* Se muestra la información del producto */
            printf("Nombre: %s\n", inventario[i].nombre);
            printf("Codigo: %s\n", inventario[i].codigo);
            printf("Cantidad: %d\n", inventario[i].cantidad);
            printf("Precio de compra: %.2f\n", inventario[i].precioCompra);
            printf("Utilidad: %.2f\n", calcularUtilidad(inventario[i]));
            return;
        }
    }

    printf("Producto no encontrado.\n");
}

void mostrarProductos(struct Producto inventario[], int numProductos)
{
    printf("\nLista de productos disponibles:\n");
    for (int i = 0; i < numProductos; i++)
    {
        printf("%d. Nombre: %s, Codigo: %s\n", i + 1, inventario[i].nombre, inventario[i].codigo);
    }
}