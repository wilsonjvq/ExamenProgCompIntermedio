//Algoritmo de manejo de colisiones con doble hash
//Compilador en linea: https://www.onlinegdb.com/online_c++_compiler
#include <iostream>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

// Registro para almacenar los datos de los estudiantes
struct Estudiante {
    string nombre;
    int numero_estudiante;
    int numero_seguro;
};

// Tabla hash con doble hash
class TablaHashDoble {
    vector<Estudiante> tabla;
    vector<bool> ocupado;
    int tamaño;

public:
    TablaHashDoble(int t) : tamaño(t) {
        tabla.resize(t);
        ocupado.resize(t, false);
    }

    // Primera funcion hash
    int funcionHash1(int clave) {
        return clave % tamaño;
    }

    // Segunda funcion hash
    int funcionHash2(int clave) {
        return 7 - (clave % 7); // Valor primo menor al tamaño
    }

    void insertar(Estudiante est) {
        int hash1 = funcionHash1(est.numero_estudiante);
        int hash2 = funcionHash2(est.numero_estudiante);
        if (hash2 == 0) hash2 = 1; // Evitar que el avance sea 0
        int i = 0;

        // Doble hash para encontrar espacio
        while (ocupado[(hash1 + i * hash2) % tamaño]) {
            i++;
        }

        int pos = (hash1 + i * hash2) % tamaño;
        tabla[pos] = est;
        ocupado[pos] = true;

    }

    Estudiante buscar(int clave) {
        int hash1 = funcionHash1(clave);
        int hash2 = funcionHash2(clave);
        if (hash2 == 0) hash2 = 1; // Evitar avance 0
        int i = 0;

        while (ocupado[(hash1 + i * hash2) % tamaño]) {
            int pos = (hash1 + i * hash2) % tamaño;
            if (tabla[pos].numero_estudiante == clave) {
                return tabla[pos];
            }
            i++;
        }

        throw runtime_error("Estudiante no encontrado.");
    }
};

int main() {
    // Crear tabla hash con tamaño primo
    TablaHashDoble tabla(11);

    // Insertar estudiantes
    tabla.insertar({"Juan", 1, 123});
    tabla.insertar({"Ana", 7, 456});
    tabla.insertar({"Luis", 25, 789});
    tabla.insertar({"Maria", 35, 321});
    tabla.insertar({"Pedro", 43, 654});
    tabla.insertar({"Laura", 51, 987});
    tabla.insertar({"Jose", 72, 112});
    tabla.insertar({"Sara", 65, 223});
    tabla.insertar({"Carlos", 37, 334});
    tabla.insertar({"Lucia", 54, 445});

    // Buscar estudiante
    try {
        Estudiante est = tabla.buscar(72);
        cout << "Encontrado: " << est.nombre << ", " << est.numero_estudiante << ", " << est.numero_seguro << endl;
    } catch (exception& e) {
        cout << e.what() << endl;
    }

    return 0;
}

