cout <"Mi proyecto farmaceutico")<<endl;

#include <iostream>
#include<sstream>
#include <fstream>
#include <vector>
#include<string>
#include<algorithm>
using namespace std;


struct Medicamento {
    string codigo;            // Código único del medicamento
    string nombre;            // Nombre comercial
    string principioActivo;   // Principio activo o componente principal
    string laboratorio;       // Nombre del laboratorio o fabricante
    string fechaFabricacion;  // Fecha de fabricación (formato: AAAA-MM-DD)
    string fechaCaducidad;    // Fecha de caducidad (formato: AAAA-MM-DD)
    int stock;                // Cantidad disponible en inventario
    double precio;            // Precio unitario
    bool requiereReceta;      // true si necesita receta médica
};

vector<Medicamento> inventario = {
    {"001", "Paracetamol", "Paracetamol", "Laboratorio A", "2023-01-01", "2025-01-01", 100, 1.50, false},
    {"002", "Ibuprofeno", "Ibuprofeno", "Laboratorio B", "2023-02-01", "2025-02-01", 50, 2.00, false},
    {"003", "Amoxicilina", "Amoxicilina", "Laboratorio C", "2023-03-01", "2025-03-01", 30, 3.00, true}
};

// sobrecargado del operador de inserción para imprimir los detalles del medicamento
ostream& operator<<(ostream& os, const Medicamento& med) {
    os << "Código: " << med.codigo << ", Nombre: " << med.nombre
       << ", Principio Activo: " << med.principioActivo
       << ", Laboratorio: " << med.laboratorio
       << ", Fecha de Fabricación: " << med.fechaFabricacion
       << ", Fecha de Caducidad: " << med.fechaCaducidad
       << ", Stock: " << med.stock
       << ", Precio: $" << med.precio
       << ", Requiere Receta: " << (med.requiereReceta ? "Sí" : "No");
    return os;
}
// sobrecargado del operador de inserción para imprimir el inventario completo
ostream& operator<<(ostream& os, const vector<Medicamento>& inventario) {
    for (const auto& med : inventario) {
        os << med << endl;
    }
    return os;
}
//sobrecargado del operador de extracción para la escritura de medicamentos
istream & operator>>(istream& is, Medicamento& med) {

    // preguntar mañana
    is>>> med.codigo >> med.nombre >> med.principioActivo
       >> med.laboratorio >> med.fechaFabricacion >> med.fechaCaducidad
       >> med.stock >> med.precio >> med.requiereReceta;
    return is;
}
//sobrecargado del operador de extracción para la lectura de medicamentos
istream & operator>>(istream& is, vector<Medicamento>& inventario) {
    Medicamento med;
    while (is >> med) {
        inventario.push_back(med);
    }
    return is;
}
void guardarInventario(vector<Medicamento>& inventario, string ruta ){
    ofstream archivo(ruta);
    if (archivo.is_open()) {
        archivo << inventario;
        archivo.close();
        cout << "Inventario guardado correctamente en " << ruta << endl;
    } else {
        cerr << "Error al abrir el archivo para guardar el inventario." << endl;
    }
}

vector<Medicamento> leer(const string& ruta) {
    vector<Medicamento> inventario;
    ifstream archivo(ruta);
    if (archivo.is_open()) {
        archivo >> inventario;
        archivo.close();
        cout << "Inventario cargado correctamente desde " << ruta << endl;
    } else {
        cerr << "Error al abrir el archivo para cargar el inventario." << endl;
    }
    return inventario;
}


Medicamento buscar(const string& codigo, const string& ruta) {
    medicamento medB;
    medB.codigo = "No encontrado"; 
    for (const auto& med : leer(ruta)) {
        if (codigo == med.codigo) {
            medB = med;
            break;
        }
    }
    return medB;
}

void agregar(const Medicamento& nuevoMed, const string& ruta) {
    vector<Medicamento> inventario = leer(ruta);
    auto it = find_if(inventario.begin(), inventario.end(),
                     [&](const Medicamento& med) { return med.codigo == nuevoMed.codigo; });
                     if (it == inventario.end()) {                    
        inventario.push_back(nuevoMed)<<"ha sido agregado al inventario."<<endl;
    } else {
        cout << "El medicamento con código " << nuevoMed.codigo << " ya existe en el inventario." << endl;
    }
    guardarInventario(inventario, ruta);
}


void eliminar(const string& codigo, const string& ruta) {
    vector<Medicamento> inventario = leer(ruta);
    auto it = remove_if(inventario.begin(), inventario.end(),
                        [&](const Medicamento& med) { return med.codigo == codigo; });
    if (it != inventario.end()) {
        inventario.erase(it, inventario.end());
        cout << "Medicamento con código " << codigo << " ha sido eliminado del inventario." << endl;
    } else {
        cout << "No se encontró el medicamento con código " << codigo << " en el inventario." << endl;
    }
    guardarInventario(inventario, ruta);
}

void actualizar(const Medicamento& medActualizado, const string& ruta) {
    vector<Medicamento> inventario = leer(ruta);
    auto it = find_if(inventario.begin(), inventario.end(),
                     [&](const Medicamento& med) { return med.codigo == medActualizado.codigo; });
    if (it != inventario.end()) {
        it->nombre = medActualizado.nombre;
        it->principioActivo = medActualizado.principioActivo;
        it->laboratorio = medActualizado.laboratorio;
        it->fechaFabricacion = medActualizado.fechaFabricacion;
        it->fechaCaducidad = medActualizado.fechaCaducidad;
        it->stock = medActualizado.stock;
        it->precio = medActualizado.precio;
        it->requiereReceta = medActualizado.requiereReceta;
        cout << "Medicamento con código " << medActualizado.codigo << " ha sido actualizado en el inventario." << endl;
    } else {
        cout << "No se encontró el medicamento con código " << medActualizado.codigo << "
    en el inventario." << endl;
    }
    guardarInventario(inventario, ruta);
}