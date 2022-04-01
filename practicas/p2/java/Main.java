public class Main
{
	public static void main(String[] args)
	{
		SymbolTab syms = new SymbolTab();
		// Define en la tabla los valores de
		// a = 7.0
		// b = 2.0
		// Consulta el tipo 'HashMap' de Java
		...

		// 3 + 2*5 = 13
		Expression e1 = new Expression("3 2 5 * +");
		System.out.println(e1+" = "+e1.eval(syms));
		System.out.println();

		// (3+2) * 5 = 25
		Expression e2 = new Expression("3 2 + 5 *");
		System.out.println(e2+" = "+e2.eval(syms));
		System.out.println();

		// 3 - 2*a = -11
		Expression e3 = new Expression("3 2 a * -");
		System.out.println(e3+" = "+e3.eval(syms));
		System.out.println();

		// (3+a) / 2 = 5
		Expression e4 = new Expression("3 a + 2 /");
		System.out.println(e4+" = "+e4.eval(syms));
		System.out.println();

		// (1+2) * a / (4.1 - b) = 10
		Expression e5 = new Expression("1 2.0 + a * 4.1 b - /");
		System.out.println(e5+" = "+e5.eval(syms));
		System.out.println();

		// (1+c) * 2 ERROR!!! 'c' no esta definida
		Expression e6 = new Expression("1 c + 2 *");
		System.out.println(e6+" = "+e6.eval(syms));
		System.out.println();
	}
}
