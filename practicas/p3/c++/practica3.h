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
        virtual string nombre(){
            return name;
        }
        virtual string to_string() = 0;
};


/**
 * @brief representará cualquier carga (producto o contenedores) que se pueden transportar dentro de un "Almacen" (contenedor o camión)
 * 
 */
class Carga {
    protected:
        string name;
        double volume;
        double weight;

    public:
        Carga(const string& _name, double _volume, double _weight);
        ~Carga();
        virtual double peso() = 0;
        virtual double volumen(){
            return volume;
        }
        virtual string nombre() = 0;
        virtual string to_string(const string ident = "  " ){
            stringstream stream;
            stream << ident << Carga::name << " [" << std::fixed << std::setprecision(1) << Carga::volume << " m3]" << " [" << std::fixed << std::setprecision(1) << Carga::weight << " kg]";
            return stream.str();
        }
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
        //string to_string(const string ident="") override;

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
        
};

/**
 * @brief representará un contenedor con su correspondiente capacidad (que equivale a su volumen). 
 * Dicho valor se le pasará en su constructor.
 * 
 */
template <typename T>
class Contenedor : public Carga, public Almacen<T>{
    protected:
        /*nada*/

    public:
        Contenedor(double _capacidad) : Carga("Carga Estandar", 0 , 0), Almacen<T>(_capacidad){
            /*nada*/
        }

        ~Contenedor(){ }


        double peso() override {
            return Almacen<Carga>::peso();
        }

        double volumen() override {
            return Almacen<Carga>::capacidad();
        }

        string nombre() override {
            return Carga::name;
        }

        string to_string(const string ident = "") override{
            stringstream stream;

            stream << ident << "Contenedor [" << std::fixed << std::setprecision(1) << Almacen<Carga>::capacidad() << " m3]" << " [" << std::fixed << std::setprecision(1) << Almacen<Carga>::peso() << " kg]" << " de " <<  Carga::name << "\n";
            for(auto& n : Almacen<Carga>::lista){
                stream << n->to_string("  " + ident) << "\n";
            }
            
            return stream.str();
        }
};



class Camion : public Nameable, public Almacen<Carga>{
    protected:
        /*nada*/
    public:
        Camion(double _capacidad) : Nameable("Camión"), Almacen<Carga>(_capacidad){
            /*nada*/
        }

        ~Camion(){ /*nada*/ }

        string to_string() override{
            stringstream stream;
            
            stream << "Camion [" <<  std::fixed << std::setprecision(1) << Almacen<Carga>::capacidad() << " m3]" << " [" << std::setprecision(1) << Almacen<Carga>::peso() << " kg]" << "\n";
            for(auto& n : Almacen<Carga>::lista){
                stream << n->to_string("  ") << "\n";
            }
            
            return stream.str();
        }

        friend ostream& operator<<(ostream& f, Camion& c){
            f << c.to_string();
            return f;
        }
};

//----------------------------------------------------------------------------------------------------------------------

class CargaEspecial : public Carga{
    private:
    /*nada*/

    public:
        CargaEspecial(const string& _name, double _volume, double _weight) : Carga(_name, _volume, _weight){
            /*nada*/
        }

        ~CargaEspecial(){ /*nada*/ }
        
        //Heredadas de la clase Carga
        double peso(){
            return Carga::weight;
        }

        string nombre(){
            return Carga::name;
        }
/*         string to_string(const string ident = "  " ){
            stringstream stream;
            stream << ident << Carga::name << " [" << std::fixed << std::setprecision(1) << Carga::volume << " m3]" << " [" << std::fixed << std::setprecision(1) << Carga::weight << " kg]";
            return stream.str();
        } */

};


class SerVivo : public CargaEspecial {
    /*Constructor*/
    private:
    /*nada*/

    public:
        SerVivo(const string& _name, double _volume, double _weight);
        ~SerVivo();
};

class Toxico : public CargaEspecial {
    /*Constructor*/
    private:
    /*nada*/

    public:
        Toxico(const string& _name, double _volume, double _weight);
        ~Toxico();
};

template <> 
class Contenedor<SerVivo> : public CargaEspecial, public Almacen<SerVivo> {

    private:
    /**/
    public:
        Contenedor(double _capacidad) : CargaEspecial("Seres Vivos", 0, 0 ), Almacen<SerVivo>(_capacidad){

        }

        double peso() override {
            return Almacen<SerVivo>::peso();
        }

        double volumen() override {
            return Almacen<SerVivo>::capacidad();
        }

        string nombre() override {
            return CargaEspecial::name;
        }


        string to_string(const string ident = "") override{
            stringstream stream;

            stream << ident << "Contenedor [" << std::fixed << std::setprecision(1) <<  Almacen<SerVivo>::capacidad() << " m3]" << " [" << std::fixed << std::setprecision(1) << Almacen<SerVivo>::peso() << " kg]" << " de " <<  Carga::name << "\n";
            for(auto& n : Almacen<SerVivo>::lista){
                stream << n->to_string("  " + ident) << "\n";
            }
            
            return stream.str();
        }

};

template <> 
class Contenedor<Toxico> : public CargaEspecial, public Almacen<Toxico> {

    private:
    /**/
    public:
        Contenedor(double _capacidad) : CargaEspecial("Productos Toxicos", 0, 0 ), Almacen<Toxico>(_capacidad){

        }
        
        double peso() override {
            return Almacen<Toxico>::peso();
        }

        double volumen() override {
            return Almacen<Toxico>::capacidad();
        }

        string nombre() override {
            return Carga::name;
        }

        string to_string(const string ident = "") override{
            stringstream stream;

            stream << ident << "Contenedor [" << std::fixed << std::setprecision(1) << Almacen<Toxico>::capacidad() << " m3]" << " [" << std::fixed << std::setprecision(1) << Almacen<Toxico>::peso() << " kg]" << " de " <<  Carga::name << "\n";
            for(auto& n : Almacen<Toxico>::lista){
                stream << n->to_string("  " + ident) << "\n";
            }
            
            return stream.str();
        }
};