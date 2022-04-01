import java.lang.Iterable;
import java.util.Iterator;


/**
 *Definimos la interfaz como si de una clase se tratase pero usamos en vez de class el modificador interface 
 *(para decir que es una clase abstracta, osea que no implementa el interior de sus metodos)
 *Dentro definimos los metodos mas basicos de una pila (apilar, desapilar y el iterador).
 *Tambien hemos hecho un extends Iterable<T> como se hacia inicialmente en las clases de la pila dinamica y estatica
 *public class DynamicStack<T> extends Iterable<T>
 *public class StaticStack<T> extends Iterable<T>
 *Asi hemos obtenido una "clase" intermedia para el polimorfismo en la clase Main.java
 */
interface PilaGenerica<T> extends Iterable<T>{
    public boolean push(T dato);
    public boolean pop();
    public Iterator<T> iterator();
};