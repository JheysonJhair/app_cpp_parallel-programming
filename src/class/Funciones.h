#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <vector>
#include <string>
#include <memory>  
#include "../class/Cliente.h"

// Carga datos del archivo en un vector de Clientes
void cargarDatos(const std::string& archivo, std::vector<Cliente>& clientes);

// Busca un cliente por su RUC en el rango de índices especificado usando hilos
void buscarClienteEnRango(const std::vector<Cliente>& clientes, const std::string& ruc, int start, int end, std::shared_ptr<Cliente>& resultado);

// Busca un cliente en el vector usando programación funcional
std::shared_ptr<Cliente> buscarClienteEnVector(const std::vector<Cliente>& clientes, const std::string& ruc);

// Busca un cliente en el archivo sin paralelismo
std::shared_ptr<Cliente> buscarClienteEnArchivo(const std::string& archivo, const std::string& ruc);

#endif 
