#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include "structs.h"
using namespace std;

std::vector<Producto> cargarProductos(const string& nombreArchivo);
void mostrarProductos(const std::vector<Producto>& productos);
void mostrarMatrizBienvenidaAnimada();
void solicitarDatosCajero();
void mostrarMenuPrincipal();
void agregarProducto(std::vector<Producto>* menu);
void mostrarStock(const std::vector<Producto>* menu);
void venderComida(std::vector<Producto>* menu, std::vector<string>* historial, double facturacionSucursal[4], map<string, int>* historialVentas);
void agregarCliente(std::vector<Cliente>* clientes);
void mostrarClientes(const std::vector<Cliente>& clientes);
void facturarProducto(std::vector<Producto>& productos);
void generarInformeVentas();
void buscarProducto(const std::vector<Producto>& menu);
void eliminarProducto(std::vector<Producto>* menu);
void agregarIngrediente(std::vector<string>* inventarioIngredientes);
void mostrarInventario(const std::vector<string>& inventarioIngredientes);
void actualizarProducto(std::vector<Producto>* menu);
void eliminarIngrediente(std::vector<string>* inventarioIngredientes);
void aplicarDescuento(std::vector<Producto>* menu);
void marcarClienteVIP(std::vector<Cliente>* clientes);
void registrarGastoOperativo(double& gastosOperativos);
void agregarCajero(std::vector<string>* cajeros);
void mostrarGananciasDiarias(double facturacionSucursal[4]);
void mostrarHistorialVentasProducto(const map<string, int>& historialVentas);
void mostrarProductosMasVendidos(const map<string, int>& historialVentas);
void modificarNombreCliente(std::vector<Cliente>* clientes);
void mostrarAyudaInteractiva();

#endif // FUNCIONES_H_INCLUDED
