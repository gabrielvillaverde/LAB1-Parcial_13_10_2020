/*
 * clienteAviso.c
 *
 *  Created on: 11 oct. 2020
 *      Author: Hzkr
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utn.h"
#include "clienteAviso.h"

/**
* Funci�n que da de baja el cliente junto con todos sus avisos
* \param pArrayAviso, recibe el array de avisos
* \param limiteAviso, recibe el limite de los avisos
* \param pArrayCliente, recibe el array de clientes
* \param limiteCliente, recibe el limite de los clientes
 * return (-1) ERROR / 0 OK
 */
int clienteAviso_baja (Aviso * pArrayAviso, int limiteAviso, Cliente * pArrayCliente, int limiteCliente)
{
	int retorno = -1;
	int idClienteABorrar;
	int indiceClienteABorrar;
	int opcionDeEliminar;

	if (pArrayAviso != NULL && limiteAviso > 0 && pArrayCliente != NULL && limiteCliente > 0)
	{
		if(		utn_getNumberInt("\nIngrese el ID del cliente que quiere borrar:\n","\nError, ID inv�lido.\n",&idClienteABorrar,2,0,9999) == 0 && // Llamo a la funci�n que obtiene un n�mero y lo guardo en idClienteABorrar.
				cliente_buscarIndicePorId(pArrayCliente, limiteCliente, idClienteABorrar, &indiceClienteABorrar) != -1) // Llamo a la funci�n para buscar el ID de un cliente, si es distinto de -1 es porque encontr� un ID para dar de baja.
		{
			printf("\nA continuaci�n se listan los avisos que corresponden al ID seleccionado:\n");
			if(aviso_imprimirTodosLosAvisosPorIdCliente(pArrayAviso, limiteAviso, pArrayCliente, limiteCliente, idClienteABorrar) == 0) // Llamo a la funci�n que imprime todos los avisos que corresponden al ID que obtengo con idClienteABorrar.
			{
				if(utn_getNumberInt("\n�Desea borrar este cliente junto con todas sus publicaciones? [1 - SI] - [2 - NO]\n", "Error, ingrese: [1 - SI] - [2 - NO].\n", &opcionDeEliminar, 2, 1, 2) == 0) // Llamo a la funci�n que obtiene un n�mero y lo guardo en opcionDeEliminar.
				{
					if(opcionDeEliminar == 1) // Si la opci�n de eliminar es == 1, es porque quiere borrar.
					{
							aviso_borrarPorIdCliente(pArrayAviso, limiteAviso, idClienteABorrar); // Llamo a la funci�n para borrar el aviso por ID del cliente, ya que lo recibo desde idClienteABorrar.
							pArrayCliente[indiceClienteABorrar].isEmpty = TRUE; // Indico que �ndice en esa posici�n del array de clientes est� vac�o.
							printf("\nSe ha borrado el cliente junto con todas sus publicaciones.\n");
					}
				}
				else
				{
					printf("\nNo se ha borrado al cliente.\n");
				}
			}
		}
		else
		{
			printf("\nEse ID de cliente no existe.\n"); // Entra ac� si es que la funci�n de cliente_buscarIndicePorId me devolvi� -1.
		}
	}
	return retorno;
}

/**
* Funci�n que calcula la cantidad de avisos activos de los clientes
* \param pArrayCliente, recibe el array de clientes
* \param limiteCliente, recibe el limite de los clientes
* \param pArrayAviso, recibe el array de avisos
* \param limiteAviso, recibe el limite de los avisos
 * return (-1) ERROR / 0 OK
 */
int clienteAviso_avisosActivosImprimir (Cliente * pArrayCliente, int limiteCliente, Aviso * pArrayAviso, int limiteAviso)
{
	int retorno = -1;

	if (pArrayCliente != NULL && limiteCliente > 0 && pArrayAviso != NULL && limiteAviso > 0)
	{
		for (int indiceCliente = 0 ; indiceCliente < limiteCliente ; indiceCliente++) // Recorro todo el array de clientes...
		{
			if(pArrayCliente[indiceCliente].isEmpty == FALSE) // Si el �ndice del array de clientes no est� vac�o...
			{
				// Estoy en condiciones de poder imprimir...
				printf("\n##########################################\n");
				printf("\nID: %d - Nombre del cliente: %s - Apellido del cliente: %s - CUIT: %s\n",pArrayCliente[indiceCliente].idCliente, pArrayCliente[indiceCliente].nombre, pArrayCliente[indiceCliente].apellido, pArrayCliente[indiceCliente].cuit); // Me imprimo los datos del cliente.
				aviso_imprimirAvisoActivoPorIdCliente(pArrayAviso, limiteAviso, pArrayCliente, limiteCliente, pArrayCliente[indiceCliente].idCliente); // Llamo a la funci�n que imprime SOLO AVISOS ACTIVOS por ID del cliente.
				printf("\n##########################################\n\n");
			}
		}
		retorno = 0;
	}
	return retorno;
}
