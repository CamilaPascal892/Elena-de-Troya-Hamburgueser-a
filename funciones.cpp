#include <iostream>
#include <string>
#include <iomanip>
#include <chrono>
#include <thread>
#include <map>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>
#include "structs.h"
#include "global.h"
using namespace std;


// Función para leer el archivo y cargar los productos
vector<Producto> cargarProductos(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    vector<Producto> productos;

    if (!archivo) {
        cerr << "No se pudo abrir el archivo!" << endl;
        return productos;
    }

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string nombre;
        int cantidad;
        double precio;

        // Leer los datos de cada línea separando por coma
        getline(ss, nombre, ',');
        ss >> cantidad;
        ss.ignore();  // Ignorar la coma
        ss >> precio;

        // Crear un objeto Producto y agregarlo al vector
        productos.push_back(Producto{nombre, precio, cantidad});
    }

    archivo.close();
    return productos;
}

// Función para mostrar los productos cargados
void mostrarProductos(const vector<Producto>& productos) {
    for (const auto& producto : productos) {
        cout << "Producto: " << producto.nombre << ", Cantidad: " << producto.stock
             << ", Precio: $" << producto.precio << endl;
    }
}

// Función que muestra la frase de forma animada
void mostrarMatrizBienvenidaAnimada() {
    string mensaje = "Bienvenido a mi casa de comidas rapidas. Nosotros sentimos: AMOR POR LAS HAMBURGUESAS!";
    int anchoPantalla = 100; // Definir el ancho de la pantalla o consola

    // Hacer que el mensaje se mueva de izquierda a derecha
    for (int i = 0; i < mensaje.length() + anchoPantalla; ++i) {
        string espacio = string(i, ' '); // Espacios para desplazar el texto
        string mostrar = espacio + mensaje;

        // Mostrar el mensaje con el espacio agregado
        cout << "\r" << mostrar.substr(0, anchoPantalla); // Se corta para que no se desborde
        cout.flush();  // Asegura que el texto se imprima inmediatamente
        // Pausar para dar el efecto de movimiento
        this_thread::sleep_for(chrono::milliseconds(100));
    }

    // Nueva línea después de la animación
    cout << endl;
}

void solicitarDatosCajero() {
    string nombreCajero, apellidoCajero;
    cout << "Ingrese el nombre del cajero: ";
    cin >> nombreCajero;
    cout << "Ingrese el apellido del cajero: ";
    cin >> apellidoCajero;
    cout << "Cajero " << nombreCajero << " " << apellidoCajero << " registrado correctamente.\n";
}

void mostrarMenuPrincipal() {
    cout << "\n=== MENU PRINCIPAL ===" << endl;
    cout << "1. Agregar Producto" << endl;
    cout << "2. Mostrar Stock" << endl;
    cout << "3. Vender Comida" << endl;
    cout << "4. Agregar Cliente" << endl;
    cout << "5. Mostrar Clientes" << endl;
    cout << "6. Facturar Pedido" << endl;
    cout << "7. Buscar Producto" << endl;
    cout << "8. Eliminar Producto" << endl;
    cout << "9. Agregar Ingrediente" << endl;
    cout << "10. Mostrar Inventario" << endl;
    cout << "11. Actualizar Producto" << endl;
    cout << "12. Eliminar Ingrediente" << endl;
    cout << "13. Aplicar Descuento" << endl;
    cout << "14. Marcar Cliente VIP" << endl;
    cout << "15. Generar Informe de Ventas" << endl;
    cout << "16. Registrar Gasto Operativo" << endl;
    cout << "17. Agregar Cajero" << endl;
    cout << "18. Ayuda Interactiva" << endl;
    cout << "19. Ver Reporte de Ganancias Diarias" << endl;
    cout << "20. Ver Historial de Ventas de un Producto" << endl;
    cout << "21. Ver Productos Más Vendidos" << endl;
    cout << "22. Modificar Nombre de Cliente" << endl;
    cout << "23. Salir" << endl;
}

void agregarProducto(vector<Producto>* menu) {
    Producto p;
    cout << "Ingrese el nombre del producto: ";
    cin >> p.nombre;
    cout << "Ingrese el precio del producto: ";
    cin >> p.precio;
    cout << "Ingrese el stock del producto: ";
    cin >> p.stock;
    menu->push_back(p);
    cout << "Producto agregado correctamente.\n";
}

void mostrarStock(const vector<Producto>* menu) {
    cout << "\n=== STOCK DE PRODUCTOS ===" << endl;
    for (const auto& p : *menu) {
        cout << p.nombre << " - Precio: $" << fixed << setprecision(2) << p.precio << " - Stock: " << p.stock << endl;
    }
}

void venderComida(vector<Producto>* menu, vector<string>* historial, double facturacionSucursal[4], map<string, int>* historialVentas) {
    string producto;
    int sucursal;
    cout << "Ingrese el nombre del producto a vender: ";
    cin >> producto;
    cout << "Ingrese la sucursal (1-4): ";
    cin >> sucursal;
    bool encontrado = false;

    for (auto& p : *menu) {
        if (p.nombre == producto && p.stock > 0) {
            p.stock--;
            historial->push_back("Venta de " + producto);  // Corregido aquí
            facturacionSucursal[sucursal - 1] += p.precio;
            (*historialVentas)[producto]++;  // Incrementamos el contador de ventas de ese producto
            cout << "Venta realizada con éxito.\n";
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        cout << "Producto no disponible o stock insuficiente.\n";
    }
}

void agregarCliente(vector<Cliente>* clientes) {
    Cliente c;
    cout << "Ingrese el nombre del cliente: ";
    cin >> c.nombre;
    c.esVIP = false;
    clientes->push_back(c);
    cout << "Cliente agregado correctamente.\n";
}

void mostrarClientes(const vector<Cliente>& clientes) {  // Pasamos por referencia constante
    cout << "\n=== CLIENTES ===" << endl;
    for (const auto& c : clientes) {
        cout << c.nombre << (c.esVIP ? " (VIP)" : "") << endl;
    }
}

// Función para facturar productos
void facturarProducto(vector<Producto>& productos) {
    Factura factura;  // Factura que guardará los detalles
    string productoSeleccionado;
    int cantidad;
    double totalFactura = 0.0;
    bool continuarFacturacion = true;
    while (continuarFacturacion) {
        // Mostrar los productos disponibles
        cout << "\n=== Productos Disponibles ===\n";
        for (int i = 0; i < productos.size(); i++) {
            cout << i + 1 << ". " << productos[i].nombre << " - Precio: $"
                 << fixed << setprecision(2) << productos[i].precio << " - Stock: "
                 << productos[i].stock << endl;
        }

        // Pedir al usuario que seleccione un producto
        cout << "\nIngrese el número del producto que desea comprar (0 para terminar): ";
        int seleccion;
        cin >> seleccion;

        if (seleccion == 0) {
            break;  // Salir de la facturación
        }

        if (seleccion < 1 || seleccion > productos.size()) {
            cout << "Opción no válida. Intente nuevamente." << endl;
            continue;
        }

        Producto& producto = productos[seleccion - 1];  // Obtenemos el producto seleccionado

        // Pedir la cantidad de productos
        cout << "Ingrese la cantidad de '" << producto.nombre << "' que desea comprar: ";
        cin >> cantidad;

        if (cantidad > producto.stock) {
            cout << "No hay suficiente stock. Solo hay " << producto.stock << " unidades disponibles." << endl;
            continue;
        }

        // Calcular el total de este producto
        double subtotal = producto.precio * cantidad;
        totalFactura += subtotal;

        // Guardar los detalles de la factura
        factura.productos.push_back(producto.nombre);
        factura.cantidades.push_back(cantidad);
        factura.precios.push_back(producto.precio);

        // Actualizar el stock
        producto.stock -= cantidad;

        cout << "Producto agregado a la factura.\n";

        // Preguntar si se desea agregar otro producto
        cout << "¿Desea agregar otro producto a la factura? (1 para sí, 0 para no): ";
        int agregarMas;
        cin >> agregarMas;
        continuarFacturacion = agregarMas == 1;
    }

    // Mostrar factura final
    cout << "\n=== Factura ===\n";
    for (size_t i = 0; i < factura.productos.size(); ++i) {
        cout << factura.productos[i] << " - " << factura.cantidades[i] << " x $"
             << fixed << setprecision(2) << factura.precios[i] << endl;
    }
    cout << "Total: $" << fixed << setprecision(2) << totalFactura << endl;
    cout << "Gracias por su compra!" << endl;
}

void generarInformeVentas() {
    cout << "\n=== Informe de Ventas ===" << endl;
    for (const auto& entry : historialVentas) {
        cout << "Producto: " << entry.first << ", Unidades Vendidas: " << entry.second << endl;
    }
}
void buscarProducto(const vector<Producto>& menu) {  // Usamos constante
    string nombre;
    cout << "Ingrese el nombre del producto a buscar: ";
    cin >> nombre;
    bool encontrado = false;
    for (const auto& p : menu) {
        if (p.nombre == nombre) {
            cout << "Producto encontrado: " << p.nombre << " - Precio: $" << fixed << setprecision(2) << p.precio << " - Stock: " << p.stock << endl;
            encontrado = true;
            break;
        }
    }
    if (!encontrado) {
        cout << "Producto no encontrado.\n";
    }
}
void eliminarProducto(vector<Producto>* menu) {
    string nombre;
    cout << "Ingrese el nombre del producto a eliminar: ";
    cin >> nombre;
    auto it = menu->begin();
    while (it != menu->end()) {
        if (it->nombre == nombre) {
            menu->erase(it);
            cout << "Producto eliminado correctamente.\n";
            return;
        }
        ++it;
    }
    cout << "Producto no encontrado.\n";
}
void agregarIngrediente(vector<string>* inventarioIngredientes) {
    string ingrediente;
    cout << "Ingrese el nombre del ingrediente: ";
    cin >> ingrediente;
    inventarioIngredientes->push_back(ingrediente);
    cout << "Ingrediente agregado correctamente.\n";
}

void mostrarInventario(const vector<string>& inventarioIngredientes) {  // Usamos constante
    cout << "\n=== INVENTARIO DE INGREDIENTES ===" << endl;
    for (const auto& i : inventarioIngredientes) {
        cout << i << endl;
    }
}
void actualizarProducto(vector<Producto>* menu) {
    string nombre;
    cout << "Ingrese el nombre del producto a actualizar: ";
    cin >> nombre;
    for (auto& p : *menu) {
        if (p.nombre == nombre) {
            cout << "Ingrese el nuevo precio: ";
            cin >> p.precio;
            cout << "Ingrese el nuevo stock: ";
            cin >> p.stock;
            cout << "Producto actualizado correctamente.\n";
            return;
        }
    }
    cout << "Producto no encontrado.\n";
}
void eliminarIngrediente(vector<string>* inventarioIngredientes) {
    string ingrediente;
    cout << "Ingrese el nombre del ingrediente a eliminar: ";
    cin >> ingrediente;
    auto it = find(inventarioIngredientes->begin(), inventarioIngredientes->end(), ingrediente);
    if (it != inventarioIngredientes->end()) {
        inventarioIngredientes->erase(it);
        cout << "Ingrediente eliminado correctamente.\n";
    } else {
        cout << "Ingrediente no encontrado.\n";
    }
}
void aplicarDescuento(vector<Producto>* menu) {
    string nombre;
    double descuento;
    cout << "Ingrese el nombre del producto a descontar: ";
    cin >> nombre;
    cout << "Ingrese el descuento en porcentaje: ";
    cin >> descuento;
    for (auto& p : *menu) {
        if (p.nombre == nombre) {
            p.precio -= p.precio * (descuento / 100);
            cout << "Descuento aplicado correctamente.\n";
            return;
        }
    }
    cout << "Producto no encontrado.\n";
}
void marcarClienteVIP(vector<Cliente>* clientes) {
    string nombre;
    cout << "Ingrese el nombre del cliente a marcar como VIP: ";
    cin >> nombre;
    for (auto& c : *clientes) {
        if (c.nombre == nombre) {
            c.esVIP = true;
            cout << "Cliente marcado como VIP.\n";
            return;
        }
    }
    cout << "Cliente no encontrado.\n";
}
void registrarGastoOperativo(double& gastosOperativos) {
    double gasto;
    cout << "Ingrese el monto del gasto operativo: ";
    cin >> gasto;
    gastosOperativos += gasto;
    cout << "Gasto registrado correctamente.\n";
}

void agregarCajero(vector<string>* cajeros) {
    string cajero;
    cout << "Ingrese el nombre del cajero: ";
    cin >> cajero;
    cajeros->push_back(cajero);
    cout << "Cajero agregado correctamente.\n";
}
void mostrarGananciasDiarias(double facturacionSucursal[4]) {
    cout << "\n=== GANANCIAS DIARIAS ===" << endl;
    for (int i = 0; i < 4; ++i) {
        cout << "Sucursal " << i + 1 << ": $" << fixed << setprecision(2) << facturacionSucursal[i] << endl;
    }
}

void mostrarHistorialVentasProducto(const map<string, int>& historialVentas) {
    cout << "\n=== HISTORIAL DE VENTAS POR PRODUCTO ===" << endl;
    for (const auto& p : historialVentas) {
        cout << "Producto: " << p.first << " - Ventas: " << p.second << endl;
    }
}
void mostrarProductosMasVendidos(const map<string, int>& historialVentas) {
    cout << "\n=== PRODUCTOS MÁS VENDIDOS ===" << endl;
    vector<pair<string, int>> ventas;
    for (const auto& p : historialVentas) {
        ventas.push_back(p);
    }

    sort(ventas.begin(), ventas.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second;
    });

    for (const auto& p : ventas) {
        cout << "Producto: " << p.first << " - Ventas: " << p.second << endl;
    }
}
void modificarNombreCliente(vector<Cliente>* clientes) {
    string nombreActual, nuevoNombre;
    cout << "Ingrese el nombre actual del cliente: ";
    cin >> nombreActual;
    cout << "Ingrese el nuevo nombre del cliente: ";
    cin >> nuevoNombre;
    for (auto& c : *clientes) {
        if (c.nombre == nombreActual) {
            c.nombre = nuevoNombre;
            cout << "Nombre del cliente actualizado correctamente.\n";
            return;
        }
    }
    cout << "Cliente no encontrado.\n";
}
void mostrarAyudaInteractiva() {
    cout << "\n=== AYUDA INTERACTIVA ===" << endl;
    cout << "Este es el sistema de gestión de la hamburguesería. Las opciones disponibles son:" << endl;
    cout << "1. Agregar Producto: Permite añadir un nuevo producto al menú." << endl;
    cout << "2. Mostrar Stock: Muestra la cantidad disponible de productos en el menú." << endl;
    cout << "3. Vender Comida: Registra la venta de un producto y la cantidad vendida." << endl;
    cout << "4. Agregar Cliente: Permite agregar un cliente al sistema." << endl;
    cout << "5. Mostrar Clientes: Muestra la lista de clientes registrados." << endl;
    cout << "6. Facturar Pedido: Realiza la facturación de un pedido realizado." << endl;
    cout << "7. Buscar Producto: Permite buscar un producto en el menú." << endl;
    cout << "8. Eliminar Producto: Permite eliminar un producto del menú." << endl;
    cout << "9. Agregar Ingrediente: Permite agregar un ingrediente al inventario." << endl;
    cout << "10. Mostrar Inventario: Muestra el inventario de ingredientes disponibles." << endl;
    cout << "11. Actualizar Producto: Permite actualizar la información de un producto." << endl;
    cout << "12. Eliminar Ingrediente: Elimina un ingrediente del inventario." << endl;
     cout << "13. Aplicar Descuento: Aplica un descuento a los productos del menú." << endl;
    cout << "14. Marcar Cliente VIP: Permite marcar a un cliente como VIP." << endl;
    cout << "15. Generar Informe de Ventas: Genera un informe de las ventas realizadas." << endl;
    cout << "16. Registrar Gasto Operativo: Registra los gastos operativos de la empresa." << endl;
    cout << "17. Agregar Cajero: Permite agregar un cajero al sistema." << endl;
    cout << "19. Mostrar Ganancias Diarias: Muestra las ganancias diarias de las sucursales." << endl;
    cout << "20. Mostrar Historial de Ventas por Producto: Muestra las ventas de productos." << endl;
    cout << "21. Mostrar Productos Más Vendidos: Muestra los productos más vendidos." << endl;
    cout << "22. Modificar Nombre de Cliente: Permite modificar el nombre de un cliente." << endl;
    cout << "23. Salir: Sale del sistema." << endl;
}
