#include <psp2/io/dirent.h>
#include <psp2/io/fcntl.h>
#include <psp2/io/stat.h>

#include <string>
#include <vector>

#include "archivos.h"

Archivos::Archivos(std::string _nombre)
{
    nombreCarpeta = _nombre;
    error.directorio = false;
    error.archivo_descriptor = false;
    error.archivo_memoria = false;
    error.codigo_archivo_descriptor = 0;
}

void Archivos::abrirDirectorio()
{
    //Abrimos la carpeta
    dir = sceIoDopen(nombreCarpeta.c_str());
    if(dir < 0)
    {
        error.directorio = true;
        return;
    }
    //Leemos la carpeta
    int ret = 1;
    while(ret != 0)
    {
        ret = sceIoDread(dir, &entrada);
        entradas.push_back(std::string(entrada.d_name));
    }
    //Cerramos la carpeta:
    cerrarDirectorio();
}

void Archivos::leerArchivos()
{
    if(error.directorio) return;

    for(int i = 0; i < entradas.size(); ++i)
    {
        //Obtenemos el tamaño del archivo
        std::string nombreArchivo = nombreCarpeta + entradas.at(i);
        SceIoStat estado;
        sceIoGetstat(nombreArchivo.c_str(), &estado);
        //Abrimos el archivo
        file = sceIoOpen(nombreArchivo.c_str(), SCE_O_RDONLY, 0777);
        if(file < 0)
        {
            error.codigo_archivo_descriptor = file;
            error.archivo_descriptor = true;
            return;
        }
        //Creamos el arreglo dinamico y leemos el archivo
        char* contenido = (char*)calloc(estado.st_size+1, sizeof(char));
        if(contenido == NULL)
        {
            error.archivo_memoria = true;
            return;
        }
        sceIoRead(file, contenido, estado.st_size);
        contenido[estado.st_size] = '\0'; //Para que string() nos acepte el arreglo
        //Guardamos el contenido en el std::vector
        enlaces.push_back(std::string(contenido));
        //Limpiamos
        free(contenido);
        contenido = NULL; //Aumentamos seguridad
    }
    error.archivo_descriptor = false;
    error.archivo_memoria = false;
    error.codigo_archivo_descriptor = 0;
}

void Archivos::cerrarDirectorio()
{
    sceIoDclose(dir);
}

void Archivos::cerrarArchivo()
{
    sceIoClose(file);
}

std::vector<std::string> Archivos::obtenerEntradas()
{
    return entradas;
}

std::vector<std::string> Archivos::obtenerEnlaces()
{
    return enlaces;
}

Archivos::Errores Archivos::comprobarErrores()
{
    return error;
}