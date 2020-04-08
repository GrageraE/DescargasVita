#include <psp2/kernel/processmgr.h>
#include <psp2/ctrl.h>

#include "red.h"
#include "archivos.h"

#include "debugScreen.h"
#define printf psvDebugScreenPrintf

int main()
{
    psvDebugScreenInit();
    printf("Bienvenido a DescargasVita\n");
    SceCtrlData data;
    sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);
    //Red r;
    printf("Pulsa X para recoger los enlaces de una carpeta\n");
    printf("Pulsa START para lanzar un IME\n");
    printf("Pulsa SELECT para salir\n");
    do{
        sceCtrlPeekBufferPositive(0, &data, 1);
        
        if(data.buttons == SCE_CTRL_CROSS)
        {
            sceKernelDelayThread(0.5*1000*1000);
            SceCtrlData data2;
            printf("Se obtendran los enlaces de la carpeta: ux0:/data/DescargasVita/\n");
            printf("Pulsa SELECT para salir\n");
            printf("Pulsa START o X para contunuar...\n");
            do{
                sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);
                sceCtrlPeekBufferPositive(0, &data2, 2);
                
                if(data2.buttons == SCE_CTRL_SELECT) goto salida;
                if(data2.buttons == SCE_CTRL_CROSS || data2.buttons == SCE_CTRL_START) break;
            }while(true);

            printf("Abriendo...\n");
            Archivos a("ux0:/data/DescargasVita/");
            a.abrirDirectorio();
            a.leerArchivos();
            std::vector<std::string> enlaces = a.obtenerEnlaces();
            printf("AVISO: Se descargaran de los siguientes enlaces:\n");
            for(int i = 0; i < enlaces.size(); ++i)
            {
                printf(enlaces.at(i).c_str());
                printf("\n");
            }
            Archivos::Errores errores = a.comprobarErrores();
            printf("Errores:\n");
            printf("Directorio: %d \n", errores.directorio);
            printf("Archivo: descriptores: %d \n", errores.archivo_descriptor);
            printf("    Codigo de error (si no es negativo, no es error): %d \n", errores.codigo_archivo_descriptor);
            printf("Archivo: memoria: %d \n", errores.archivo_memoria);
            sceKernelDelayThread(3*1000*1000);
            goto salida;
        }
    }while(data.buttons != SCE_CTRL_SELECT);
    salida:;
    //.limpiar();
    printf("\nSaliendo...\n");
    sceKernelExitProcess(0);
    return 0;
}