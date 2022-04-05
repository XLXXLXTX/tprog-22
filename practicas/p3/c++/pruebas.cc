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

    /*
    
    for(Producto p : productos){
        cout << p.to_string() << endl;
    }
    
    */
   
    //-------

    Camion camion(3);

    //Producto apuntes_tepro("Apuntes de Tecnologia de Programacion",1,0.1);
    if (!camion.guardar(apuntes_tepro)){
      cout << "Camion lleno con apuntes de tepro" << endl;
    }
    //Producto trenzas_almudevar("Trenzas de Almudevar",0.5,0.8);
    if (!camion.guardar(trenzas_almudevar)){
      cout << "Camion lleno con Trenzas de Almudevar" << endl;
    }
    
    cout << "***Camion normal:***" << endl;
    cout << camion.to_string() << endl;

    
    //------------------------------
    Camion camion_de_contenedores(10);

    Contenedor<Carga>	contenedor_estandar(4);
    contenedor_estandar.guardar(longaniza_graus);
	  contenedor_estandar.guardar(adoquines_zaragoza); 
    Producto pablol("Fregona de pablol",0.9,3.0);

    cout << contenedor_estandar.to_string() << endl;
    
    camion_de_contenedores.guardar(pablol);

    if(!camion_de_contenedores.guardar(contenedor_estandar)){
		cout << "Camion lleno NO CABE EL CONTENEDOR" << endl;
    }

    cout << "***Camion de contenedores:***" << endl;
    cout << camion_de_contenedores.to_string() << endl;

    //------------------------------
    

}


/*La salida del programa hasta aquí deberia ser parecida a lo siguiente:

> ./main
Camion lleno con Trenzas de Almudevar

Camion [10 m3] [115.9 kg]
  Contenedor [4 m3] [5.8 kg] de Carga Estandar
    Longaniza de Graus [0.5 m3] [0.8 kg]
    Adoquines de Zaragoza [0.1 m3] [5 kg]
  Contenedor [3 m3] [10 kg] de Productos Toxicos
    Discos de Melendi [1 m3] [10 kg]
  Contenedor [2 m3] [100 kg] de Seres Vivos
    Elvis Presley [0.1 m3] [100 kg]
  Apuntes de Tecnologia de Programacion [1 m3] [0.1 kg]

*/