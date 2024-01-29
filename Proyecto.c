#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 50
#define MAX_USERS 100
#define MAX_PRODUCTOS 100

/* Definición de la estructura de usuario */
struct User
{
    char nombredeusuario[MAX_LENGTH];
    char contraseña[MAX_LENGTH];
};

/* Función para agregar un nuevo usuario */
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

/* Función para leer los usuarios desde el archivo */
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

/* Definición de la estructura de producto */
struct Producto
{
    char codigo[20];
    char nombre[50];
    float precioCompra;
    int cantidad;
    char tipo[20];
    struct Fecha
    {
        int dia;
        int mes;
        int año;
    } fechaIngreso;
};

/* Función para calcular la utilidad de un producto */
float calcularUtilidad(struct Producto producto)
{
    return 0.1 * producto.precioCompra; // Utilidad es el 10% del precio de compra
}

/* Función para guardar el inventario en el archivo */
void guardarInventario(struct Producto inventario[], int numProductos)
{
    /* Se abre el archivo "inventario.txt" en modo de escritura */
    FILE *archivost = fopen("inventario.txt", "w");
    if (archivost == NULL)
    {
        printf("Error al abrir el archivo.");
        return;
    }

    /* Se escribe cada producto en el archivo */
    for (int i = 0; i < numProductos; i++)
    {
        fprintf(archivost, "%s %s %.2f %d %s %d/%d/%d\n",
                inventario[i].codigo,
                inventario[i].nombre,
                inventario[i].precioCompra,
                inventario[i].cantidad,
                inventario[i].tipo,
                inventario[i].fechaIngreso.dia,
                inventario[i].fechaIngreso.mes,
                inventario[i].fechaIngreso.año);
    }

    /* Se cierra el archivo */
    fclose(archivost);
}

/* Función para cargar el inventario desde el archivo */
int cargarInventario(struct Producto inventario[])
{
    /* Se abre el archivo "inventario.txt" en modo de lectura */
    FILE *archivost = fopen("inventario.txt", "r");
    if (archivost == NULL)
    {
        printf("Error al abrir el archivo.");
        return 0;
    }

    int numProductos = 0;
    /* Se lee cada producto del archivo */
    while (fscanf(archivost, "%s %s %f %d %s %d/%d/%d",
                  inventario[numProductos].codigo,
                  inventario[numProductos].nombre,
                  &inventario[numProductos].precioCompra,
                  &inventario[numProductos].cantidad,
                  inventario[numProductos].tipo,
                  &inventario[numProductos].fechaIngreso.dia,
                  &inventario[numProductos].fechaIngreso.mes,
                  &inventario[numProductos].fechaIngreso.año) == 8)
    {
        numProductos++;
    }

    /* Se cierra el archivo */
    fclose(archivost);
    return numProductos;
}

/* Función para ingresar nuevos productos */
int ingresarProducto(struct Producto inventario[], int numProductos)
{
    int cantidadProductos;
    printf("\nCuantos productos desea ingresar? ");
    scanf("%d", &cantidadProductos);

    /* Se solicita información para cada producto */
    for (int i = 0; i < cantidadProductos; i++)
    {
        printf("\nIngrese los datos para el producto %d:\n", i + 1);
        printf("Codigo: ");
        scanf("%s", inventario[numProductos + i].codigo);
        printf("Nombre: ");
        scanf("%s", inventario[numProductos + i].nombre);
        printf("Precio de compra: ");
        scanf("%f", &inventario[numProductos + i].precioCompra);
        printf("Cantidad: ");
        scanf("%d", &inventario[numProductos + i].cantidad);
        printf("Tipo de producto: ");
        scanf("%s", inventario[numProductos + i].tipo);
        printf("Fecha de ingreso (DD MM YYYY): ");
        scanf("%d %d %d", &inventario[numProductos + i].fechaIngreso.dia,
              &inventario[numProductos + i].fechaIngreso.mes,
              &inventario[numProductos + i].fechaIngreso.año);
    }

    /* Se guarda el inventario después de ingresar los nuevos productos */
    guardarInventario(inventario, numProductos + cantidadProductos);

    return numProductos + cantidadProductos;
}

/* Función para buscar un producto por su código */
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
            printf("Tipo de producto: %s\n", inventario[i].tipo);
            printf("Fecha de ingreso: %d/%d/%d\n", inventario[i].fechaIngreso.dia,
                   inventario[i].fechaIngreso.mes,
                   inventario[i].fechaIngreso.año);
            printf("Utilidad: %.2f\n", calcularUtilidad(inventario[i]));
            return;
        }
    }

    printf("Producto no encontrado.\n");
}

/* Función para mostrar la lista de productos disponibles */
void mostrarProductos(struct Producto inventario[], int numProductos)
{
    printf("\nLista de productos disponibles:\n");
    for (int i = 0; i < numProductos; i++)
    {
        printf("%d. Nombre: %s, Codigo: %s\n", i + 1, inventario[i].nombre, inventario[i].codigo);
    }
}

int main()
{
    struct User usuarios[MAX_USERS];
    int num_usuarios = leerUsuarios(usuarios);

    int opcion;

    while (1)
    {
        printf("\nSeleccione una opcion:\n");
        printf("1. Ingresar\n");
        printf("2. Crear usuario\n");
        printf("3. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
        {
            char input_nombredeusuario[MAX_LENGTH];
            char input_contraseña[MAX_LENGTH];

            printf("\nIngrese su nombre de usuario: ");
            scanf("%s", input_nombredeusuario);
            printf("Ingrese su contrasena: ");
            scanf("%s", input_contraseña);

            int i;
            for (i = 0; i < num_usuarios; i++)
            {
                if (strcmp(input_nombredeusuario, usuarios[i].nombredeusuario) == 0 && strcmp(input_contraseña, usuarios[i].contraseña) == 0)
                {
                    printf("Inicio de sesion exitoso. Bienvenido, %s\n", input_nombredeusuario);

                    int opcion_despues_logeo;
                    while (1)
                    {
                        printf("\nSeleccione una opcion:\n");
                        printf("1. Gestionar inventario\n");
                        printf("2. Cerrar sesion\n");
                        printf("Opcion: ");
                        scanf("%d", &opcion_despues_logeo);

                        if (opcion_despues_logeo == 1)
                        {
                            printf("\nGestionando inventario...\n");

                            struct Producto inventario[MAX_PRODUCTOS];
                            int numProductos = 0;

                            /* Cargar el inventario desde el archivo */
                            numProductos = cargarInventario(inventario);

                            int opcion_inventario;
                            do
                            {
                                printf("\nMenu de gestion del inventario:\n");
                                printf("1. Ingresar nuevos productos\n");
                                printf("2. Buscar producto por codigo\n");
                                printf("3. Mostrar nombres y codigos de productos disponibles\n");
                                printf("0. Salir\n");
                                printf("Ingrese su opcion: ");
                                scanf("%d", &opcion_inventario);

                                switch (opcion_inventario)
                                {
                                case 1:
                                    numProductos = ingresarProducto(inventario, numProductos);
                                    break;
                                case 2:
                                    buscarProducto(inventario, numProductos);
                                    break;
                                case 3:
                                    mostrarProductos(inventario, numProductos);
                                    break;
                                case 0:
                                    printf("Saliendo del inventario...\n");
                                    break;
                                default:
                                    printf("Opcion no valida. Intente de nuevo.\n");
                                    break;
                                }
                            } while (opcion_inventario != 0);
                            // Fin de la gestión del inventario
                        }
                        else if (opcion_despues_logeo == 2)
                        {
                            printf("\nSaliendo...\n");
                        }
                        else
                        {
                            printf("\nOpción no valida.\n");
                        }
                        break;
                    }
                    break;
                }
            }
            if (i == num_usuarios)
            {
                printf("Nombre de usuario o contrasena incorrectos.\n");
            }
        }
        break;
        case 2:
        {
            char nuevo_nombredeusuario[MAX_LENGTH];
            char nueva_contraseña[MAX_LENGTH];

            printf("\nIngrese un nuevo nombre de usuario: ");
            scanf("%s", nuevo_nombredeusuario);
            printf("Ingrese una nueva contrasena: ");
            scanf("%s", nueva_contraseña);

            agregarUsuario(nuevo_nombredeusuario, nueva_contraseña);
            printf("Usuario creado con exito.\n");

            num_usuarios = leerUsuarios(usuarios);
        }
        break;
        case 3:
            printf("\nSaliendo del programa...\n");
            return 0;
        default:
            printf("\nOpción no valida.\n");
            break;
        }
    }
}
