//Algoritmo de busqueda de palabras clave con KMP y Boyer-Moore
//Compilador en linea: https://www.onlinegdb.com/online_c++_compiler
#include <iostream>
#include <vector>
#include <string>
#include <chrono>

using namespace std;

// Funcion para construir el arreglo LPS para KMP
void construirLPS(const string& patron, vector<int>& lps) {
    int largo = 0;
    lps[0] = 0;
    int i = 1;

    while (i < patron.size()) {
        if (patron[i] == patron[largo]) {
            largo++;
            lps[i] = largo;
            i++;
        } else {
            if (largo != 0) {
                largo = lps[largo - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// Algoritmo KMP
vector<int> buscarKMP(const string& texto, const string& patron) {
    vector<int> lps(patron.size());
    construirLPS(patron, lps);
    vector<int> ocurrencias;

    int i = 0, j = 0;
    while (i < texto.size()) {
        if (patron[j] == texto[i]) {
            i++;
            j++;
        }
        if (j == patron.size()) {
            ocurrencias.push_back(i - j);
            j = lps[j - 1];
        } else if (i < texto.size() && patron[j] != texto[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    return ocurrencias;
}

// Algoritmo Boyer-Moore
vector<int> buscarBM(const string& texto, const string& patron) {
    int m = patron.size();
    int n = texto.size();
    vector<int> badChar(256, -1);

    for (int i = 0; i < m; i++) {
        badChar[patron[i]] = i;
    }

    vector<int> ocurrencias;
    int shift = 0;

    while (shift <= (n - m)) {
        int j = m - 1;
        while (j >= 0 && patron[j] == texto[shift + j]) {
            j--;
        }
        if (j < 0) {
            ocurrencias.push_back(shift);
            shift += (shift + m < n) ? m - badChar[texto[shift + m]] : 1;
        } else {
            shift += max(1, j - badChar[texto[shift + j]]);
        }
    }
    return ocurrencias;
}

// Funcion principal
int main() {
    // Simulamos el archivo de texto como un vector de lineas
    vector<string> texto = {
    "El algoritmo KMP es un algoritmo de busqueda de subcadenas simple.",
    "Su objetivo es buscar la existencia de una subcadena llamada patron dentro de otra cadena.",
    "La busqueda se lleva a cabo utilizando informacion basada en los fallos previos.",
    "Se crea previamente una tabla de valores sobre su propio contenido.",
    "El objetivo de esta tabla es determinar donde podria darse la siguiente existencia.",
    "Asi se evita analizar mas de una vez los caracteres de la cadena de busqueda.",
    "En 1970, S.A. Cook sugirio un algoritmo con un tiempo de M+N en el peor caso.",
    "Knuth, Pratt y Morris desarrollaron el algoritmo KMP y lo publicaron en 1976.",
    "El algoritmo localiza la posicion de comienzo de una cadena dentro de otra.",
    "Se calcula una tabla de saltos o tabla de fallos sobre el patron.",
    "Esta tabla se utiliza para hacer saltos cuando hay un fallo de coincidencia.",
    "La cadena donde se busca y el patron se comparan con punteros de avance.",
    "Si ocurre un fallo, el puntero salta segun la tabla de fallos.",
    "El array de busqueda utiliza un puntero absoluto para determinar la seccion.",
    "Dentro de esta seccion, se compara cada caracter con el patron.",
    "Si existen coincidencias, el puntero del patron avanza.",
    "Si se alcanza el final del patron, se devuelve la posicion encontrada.",
    "En caso de fallo, el puntero absoluto se actualiza y el patron se realinea.",
    "El objetivo de la tabla de fallos es no examinar un caracter mas de una vez.",
    "La tabla identifica donde puede existir una nueva coincidencia tras un fallo.",
    "En el patron, se localizan partes que se repiten desde el comienzo.",
    "Por ejemplo, al buscar 'posponer', la tabla indica saltos tras un fallo.",
    "Si el fallo ocurre en la posicion 5, la tabla puede sugerir un salto de 3.",
    "Esto permite alinear el patron con la cadena de busqueda y continuar.",
    "La tabla de fallos se confecciona marcando distancias desde un punto a otro.",
    "Los primeros valores de la tabla son fijados para evitar retrocesos excesivos.",
    "El primer valor es -1, asegurando que siempre se avance en la busqueda.",
    "Las repeticiones relevantes son aquellas que comienzan desde el inicio del patron.",
    "Por ejemplo, si el patron es 'cateter', las repeticiones parciales no cuentan.",
    "El algoritmo KMP es un algoritmo de busqueda de subcadenas simple.",
    "Su objetivo es buscar la existencia de una subcadena llamada patron dentro de otra cadena.",
    "La busqueda se lleva a cabo utilizando informacion basada en los fallos previos.",
    "Se crea previamente una tabla de valores sobre su propio contenido.",
    "El objetivo de esta tabla es determinar donde podria darse la siguiente existencia.",
    "Asi se evita analizar mas de una vez los caracteres de la cadena de busqueda.",
    "En 1970, S.A. Cook sugirio un algoritmo con un tiempo de M+N en el peor caso.",
    "Knuth, Pratt y Morris desarrollaron el algoritmo KMP y lo publicaron en 1976.",
    "El algoritmo localiza la posicion de comienzo de una cadena dentro de otra.",
    "Se calcula una tabla de saltos o tabla de fallos sobre el patron.",
    "Esta tabla se utiliza para hacer saltos cuando hay un fallo de coincidencia.",
    "La cadena donde se busca y el patron se comparan con punteros de avance.",
    "Si ocurre un fallo, el puntero salta segun la tabla de fallos.",
    "El array de busqueda utiliza un puntero absoluto para determinar la seccion.",
    "Dentro de esta seccion, se compara cada caracter con el patron.",
    "Si existen coincidencias, el puntero del patron avanza.",
    "Si se alcanza el final del patron, se devuelve la posicion encontrada.",
    "En caso de fallo, el puntero absoluto se actualiza y el patron se realinea.",
    "El objetivo de la tabla de fallos es no examinar un caracter mas de una vez.",
    "La tabla identifica donde puede existir una nueva coincidencia tras un fallo.",
    "En el patron, se localizan partes que se repiten desde el comienzo.",
    "Por ejemplo, al buscar 'posponer', la tabla indica saltos tras un fallo.",
    "Si el fallo ocurre en la posicion 5, la tabla puede sugerir un salto de 3.",
    "Esto permite alinear el patron con la cadena de busqueda y continuar.",
    "La tabla de fallos se confecciona marcando distancias desde un punto a otro.",
    "Los primeros valores de la tabla son fijados para evitar retrocesos excesivos.",
    "El primer valor es -1, asegurando que siempre se avance en la busqueda.",
    "Las repeticiones relevantes son aquellas que comienzan desde el inicio del patron.",
    "Por ejemplo, si el patron es 'cateter', las repeticiones parciales no cuentan.",
    "El algoritmo KMP es un algoritmo de busqueda de subcadenas simple.",
    "Su objetivo es buscar la existencia de una subcadena llamada patron dentro de otra cadena.",
    "La busqueda se lleva a cabo utilizando informacion basada en los fallos previos.",
    "Se crea previamente una tabla de valores sobre su propio contenido.",
    "El objetivo de esta tabla es determinar donde podria darse la siguiente existencia.",
    "Asi se evita analizar mas de una vez los caracteres de la cadena de busqueda.",
    "En 1970, S.A. Cook sugirio un algoritmo con un tiempo de M+N en el peor caso.",
    "Knuth, Pratt y Morris desarrollaron el algoritmo KMP y lo publicaron en 1976.",
    "El algoritmo localiza la posicion de comienzo de una cadena dentro de otra.",
    "Se calcula una tabla de saltos o tabla de fallos sobre el patron.",
    "Esta tabla se utiliza para hacer saltos cuando hay un fallo de coincidencia.",
    "La cadena donde se busca y el patron se comparan con punteros de avance.",
    "Si ocurre un fallo, el puntero salta segun la tabla de fallos.",
    "El array de busqueda utiliza un puntero absoluto para determinar la seccion.",
    "Dentro de esta seccion, se compara cada caracter con el patron.",
    "Si existen coincidencias, el puntero del patron avanza.",
    "Si se alcanza el final del patron, se devuelve la posicion encontrada.",
    "En caso de fallo, el puntero absoluto se actualiza y el patron se realinea.",
    "El objetivo de la tabla de fallos es no examinar un caracter mas de una vez.",
    "La tabla identifica donde puede existir una nueva coincidencia tras un fallo.",
    "En el patron, se localizan partes que se repiten desde el comienzo.",
    "Por ejemplo, al buscar 'posponer', la tabla indica saltos tras un fallo.",
    "Si el fallo ocurre en la posicion 5, la tabla puede sugerir un salto de 3.",
    "Esto permite alinear el patron con la cadena de busqueda y continuar.",
    "La tabla de fallos se confecciona marcando distancias desde un punto a otro.",
    "Los primeros valores de la tabla son fijados para evitar retrocesos excesivos.",
    "El primer valor es -1, asegurando que siempre se avance en la busqueda.",
    "Las repeticiones relevantes son aquellas que comienzan desde el inicio del patron.",
    "Por ejemplo, si el patron es 'cateter', las repeticiones parciales no cuentan.",
    "El algoritmo KMP es un algoritmo de busqueda de subcadenas simple.",
    "Su objetivo es buscar la existencia de una subcadena llamada patron dentro de otra cadena.",
    "La busqueda se lleva a cabo utilizando informacion basada en los fallos previos.",
    "Se crea previamente una tabla de valores sobre su propio contenido.",
    "El objetivo de esta tabla es determinar donde podria darse la siguiente existencia.",
    "Asi se evita analizar mas de una vez los caracteres de la cadena de busqueda.",
    "En 1970, S.A. Cook sugirio un algoritmo con un tiempo de M+N en el peor caso.",
    "Knuth, Pratt y Morris desarrollaron el algoritmo KMP y lo publicaron en 1976.",
    "El algoritmo localiza la posicion de comienzo de una cadena dentro de otra.",
    "Se calcula una tabla de saltos o tabla de fallos sobre el patron.",
    "Esta tabla se utiliza para hacer saltos cuando hay un fallo de coincidencia.",
    "La cadena donde se busca y el patron se comparan con punteros de avance.",
    "Si ocurre un fallo, el puntero salta segun la tabla de fallos.",
    "El array de busqueda utiliza un puntero absoluto para determinar la seccion.",
    "Dentro de esta seccion, se compara cada caracter con el patron.",
    "Si existen coincidencias, el puntero del patron avanza.",
    "Si se alcanza el final del patron, se devuelve la posicion encontrada.",
    "En caso de fallo, el puntero absoluto se actualiza y el patron se realinea.",
    "El objetivo de la tabla de fallos es no examinar un caracter mas de una vez.",
    "La tabla identifica donde puede existir una nueva coincidencia tras un fallo.",
    "En el patron, se localizan partes que se repiten desde el comienzo.",
    "Por ejemplo, al buscar 'posponer', la tabla indica saltos tras un fallo.",
    "Si el fallo ocurre en la posicion 5, la tabla puede sugerir un salto de 3.",
    "Esto permite alinear el patron con la cadena de busqueda y continuar.",
    "La tabla de fallos se confecciona marcando distancias desde un punto a otro.",
    "Los primeros valores de la tabla son fijados para evitar retrocesos excesivos.",
    "El primer valor es -1, asegurando que siempre se avance en la busqueda.",
    "Las repeticiones relevantes son aquellas que comienzan desde el inicio del patron.",
    "Por ejemplo, si el patron es 'cateter', las repeticiones parciales no cuentan.",
    "El algoritmo KMP es un algoritmo de busqueda de subcadenas simple.",
    "Su objetivo es buscar la existencia de una subcadena llamada patron dentro de otra cadena.",
    "La busqueda se lleva a cabo utilizando informacion basada en los fallos previos.",
    "Se crea previamente una tabla de valores sobre su propio contenido.",
    "El objetivo de esta tabla es determinar donde podria darse la siguiente existencia.",
    "Asi se evita analizar mas de una vez los caracteres de la cadena de busqueda.",
    "En 1970, S.A. Cook sugirio un algoritmo con un tiempo de M+N en el peor caso.",
    "Knuth, Pratt y Morris desarrollaron el algoritmo KMP y lo publicaron en 1976.",
    "El algoritmo localiza la posicion de comienzo de una cadena dentro de otra.",
    "Se calcula una tabla de saltos o tabla de fallos sobre el patron.",
    "Esta tabla se utiliza para hacer saltos cuando hay un fallo de coincidencia.",
    "La cadena donde se busca y el patron se comparan con punteros de avance.",
    "Si ocurre un fallo, el puntero salta segun la tabla de fallos.",
    "El array de busqueda utiliza un puntero absoluto para determinar la seccion.",
    "Dentro de esta seccion, se compara cada caracter con el patron.",
    "Si existen coincidencias, el puntero del patron avanza.",
    "Si se alcanza el final del patron, se devuelve la posicion encontrada.",
    "En caso de fallo, el puntero absoluto se actualiza y el patron se realinea.",
    "El objetivo de la tabla de fallos es no examinar un caracter mas de una vez.",
    "La tabla identifica donde puede existir una nueva coincidencia tras un fallo.",
    "En el patron, se localizan partes que se repiten desde el comienzo.",
    "Por ejemplo, al buscar 'posponer', la tabla indica saltos tras un fallo.",
    "Si el fallo ocurre en la posicion 5, la tabla puede sugerir un salto de 3.",
    "Esto permite alinear el patron con la cadena de busqueda y continuar.",
    "La tabla de fallos se confecciona marcando distancias desde un punto a otro.",
    "Los primeros valores de la tabla son fijados para evitar retrocesos excesivos.",
    "El primer valor es -1, asegurando que siempre se avance en la busqueda.",
    "Las repeticiones relevantes son aquellas que comienzan desde el inicio del patron.",
    "Por ejemplo, si el patron es 'cateter', las repeticiones parciales no cuentan.",
    "El algoritmo KMP es un algoritmo de busqueda de subcadenas simple.",
    "Su objetivo es buscar la existencia de una subcadena llamada patron dentro de otra cadena.",
    "La busqueda se lleva a cabo utilizando informacion basada en los fallos previos.",
    "Se crea previamente una tabla de valores sobre su propio contenido.",
    "El objetivo de esta tabla es determinar donde podria darse la siguiente existencia.",
    "Asi se evita analizar mas de una vez los caracteres de la cadena de busqueda.",
    "En 1970, S.A. Cook sugirio un algoritmo con un tiempo de M+N en el peor caso.",
    "Knuth, Pratt y Morris desarrollaron el algoritmo KMP y lo publicaron en 1976.",
    "El algoritmo localiza la posicion de comienzo de una cadena dentro de otra.",
    "Se calcula una tabla de saltos o tabla de fallos sobre el patron.",
    "Esta tabla se utiliza para hacer saltos cuando hay un fallo de coincidencia.",
    "La cadena donde se busca y el patron se comparan con punteros de avance.",
    "Si ocurre un fallo, el puntero salta segun la tabla de fallos.",
    "El array de busqueda utiliza un puntero absoluto para determinar la seccion.",
    "Dentro de esta seccion, se compara cada caracter con el patron.",
    "Si existen coincidencias, el puntero del patron avanza.",
    "Si se alcanza el final del patron, se devuelve la posicion encontrada.",
    "En caso de fallo, el puntero absoluto se actualiza y el patron se realinea.",
    "El objetivo de la tabla de fallos es no examinar un caracter mas de una vez.",
    "La tabla identifica donde puede existir una nueva coincidencia tras un fallo.",
    "En el patron, se localizan partes que se repiten desde el comienzo.",
    "Por ejemplo, al buscar 'posponer', la tabla indica saltos tras un fallo.",
    "Si el fallo ocurre en la posicion 5, la tabla puede sugerir un salto de 3.",
    "Esto permite alinear el patron con la cadena de busqueda y continuar.",
    "La tabla de fallos se confecciona marcando distancias desde un punto a otro.",
    "Los primeros valores de la tabla son fijados para evitar retrocesos excesivos.",
    "El primer valor es -1, asegurando que siempre se avance en la busqueda.",
    "Las repeticiones relevantes son aquellas que comienzan desde el inicio del patron.",
    "Por ejemplo, si el patron es 'cateter', las repeticiones parciales no cuentan.",
    "El patron 'cateter' solo considera repeticiones desde el comienzo del texto."
    };


    // Palabras clave a buscar
    vector<string> palabras_clave = {"tabla", "KMP", "algoritmo"};

    for (const string& palabra : palabras_clave) {
        cout << "Buscando la palabra clave: " << palabra << endl;

        // Búsqueda con KMP
        auto inicioKMP = chrono::high_resolution_clock::now();
        for (int i = 0; i < texto.size(); i++) {
            vector<int> posiciones = buscarKMP(texto[i], palabra);
            if (!posiciones.empty()) {
                cout << "KMP - Linea " << i + 1 << ": ";
                for (int pos : posiciones) {
                    cout << "Posicion " << pos << " ";
                }
                cout << endl;
            }
        }
        auto finKMP = chrono::high_resolution_clock::now();
        auto duracionKMP = chrono::duration_cast<chrono::milliseconds>(finKMP - inicioKMP).count();
        cout << "Tiempo de ejecucion KMP: " << duracionKMP << " ms" << endl;

        // Búsqueda con Boyer-Moore
        auto inicioBM = chrono::high_resolution_clock::now();
        for (int i = 0; i < texto.size(); i++) {
            vector<int> posiciones = buscarBM(texto[i], palabra);
            if (!posiciones.empty()) {
                cout << "Boyer-Moore - Linea " << i + 1 << ": ";
                for (int pos : posiciones) {
                    cout << "Posicion " << pos << " ";
                }
                cout << endl;
            }
        }
        auto finBM = chrono::high_resolution_clock::now();
        auto duracionBM = chrono::duration_cast<chrono::milliseconds>(finBM - inicioBM).count();
        cout << "Tiempo de ejecucion Boyer-Moore: " << duracionBM << " ms" << endl;

        cout << "-------------------------" << endl;
    }

    return 0;
}