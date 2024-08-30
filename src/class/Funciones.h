#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <vector>
#include <string>
#include <memory>  
#include "../class/Cliente.h"

void cargarDatos(const std::string& archivo, std::vector<Cliente>& clientes);

void buscarClienteEnRango(const std::vector<Cliente>& clientes, const std::string& ruc, int start, int end, std::shared_ptr<Cliente>& resultado);

std::shared_ptr<Cliente> buscarClienteEnVector(const std::vector<Cliente>& clientes, const std::string& ruc);

std::shared_ptr<Cliente> buscarClienteEnArchivo(const std::string& archivo, const std::string& ruc);

#endif 
