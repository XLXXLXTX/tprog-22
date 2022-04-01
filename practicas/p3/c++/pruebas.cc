#include "practica3.h"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]){

    /**
     * Compilar usando: 
     * g++ pruebas.cc practica3.cc -o pruebas  
     */
    
    //Pruebas sobre obj de la clase Productos
    Producto longaniza_graus("Longaniza de Graus",0.5,0.8);
    Producto adoquines_zaragoza("Adoquines de Zaragoza",0.1,5.0);
    Producto apuntes_tepro("Apuntes de Tecnologia de Programacion",1,0.1);
    Producto trenzas_almudevar("Trenzas de Almudevar",0.5,0.8);

    vector<Producto> productos;
    productos.push_back(longaniza_graus);
    productos.push_back(adoquines_zaragoza);
    productos.push_back(apuntes_tepro);
    productos.push_back(trenzas_almudevar);

    for(Producto p : productos){
        cout << p.to_string() << endl;
    }
    
    //-------
    Contenedor<Carga>	contenedor_estandar(4);
    contenedor_estandar.guardar(longaniza_graus);
	contenedor_estandar.guardar(adoquines_zaragoza); 

    cout << contenedor_estandar.to_string() << endl;

    return 0;
}
