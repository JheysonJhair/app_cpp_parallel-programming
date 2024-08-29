#include <iostream>
#include <vector>
#include <thread>
#include <memory>
#include "../class/Funciones.h"
#include "../class/Cliente.h"

const int NUM_THREADS = 4; 

void buscarConHilos(const std::string& archivo, const std::string& ruc) {
    std::vector<Cliente> clientes;
    cargarDatos(archivo, clientes);
    
    int numClientes = clientes.size();
    int chunkSize = numClientes / NUM_THREADS;
    std::vector<std::thread> threads;
    std::shared_ptr<Cliente> resultado = nullptr;
    
    for (int i = 0; i < NUM_THREADS; ++i) {
        int start = i * chunkSize;
        int end = (i == NUM_THREADS - 1) ? numClientes : (i + 1) * chunkSize;
        
        threads.emplace_back([&clientes, &ruc, start, end, &resultado]() {
            buscarClienteEnRango(clientes, ruc, start, end, resultado);
        });
    }
    
    for (auto& thread : threads) {
        thread.join();
    }
    
    if (resultado) {
        std::cout << "Cliente encontrado: " << resultado->nombre << std::endl;
    } else {
        std::cout << "Cliente no encontrado." << std::endl;
    }
}

void buscarConVector(const std::string& archivo, const std::string& ruc) {
    std::vector<Cliente> clientes;
    cargarDatos(archivo, clientes);
    
    std::shared_ptr<Cliente> resultado = buscarClienteEnVector(clientes, ruc);
    
    if (resultado) {
        std::cout << "Cliente encontrado: " << resultado->nombre << std::endl;
    } else {
        std::cout << "Cliente no encontrado." << std::endl;
    }
}

void buscarSinParalelismo(const std::string& archivo, const std::string& ruc) {
    std::shared_ptr<Cliente> resultado = buscarClienteEnArchivo(archivo, ruc);
    
    if (resultado) {
        std::cout << "Cliente encontrado: " << resultado->nombre << std::endl;
    } else {
        std::cout << "Cliente no encontrado." << std::endl;
    }
}

int main() {
    std::string archivo = "../data/padron_reducido_ruc.txt";
    
    while (true) {
        std::cout << "===========================================================================" << std::endl;
        std::cout << "|                             MENU PRINCIPAL                              |" << std::endl;
        std::cout << "===========================================================================" << std::endl;
        std::cout << "|1. Buscar datos de un cliente usando hilos                               |" << std::endl;
        std::cout << "|2. Buscar datos de un cliente usando programacion funcional en un vector |" << std::endl;
        std::cout << "|3. Buscar datos de un cliente sin paralelismo (optimizacion)             |" << std::endl;
        std::cout << "|-------------------------------------------------------------------------|" << std::endl;
        std::cout << "|4. Salir                                                                 |" << std::endl;
        std::cout << "|-------------------------------------------------------------------------|" << std::endl;

        int opcion;
        std::cin >> opcion;
        
        if (opcion == 4) {
            break;
        }
        
        std::string rucABuscar;
        std::cout << "Ingrese el RUC que desea buscar: ";
        std::cin >> rucABuscar;
        
        switch (opcion) {
            case 1:
                buscarConHilos(archivo, rucABuscar);
                break;
            case 2:
                buscarConVector(archivo, rucABuscar);
                break;
            case 3:
                buscarSinParalelismo(archivo, rucABuscar);
                break;
            default:
                std::cout << "Opción no válida. Inténtelo de nuevo." << std::endl;
                break;
        }
    }
    
    return 0;
}
