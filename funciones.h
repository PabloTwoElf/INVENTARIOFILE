#ifndef FUNCIONES_H
#define FUNCIONES_H

#define MAX_PRODUCTOS 10

typedef struct {
    char nombre[20];
    char descripcion[100];
    float cantidad;
    float precio;
} Producto;

void mostrarInventario(Producto productos[]);
void modificarProducto(Producto productos[]);
void ingresarProductoPersonalizado(Producto productos[]);

void eliminarProducto(Producto productos[]);
void guardarInventario(Producto productos[]);
void cargarInventario(Producto productos[]);
void editarDatos(Producto productos[]);

#endif
