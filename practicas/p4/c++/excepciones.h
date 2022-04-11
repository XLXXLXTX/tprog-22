#pragma once
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

/**
 * @brief Excepcion personalizada para el arbol de fichero a realizar
 * deriva de runtime_error que es padre de todas las excepciones 
 * 
 */
class arbol_ficheros_error {
    public:
        //Cada excepcion redefine la funcion what() con su propio msg de error
        virtual const char* what() const throw() = 0;   
};

/**
 * @brief Excepcion para indicar que se quiere acceder a un directorio que no existe.
 * 
 */
class directorio_inexistente : public arbol_ficheros_error {
    const char* what() const throw(){
        return "ERROR: directorio inexistente";
    }
};

/**
 * @brief Excepcion para indicar que se quiere añadir un fichero con el mismo nombre
 * que otro fichero ya existente en el mismo directorio. 
 * 
 */
class fichero_ya_existente : public arbol_ficheros_error {
    const char* what() const throw(){
        return "ERROR: ya existe un fichero con el mismo nombre";
    }
};