/*
 ============================================================================
 Name        : PARCIAL.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "utn.h"
#include "cliente.h"
#include "aviso.h"
#include "clienteAviso.h"
#include "informes.h"

#define QTY_CLIENTES 100
#define QTY_AVISOS 1000

int main(void) {

	setbuf(stdout,NULL);

	Cliente arrayCliente[QTY_CLIENTES];
	Aviso arrayAviso[QTY_AVISOS];

	int opcion;
	int opcionSubMenu;
	int contadorClientes = 4;
	int indiceAvisos = 6;

	cliente_init(arrayCliente, QTY_CLIENTES); // Inicializo el array de clientes con todos los valores de isEmpty en TRUE, es decir, todo el array est� vac�o.
	aviso_init(arrayAviso, QTY_AVISOS); // Inicializo el array de avisos con todos los valores de isEmpty en TRUE, es decir, todo el array est� vac�o.

	cliente_altaForzada(arrayCliente, QTY_CLIENTES, "Lio", "Messi", "20-38428752-9");
	cliente_altaForzada(arrayCliente, QTY_CLIENTES, "Gabriel", "Villaverde", "20-39493486-9");
	cliente_altaForzada(arrayCliente, QTY_CLIENTES, "Jorge", "Mendez", "20-38542751-9");
	cliente_altaForzada(arrayCliente, QTY_CLIENTES, "Facundo", "Gonzalez", "20-37472450-9");

	aviso_altaForzada(arrayAviso, QTY_AVISOS, 50, "Busco empleados para mi negocio.", 1, AVISO_ACTIVO);
	aviso_altaForzada(arrayAviso, QTY_AVISOS, 900, "Doy clases de f�tbol.", 1, AVISO_PAUSADO);
	aviso_altaForzada(arrayAviso, QTY_AVISOS, 60, "Compro casa.", 2, AVISO_ACTIVO);
	aviso_altaForzada(arrayAviso, QTY_AVISOS, 70, "Compro muebles.", 3, AVISO_ACTIVO);
	aviso_altaForzada(arrayAviso, QTY_AVISOS, 80, "Urgente: Se solicita personal m�dico.", 4, AVISO_PAUSADO);
	aviso_altaForzada(arrayAviso, QTY_AVISOS, 80, "Urgente: Se buscan jugadores de f�tbol.", 4, AVISO_PAUSADO);

	do
	{
		if(utn_getNumberInt("Bienvenido al sistema, seleccione una opci�n: \n\n1 - Alta de cliente\n2 - Modificar datos de cliente\n3 - Baja de cliente\n"
		"4 - Publicar un nuevo aviso\n5 - Pausar publicaci�n\n6 - Reanudar publicaci�n\n7 - Imprimir clientes\n8 - Informar\n"
		"8 - Salir del sistema","\nError. Seleccione una opci�n v�lida (1-8)\n", &opcion, 2, 1, 8) == 0)
		{
			switch(opcion)
			{
			case 1:
				printf("\nUsted quiere dar de alta un cliente.\n");
				cliente_alta(arrayCliente, QTY_CLIENTES);
				contadorClientes++;
				break;
			case 2:
				printf("\nUsted quiere modificar datos de un cliente.\n");
				if(contadorClientes > 0 )
				{
					cliente_modificar(arrayCliente, QTY_CLIENTES);
				}
				else
				{
					printf("\nDebe cargar al menos un cliente para poder hacer modificaciones.\n");
				}
				break;
			case 3:
				printf("\nUsted quiere dar de baja un cliente, por favor elija cu�l desea eliminar:.\n");
				if(contadorClientes > 0 )
				{
					cliente_imprimir(arrayCliente, QTY_CLIENTES);
					clienteAviso_baja(arrayAviso, QTY_AVISOS, arrayCliente, QTY_CLIENTES);
					contadorClientes--;
				}
				else
				{
					printf("\nDebe cargar al menos un cliente para poder hacer eliminaciones.\n");
				}

				break;
			case 4:
				if(contadorClientes > 0)
				{
					printf("\nUsted quiere publicar un nuevo aviso.\n");
					aviso_alta(arrayAviso, QTY_AVISOS, arrayCliente, QTY_CLIENTES, &indiceAvisos);
				}
				else
				{
					printf("\nA�n no hay ning�n cliente cargado. Primero reg�stre sus datos como cliente, luego vuelva a la opci�n 4 e ingrese el ID que se le asign� para publicar un aviso.\n");
				}
				break;
			case 5:
					printf("\nUsted quiere pausar una publicaci�n.\n");
					aviso_pausar(arrayAviso, QTY_AVISOS, arrayCliente, QTY_CLIENTES);
				break;
			case 6:
				printf("\nUsted quiere reanudar una publicaci�n.\n");
				aviso_activar(arrayAviso, QTY_AVISOS, arrayCliente, QTY_CLIENTES);
				break;
			case 7:
				printf("\nUsted quiere imprimir el listado de los clientes junto con la cantidad de avisos activos que cada uno posee.\n");
				clienteAviso_avisosActivosImprimir(arrayCliente, QTY_CLIENTES, arrayAviso, QTY_AVISOS);
				break;
			case 8:
				do
				{
				if(utn_getNumberInt("\nUsted est� en el submen� de informes, seleccione una opci�n: \n\n1 - Cliente con m�s avisos.\n2 - Cantidad de avisos pausados.\n3 - Rubro con m�s avisos.\n4 - Salir del submen� de informes.\n", "\nError. Seleccione una opci�n v�lida (1-4)\n", &opcionSubMenu, 2, 1, 4) == 0)
					{
						switch(opcionSubMenu)
						{
						case 1:
							printf("\nUsted quiere un informe del cliente con m�s avisos.\n");
							informes_calcularClienteConMasAvisos(arrayCliente, QTY_CLIENTES, arrayAviso, QTY_AVISOS);
							break;
						case 2:
							printf("\nUsted quiere un informe de la cantidad de avisos pausados.\n");
							informes_calcularCantidadDeAvisosPausados(arrayAviso, QTY_AVISOS);
							break;
						case 3:
							printf("\nUsted quiere un informe del rubro con m�s avisos.\n");
							informes_calcularRubroConMasAvisos(arrayAviso, QTY_AVISOS);
							break;
						}
					}
				}while(opcionSubMenu != 4);
				break;
			}
		}
	}while(opcion != 8);
	return EXIT_SUCCESS;
}
