#include <iostream>
#include <fstream>
#include <iomanip>

   int main() {
       std::ifstream archivo("nombreArchivoSalida.rlc", std::ios::binary);
       if (!archivo.is_open()) {
           std::cerr << "Error al abrir el archivo." << std::endl;
           return 1;
       }

       std::ios::fmtflags oldFlags = std::cout.flags();  // Guardar las banderas actuales de cout
       std::cout << std::hex << std::setfill('0');  // Configurar cout para mostrar en hexadecimal

       char byte;
       while (archivo.get(byte)) {
           std::cout << std::setw(2) << static_cast<int>(static_cast<unsigned char>(byte)) << ' ';
       }

       std::cout << std::dec;  // Restaurar cout a su configuración original
       std::cout.flags(oldFlags);  // Restaurar las banderas originales

       archivo.close();
       return 0;
   }
