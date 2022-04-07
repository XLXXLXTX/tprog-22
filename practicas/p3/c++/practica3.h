#pragma once
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

/**
 * @brief Clase que representa el poder darle un nombre a una clase que no proviene de "Carga" y pueda tener un metodo to_string (camión).
 * 
 */
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

//----------------------------------------------------------------------------------------------------------------------

/**
 * @brief representará cualquier carga (producto o contenedores) que se pueden transportar dentro de un "Almacen" (contenedor o camión).
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

        virtual double peso(){
            return weight;
        }

        virtual double volumen(){
            return volume;
        }

        virtual string nombre(){
            return name;
        }

        virtual string to_string(const string ident = "  " ){
            stringstream stream;
            stream << ident << Carga::name << " [" << std::fixed << std::setprecision(1) << Carga::volume << " m3]" << " [" << std::fixed << std::setprecision(1) << Carga::weight << " kg]";
            return stream.str();
        }
};

//----------------------------------------------------------------------------------------------------------------------

/**
 * @brief representará un productomediante un nombre identificativo (una cadena de texto), su volumen, y su peso.
 * 
 */
class Producto : public Carga{
    private:
    /*nada*/

    public:
        Producto(const string& _name, double _volume, double _weight);
        ~Producto();
};

//----------------------------------------------------------------------------------------------------------------------

/**
 * @brief Interfaza Almacen para heredar el poder guardar elementos
 * 
 */
template <typename T>
class Almacen{ 
    protected:
        //Campos utiles para el tratamiento de objetos que heredan el poder almacenar objetos.
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

//----------------------------------------------------------------------------------------------------------------------

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

        string to_string(const string ident = "") override{
            stringstream stream;

            stream << ident << "Contenedor [" << std::fixed << std::setprecision(1) << Almacen<Carga>::capacidad() << " m3]" << " [" << std::fixed << std::setprecision(1) << Almacen<Carga>::peso() << " kg]" << " de " <<  Carga::name << "\n";
            for(auto& n : Almacen<Carga>::lista){
                stream << n->to_string("  " + ident) << "\n";
            }
            
            return stream.str();
        }
};

//----------------------------------------------------------------------------------------------------------------------

/**
 * @brief Clase Camion para poder guardar objetos (hereda de Almacen) y que tenga la etiqueta de que es un camion (hereda de Nameable)
 * 
 */
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

        /**
         * @brief Redefinicion del operador << para poder escribir el obj sin llamar a la funcion to_string()
         * 
         * @param f ostream
         * @param c camion
         * @return ostream& 
         */
        friend ostream& operator<<(ostream& f, Camion& c){
            f << c.to_string();
            return f;
        }
};

//----------------------------------------------------------------------------------------------------------------------

/**
 * @brief Clase CargaEspecial, hereda de Carga (la clase padre de todas las cargas)
 * 
 */
class CargaEspecial : public Carga{
    private:
    /*nada*/

    public:
        CargaEspecial(const string& _name, double _volume, double _weight) : Carga(_name, _volume, _weight){
            /*nada*/
        }

        ~CargaEspecial(){ /*nada*/ }

};

//----------------------------------------------------------------------------------------------------------------------

/**
 * @brief clase SerVivo que viene de una clase intermedia CargaEspecial para diferenciarla de la clase Producto (Carga estandar)
 * 
 */
class SerVivo : public CargaEspecial {
    private:
    /*nada*/

    public:
        SerVivo(const string& _name, double _volume, double _weight);
        ~SerVivo();
};

//----------------------------------------------------------------------------------------------------------------------

class Toxico : public CargaEspecial {
    private:
    /*nada*/

    public:
        Toxico(const string& _name, double _volume, double _weight);
        ~Toxico();
};

//----------------------------------------------------------------------------------------------------------------------

/**
 * @brief Clase Contenedor<SerVivo> para poder darle la etiqueta de que es un "Contenedor de Seres Vivos" al ser creado un obj
 *(Tiene las mismas caracteristicas que un contenedor pero solo puede contener obj de la clase SerVivo)
 * @tparam  
 */
template <> 
class Contenedor<SerVivo> : public CargaEspecial, public Almacen<SerVivo> {

    private:
    /*nada*/

    public:
        Contenedor(double _capacidad) : CargaEspecial("Seres Vivos", 0, 0 ), Almacen<SerVivo>(_capacidad){
            /*nada*/
        }

        double peso() override {
            return Almacen<SerVivo>::peso();
        }

        double volumen() override {
            return Almacen<SerVivo>::capacidad();
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

//----------------------------------------------------------------------------------------------------------------------

/**
 * @brief Clase Contenedor<Toxico> para poder darle la etiqueta de que es un "Contenedor de Productos Toxicos" al ser creado un obj
 *(Tiene las mismas caracteristicas que un contenedor pero solo puede contener obj de la clase Toxico)
 * @tparam  
 */
template <> 
class Contenedor<Toxico> : public CargaEspecial, public Almacen<Toxico> {

    private:
    /*nada*/

    public:
        Contenedor(double _capacidad) : CargaEspecial("Productos Toxicos", 0, 0 ), Almacen<Toxico>(_capacidad){
            /*nada*/
        }
        
        double peso() override {
            return Almacen<Toxico>::peso();
        }

        double volumen() override {
            return Almacen<Toxico>::capacidad();
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