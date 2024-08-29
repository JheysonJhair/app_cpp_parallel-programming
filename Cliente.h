#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>

class Cliente {
public:
    std::string ruc;
    std::string nombre;
    std::string estado;
    std::string condicion;

    Cliente() = default;
    Cliente(const std::string& ruc, const std::string& nombre, const std::string& estado, const std::string& condicion)
        : ruc(ruc), nombre(nombre), estado(estado), condicion(condicion) {}
};

#endif // CLIENTE_H
