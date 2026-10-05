/*
 * ISWZ1102 - PROGRAMACIÓN 1
 * Ejercicio: Gestión de ventas de un único producto
 * Autor: Nicolás Chisaguano - NRC 5429
 * Fecha: 4-10-2026
 *
 * El programa permite registrar un producto, venderlo (con descuento),
 * reabastecer el stock, consultar su información y ver las ganancias.
 */

#include <stdio.h>
#include <string.h>

int main()
{
    /* ---------- VARIABLES ---------- */
    int id = 0;                    /* ID del producto */
    char nombre[50] = "";          /* Nombre del producto */
    int stock = 0;                 /* Unidades disponibles */
    float precio = 0;              /* Precio unitario */

    float ganancias = 0;           /* Dinero acumulado por ventas */
    int unidades_vendidas = 0;     /* Total de unidades vendidas */

    int opcion = 0;                /* Opción elegida en el menú */
    int cantidad = 0;              /* Unidades a vender o agregar */
    float descuento = 0;           /* Descuento en porcentaje (0 a 100) */
    float subtotal = 0;            /* Venta sin descuento */
    float total_venta = 0;         /* Venta con descuento */
    int registrado = 0;            /* 0 = no hay producto, 1 = ya registrado */
    int valido = 0;                /* Bandera para validar entradas */

    /* ---------- CICLO PRINCIPAL DEL MENÚ ---------- */
    do
    {
        printf("\n==============================\n");
        printf("\tTIENDA - MENU\n");
        printf("==============================\n");
        printf("1. Registrar producto\n");
        printf("2. Vender producto\n");
        printf("3. Reabastecer stock\n");
        printf("4. Consultar producto\n");
        printf("5. Ver ganancias\n");
        printf("6. Salir\n");
        printf("Elija una opcion: ");

        /* Validar que la opción sea un número (evita letras) */
        if (scanf("%d", &opcion) != 1)
        {
            opcion = 0; /* Opción inválida */
        }
        while (getchar() != '\n'); /* Limpia el buffer de entrada */

        switch (opcion)
        {
        /* ----- 1. REGISTRAR PRODUCTO ----- */
        case 1:
            printf("\n--- REGISTRAR PRODUCTO ---\n");

            /* ID: debe ser un entero mayor que 0 */
            valido = 0;
            while (valido == 0)
            {
                printf("Ingrese el ID: ");
                if (scanf("%d", &id) == 1 && id > 0)
                {
                    valido = 1;
                }
                else
                {
                    printf("Error: el ID debe ser un numero entero mayor que 0.\n");
                }
                while (getchar() != '\n');
            }

            /* Nombre: se usa fgets para permitir espacios */
            printf("Ingrese el nombre: ");
            fgets(nombre, 50, stdin);
            nombre[strcspn(nombre, "\n")] = '\0'; /* Quita el salto de linea */

            /* Stock: entero mayor o igual a 0 */
            valido = 0;
            while (valido == 0)
            {
                printf("Ingrese la cantidad en stock: ");
                if (scanf("%d", &stock) == 1 && stock >= 0)
                {
                    valido = 1;
                }
                else
                {
                    printf("Error: el stock debe ser un numero entero mayor o igual a 0.\n");
                }
                while (getchar() != '\n');
            }

            /* Precio: decimal mayor que 0 */
            valido = 0;
            while (valido == 0)
            {
                printf("Ingrese el precio unitario: $");
                if (scanf("%f", &precio) == 1 && precio > 0)
                {
                    valido = 1;
                }
                else
                {
                    printf("Error: el precio debe ser un numero mayor que 0.\n");
                }
                while (getchar() != '\n');
            }

            /* Un producto nuevo reinicia las ventas */
            ganancias = 0;
            unidades_vendidas = 0;
            registrado = 1;
            printf("\nProducto registrado correctamente.\n");
            break;

        /* ----- 2. VENDER PRODUCTO ----- */
        case 2:
            if (registrado == 0)
            {
                printf("\nPrimero debe registrar un producto (opcion 1).\n");
            }
            else if (stock == 0)
            {
                printf("\nNo hay stock disponible. Reabastezca el producto (opcion 3).\n");
            }
            else
            {
                printf("\n--- VENDER PRODUCTO ---\n");
                printf("Stock disponible: %d\n", stock);

                /* Cantidad a vender: mayor que 0 y no mayor al stock */
                valido = 0;
                while (valido == 0)
                {
                    printf("Cuantas unidades desea vender: ");
                    if (scanf("%d", &cantidad) != 1 || cantidad <= 0)
                    {
                        printf("Error: ingrese un numero entero mayor que 0.\n");
                    }
                    else if (cantidad > stock)
                    {
                        printf("Error: stock insuficiente (solo hay %d unidades).\n", stock);
                    }
                    else
                    {
                        valido = 1;
                    }
                    while (getchar() != '\n');
                }

                /* Descuento: entre 0 y 100 */
                valido = 0;
                while (valido == 0)
                {
                    printf("Descuento en porcentaje (0 si no hay): ");
                    if (scanf("%f", &descuento) == 1 && descuento >= 0 && descuento <= 100)
                    {
                        valido = 1;
                    }
                    else
                    {
                        printf("Error: el descuento debe estar entre 0 y 100.\n");
                    }
                    while (getchar() != '\n');
                }

                /* Cálculos de la venta */
                subtotal = cantidad * precio;
                total_venta = subtotal - (subtotal * descuento / 100);

                /* Actualizar stock, ganancias y unidades vendidas */
                stock = stock - cantidad;
                ganancias = ganancias + total_venta;
                unidades_vendidas = unidades_vendidas + cantidad;

                printf("\n--- RESUMEN DE LA VENTA ---\n");
                printf("Unidades:\t%d\n", cantidad);
                printf("Subtotal:\t$%.2f\n", subtotal);
                printf("Descuento:\t%.2f%%\n", descuento);
                printf("Total:\t\t$%.2f\n", total_venta);
                printf("Venta realizada con exito.\n");
            }
            break;

        /* ----- 3. REABASTECER STOCK ----- */
        case 3:
            if (registrado == 0)
            {
                printf("\nPrimero debe registrar un producto (opcion 1).\n");
            }
            else
            {
                printf("\n--- REABASTECER STOCK ---\n");

                valido = 0;
                while (valido == 0)
                {
                    printf("Cuantas unidades desea agregar: ");
                    if (scanf("%d", &cantidad) == 1 && cantidad > 0)
                    {
                        valido = 1;
                    }
                    else
                    {
                        printf("Error: ingrese un numero entero mayor que 0.\n");
                    }
                    while (getchar() != '\n');
                }

                stock = stock + cantidad;
                printf("Stock actualizado: %d unidades.\n", stock);
            }
            break;

        /* ----- 4. CONSULTAR PRODUCTO ----- */
        case 4:
            if (registrado == 0)
            {
                printf("\nPrimero debe registrar un producto (opcion 1).\n");
            }
            else
            {
                printf("\n--- INFORMACION DEL PRODUCTO ---\n");
                printf("ID:\t\t%d\n", id);
                printf("Nombre:\t\t%s\n", nombre);
                printf("Stock:\t\t%d unidades\n", stock);
                printf("Precio:\t\t$%.2f\n", precio);
            }
            break;

        /* ----- 5. VER GANANCIAS ----- */
        case 5:
            if (registrado == 0)
            {
                printf("\nPrimero debe registrar un producto (opcion 1).\n");
            }
            else
            {
                printf("\n--- GANANCIAS ---\n");
                printf("Unidades vendidas:\t%d\n", unidades_vendidas);
                printf("Ganancias totales:\t$%.2f\n", ganancias);
            }
            break;

        /* ----- 6. SALIR ----- */
        case 6:
            printf("\nGracias por usar el programa. Hasta luego.\n");
            break;

        /* ----- OPCIÓN INVÁLIDA ----- */
        default:
            printf("\nOpcion invalida. Elija un numero del 1 al 6.\n");
        }

        /* Pausa: deja leer el resultado antes de volver a mostrar el menu */
        if (opcion != 6)
        {
            printf("\nPresione Enter para continuar...");
            getchar();
        }

    } while (opcion != 6);

    return 0;
}
