#include "../class/Funciones.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <thread>
#include <mutex>
#include <algorithm>

std::mutex resultadoMutex;

void cargarDatos(const std::string& archivo, std::vector<Cliente>& clientes) {
    std::ifstream file(archivo);
    std::string linea;
    
    if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << archivo << std::endl;
        return;
    }
    
    std::getline(file, linea);
    
    while (std::getline(file, linea)) {
        if (linea.empty()) continue;
        
        std::stringstream ss(linea);
        std::string ruc, nombre, estado, condicion;
        std::getline(ss, ruc, '|');
        std::getline(ss, nombre, '|');
        std::getline(ss, estado, '|');
        std::getline(ss, condicion, '|');
        
        if (ruc.empty()) {
            std::cerr << "RUC vacío en la línea: " << linea << std::endl;
            continue;
        }
        
        clientes.emplace_back(ruc, nombre, estado, condicion);
    }
    
    file.close();
}

void buscarClienteEnRango(const std::vector<Cliente>& clientes, const std::string& ruc, int start, int end, std::shared_ptr<Cliente>& resultado) {
    for (int i = start; i < end; ++i) {
        if (clientes[i].ruc == ruc) {
            std::lock_guard<std::mutex> guard(resultadoMutex);
            if (!resultado) {
                resultado = std::make_shared<Cliente>(clientes[i]);
            }
            return;
        }
    }
}

std::shared_ptr<Cliente> buscarClienteEnVector(const std::vector<Cliente>& clientes, const std::string& ruc) {
    auto it = std::find_if(clientes.begin(), clientes.end(), [&ruc](const Cliente& cliente) {
        return cliente.ruc == ruc;
    });

    if (it != clientes.end()) {
        return std::make_shared<Cliente>(*it);
    }
    
    return nullptr;
}

std::shared_ptr<Cliente> buscarClienteEnArchivo(const std::string& archivo, const std::string& ruc) {
    std::ifstream file(archivo);
    std::string linea;
    
    if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << archivo << std::endl;
        return nullptr;
    }
    
    std::getline(file, linea);
    
    while (std::getline(file, linea)) {
        if (linea.empty()) continue;
        
        std::stringstream ss(linea);
        std::string rucEnArchivo, nombre, estado, condicion;
        std::getline(ss, rucEnArchivo, '|');
        
        if (rucEnArchivo == ruc) {
            std::getline(ss, nombre, '|');
            std::getline(ss, estado, '|');
            std::getline(ss, condicion, '|');
            return std::make_shared<Cliente>(rucEnArchivo, nombre, estado, condicion);
        }
    }
    
    return nullptr;
}
