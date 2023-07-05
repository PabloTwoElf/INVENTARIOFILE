#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funciones.h"


int main() {
    Producto productos[MAX_PRODUCTOS];

    // Inicializar productos
    for (int i = 0; i < MAX_PRODUCTOS; i++) {
        strcpy(productos[i].nombre, "");
        strcpy(productos[i].descripcion, "");
        productos[i].cantidad = 0;
        productos[i].precio = 0;
    }

    // Cargar inventario desde archivo
    cargarInventario(productos);

    int opcion;

    do {
        printf("\n");
        printf("1. Mostrar inventario\n");
        printf("2. Ingresar nuevo producto personalizado\n");
        printf("3. Modificar un producto\n");
        printf("4. Eliminar un producto\n");
        printf("5. Guardar inventario\n");
        printf("6. Salir\n");

        printf("Selecciona una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                mostrarInventario(productos);
                break;
            case 2:
                ingresarProductoPersonalizado(productos);
                break;
            case 3:
                modificarProducto(productos);
                break;
            case 4:
                eliminarProducto(productos);
                break;
            case 5:
                guardarInventario(productos);
                break;
            case 6:
                printf("Hasta luego. ¡Gracias por utilizar el sistema!\n");
                break;
            default:
                printf("Opción no válida. Intenta de nuevo.\n");
                break;
        }
    } while (opcion != 6);

    

    return 0;
}