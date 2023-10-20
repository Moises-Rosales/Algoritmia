#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void comprimirRLE(const string &nombreArchivoEntrada, const string &nombreArchivoSalida) {
    ifstream archivoEntrada(nombreArchivoEntrada, ios::binary);
    ofstream archivoSalida(nombreArchivoSalida, ios::binary);

    if (!archivoEntrada.is_open() || !archivoSalida.is_open()) {
        cerr << "Error al abrir los archivos de entrada o salida." << endl;
        return;
    }

    // Escribir la cabecera
    uint8_t cabecera[] = {'R', 'L', 'C', 8, 16};
    archivoSalida.write(reinterpret_cast<char*>(cabecera), sizeof(cabecera));

    char caracterActual, caracterAnterior = 0;
    int repeticiones = 0;

    while (archivoEntrada.read(&caracterActual, 1)) {
        if (caracterActual == caracterAnterior) {
            repeticiones++;
        } else {
            archivoSalida.write(&caracterAnterior, 1);
            archivoSalida.write(reinterpret_cast<char*>(&repeticiones), 2);
            repeticiones = 1;
            caracterAnterior = caracterActual;
        }
    }

    // Escribir el último carácter y sus repeticiones
    archivoSalida.write(&caracterAnterior, 1);
    archivoSalida.write(reinterpret_cast<char*>(&repeticiones), 2);

    archivoEntrada.close();
    archivoSalida.close();

    cout << "Compresión completada." << endl;
}

int main() {
    string nombreArchivoEntrada, nombreArchivoSalida;
    cout << "Ingrese el nombre del archivo de entrada: ";
    cin >> nombreArchivoEntrada;
    cout << "Ingrese el nombre del archivo de salida (con extension .rlc): ";
    cin >> nombreArchivoSalida;

    comprimirRLE(nombreArchivoEntrada, nombreArchivoSalida);

    return 0;
}
