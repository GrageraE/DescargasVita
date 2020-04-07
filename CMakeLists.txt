CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

project(DescargasVita)
include("${VITASDK}/share/vita.cmake" REQUIRED)

set(VITA_APP_NAME ${PROJECT_NAME})
set(VITA_VERSION "01.00")
set(VITA_ID "GRAG00007")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(
    include/
)

add_executable(${PROJECT_NAME}
src/main.cpp
src/red.cpp
src/archivos.cpp
#src/ime.cpp
)

target_link_libraries(${PROJECT_NAME}
SceDisplay_stub
SceCtrl_stub
SceSysmodule_stub
SceNet_stub
SceHttp_stub
SceNetCtl_stub
SceIofilemgr_stub 
SceIme_stub
SceCommonDialog_stub
)

vita_create_self(${PROJECT_NAME}.self ${PROJECT_NAME})
vita_create_vpk(${PROJECT_NAME}.vpk ${VITA_ID} ${PROJECT_NAME}.self
VERSION ${VITA_VERSION}
NAME ${VITA_APP_NAME}
#Include the 'sce_sys' Live Area content
)