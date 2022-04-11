#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include "excepciones.h"

using namespace std;

/**
 * @brief Clase padre de Directorio, Fichero y Enlace
 * 
 */
class Elemento {
    protected:
        string name;
        int sizeInBytes;

    public:
        //Constructor
        Elemento(const string& _name, int _sizeInBytes) : name(_name), sizeInBytes(_sizeInBytes){
            /*nada*/
        }

        //funcion para recuperar el nombre del elemento
        string nombre(){
            return name;
        }

        //Funcion virtual para que cada clase hijo la redefina si es necesario 
        virtual int tamanio(){
            return sizeInBytes;
        }

};



/**
 * @brief Representa un directorio (incluyendo el raiz)
 * 
 */
template <typename T>
class Directorio{
    protected:
        //un directorio puede contenener: otros directorios, ficheros y enlaces
        vector<T*> contenidoDir;
    public:
        Directorio();
};

class Fichero{
    protected:

    public:
        Fichero();
};

class Enlace{
    protected:

    public:
        Enlace();
};

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

class Ruta {

};