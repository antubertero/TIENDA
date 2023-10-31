
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

const char listado[] =  "ListaInventario.bin";

typedef struct
{

    int codigoID;
    char nombreProducto[20];
    int cantidadStock;
    float precio;




} stProducto;




int main()
{

    menu();

    return 0;
}


void menu()
{

    system("cls"); // Limpia la pantalla en Windows
    int menuOpci;
    printf("\n\nTIENDA EL MENDOCINO\n\n");

    printf("\n1) Ventas\n\n2) Administracion\n\nIngresar opcion: ");
    scanf("%i", &menuOpci);

    switch(menuOpci)
    {

    case 1:
        system("cls"); // Limpia la pantalla en Windows
        printf("    ----Ventas----\n\n");
        printf("\n\nMenu principal\n\n");
        menuVentas();
        break;

    default:

        menu();

        break;


    case 2:
        system("cls"); // Limpia la pantalla en Windows
        printf("    ----Administracion----\n\n1)Lista de inventario\n2)Busqueda por codigo\n3)Carga de inventario\n4)Modificar inventario\n\nIngresar opcion:  ");
        scanf("%i", &menuOpci);

        switch(menuOpci)
        {

        case 1:
            system("cls"); // Limpia la pantalla en Windows
            printf("\n\nLista de inventario");
            listadoDeProductos();

            break;

        case 2:
            system("cls"); // Limpia la pantalla en Windows
            printf("\n\nBusqueda por codigo");
            busquedaPorCodigo();

            break;

        case 3:
            system("cls"); // Limpia la pantalla en Windows
            printf("\n\nCarga de inventario");
            cargaDeInventarios();
            break;
        case 4:
            system("cls"); // Limpia la pantalla en Windows
            printf("Modificar");
            modificar();

            break;
        default:

            menu();
            break;

        }
        break;

    }

}
/// Menu ventas

/*
Esta función muestra un menú de opciones relacionadas con las ventas.
El usuario puede elegir entre iniciar una venta o volver al menú principal.
Dependiendo de la elección, se ejecuta la función correspondiente
*/


void menuVentas()
{

    system("cls"); // Limpia la pantalla en Windows
    int opcion;

    printf("1) Iniciar venta \n\n2) volver al menu principal: \n\nIngresar opcion:  ");
    scanf("%i",&opcion );
    switch(opcion)
    {

    case 1:
        system("cls"); // Limpia la pantalla en Windows
        venta();

    case 2:
        system("cls"); // Limpia la pantalla en Windows
        menu();

    default:
        system("cls"); // Limpia la pantalla en Windows
        menu();

    }

}
// venta
/*
En esta función, el usuario puede realizar ventas de productos.
Se le solicita ingresar el código del producto y la cantidad vendida.
Luego, verifica si el producto existe y si hay suficiente stock para realizar la venta.
Si es posible, actualiza el stock, calcula el total parcial y acumula el total de la compra.
La función permite al usuario agregar más productos al carrito o terminar la compra.*/


void venta()
{
    int  salida, codigoProducto, cantidadVendidas;
    float precio, totalParcial, total= 0;

    do
    {
        system("cls"); // Limpia la pantalla en Windows
        printf("\n\nIngresar el codigo del producto: ");
        scanf("%i", &codigoProducto);

        int estado = verificacionDeCodigo(codigoProducto);
        if(estado== 1)
        {

            do{
            printf("\ningresar la cantidad de unidades vendidas:  ");
            scanf("%i",&cantidadVendidas);
            if(cantidadVendidas<0){

                printf("Usted ingreso un numero negativo. INGRESAR NUEVAMENTE UN VALOR");
                Sleep(3000); // Duerme durante 3000 milisegundos (3 segundos)
                system("cls"); // Limpia la pantalla en Windows
            }
            }while(cantidadVendidas<0);

            FILE* archivo;
            archivo = fopen(listado, "r+b");
            stProducto producto;
            int entrada = 0;

            if(archivo != NULL)
            {

                while(fread(&producto, sizeof(stProducto), 1, archivo)>0)
                {

                    if(producto.codigoID == codigoProducto && producto.cantidadStock>cantidadVendidas)
                    {

                        producto.cantidadStock = producto.cantidadStock - cantidadVendidas;
                        precio = producto.precio;
                        fseek(archivo, -sizeof(stProducto), SEEK_CUR);
                        fwrite(&producto, sizeof(stProducto), 1, archivo);
                        fclose(archivo);

                        totalParcial = cantidadVendidas * precio;
                        total = total +totalParcial;

                        printf("\nPrecio total: %f", totalParcial);
                        Sleep(3000); // Duerme durante 3000 milisegundos (3 segundos)
                        entrada = 1;

                    }

                }
                if(entrada == 0)
                {
                    system("cls"); // Limpia la pantalla en Windows
                    printf("No tiene sufucientes stock para la venta. \n\nIngresar otro producto");
                    Sleep(3000); // Duerme durante 3000 milisegundos (3 segundos)
                }
            }
            else
            {

                printf("\nNo se puco abrir el archivo ");

            }


        }
        else if(estado == 0)
        {
            system("cls"); // Limpia la pantalla en Windows
            printf("el codigo ingresado no existe");
            Sleep(3000); // Duerme durante 3000 milisegundos (3 segundos)
            venta();

        }
        system("cls"); // Limpia la pantalla en Windows

        printf("\n 1) CARGAR CARRITO: \n\n2) TERMINAR COMPRA:  \n\nIngresar opcion: ");
        scanf("%i", &salida);




    }
    while(salida == 1);
    system("cls"); // Limpia la pantalla en Windows

    printf("\n\nEl total de su compra es igual a %f\n\nGRACIAS POR SU COMPRA\n", total);
    Sleep(5000); // Duerme durante 5000 milisegundos (5 segundos)

    menuVentas();


}


/// ============
/// Administracion

// modificar producto

/*Esta función permite al usuario modificar los detalles de un producto existente en
función de su código. Primero, solicita el código del producto a
modificar y verifica su existencia. Luego, ofrece opciones para modificar
diferentes aspectos del producto, como el código, el nombre, la cantidad
en stock o el precio. Después de realizar las modificaciones, actualiza la información
en el archivo de productos.*/

void modificar()
{

    int opcion, opcionMenu, codigoNuevo ;
    system("cls"); // Limpia la pantalla en Windows
    printf("\n\nIngresar el codigo del porducto que quieres modificar \n\ningresar CODIGO: ");
    scanf("%i", &opcion);
    int verificacion = verificacionDeCodigo(opcion);
    if(verificacion == 1)
    {

        FILE* archivo;
        stProducto producto;
        archivo = fopen(listado, "r+b");

        if(archivo != NULL)
        {

            while(fread(&producto, sizeof(stProducto), 1, archivo)>0)
            {

                if(opcion == producto.codigoID)
                {

                    printf("\nQue quieres modificar? \n\n1) Codigo\n2) Nombre\n3) Cantidad\n4) Precio\n\nIngresar opcion:  ");
                    scanf("%i", &opcionMenu);
                    switch(opcionMenu)
                    {

                    case 1:
                        printf("\nIngresar el nuevo cogigo: ");
                        scanf("%i", &codigoNuevo);
                        // verificar si ya existe le codiogo;
                        int confi = verificacionDeCodigo(codigoNuevo);
                        if(confi == 0)
                        {

                            printf("El codigo ingresado esta diponible: ");
                            Sleep(3000); // Duerme durante 3000 milisegundos (3 segundos)
                            system("cls"); // Limpia la pantalla en Windows
                            producto.codigoID = codigoNuevo;

                        }
                        else
                        {

                            printf("El codigo ya esta asignado a otro producto.");
                            Sleep(3000); // Duerme durante 3000 milisegundos (3 segundos)
                            system("cls"); // Limpia la pantalla en Windows
                            fclose(archivo);
                            modificar();


                        }
                        break;

                    case 2:
                        printf("\nIngresar el nombre modificado:  ");
                        scanf("%s", &producto.nombreProducto);
                        break;

                    case 3:
                        printf("\nIngresar la cantidad nueva del producto:  ");
                        do
                        {

                            scanf("%i", &producto.cantidadStock);
                            if(producto.cantidadStock<0)
                            {

                                printf("no se puede ingresar un numero negativo\n\ningresar nuevamente un valor:  ");
                                Sleep(3000); // Duerme durante 3000 milisegundos (3 segundos)


                            }

                        }
                        while(producto.cantidadStock<0);

                        break;


                    case 4:
                        printf("\nIngresar el nuevo precio del producto:  ");
                        do
                        {

                            scanf("%f", &producto.precio);
                            if(producto.precio<0)
                            {

                                printf("usted ingreso un precio negativo. \n\nIngreesar nuevamente un valor: ");
                                Sleep(3000); // Duerme durante 3000 milisegundos (3 segundos)

                            }
                        }
                        while(producto.precio<0);
                        break;

                    default:
                        printf("\n\nUsted ingreso una opcion incorrecta");
                        Sleep(3000); // Duerme durante 3000 milisegundos (3 segundos)
                        system("cls"); // Limpia la pantalla en Windows
                        menu();
                        break;

                    }

                    fseek(archivo, -sizeof(stProducto), SEEK_CUR);
                    fwrite(&producto, sizeof(stProducto), 1, archivo);
                    fclose(archivo);
                }
            }


        }
        else
        {

            printf("\nEl archivo no se pudo abrir");

        }
    }
    else
    {

        int opcion2;
        printf("\n\nEl codigo ingresado no se encuentra en el listado de productos\n\n1) ingresar nuevo codigo\n\n2) Volver al menu\n\nIngresar opcion:  ");
        scanf("%i", &opcion2 );
        if(opcion2 == 1)
        {
            modificar();
        }
        else
        {
            menu();
        }
    }
    menu();


}

// busqueda por codigo

/*Esta función permite buscar un producto por su código en
la base de datos. Solicita al usuario ingresar el código y
verifica si existe en el archivo. Si se encuentra el
producto, muestra sus detalles. Si no se encuentra, ofrece la opción
de ingresar nuevamente el código o regresar al menú principal.*/

void busquedaPorCodigo()
{

    FILE* archivo;
    stProducto producto;
    int codigoBusqueda, verificacion =0;

    archivo = fopen(listado, "rb");

    if(archivo!=NULL)
    {

        printf("\nIngresar el codigo que quieres buscar\n\nIngresar valor:  ");
        scanf("%i", &codigoBusqueda);
        Sleep(3000); // Duerme durante 3000 milisegundos (3 segundos)
        system("cls"); // Limpia la pantalla en Windows

        while(fread(&producto, sizeof(stProducto), 1, archivo)>0)
        {
            if(codigoBusqueda == producto.codigoID)
            {

                printf("El codido se encontro:\n\ncodigo: %i \nNombre: %s\nUnidades: %i\nPrecio: %f", producto.codigoID, producto.nombreProducto, producto.cantidadStock, producto.precio);
                verificacion = 1;

            }
        }
        fclose(archivo);
    }
    else
    {

        printf("No se pudo abrir el archivo");

    }

    int salida;
    if(verificacion == 0)
    {
        Sleep(3000); // Duerme durante 3000 milisegundos (3 segundos)
        system("cls"); // Limpia la pantalla en Windows
        printf("\nEl codigo ingresado no se encontro en la lista de datos\n\nQuiere ingresar nuevamente el codigo ? \n\n1)si\n\n2)no\n\ningresar opcion:  ");
        scanf("%i",&salida );

        if(salida==1)
        {

            busquedaPorCodigo();

        }
        else
        {

            menu();

        }

    }
    Sleep(6000); // Duerme durante 6000 milisegundos (3 segundos)
    system("cls"); // Limpia la pantalla en Windows
    printf("\n1) buscar otro CODIGO\n\n2)volver al menu\n\nIngresar opcion:  ");
    scanf("%i", &salida);
    if(salida == 1)
    {

        busquedaPorCodigo();

    }
    else
    {

        menu();

    }


}

// listado de inventario

/*Esta función muestra un listado de todos los productos almacenados en la
base de datos. Lee los registros del archivo y muestra los códigos, nombres,
cantidades en stock y precios de los productos en el listado.
Después de mostrar el listado, espera una entrada del usuario para regresar al menú principal.*/

void listadoDeProductos()
{

    FILE* archivo;
    stProducto productos;

    archivo = fopen(listado, "rb");

    if(archivo!= NULL)
    {

        printf("LISTADO DE PRODUCTOS");

        while(fread(&productos, sizeof(stProducto), 1, archivo)>0)
        {

            printf("\nCodigo: %i  Nombre: %s  Unidades:  %i   Precio:  %f", productos.codigoID, productos.nombreProducto, productos.cantidadStock, productos.precio);

        }
        fclose(archivo);

    }
    else
    {

        printf("El archivo no se pudo abrir");

    }
    int salida;
    printf("\n\nIngresar cualquier numero para volver al menu\n\n");
    scanf("%i", &salida);
    menu();


}



///------------

//carga de datos

/*Esta función permite cargar inventarios de productos.
Solicita al usuario ingresar un código y verifica si existe en la base de datos.
Si el código existe, llama a la función agregarElementos(codigo) para agregar
elementos al stock de ese producto. Si el código no existe, llama a la función
crearNuevoProducto(codigo) para crear un nuevo producto en la base de datos.*/

void cargaDeInventarios()
{

    int codigo;
    printf("\n Ingresar el codigo que quieres cargar\n\nCODIGO: ");
    scanf("%i", &codigo);

    int verificacion = verificacionDeCodigo(codigo);

    if(verificacion == 1)  // el codigo de producto existe
    {
        system("cls"); // Limpia la pantalla en Windows
        agregarElementos(codigo);

    }
    else if(verificacion == 0)   // el codigo del prducto no existe. se tiene que crear uno
    {
        system("cls"); // Limpia la pantalla en Windows
        crearNuevoProducto(codigo);

    }

}

// crear nuevo producto

/*Esta función maneja la creación de un nuevo producto en la base de datos.
Si el usuario elige crear un nuevo producto, solicita detalles como el nombre,
la cantidad de stock y el precio. Luego, guarda estos detalles en el archivo de productos.
Si el usuario no elige crear un nuevo producto, vuelve a la
función cargaDeInventarios() para permitir otra opción.*/

void crearNuevoProducto(int codigo)
{

    int opcion;
    stProducto producto;
    FILE* archivo;
    printf("\n\nEl codigo ingresado no se encuentra en la base de datos\n\nopciones: \n\n1) Crear nuevo producto: \n2) volver a cargar el dato: \n\nIngresar opcion:  ");
    fflush(stdin);
    scanf("%i", &opcion);
    if(opcion == 1)
    {

        archivo = fopen(listado, "ab");

        if(archivo!=NULL)
        {




            printf("\n\nCrear nuevo producto: ");
            printf("\n\nIngresar el nombre del producto:  ");
            scanf("%s", &producto.nombreProducto);
            fflush(stdin);
            printf("\nIngresar la cantidad de stock:  ");

            do
            {

                scanf("%i", &producto.cantidadStock);
                if(producto.cantidadStock<0)
                {

                    printf("no se puede ingresar un numero negativo\n\ningresar nuevamente un valor:  ");

                }

            }
            while(producto.cantidadStock<0);

            printf("\nIngresar el precio del producto ");
            do
            {

                scanf("%f", &producto.precio);
                if(producto.precio<0)
                {

                    printf("usted ingreso un precio negativo. \n\nIngreesar nuevamente un valor: ");
                    Sleep(3000); // Duerme durante 3000 milisegundos (3 segundos)
                    system("cls"); // Limpia la pantalla en Windows

                }
            }
            while(producto.precio<0);
            producto.codigoID = codigo;

            fwrite(&producto, sizeof(stProducto), 1, archivo);
            fclose(archivo);
        }
        else
        {

            printf("No se puido abrir el archivo");

        }

        system("cls"); // Limpia la pantalla en Windows
        printf("El nuevo producto se cargo con exito");
        Sleep(3000); // Duerme durante 3000 milisegundos (3 segundos)
        system("cls"); // Limpia la pantalla en Windows

    }
    else if(opcion != 1)
    {

        cargaDeInventarios();

    }

    menu();
}

// argegar elementos al stock
/*Esta función permite agregar elementos al stock de un producto existente
en la base de datos. Primero, abre el archivo de productos en modo
lectura y escritura. Luego, busca el producto con el código proporcionado y
permite al usuario ingresar la cantidad de elementos a agregar.
Después de confirmar la operación, actualiza el stock del producto
en el archivo y muestra un mensaje de éxito.*/

void agregarElementos(int codigo)
{

    FILE* archivo;
    stProducto producto;
    int elementos, conf;
    int entrada=0;

    archivo = fopen(listado, "r+b");

    if(archivo != NULL)
    {
        while(fread(&producto, sizeof(stProducto), 1, archivo)>0)
        {
            if(codigo == producto.codigoID)
            {
                printf("CODIGO : %i\nNombre del producto: %s\nPrecio: %f\n\nIngresar la cantidad de elementos ingresados:  ",producto.codigoID, producto.nombreProducto, producto.precio);
                do
                {
                    printf("\nIngresar valor:  ");
                    scanf("%i", &elementos);

                    if(elementos<0)
                    {

                        printf("usted ingreso un valor negativo. \n\nIngreesar nuevamente un valor: ");

                    }
                }
                while(elementos<0);

                printf("\n\nUsted ingreso %i. INGRESAR UN 1 PARA CONFIRMAR\n\nIngresar opcion: ", elementos);
                fflush(stdin);
                scanf("%i", &conf);
                if(conf == 1)
                {

                    producto.cantidadStock = producto.cantidadStock + elementos;
                    fseek(archivo, -sizeof(stProducto), SEEK_CUR);
                    fwrite(&producto, sizeof(stProducto), 1, archivo);
                    fclose(archivo);
                    system("cls"); // Limpia la pantalla en Windows
                    printf("\n\ndato cargado con exito");
                    Sleep(3000); // Duerme durante 3000 milisegundos (3 segundos)


                    menu();

                }
                else
                {

                    printf("No se pudo confirar la operacion");

                }
            }
        }
    }
    else
    {

        printf("el archvo no se pudo abrir");

    }



    menu();


}
///--------------------

// verificacion de estado de codigo
/*
Esta función recibe un código de producto como argumento y verifica si
ese código existe en el archivo de productos. Devuelve 1 si el código
existe y 0 si no existe.
*/

int verificacionDeCodigo(int codigo)
{

    int saidaEstado = 0;
    FILE* archivo;
    stProducto producto;


    archivo = fopen(listado,"rb");

    if(archivo!=NULL)
    {

        while(fread(&producto, sizeof(stProducto), 1, archivo)>0)
        {

            if(codigo == producto.codigoID)
            {

                saidaEstado = 1;

            }


        }
        fclose(archivo);


    }
    else
    {

        printf("El archivo no se pudo abrir");

    }



    return saidaEstado;


}

