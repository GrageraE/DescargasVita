#pragma once
#include <string>

class Red{
public:
    Red();
    void limpiar();
    void setUrl();
private:
    void inicializarRed();
    void limpiarRed();
    void descargar();
    std::string* url = nullptr;
};