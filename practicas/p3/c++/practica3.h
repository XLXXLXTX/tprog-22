#pragma once
#include <iostream>
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
        double size;
        double remainingSpace;
        vector<T*> lista;    //lista para almacenar cualquier cosa (T generico)


    public:
        Almacen(double _capacidad){
            size=_capacidad;
            remainingSpace=_capacidad;
        }

        ~Almacen(){/*nada*/}
        
        //almacena cualquier generico
        bool guardar(T& elemento){
            if(espacioDisponible() >= elemento.volumen()){
                remainingSpace = espacioDisponible() - elemento.volumen();
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
class Contenedor : public Nameable, public Almacen<T>{
    //Como hereda de Almacen<T>, le decimos que solo va a guardar elementos de tipo Carga
    protected:
    /**/

    public:
        Contenedor(double _capacidad): Nameable("Contenedor"), Almacen<T>(_capacidad){

        }

        ~Contenedor(){ }

        string nombre() override {
            return name;
        }

        string to_string() override{
            string info;
            info = "Contenedor{nombre=" + Nameable::name + ", capacidad=" + std::to_string(Almacen<T>::size)+"}" + "\n";
            for(auto& n : Almacen<T>::lista){
                info += "\t\t" + n->to_string() + "\n";
            }
            return info;
        }
};



class Camion {

};

//----------------------------------------------------------------------------------------------------------------------

