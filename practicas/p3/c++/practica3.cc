#include "practica3.h"
#include <iostream>
using namespace std;

//------------------------------------------------------------------------------
// Clase Nameable
//------------------------------------------------------------------------------
Nameable::Nameable(const string& nombre) 
         : name(nombre){
}

Nameable::~Nameable(){/*nada*/}

//------------------------------------------------------------------------------
// Clase Carga
//------------------------------------------------------------------------------
Carga::Carga(const string& _name, double _volume, double _weight) 
     : name(_name), volume(_volume), weight(_weight) {
            
}

Carga::~Carga(){/*nada*/}

//------------------------------------------------------------------------------
// Clase Producto
//------------------------------------------------------------------------------
Producto::Producto(const string& _name, double _volume, double _weigth) 
         : Carga(_name, _volume, _weigth) {

}

Producto::~Producto(){/*nada*/}

double Producto::peso(){
    return Carga::weight;
}

double Producto::volumen(){
    return Carga::volume;
}

string Producto::nombre(){
    return Carga::name;
}

/* string Producto::to_string(const string ident) {
    stringstream stream;
    stream << ident << Carga::name << " [" << std::setprecision(1) << Carga::volume << " m3]" << " [" << std::setprecision(2) << Carga::weight << " kg]";
    return stream.str();
} */

SerVivo::SerVivo(const string& _name, double _volume, double _weight) : CargaEspecial( _name, _volume, _weight){
    /*nada*/

}

SerVivo::~SerVivo(){
    /*nada*/
}

Toxico::Toxico(const string& _name, double _volume, double _weight) : CargaEspecial( _name, _volume, _weight){
    /*nada*/

}

Toxico::~Toxico(){
    /*nada*/
}

