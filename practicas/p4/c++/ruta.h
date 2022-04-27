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
        virtual int tamanio(){
            return sizeInBytes;
        }

        virtual string pathFile(){
            return name;
        }
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

        int tamanio() override{
            int aux = 0;
            for (auto& a : contenidoDir){
                aux+= a->tamanio();
            }
            return aux;
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

};

class Fichero : public Elemento{
    protected:
        
    public:
        Fichero(const string& _name, int _size) : Elemento(_name, _size){
            /*nada*/
        }
        ~Fichero();

        void setSize(int newValue){
            sizeInBytes = newValue;
        }
        
};

class Enlace : public Elemento{
    protected:
        shared_ptr<Elemento> elementoOriginal;

    public:
        Enlace(const string& _name, shared_ptr<Elemento> _elemento) : Elemento(_name, _elemento->tamanio()){
            /*nada*/
            elementoOriginal = _elemento;
        }
        ~Enlace();
        
        int tamanio() override{
            return elementoOriginal->tamanio();
        }
        
        
};

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

class Ruta {

    protected:
        //string name;
        string path;
        Directorio* directorio;
        Directorio* raiz;
        
    public:
        Ruta(Directorio _elemento){
            path = "/" + _elemento.pathFile();
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
                aux <<std::to_string(a->tamanio()) << " " << a->nombre() << endl;
            }
            return aux.str();
        }

        void vi(string _name, int _size){
            bool encontrado = false;
            for(auto& a : directorio->contenido()){
                
                //TODO:gestionar con excepciones
                //Debe solo poder cambiarse el tamaño si es un fichero
                
                //TODO: obligar a que sea fichero para poder usar el setSize()
                    if(a->nombre() == _name){
                    a->setSize(_size);
                    encontrado = true;
                } 
            }

            //TODO: hacer excepcion
            if(!encontrado){
                //throw fichero_inexistente()
                shared_ptr<Fichero> aux = make_shared<Fichero>(_name, _size);
                directorio->guardar(aux);
            }
        }
        
        void mkdir(string _name){
            //TODO: gestionar si existe ya un directorio con el mismo nombre
            bool encontrado = false;
            for(auto& a : directorio->contenido()){
                
                //TODO:gestionar con excepciones
                //Debe solo poder cambiarse el tamaño si es un fichero
                
                //TODO: obligar a que sea fichero para poder usar el setSize()
                    if(a->nombre() == _name){
                    a->setSize(_size);
                    encontrado = true;
                } 
            }

            shared_ptr<Directorio> aux = make_shared<Directorio>(_name); 
            directorio->guardar(aux);
        }

        void cd(string _path){
            for(auto& a : directorio->contenido()){
                
                    string aux = path;
                    aux = aux + "/" + a->nombre;
                    if(aux == _path){
                    
                } 
            }
        }
        
        void ln(string _path, string _name){
            
            //TODO: que tamanio le damos al elemento para crearlo?
            shared_ptr<Elemento> elemento = make_shared<Elemento>(_name, _path, 0) 
            shared_ptr<Enlace> enlace = make_shared<Enlace>(elemento.name(), elemento);
            this->directorio.guardar(enlace);

        }

        int stat(string _path){
            Directorio* aux(_path);
            this->directorio = aux;
            return aux->tamanio();
        }
        
        void rm(string _path){
            //TODO: recorrer todo el vector de directorios para ver cuales coinciden con _path ???
            // _path = "/dir1/dir2/fichero1.txt"
            // / dir1 dir2 fichero.txt
            // Ruta("/")           
            Directorio* aux;
            aux = 
            delete(aux);
        }
        
*/
};