#pragma once
#include <psp2/io/dirent.h>
#include <psp2/io/fcntl.h>
#include <psp2/io/stat.h>

#include <string>
#include <vector>

class Archivos{
public:
    Archivos(std::string _nombre);
    void abrirDirectorio();
    
    void abrirArchivosDirectorio();
    void cerrarArchivosDirectorio();

    std::vector<std::string> obtenerEntradas();
private:
    void cerrarDirectorio();
    std::string nombreCarpeta;
    SceUID dir;
    SceUID file;
    SceIoDirent entrada;
    std::vector<std::string> entradas;
};