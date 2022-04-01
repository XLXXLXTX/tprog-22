// Similar a los includes de C++, importamos aquellas clases que nos sean utiles
import java.lang.Iterable;
import java.util.Iterator;
import java.util.NoSuchElementException;
import java.lang.UnsupportedOperationException;

// En Java, no existe el concepto de pre-declaracion ni de funcion. Java es un
// lenguaje puramente orientado a objetos, por lo que todo son clases.
//
// El uso de programación paramétrica no requiere ninguna palabra clave.
// Directamente ponemos el tipo parámetro entre <>.
// Para hacer uso de iteradores, implementamos el interfaz Iterable<T>.
// Esto es un mecanismo básico de la herencia en Java que es inevitable en
// este caso y sobre el que hablaremos más adelante en clase de teoría.

/**
 *Nuestra clase pila estatica va a heredar las funciones de la interfaz pila generica (push, pop y el iterator) 
 *y dentro de esta clase vamos a poder redefinirlas
 *Como cuando en C++ ponemos el modificador virtual para poder redefinir el interior de una funcion, en la clase
 *que hereda de la clase padre, pero en este caso en vez de poner virtual se ha creado una interfaz (PilaGenerica)
 */
public class StaticStack<T> implements PilaGenerica<T>
{
	// Esta es la única forma que tiene Java de declarar valores inmutables.
	private static final int MAX = 40;

	// Habrás notado que en Java no hay bloques "private" y "public", sino que
	// es una palabra clave que se pone en cada elemento (atributo o método).
	private T[] datos;
	private int total;

	// El constructor de Java llama a los constructores de los parámetros dentro
	// del bloque de código.
	@SuppressWarnings("unchecked")
	public StaticStack()
	{
		datos = (T[])(new Object[MAX]);
		total = 0;
	}

	// TODO: Rellena el código de este método para que añada un elemento a
	// la pila y devuelva si ha sido posible (o no) meterlo.
	public boolean push(T t)
	{
		if(total < MAX){
			datos[total] = t;
			total = total + 1;
			return true;
		}else{
			return false;
		}
	}

	// TODO: Rellena el código de este método para que borre el último
	// elemento de la pila y devuelva si ha sido posible (o no) borrarlo.
	public boolean pop()
	{
		if(total>0){
			total = total - 1;
			return true;
		}else{
			return false;
		}
	}

	// Esta clase representa a un iterador sobre la pila.
	// De nuevo, por el comportamiento estándar de los
	// iteradores en Java, deberemos utilizar la herencia.
	private class StackIterator implements Iterator<T>
	{
		// Aquí declaramos los atributos
		StaticStack<T>	stk;
		int				i;

		// Este es el constructor del iterador.
		private StackIterator(StaticStack<T> stk)
		{
			this.stk = stk;
			i        = stk.total - 1;
		}

		// Todos los iteradores deben de implementar un método que devuelva
		// si hay siguiente elemento (o no).
		//TODO: Devuelve si hay siguiente elemento o no.
		public boolean hasNext()
		{
			if(i>=0){
				return true;
			}else{
				return false;
			}
		}

		// Todos los iteradores deben de implementar un método que devuelva el
		// elemento en la posción actual y avance el iterador.
		// Por construcción, este método debe lanzar una excepción si no existe
		// el siguiente elemento.
		// Recuerda que se recorren desde el último al primero.
		public T next() throws NoSuchElementException
		{
			if (!hasNext())
			{
				// Aquí lanzamos la excepción
				throw new NoSuchElementException();
			}
			else
			{
				// TODO: Devuelve el elemento apuntado por el iterador,
				// y avanza el iterador.
				int aux = i;
				i = i - 1;
				return datos[aux];

			}
		}

		// Los iteradores en Java deben tener también este método.
		// Para no implementarlo (no lo vamos a usar y nuestra definición de
		// pila no lo incluye) simplemente lanzamos una excepción.
		public void remove() throws UnsupportedOperationException
		{
			throw new UnsupportedOperationException();
		}
	}

	// Este método de la estructura de datos simplemente devuelve un nuevo
	// iterador con el que recorrer la estructura de datos.
	public Iterator<T> iterator()
	{
		return new StackIterator(this);
	}
}
