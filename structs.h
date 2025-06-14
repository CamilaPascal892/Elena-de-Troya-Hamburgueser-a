#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED
using namespace std;

struct Producto {
    string nombre;
    double precio;
    int stock;
};

struct Cliente {
    string nombre;
    bool esVIP;
};

struct Factura {
    std::vector<string> productos;
    std::vector<int> cantidades;
    std::vector<double> precios;
    double total;
};

#endif // STRUCTS_H_INCLUDED
