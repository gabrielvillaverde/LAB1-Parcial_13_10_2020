/*
 * cliente.c
 *
 *  Created on: 1 oct. 2020
 *      Author: Hzkr
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utn.h"
#include "cliente.h"

static int cliente_generarNuevoId (void); // Prototipo

/**
* Funci�n que genera un nuevo ID para cada cliente.
* \return ID del cliente.
*/
static int cliente_generarNuevoId (void)
{
	static int id = 0;
	id = id+1;
	return id;
}

/**
* Funci�n que inicializa el array de clientes
* \param pArrayCliente, recibe el array de clientes.
* \param limiteCliente, recibe el limite de los clientes.
* \return (-1) ERROR / 0 OK
*/
int cliente_init(Cliente * pArrayCliente, int limiteCliente)
{
	int retorno = -1;
	if (pArrayCliente != NULL && limiteCliente > 0)
	{
		for (int i = 0 ; i < limiteCliente ; i++)
		{
			pArrayCliente[i].isEmpty = TRUE; // Indico que est�n vac�as TODAS las posiciones del array de clientes.
		}
		retorno = 0;
	}
	return retorno;
}

/**
* Funci�n que da de alta un cliente
* \param pArrayCliente, recibe el array de clientes.
* \param limiteCliente, recibe el limite de los clientes.
* \return (-1) ERROR / 0 OK
*/
int cliente_alta (Cliente * pArrayCliente, int limiteCliente)
{
	int retorno = -1;
	int indice;

	Cliente bufferCliente; // Creo una variable auxiliar del tipo de dato Cliente, para cargar los datos que obtendr� m�s abajo y guardarlos en bufferCliente.

	if (pArrayCliente != NULL && limiteCliente > 0)
	{
		if (cliente_buscarLibreRef (pArrayCliente, limiteCliente, &indice) == 0) // Si encontr� un lugar libre en el array de clientes...
		{
			if (utn_getName("\nIngrese el nombre:\n", "Error, ingrese un nombre v�lido:\n", bufferCliente.nombre, 2, SIZE_NOMBRE) == 0 && // Le solicito los datos al usuario y los guardo en cada campo de bufferCliente.
				utn_getName("\nIngrese el apellido:\n", "Error, ingrese un apellido v�lido.\n", bufferCliente.apellido, 2, SIZE_APELLIDO) == 0 &&
				utn_getCuit("\nIngrese el CUIT:\n", "Error, ingrese un CUIT v�lido.\n", bufferCliente.cuit, 2, SIZE_CUIT) == 0)
			{	// Si obtuve los datos...
				pArrayCliente[indice] = bufferCliente; // DEEP COPY: Asigno los valores de bufferCliente en la posici�n del �ndice correspondiente.
				pArrayCliente[indice].idCliente = cliente_generarNuevoId(); // Genero un nuevo ID correspondiente a ese �ndice.
				printf("\nEl ID generado para este cliente es el: %d\n", pArrayCliente[indice].idCliente); // Muestro por consola el ID que se gener� para ese cliente.
				pArrayCliente[indice].isEmpty = FALSE; // Indico que dicha posici�n ya no est� vac�a.
				printf("\nSe ha cargado el cliente correctamente.\n");
				retorno = 0;
			}
		}
		else
		{
			printf("\nNo se pueden cargar m�s clientes.\n");
		}
	}
	return retorno;
}

/**
* Funci�n de hardcode. Obligo a mi programa a que inicialice con valores cargados por m� previamente.
* \param pArrayCliente, recibe el array de clientes.
* \param limiteCliente, recibe el limite de los clientes.
* \param nombre, recibe el nombre del cliente
* \param apellido, recibe el apellido del cliente
* \param cuit, recibe el cuit del cliente
* \return (-1) ERROR / 0 OK
*/
int cliente_altaForzada(Cliente * pArrayCliente, int limiteCliente, char * nombre, char * apellido, char * cuit)
{
	int retorno = -1;
	int indice;

	if(cliente_buscarLibreRef(pArrayCliente, limiteCliente, &indice) == 0) // Si hay un lugar libre en mi array de clientes...
	{
		strncpy(pArrayCliente[indice].nombre, nombre, SIZE_NOMBRE); // Uso la funci�n de strncpy para copiar en el �ndice del array de clientes, el nombre, apellido y CUIT.
		strncpy(pArrayCliente[indice].apellido, apellido, SIZE_APELLIDO);
		strncpy(pArrayCliente[indice].cuit, cuit, SIZE_CUIT);
		pArrayCliente[indice].idCliente = cliente_generarNuevoId(); // Genero un nuevo ID.
		pArrayCliente[indice].isEmpty = FALSE; // Indico que ese �ndice ya no est� vac�o.
		retorno = 0;
	}
	return retorno;
}

/**
* Funci�n que da de baja un cliente
* \param pArrayCliente, recibe el array de clientes.
* \param limiteCliente, recibe el limite de los clientes.
* \return (-1) ERROR / 0 OK
*/
/*
int cliente_baja (Cliente * pArrayCliente, int limiteCliente)
{
	int retorno = -1;
	int idABorrar;
	int indiceABorrar;
	if (pArrayCliente != NULL && limiteCliente > 0)
	{
		printf("\nA continuaci�n se listan los clientes que usted puede borrar:\n");
		cliente_imprimir(pArrayCliente, limiteCliente);
		if(utn_getNumberInt("\nIngrese ID del cliente que quiere borrar:\n","\nError.\n",&idABorrar,2,0,9999)==0)
		{
			// Busco la posici�n que quiero borrar
			if(cliente_buscarIndicePorId(pArrayCliente,limiteCliente,idABorrar,&indiceABorrar)==0)
			{
				// Borro esa posici�n
				pArrayCliente[indiceABorrar].isEmpty = TRUE; // M�todo de baja l�gica, simplemente cambio el valor de este campo.
				printf("\nSe ha dado de baja el cliente correctamente.\n");
			}
			else
			{
				printf("\nEse ID no existe.\n");
			}
		}
	}
	return retorno;
}
*/

/**
* Funci�n que modifica los clientes
* \param pArrayCliente, recibe el array de clientes.
* \param limiteCliente, recibe el limite de los clientes.
* \return (-1) ERROR / 0 OK
*/
int cliente_modificar (Cliente * pArrayCliente, int limiteCliente)
{
	int retorno = -1;
	int idBuscado;
	int indiceAModificar;

	Cliente bufferCliente; // Me creo una variable auxiliar del tipo de dato Cliente, donde voy a guardar luego los datos que solicito al usuario para modificar los campos correspondientes.
	if (pArrayCliente != NULL && limiteCliente > 0)
	{
		printf("\nA continuaci�n se listan los clientes que usted puede modificar:\n");
		cliente_imprimir(pArrayCliente, limiteCliente); // Llamo a la funci�n para modificar clientes.

		if(utn_getNumberInt("\nIngrese el ID del cliente que desea modificar:\n","\nError.\n",&idBuscado,2,0,9999) == 0) // Llamo a la funci�n que obtiene un n�mero para guardarme el ID en idBuscado.
		{
			if(cliente_buscarIndicePorId(pArrayCliente, limiteCliente,idBuscado,&indiceAModificar) == 0) // Llamo a la funci�n que busca el �ndice a modificar por ID. Recibe el ID buscado que obtuvo la funci�n getNumberInt y devuelve el �ndice por valor de referencia.
			{
				bufferCliente = pArrayCliente[indiceAModificar]; // Me guardo en mi variable auxiliar bufferCliente el �ndice que voy a modificar del array de clientes.

				if (utn_getName("\nIngrese el nuevo nombre:\n", "Error, ingrese un nombre v�lido:\n", bufferCliente.nombre, 2, SIZE_NOMBRE) == 0 && // Le pido los datos al usuario y los voy guardando en bufferCliente.
					utn_getName("\nIngrese el nuevo apellido:\n", "Error, ingrese un apellido v�lido.\n", bufferCliente.apellido, 2, SIZE_APELLIDO) == 0 &&
					utn_getCuit("\nIngrese el nuevo CUIT:\n", "Error, ingrese un CUIT v�lido.\n", bufferCliente.cuit, 2, SIZE_CUIT) == 0)
				{
					pArrayCliente[indiceAModificar] = bufferCliente; // Copio en el �ndice a modificar del array lo que contiene bufferCliente ya con los datos nuevos.
					printf("\nCliente modificado correctamente.\n");
					retorno = 0;
				}
			}
			else
			{
				printf("\nEse ID no existe.\n");
			}
		}
	}
	return retorno;
}

/**
* Funci�n que imprime los clientes
* \param pArrayCliente, recibe el array de clientes.
* \param limiteCliente, recibe el limite de los clientes.
* \return (-1) ERROR / 0 OK
*/
int cliente_imprimir (Cliente * pArrayCliente , int limiteCliente)
{
	int retorno = -1;

	if (pArrayCliente != NULL && limiteCliente > 0)
	{
		for (int i = 0 ; i < limiteCliente ; i++) // Recorro el array de clientes
		{
			if(pArrayCliente[i].isEmpty == FALSE) // Si la posici�n "i" del array de clientes NO est� vac�a...
			{
				// Estoy en condiciones de poder imprimir cada elemento del tipo de dato Cliente.
				printf("\nID: %d - Nombre del cliente: %s - Apellido del cliente: %s - CUIT: %s\n",pArrayCliente[i].idCliente,pArrayCliente[i].nombre, pArrayCliente[i].apellido, pArrayCliente[i].cuit);
			}
		}
		retorno = 0;
	}
	return retorno;
}

/**
* Funci�n que busca un lugar libre en el array de clientes, devuelve el �ndice por valor de retorno.
* \param pArrayCliente, recibe el array de clientes.
* \param limiteCliente, recibe el limite de los clientes.
* \return (-1) ERROR / 0 OK
*/
int cliente_buscarLibre (Cliente * pArrayCliente, int limiteCliente)
{
	int retorno = -1;
	int i;

	if (pArrayCliente != NULL && limiteCliente > 0)
	{
		for ( i = 0 ; i < limiteCliente ; i++)
		{
			if(pArrayCliente[i].isEmpty == TRUE)
			{
				retorno = i; // Retorno por valor.
				break;
			}
		}
	}
	return retorno;
}

/**
* Funci�n que busca un lugar libre en el array de clientes, devuelve el valor por referencia
* \param pArrayCliente, recibe el array de clientes.
* \param limiteCliente, recibe el limite de los clientes.
* \param pIndice, es el puntero al �ndice que se est� buscando, devuelve el �ndice por valor de referencia.
* \return (-1) ERROR / 0 OK
*/
int cliente_buscarLibreRef (Cliente * pArrayCliente, int limiteCliente, int * pIndice)
{
	int retorno = -1;
	int i;

	if (pArrayCliente != NULL && limiteCliente > 0 && pIndice != NULL)
	{
		for (i = 0 ; i < limiteCliente ; i++)
		{
			if(pArrayCliente[i].isEmpty == TRUE) // Si el elemento i en el array de clientes est� vac�o...
			{
				*pIndice = i; // Retorno el valor por referencia.
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

/**
* Funci�n que busca el �ndice en el array de clientes por ID.
* \param pArrayCliente, recibe el array de clientes.
* \param limiteCliente, recibe el limite de los clientes.
* \param idBuscado, recibe el ID que se est� buscando.
* \param pIndice, es el puntero al �ndice que se est� buscando, devuelve el �ndice por valor de referencia.
* \return (-1) ERROR / 0 OK
*/
int cliente_buscarIndicePorId (Cliente * pArrayCliente, int limiteCliente, int idBuscado, int * pIndice)
{
	int retorno = -1;
	int i;

	if (pArrayCliente != NULL && limiteCliente > 0 && pIndice != NULL && idBuscado >= 0)
	{
		for (i = 0 ; i < limiteCliente ; i++) // Recorro el array de clientes
		{
			if(pArrayCliente[i].isEmpty == FALSE && pArrayCliente[i].idCliente == idBuscado) // Si la posici�n i del array no est� vac�a, y adem�s coincide en el campo idCliente con el idBuscado...
			{
				*pIndice = i; // Devuelvo i por valor de referencia.
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

/*int cliente_ordenarPorNombre (Cliente * pArrayCliente, int limiteCliente)
{
	int retorno = -1;
	int flagSwap;
	int indiceCliente;

	Cliente bufferAuxiliar;

	if(pArrayCliente != NULL && limiteCliente > 0)
	{
		do
		{
			flagSwap = 0;
			for(indiceCliente = 0 ; indiceCliente < limiteCliente-1 ; indiceCliente++)
			{
				if(strncmp(pArrayCliente[indiceCliente].nombre, pArrayCliente[indiceCliente+1].nombre, SIZE_NOMBRE) > 0)
				{
					flagSwap = 1;
					bufferAuxiliar = pArrayCliente[indiceCliente];
					pArrayCliente[indiceCliente] = pArrayCliente[indiceCliente+1];
					pArrayCliente[indiceCliente+1] = bufferAuxiliar;
				}
			}
			limiteCliente--;
		}while(flagSwap);
	}
	return retorno;
}*/

/*int cliente_ordenarPorNombreLuegoPorId (Cliente * pArrayCliente, int limiteCliente)
{
	int retorno = -1;
	int flagSwap;
	int indiceCliente;

	Cliente bufferAuxiliar;

	if(pArrayCliente != NULL && limiteCliente > 0)
	{
		do
		{
			flagSwap = 0;
			for(indiceCliente = 0 ; indiceCliente < limiteCliente-1 ; indiceCliente++)
			{
				if(strncmp(pArrayCliente[indiceCliente].nombre, pArrayCliente[indiceCliente+1].nombre, SIZE_NOMBRE) > 0)
				{
					flagSwap = 1;
					bufferAuxiliar = pArrayCliente[indiceCliente];
					pArrayCliente[indiceCliente] = pArrayCliente[indiceCliente+1];
					pArrayCliente[indiceCliente+1] = bufferAuxiliar;
				}
				else if(strncmp(pArrayCliente[indiceCliente].nombre, pArrayCliente[indiceCliente+1].nombre, SIZE_NOMBRE) == 0 &&
						pArrayCliente[indiceCliente].idCliente < pArrayCliente[indiceCliente+1].idCliente)
				{
					{
						flagSwap = 1;
						bufferAuxiliar = pArrayCliente[indiceCliente];
						pArrayCliente[indiceCliente] = pArrayCliente[indiceCliente+1];
						pArrayCliente[indiceCliente+1] = bufferAuxiliar;
					}
				}
			}
			limiteCliente--;
		}while(flagSwap);
	}
	return retorno;
}
*/
