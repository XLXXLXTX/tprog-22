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

string Producto::to_string(const string ident) {
    stringstream stream;
    stream << std::setprecision(2) << ident << Carga::name << " [" << std::to_string(Carga::volume) << " m3]" << " [" << std::to_string(Carga::weight) << " kg]";
    return stream.str();
}

//------------------------------------------------------------------------------
// Clase Almacen
//------------------------------------------------------------------------------

/*

template <typename T>
Almacen<T>::Almacen(double _capacidad){
    size=_capacidad;
    remainingSpace=_capacidad;
}

template <typename T>
Almacen<T>::~Almacen(){}

template <typename T>
bool Almacen<T>::guardar(T& elemento){
    
    if(Almacen::espacioDisponible() >= elemento.volumen()){
        Almacen::remainingSpace = Almacen::espacioDisponible() - elemento.volumen();
        Almacen::lista.push_back(elemento);
        return true;
    }else{
        return false;
    }
}

template <typename T>
double Almacen<T>::capacidad(){
    return Almacen::size;
}

template <typename T>
double Almacen<T>::espacioDisponible(){
    return Almacen::remainingSpace;
}

*/

//------------------------------------------------------------------------------
// Clase Contenedor
//------------------------------------------------------------------------------

/*

template <typename T>
Contenedor<T>::Contenedor(double _capacidad) 
           : Nameable("Contenedor"), Almacen<T>(_capacidad){
               
}

template <typename T>
Contenedor<T>::~Contenedor(){ }

template <typename T>
string Contenedor<T>::nombre(){
    return Nameable::name;
}

template <typename T>
string Contenedor<T>::to_string(){
    string info;
    info = "Contenedor{nombre=" + Nameable::name + ", capacidad=" + std::to_string(Almacen<T>::size)+"}" + "\n";
    for(auto n : Almacen<T>::lista){
        info += "\t\t" + n.to_string() + "\n";
    }
    return info;
}

*/