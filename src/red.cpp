#include <psp2/net/http.h>
#include <psp2/net/net.h>
#include <psp2/net/netctl.h>

#include <psp2/sysmodule.h>
//#include "debugScreen.h"


#include <stdlib.h>
#include <memory>

#include "red.h"

void Red::inicializarRed()
{
    //Cargamos los modulos
    if(!sceSysmoduleIsLoaded(SCE_SYSMODULE_NET)) sceSysmoduleLoadModule(SCE_SYSMODULE_NET);
    if(!sceSysmoduleIsLoaded(SCE_SYSMODULE_HTTP)) sceSysmoduleLoadModule(SCE_SYSMODULE_HTTP);
    //Inicializamos la red
    SceNetInitParam* param;
    param->flags = 0;
    param->size = 1024*1024;
    param->memory = malloc(1024*1024);
    sceNetInit(param);
    sceNetCtlInit();
    //Inicializamos el Http
    sceHttpInit(1024*1024);
}

void Red::limpiarRed()
{
    sceNetCtlTerm();
    sceNetTerm();
    sceHttpTerm();
    if(sceSysmoduleIsLoaded(SCE_SYSMODULE_HTTP)) sceSysmoduleUnloadModule(SCE_SYSMODULE_HTTP);
    if(sceSysmoduleIsLoaded(SCE_SYSMODULE_NET)) sceSysmoduleUnloadModule(SCE_SYSMODULE_NET);

}

Red::Red()
{
    inicializarRed();
}

void Red::limpiar()
{
    limpiarRed();
}