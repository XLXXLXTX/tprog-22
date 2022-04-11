import java.util.Scanner;

class Main
{
	public static void main(String[] args)
	{
		Directorio raiz;
		Ruta ruta;
		try
		{
			raiz = new Directorio("");
			ruta = new Ruta(raiz);
		}
		catch (ExcepcionArbolFicheros e)
		{
			System.out.println(e);
			return;
		}

		Scanner scn = new Scanner(System.in);
		for (boolean done=false; !done;)
		{
			System.out.print(ruta.pwd()+"> ");

			// Leer linea de entrada
			String line;
			try {
				line = scn.nextLine();
			} catch (Exception e) {
				done = true;
				continue;
			}
			if (line.isEmpty())
				continue;

			// Separar tokens
			String[] cmd = line.split(" ");

			if ((cmd.length==0) || cmd[0].isEmpty())
				continue;

			try
			{
				if (cmd[0].equals("exit") || cmd[0].equals("by"))
				{
					done = true;
				}
				else if (cmd[0].equals("pwd"))
				{
					System.out.println(ruta.pwd());
				}
				else if (cmd[0].equals("ls"))
				{
					System.out.println(ruta.ls());
				}
				else if (cmd[0].equals("du"))
				{
					System.out.println(ruta.du());
				}
				else if (cmd[0].equals("vi"))
				{
					ruta.vi(cmd[1], Integer.parseInt(cmd[2]));
				}
				else if (cmd[0].equals("mkdir"))
				{
					ruta.mkdir(cmd[1]);
				}
				else if (cmd[0].equals("cd"))
				{
					ruta.cd(cmd[1]);
				}
				else if (cmd[0].equals("stat"))
				{
					System.out.println(ruta.stat(cmd[1]));
				}
				else if (cmd[0].equals("ln"))
				{
					ruta.ln(cmd[1],cmd[2]);
				}
				else if (cmd[0].equals("rm"))
				{
					ruta.rm(cmd[1]);
				}
				else
				{
					System.out.println("Error sintactico: comando desconocido");
				}
			}
			catch(ExcepcionArbolFicheros e)
			{
				System.out.println(e);
			}
			catch (ArrayIndexOutOfBoundsException e)
			{
				System.out.println("Error sintactico: parametros insuficientes");
				System.out.println(e);
			}
		}

		System.out.println("\nBy!!");
	}
};
