#pragma once
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

class Nameable {
    protected:
        string name;

    public:
        Nameable(const string& nombre);
        ~Nameable();
        virtual string nombre() = 0;
        virtual string to_string() =0;
};


/**
 * @brief representará cualquier carga (producto o contenedores) que se pueden transportar dentro de un "Almacen" (contenedor o camión)
 * 
 */
class Carga {
    protected:
        double weight;
        double volume;
        string name;
    
    public:
        Carga(const string& _name, double _volume, double _weight);
        ~Carga();
        virtual double peso() = 0;
        virtual double volumen() = 0;
        virtual string nombre() = 0;
        virtual string to_string() = 0;
};

/**
 * @brief representará un productomediante un nombre identificativo (una cadena de texto), su volumen, y su peso.
 * 
 */
class Producto : public Carga{
    /*Constructor*/
    private:
    /*nada*/

    public:
        Producto(const string& _name, double _volume, double _weight);
        ~Producto();
        
        //Heredadas de la clase Carga
        double peso() override;
        double volumen() override;
        string nombre() override;
        string to_string() override;

};

//----------------------------------------------------------------------------------------------------------------------

/**
 * @brief Interfaza Almacen para heredar el poder guardar elementos
 * 
 */
template <typename T>
class Almacen{ 
    protected:
        //vector de cosas genericas a guardar
        double totalWeight;
        double size;
        double remainingSpace;
        vector<T*> lista;    //lista para almacenar cualquier cosa (T generico)
        
        double peso(){
            return totalWeight;
        }

    public:
        Almacen(double _capacidad){ 
            /*capacidad ~= volumen del total de objetos que caben*/
            /*peso del Almacen NO tiene limite, es la suma de los peso de los objetos que contniene*/
            size=_capacidad;
            remainingSpace=_capacidad;
            totalWeight=0;
        }

        ~Almacen(){/*nada*/}
        
        //almacena cualquier generico
        bool guardar(T& elemento){
            if(espacioDisponible() >= elemento.volumen()){
                remainingSpace = espacioDisponible() - elemento.volumen();
                totalWeight += elemento.peso();
                this->lista.push_back(&elemento);
                return true;
            }else{
                return false;
            }
        } 

        double capacidad(){
            return size;
        }
        double espacioDisponible(){
            return remainingSpace;
        }

        //bool hayHueco(); //Freestyle
        
};

/**
 * @brief representará un contenedor con su correspondiente capacidad (que equivale a su volumen). Dicho valor se le pasará en su constructor
 * 
 */
template <typename T>
class Contenedor : public Carga, public Almacen<T>{
    protected:
        /*nada*/

    public:
        Contenedor(double _capacidad) : Carga("Carga Estandar", 0, 0), Almacen<T>(_capacidad){
            /*nada*/
        }

        ~Contenedor(){ }


        double peso() override {
            return Almacen<T>::peso();
        }

        double volumen() override {
            return Almacen<T>::capacidad();
        }

        string nombre() override {
            return Carga::name;
        }

        string to_string() override{
            stringstream stream;
            
            //TODO: arreglar el formato del to_string() si el cotenedor esta dentro de un camion.

            stream << std::setprecision(2) << "Contenedor [" << std::to_string(Almacen<T>::capacidad()) << " m3]" << " [" << std::to_string(Almacen<T>::peso()) << " kg]" << " de " <<  Carga::name << "\n";
            for(auto& n : Almacen<T>::lista){
                stream << "  " << n->to_string() << "\n";
            }
            return stream.str();

            /* string info;
            info = std::setprecision(2) + "Contenedor [" + std::to_string(Almacen<T>::capacidad()) + "m3]" + " [" + std::to_string(Almacen<T>::peso()) + " kg]" + " de "+  Carga::name + "\n";
            for(auto& n : Almacen<T>::lista){
                info += "  " + n->to_string() + "\n";
            }
            return info; */
        }
};



class Camion : public Nameable, public Almacen<Carga>{
    protected:
        /*nada*/
    public:
        Camion(double _capacidad) : Nameable("Camión"), Almacen<Carga>(_capacidad){
            /*nada*/
        }

        ~Camion(){ /**/ }

        string nombre() override {
            return name;
        }

        string to_string() override{
            stringstream stream;
            
            stream << std::setprecision(2) << "Camion [" << std::to_string(Almacen<Carga>::capacidad()) << " m3]" << " [" << std::to_string(Almacen<Carga>::peso()) << " kg]" << "\n";
            for(auto& n : Almacen<Carga>::lista){
                stream << "  " << n->to_string() << "\n";
            }
            
            return stream.str();
            /* string info;
            info = std::setprecision(2) + "Camion [" + std::to_string(Almacen<Carga>::capacidad()) + " m3]" + " [" + std::to_string(Almacen<Carga>::peso()) + " kg]" + "\n";
            for(auto& n : Almacen<Carga>::lista){
                info += "  " + n->to_string() + "\n";
            }
            return info; */
        }

};

//----------------------------------------------------------------------------------------------------------------------

class SerVivo {

};

class Toxico {

};