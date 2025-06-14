#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <chrono>
#include <thread>
#include <map>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "funciones.h"
#include "global.h"

using namespace std;


vector<Producto> menu;
vector<Cliente> clientes;
vector<string> historial;
vector<string> inventarioIngredientes;
vector<string> cajeros;
double facturacionSucursal[4] = {0, 0, 0, 0};
double gastosOperativos = 0;
map<string, int> historialVentas;  // Mapa para llevar el conteo de ventas de cada producto


int main() {
    menu = cargarProductos("new.txt");
    mostrarMatrizBienvenidaAnimada();

    int opcion;
    do {
        mostrarMenuPrincipal();
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                agregarProducto(&menu);
                break;
            case 2:
                mostrarStock(&menu);
                break;
            case 3:
                venderComida(&menu, &historial, facturacionSucursal, &historialVentas);
                break;
            case 4:
                agregarCliente(&clientes);
                break;
            case 5:
                mostrarClientes(clientes);
                break;
            case 6:
                facturarProducto(menu);
                break;
            case 7:
                buscarProducto(menu);
                break;
            case 8:
                eliminarProducto(&menu);
                break;
            case 9:
                agregarIngrediente(&inventarioIngredientes);
                break;
            case 10:
                mostrarInventario(inventarioIngredientes);
                break;
            case 11:
                actualizarProducto(&menu);
                break;
            case 12:
                eliminarIngrediente(&inventarioIngredientes);
                break;
            case 13:
                aplicarDescuento(&menu);
                break;
            case 14:
                marcarClienteVIP(&clientes);
                break;
            case 15:
                generarInformeVentas();
                break;
            case 16:
                registrarGastoOperativo(gastosOperativos);
                break;
            case 17:
                agregarCajero(&cajeros);
                break;
            case 18:
                mostrarAyudaInteractiva();
                break;
            case 19:
                mostrarGananciasDiarias(facturacionSucursal);
                break;
            case 20:
                mostrarHistorialVentasProducto(historialVentas);
                break;
            case 21:
                mostrarProductosMasVendidos(historialVentas);
                break;
            case 22:
                modificarNombreCliente(&clientes);
                break;
            case 23:
                cout << "Saliendo del sistema...\n";
                break;
            default:
                cout << "Opcion no válida, por favor intente nuevamente.\n";
                break;
        }

    } while (opcion != 23);

    return 0;
}
