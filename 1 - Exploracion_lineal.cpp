//Algoritmo de manejo de colisiones con exploracion lineal
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

// Tabla hash con exploracion lineal
class TablaHashLineal {
    vector<Estudiante> tabla;
    vector<bool> ocupado;
    int tamaño;

public:
    TablaHashLineal(int t) : tamaño(t) {
        tabla.resize(t);
        ocupado.resize(t, false);
    }

    int funcionHash(int clave) {
        return clave % tamaño;
    }

    void insertar(Estudiante est) {
        int clave = funcionHash(est.numero_estudiante);
        int i = clave;

        // Exploracion lineal para encontrar espacio
        while (ocupado[i]) {
            i = (i + 1) % tamaño;
        }

        tabla[i] = est;
        ocupado[i] = true;
    }

    Estudiante buscar(int clave) {
        int hash = funcionHash(clave);
        int i = hash;

        while (ocupado[i]) {
            if (tabla[i].numero_estudiante == clave) {
                return tabla[i];
            }
            i = (i + 1) % tamaño;
        }

        throw runtime_error("Estudiante no encontrado.");
    }
};

int main() {
    TablaHashLineal tabla(10);

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
        Estudiante est = tabla.buscar(25);
        cout << "Encontrado: " << est.nombre << ", " << est.numero_estudiante << ", " << est.numero_seguro << endl;
    } catch (exception& e) {
        cout << e.what() << endl;
    }

    return 0;
}