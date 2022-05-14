#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include "excepciones.h"
#include <memory>
#include <stdio.h>
#include <string.h>


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
        virtual int getTamanio(){
            return sizeInBytes;
        }

        virtual void setTamanio(int newValue){
            sizeInBytes = newValue;
        }
/*         virtual string pathFile(){
            return name;
        } */
};

/**
 * @brief Representa un directorio (incluyendo el raiz)
 * 
 */

class Directorio : public Elemento {
    protected:
        //un directorio puede contenener: otros directorios, ficheros y enlaces
        vector<shared_ptr<Elemento>> contenidoDir;
    public:
        Directorio(const string& _name) : Elemento(_name, 0){
        }

        ~Directorio(){
        }

        int getTamanio() override{
            int aux = 0;
            for (auto& a : contenidoDir){
                aux+= a->getTamanio();
            }
            return aux;
        }

        void setTamanio(int newValue) override {
            throw fichero_no_editable();
        }

        bool guardar(shared_ptr<Elemento> elemento){
            for(auto& a : contenidoDir){
                if(elemento->nombre() == a->nombre()){
                    throw fichero_ya_existente();
                    return false;
                }
            }
            contenidoDir.push_back(elemento);
            return true;

        }
        
        
        vector<shared_ptr<Elemento>> contenido(){
            return contenidoDir;
        }

        //Devolver solo directorios
        vector<shared_ptr<Directorio>> getSubDirs(){
            
            vector<shared_ptr<Directorio>> subdirectorios;
            
            shared_ptr<Directorio> sub;

            for(auto& a : contenidoDir){
                sub = dynamic_pointer_cast<Directorio>(a);   //Forzar casteo de Elemento a Directorio
                if(sub != nullptr){
                    subdirectorios.push_back(sub);
                    sub = nullptr;
                }
            }

            return subdirectorios;
        }

};

class Fichero : public Elemento{
    protected:
        
    public:
        Fichero(const string& _name, int _size) : Elemento(_name, _size){
            /*nada*/
        }
        ~Fichero();
        
};

class Enlace : public Elemento{
    protected:
        shared_ptr<Elemento> elementoOriginal;

    public:
        Enlace(const string& _name, shared_ptr<Elemento> _elemento) : Elemento(_name, _elemento->getTamanio()){
            /*nada*/
            elementoOriginal = _elemento;
        }
        ~Enlace();
        
        int getTamanio() override{
            return elementoOriginal->getTamanio();
        }
        
        
};

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

class Ruta {

    protected:
        //string name;
        string path;
/*         Directorio* raiz;
        Directorio* directorio; */

        Directorio* directorio;
        Directorio* raiz;

        
    public:
        Ruta(Directorio _elemento){
            path = "/" + _elemento.nombre();
            directorio = &_elemento;
            raiz = &_elemento;
        }

        ~Ruta(){
        }
        
        string pwd(){
            return path;
        }
   
        string ls(){
            stringstream aux;
            for(auto& a : directorio->contenido()){
                aux << a->nombre() << endl;
            }
            return aux.str();
        }
    
        string du(){
            stringstream aux;
            
            for(auto& a : directorio->contenido()){
                aux <<std::to_string(a->getTamanio()) << " " << a->nombre() << endl;
            }
            return aux.str();
        }

        void vi(string _name, int _size){
            bool encontrado = false;
            shared_ptr<Elemento> fich;
            for(auto& a : directorio->contenido()){
                
                if(a->nombre() == _name){
                    fich = dynamic_pointer_cast<Fichero>(a);   //Forzar casteo de Elemento a Directorio
                    if(fich != NULL){
                        fich->setTamanio(_size);         //Si se ha podido forzar a Directorio, usamos setSize()
                        encontrado = true;            //solo esta definida en clase Fichero
                    }else{
                        throw fichero_no_editable();
                    }
                } 
                
            }

            //Si el fichero no existe, se crea uno con el nombre y tamaño que recibe la func
            if(!encontrado){
                shared_ptr<Fichero> aux = make_shared<Fichero>(_name, _size);
                directorio->guardar(aux);
            }
        }
        
        void mkdir(string _name){
            //TODO: gestionar si existe ya un directorio con el mismo nombre
            bool encontrado = false;
            for(auto& a : directorio->getSubDirs()){
                
                if(a->nombre() == _name){
                    throw directorio_ya_existente();
                }
            }

            //Si no existe se crea.
            shared_ptr<Directorio> aux = make_shared<Directorio>(_name); 
            directorio->guardar(aux);
        }

        void cd(string _path){
            
             if(_path == ".."){
                if(path == "/"){
                    cerr << "no se puede ir mas atras";
                }else{
                    char* aux;
                    string pathAux;
                    directorio = raiz;
                    //La primera iteracion para quitar / de la raiz
                    char* dup = strdup(path.c_str());
                    aux = strtok(dup, "/");
                    while(aux){
                        aux = strtok(NULL, "/");
                        for (auto& a : directorio->getSubDirs()){
                            if(a->nombre() == aux){
                                //directorio = a;
                                pathAux = "/" + a->nombre();
                            }
                        }
                    }
                    path = pathAux;
                }

            }else if(_path == "."){

            }else{
                path = _path;
                char* aux;
                directorio = raiz;
                //La primera iteracion para quitar / de la raiz
                
                char* dup = strdup(path.c_str());
                aux = strtok(dup, "/");
                //aux = strtok(path, "/");
                while(aux){
                    aux = strtok(NULL, "/");
                    for (auto& a : directorio->contenido()){
                        if(a->nombre() == aux){
                            //directorio = a;
                        }
                    }
                }
            
            } 
            
        }
        /*
        void ln(string _path, string _name){
            
/*             //TODO: que tamanio le damos al elemento para crearlo?
            shared_ptr<Elemento> elemento = make_shared<Elemento>(_name, _path, 0) 
            shared_ptr<Enlace> enlace = make_shared<Enlace>(elemento.name(), elemento);
            this->directorio.guardar(enlace); 
        }
    /*
        int stat(string _path){
            
            // llamar a funcion cd de path - ultima parte del separador

/*             Directorio* aux(_path);
            this->directorio = aux;
            return aux->tamanio(); 
            return 0;
        }
        
        void rm(string _path){
            //TODO: recorrer todo el vector de directorios para ver cuales coinciden con _path ???
            // _path = "/dir1/dir2/fichero1.txt"
            // / dir1 dir2 fichero.txt
            // Ruta("/")           
/*             Directorio* aux;
            aux = 
            delete(aux); 
        }
        
*/
};
