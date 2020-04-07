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
            SceCtrlData data2;
            printf("Se obtendran los enlaces de la carpeta: ux0:/data/DescargasVita/\n");
            printf("Pulsa SELECT para salir\n");
            printf("Pulsa START o X para contunuar...\n");
            do{
                sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);
                sceCtrlPeekBufferPositive(0, &data2, 2);
                
                if(data2.buttons == SCE_CTRL_SELECT) goto salida;
                else if(data2.buttons == SCE_CTRL_START) break;
            }while(data2.buttons != SCE_CTRL_START || data2.buttons != SCE_CTRL_CROSS);

            printf("Abriendo...\n");
            Archivos a("ux0:/data/DescargasVita");
            a.abrirDirectorio();
            std::vector<std::string> lista = a.obtenerEntradas();
            for(int i = 0; i < lista.size(); ++i)
            {
                printf("%s \n", lista.at(i).c_str());
            }
        }
    }while(data.buttons != SCE_CTRL_SELECT);
    salida:;
    //.limpiar();
    printf("Saliendo...\n");
    sceKernelExitProcess(0);
    return 0;
}