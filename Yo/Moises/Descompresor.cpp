#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void descomprimirRLE(const string &nombreArchivoEntrada, const string &nombreArchivoSalida) {
    ifstream archivoEntrada(nombreArchivoEntrada, ios::binary);
    ofstream archivoSalida(nombreArchivoSalida, ios::binary);

    if (!archivoEntrada.is_open() || !archivoSalida.is_open()) {
        cerr << "Error al abrir los archivos de entrada o salida." << endl;
        return;
    }

    // Leer y validar la cabecera
    uint8_t cabecera[5];
    archivoEntrada.read(reinterpret_cast<char*>(cabecera), sizeof(cabecera));

    if (cabecera[0] != 'R' || cabecera[1] != 'L' || cabecera[2] != 'C' || cabecera[3] != 8 || cabecera[4] != 16) {
        cerr << "El archivo de entrada no tiene la cabecera esperada." << endl;
        return;
    }

    char caracter;
    uint16_t repeticiones;

    while (archivoEntrada.read(&caracter, 1)) {
        archivoEntrada.read(reinterpret_cast<char*>(&repeticiones), 2);

        for (int i = 0; i < repeticiones; i++) {
            archivoSalida.write(&caracter, 1);
        }
    }

    archivoEntrada.close();
    archivoSalida.close();

    cout << "Descompresión completada." << endl;
}

int main() {
    string nombreArchivoEntrada, nombreArchivoSalida;
    cout << "Ingrese el nombre del archivo comprimido: ";
    cin >> nombreArchivoEntrada;
    cout << "Ingrese el nombre del archivo de salida: ";
    cin >> nombreArchivoSalida;

    descomprimirRLE(nombreArchivoEntrada, nombreArchivoSalida);

    return 0;
}
