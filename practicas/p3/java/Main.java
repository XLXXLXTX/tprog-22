class Main
{
	public static void main(String[] args)
	{
		Contenedor<Carga>	contenedor_estandar = new Contenedor<>(4);
		Contenedor<Toxico>	contenedor_toxico   = new Contenedor<>(3);
		Contenedor<SerVivo>	contenedor_servivo  = new Contenedor<>(2);

		Producto longaniza_graus = new Producto("Longaniza de Graus",0.5,0.8);
		contenedor_estandar.guardar(longaniza_graus);
		Producto adoquines_zaragoza = new Producto("Adoquines de Zaragoza",0.1,5.0);
		contenedor_estandar.guardar(adoquines_zaragoza);

		Toxico discos_melendi = new Toxico("Discos de Melendi",1,10);
		// Esto no deberia compilar
		// contenedor_estandar.guardar(discos_melendi);
		contenedor_toxico.guardar(discos_melendi);

		Camion camion = new Camion(10);

		SerVivo elvis_presley = new SerVivo("Elvis Presley",0.1,100);
		// Esto no deberia compilar
		// camion.guardar(elvis_presley);
		contenedor_servivo.guardar(elvis_presley);

		if (!camion.guardar(contenedor_estandar))
			System.out.println("Camion lleno con contenedor estandar");
		if (!camion.guardar(contenedor_toxico))
			System.out.println("Camion lleno con contenedor toxico");
		if (!camion.guardar(contenedor_servivo))
			System.out.println("Camion lleno con contenedor de seres vivos");

		Producto apuntes_tepro = new Producto("Apuntes de Tecnologia de Programacion",1,0.1);
		if (!camion.guardar(apuntes_tepro))
			System.out.println("Camion lleno con apuntes de tepro");

		Producto trenzas_almudevar = new Producto("Trenzas de Almudevar",0.5,0.8);
		if (!camion.guardar(trenzas_almudevar))
			System.out.println("Camion lleno con Trenzas de Almudevar");

		System.out.println();
		System.out.println(camion);

/*
La salida del programa hasta aquí deberia ser parecida a lo siguiente:

> java Main
Camion lleno con Trenzas de Almudevar

Camion [10.0 m3] [115.9 kg]
  Contenedor [4.0 m3] [5.8 kg] de Producto
    Longaniza de Graus [0.5 m3] [0.8 kg]
    Adoquines de Zaragoza [0.1 m3] [5.0 kg]
  Contenedor [3.0 m3] [10.0 kg] de Toxico
    Discos de Melendi [1.0 m3] [10.0 kg]
  Contenedor [2.0 m3] [100.0 kg] de SerVivo
    Elvis Presley [0.1 m3] [100.0 kg]
  Apuntes de Tecnologia de Programacion [1.0 m3] [0.1 kg]

*/

		Contenedor<Carga>	otro_contenedor_estandar = new Contenedor<>(1);
		Contenedor<Toxico>	otro_contenedor_toxico   = new Contenedor<>(1);
		Contenedor<SerVivo>	otro_contenedor_servivo  = new Contenedor<>(1);
		contenedor_estandar.guardar(otro_contenedor_estandar);
		contenedor_estandar.guardar(otro_contenedor_toxico);
		contenedor_estandar.guardar(otro_contenedor_servivo);
		// Estas lineas no deberian compilar
		//contenedor_estandar.guardar(camion);
		//contenedor_toxico.guardar(otro_contenedor_toxico);
		//contenedor_servivo.guardar(otro_contenedor_servivo);
	}
}

