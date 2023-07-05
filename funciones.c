#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funciones.h"

void mostrarInventario(Producto productos[]) {
    printf("----------------INVENTARIO DE PRODUCTOS TALLER----------------------------------------\n");
    printf(" ID  |     NOMBRE               |     DESCRIPCION                |   CANTIDAD   |    PRECIO   \n");
    printf("--------------------------------------------------------------------------------------\n");

    int i;
    for (i = 0; i < MAX_PRODUCTOS; i++) {
        if (productos[i].cantidad != 0) {
            printf("%-2d   | %-22s | %-30s | %12.0f | %12.2f\n", i + 1, productos[i].nombre, productos[i].descripcion, productos[i].cantidad, productos[i].precio);
        }
    }

    printf("--------------------------------------------------------------------------------------\n");
}

void modificarProducto(Producto productos[]) {
    int opcion;

    printf("¿Qué producto deseas modificar?\n");
    for (int i = 0; i < MAX_PRODUCTOS; i++) {
        if (productos[i].cantidad != 0) {
            printf("%d. %s\n", i + 1, productos[i].nombre);
        }
    }
    printf("%d. Cancelar\n", MAX_PRODUCTOS + 1);

    printf("Selecciona una opción: ");
    scanf("%d", &opcion);

    if (opcion < 1 || opcion > MAX_PRODUCTOS + 1) {
        printf("Opción no válida. Intenta de nuevo.\n");
        return;
    }

    if (opcion == MAX_PRODUCTOS + 1) {
        printf("Operación cancelada.\n");
        return;
    }

    int index = opcion - 1;
    Producto *producto = &productos[index];

    printf("Ingresa la nueva cantidad para el Producto %d: ", opcion);
    scanf("%f", &producto->cantidad);

    printf("Ingresa el nuevo nombre para el Producto %d: ", opcion);
    scanf(" %[^\n]", producto->nombre);

    printf("Ingresa la nueva descripción para el Producto %d: ", opcion);
    scanf(" %[^\n]", producto->descripcion);

    printf("Ingresa el nuevo precio para el Producto %d: ", opcion);
    scanf("%f", &producto->precio);

    printf("Producto %d modificado exitosamente.\n", opcion);
}
    // ...


void ingresarProductoPersonalizado(Producto productos[]) {
     int i;

    for (i = 0; i < MAX_PRODUCTOS; i++) {
        if (productos[i].cantidad == 0) {
            printf("Ingrese el nombre del producto: ");
            scanf(" %[^\n]", productos[i].nombre);

            printf("Ingrese la descripción del producto: ");
            scanf(" %[^\n]", productos[i].descripcion);

            printf("Ingrese la cantidad del producto: ");
            scanf("%f", &productos[i].cantidad);

            printf("Ingrese el precio del producto: ");
            scanf("%f", &productos[i].precio);

            printf("Producto ingresado exitosamente.\n");
            return;
        }
    }
    // ...
}
void eliminarProducto(Producto productos[]) {
    int opcion;

    printf("¿Qué producto deseas eliminar?\n");
    for (int i = 0; i < MAX_PRODUCTOS; i++) {
        if (productos[i].cantidad != 0) {
            printf("%d. %s\n", i + 1, productos[i].nombre);
        }
    }

    printf("Selecciona el número de producto que deseas eliminar: ");
    scanf("%d", &opcion);

    // Validar la opción seleccionada
    if (opcion < 1 || opcion > MAX_PRODUCTOS) {
        printf("Opción no válida. Intenta de nuevo.\n");
        return;
    }

    // Obtener el índice correspondiente al producto seleccionado
    int index = opcion - 1;

    // Eliminar el producto estableciendo sus campos en cero
    productos[index].cantidad = 0;
    productos[index].precio = 0;
    strcpy(productos[index].nombre, "");
    strcpy(productos[index].descripcion, "");

    printf("Producto %d eliminado exitosamente.\n", opcion);
}


void guardarInventario(Producto productos[]) {
    FILE *archivo = fopen("inventario", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    fprintf(archivo, "---------------------------------INVENTARIO DE PRODUCTOS TALLER----------------------------------------\n");
    fprintf(archivo, " ID  |     NOMBRE               |     DESCRIPCION                |   CANTIDAD   |    PRECIO   \n");
    fprintf(archivo, "-------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < MAX_PRODUCTOS; i++) {
        if (productos[i].cantidad != 0) {
            fprintf(archivo, "%-2d   | %-22s | %-30s | %12.0f | %12.2f\n", i + 1, productos[i].nombre, productos[i].descripcion, productos[i].cantidad, productos[i].precio);
        }
    }

    fprintf(archivo, "--------------------------------------------------------------------------------------\n");

    fclose(archivo);
    printf("Inventario guardado exitosamente.\n");
}

void cargarInventario(Producto productos[]) {
    FILE *archivo = fopen("inventario", "r");
    if (archivo == NULL) {
        printf("No se encontró el archivo de inventario. Se creará uno nuevo.\n");
        return;
    }

    char linea[150]; // Tamaño suficiente para almacenar una línea del archivo

    int i = 0;
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        // Utilizar strtok para dividir la línea en los campos separados por punto y coma
        char *nombre = strtok(linea, ";");
        char *descripcion = strtok(NULL, ";");
        float cantidad = atof(strtok(NULL, ";"));
        float precio = atof(strtok(NULL, ";"));

        // Asignar los valores al producto correspondiente en la estructura productos[]
        strcpy(productos[i].nombre, nombre);
        strcpy(productos[i].descripcion, descripcion);
        productos[i].cantidad = cantidad;
        productos[i].precio = precio;

        i++;
    }

    fclose(archivo);
    printf("Inventario cargado exitosamente.\n");
}



void editarDatos(Producto productos[]) {
    FILE *archivo = fopen("inventario", "r+");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    // Mostrar inventario para seleccionar el producto a editar
    mostrarInventario(productos);

    int opcion;
    printf("Selecciona el número de producto que deseas editar: ");
    scanf("%d", &opcion);

    // Validar la opción seleccionada
    if (opcion < 1 || opcion > MAX_PRODUCTOS) {
        printf("Opción no válida. Intenta de nuevo.\n");
        fclose(archivo);
        return;
    }

    int index = opcion - 1;
    Producto *producto = &productos[index];

    // Mover el puntero de lectura/escritura al inicio del registro del producto seleccionado
    fseek(archivo, sizeof(Producto) * index, SEEK_SET);

    // Sobrescribir los datos del producto en el archivo
    fwrite(producto, sizeof(Producto), 1, archivo);

    fclose(archivo);

    printf("Producto %d modificado exitosamente.\n", opcion);
}


