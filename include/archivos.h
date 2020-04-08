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
    
    void leerArchivos();

    struct Errores{
        bool directorio;
        bool archivo_descriptor;
        int codigo_archivo_descriptor;
        bool archivo_memoria;
    };
    Archivos::Errores comprobarErrores();

    std::vector<std::string> obtenerEntradas();
    std::vector<std::string> obtenerEnlaces();
private:
    void cerrarDirectorio();
    void cerrarArchivo();
    std::string nombreCarpeta;
    SceUID dir; //Representa el directorio
    SceUID file; //Respresenta el archivo
    SceIoDirent entrada; //Representa los datos de un archivo que se encuentre en dir
    std::vector<std::string> entradas; //Representa el nombre de todos los archivos
    std::vector<std::string> enlaces; //Los enlaces
    Errores error; 
};