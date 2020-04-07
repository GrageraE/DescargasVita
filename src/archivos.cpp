#include <psp2/io/dirent.h>
#include <psp2/io/fcntl.h>
#include <psp2/io/stat.h>

#include <string>
#include <vector>

#include "archivos.h"

Archivos::Archivos(std::string _nombre)
{
    nombreCarpeta = _nombre;
}

void Archivos::abrirDirectorio()
{
    //Abrimos la carpeta
    dir = sceIoDopen(nombreCarpeta.c_str());
    if(dir < 0) return; //TODO: Manejar error
    //Leemos la carpeta
    int ret = 1;
    while(ret != 0)
    {
        ret = sceIoDread(dir, &entrada);
        entradas.push_back(entrada.d_name);
    }
    //Cerramos la carpeta:
    cerrarDirectorio();
}

void Archivos::cerrarDirectorio()
{
    sceIoDclose(dir);
}

std::vector<std::string> Archivos::obtenerEntradas()
{
    return entradas;
}