
public class Main
{
	// TODO: Define la cabecera de este metodo aprovechando la herencia
	// para que sea equivalente a declarar los dos metodos siguientes:
	//
	// public static void anyadir_elementos(StaticStack<Integer> stk)
	// public static void anyadir_elementos(DynamicStack<Integer> stk)
	// ... anyadir_elementos ...
	public static void anyadir_elementos(PilaGenerica<Integer> stk)
	{
		stk.push(42);
		stk.push(15);

		stk.pop();
		
		for (int i=0; i<100; i+=5)
			stk.push(i);
		
	}

	// TODO: Define la cabecera de este metodo aprovechando la herencia
	// para que sea equivalente a declarar los dos metodos siguientes:
	//
	// public static void mostrar_elementos(StaticStack<Integer> stk)
	// public static void mostrar_elementos(DynamicStack<Integer> stk)
	// ... mostrar_elementos ...
	public static void mostrar_elementos(PilaGenerica<Integer> stk)
	{
 		for (Integer i : stk)
			System.out.print(i+" ");
		System.out.println();

	}

	public static void main(String[] args)
	{
		StaticStack<Integer>  s_stk = new StaticStack<Integer>();
		DynamicStack<Integer> d_stk = new DynamicStack<Integer>();

		anyadir_elementos(s_stk);
		anyadir_elementos(d_stk);

		mostrar_elementos(s_stk);
		mostrar_elementos(d_stk);
	}
	
}
