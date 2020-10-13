/*
 * aviso.c
 *
 *  Created on: 6 oct. 2020
 *      Author: Hzkr
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utn.h"
#include "aviso.h"
#include "clienteAviso.h"

static int aviso_generarNuevoId (void); // Prototipo

/**
* Función que genera un nuevo ID para cada aviso.
* \return ID del aviso.
*/
static int aviso_generarNuevoId (void)
{
	static int id = 0;
	id = id+1;
	return id;
}

/**
* Función que inicializa el array de avisos
* \param pArrayAviso, recibe el array de avisos.
* \param limiteAviso, recibe el limite de los avisos.
* \return (-1) ERROR / 0 OK
*/
int aviso_init (Aviso * pArrayAviso, int limiteAviso)
{
	int retorno = -1;
	if (pArrayAviso != NULL && limiteAviso > 0)
	{
		for (int i = 0; i < limiteAviso ; i++)
		{
			pArrayAviso[i].isEmpty = TRUE; // Indico que están vacías TODAS las posiciones del array de avisos.
		}
		retorno = 0;
	}
	return retorno;
}

/**
* Función que da de alta los avisos
* \param pArrayAviso, recibe el array de avisos.
* \param limiteAviso, recibe el limite de los avisos.
* \param pArrayCliente, recibe el array de clientes.
* \param limiteCliente, recibe el limite de los clientes.
* \param indiceAvisos, recibe el índice de avisos, el cuál por los avisos hardcodeados lo inicio en 6.
* \return (-1) ERROR / 0 OK
*/
int aviso_alta (Aviso * pArrayAviso, int limiteAviso, Cliente * pArrayCliente, int limiteCliente, int * indiceAvisos)
{
	int retorno = -1;
	int indice;

	Aviso bufferAviso; // Me creo una variable auxiliar del tipo Aviso.

	if (pArrayAviso != NULL && limiteAviso > 0 && pArrayCliente != NULL && limiteCliente > 0) // Verifico lo que recibo como parámetro.
	{
		if (aviso_buscarLibreRef (pArrayAviso, limiteAviso, &indice) == 0) // Si encontré un lugar libre en mi array de avisos...
		{
			// Le solicito los datos al usuario y los guardo en cada campo del auxiliar bufferAviso.
			if (utn_getNumberInt("\nIngrese el ID del cliente:\n", "\nError, intente nuevamente.\n", &bufferAviso.idCliente, 2, 0, 9999) == 0 &&
				cliente_buscarIndicePorId(pArrayCliente, limiteCliente, bufferAviso.idCliente, &indice) != -1 && // Si la función de buscar un índice por ID me devuelve algo distinto a -1, es porque encontró un ID.
				utn_getNumberInt("\nIngrese el número de rubro:\n", "\nError, ingrese un número de rubro válido entre 0 y 9999.\n",&bufferAviso.numeroDeRubro, 2, 0, 9999) == 0 &&
				utn_getAlphaNum("\nIngrese el texto del aviso:\n", "\nError, ingrese un texto válido de máximo 64 caracteres:\n", bufferAviso.textoDelAviso, 2, SIZE_TEXTO_AVISO) == 0)
			{
				pArrayAviso[*indiceAvisos] = bufferAviso; // Guardo en el indice de avisos lo que contiene la variable auxiliar bufferAviso.
				pArrayAviso[*indiceAvisos].idAviso = aviso_generarNuevoId(); // Genero un nuevo ID de aviso.
				printf("\nEl ID generado para este aviso es el: %d\n", pArrayAviso[*indiceAvisos].idAviso);
				pArrayAviso[*indiceAvisos].isEmpty = FALSE; // Indico que ese índice de mi array de avisos ya no está vacío.
				pArrayAviso[*indiceAvisos].estado = AVISO_ACTIVO; // Lo cargo como un aviso activo ya que así lo pide la consigna.
				*indiceAvisos = *indiceAvisos + 1; // Aumento el contador del índice de avisos en 1 y retorno por valor de referencia.
				retorno = 0;
			}
			else
			{
				printf("\nError, ese ID no existe.\n"); // Muestra este mensaje si la función de buscarIndicePorId devuelve un -1, es decir, no existe el índice que se corresponde al ID ingresado.
			}
		}
	}
	return retorno;
}

/**
* Función de hardcode. Obligo a mi programa a que inicialice con valores cargados por mí previamente.
* \param pArrayAviso, recibe el array de avisos.
* \param limiteAviso, recibe el limite de los avisos.
* \param numeroDeRubro, recibe el número de rubro.
* \param textoDelAviso, recibe el texto del aviso.
* \param idCliente, recibe el ID del cliente.
* \param estadoAviso, recibe el estado del aviso
* \return (-1) ERROR / 0 OK
*/
int aviso_altaForzada(Aviso * pArrayAviso, int limiteAviso, int numeroDeRubro, char * textoDelAviso, int idCliente, int estadoAviso)
{
	int retorno = -1;
	int indice;

	if(aviso_buscarLibreRef(pArrayAviso, limiteAviso, &indice) == 0) // Si hay un lugar libre en mi array de avisos...
	{
		pArrayAviso[indice].numeroDeRubro = numeroDeRubro; // Asigno en el índice de mi array de avisos el número de Rubro. No hace falta strncpy porque se trata de un entero.
		pArrayAviso[indice].idCliente = idCliente;
		strncpy(pArrayAviso[indice].textoDelAviso, textoDelAviso, SIZE_TEXTO_AVISO); // Uso la función de strncpy para copiar en el índice del array de avisos el texto del aviso ya que se trata de un char.
		pArrayAviso[indice].idAviso = aviso_generarNuevoId(); // Genero un nuevo ID.
		pArrayAviso[indice].isEmpty = FALSE; // Indico que ese índice ya no está vacío.
		pArrayAviso[indice].estado = estadoAviso;
		retorno = 0;
	}
	return retorno;
}

/**
* Función que pausa los avisos
* \param pArrayAviso, recibe el array de avisos.
* \param limiteAviso, recibe el limite de los avisos.
* \param pArrayCliente, recibe el array de clientes.
* \param limiteCliente, recibe el limite de los clientes.
* \return (-1) ERROR / 0 OK
*/
int aviso_pausar (Aviso * pArrayAviso, int limiteAviso, Cliente * pArrayCliente, int limiteCliente)
{
	int retorno = -1;
	int idAvisoAPausar;
	int indiceAPausar;
	int opcionDePausar;

	if (pArrayAviso != NULL && limiteAviso > 0)
	{
		printf("\nEstos son los avisos activos de todos los clientes:\n");
		aviso_imprimirPorEstado(pArrayAviso, limiteAviso, pArrayCliente, limiteCliente, AVISO_ACTIVO); // Llamo a la función que imprime avisos por estado, en este caso PAUSADO.
		if(	utn_getNumberInt("\nIngrese el ID del aviso que quiere pausar:\n","\nError, ID inválido.\n",&idAvisoAPausar,2,0,9999) == 0 &&
			aviso_buscarIndicePorId(pArrayAviso,limiteAviso,idAvisoAPausar,&indiceAPausar) != -1) // Si me devuelve algo distinto a -1, es porque valido correctamente y el ID correspondiente a ese índice existe.
		{
			printf("\nEstos son los datos del cliente al que corresponde ese aviso:.\n");
			if(aviso_imprimirPorId(pArrayAviso, limiteAviso, pArrayCliente, limiteCliente, idAvisoAPausar) == 0) // Le muestro los datos del cliente al que corresponden ese aviso llamando a la función que imprime los avisos por ID.
			{
				if(utn_getNumberInt("\n¿Desea pausar esta publicación? [1 - SI] - [2 - NO]\n", "Error, ingrese: [1 - SI] - [2 - NO].\n", &opcionDePausar, 2, 1, 2) == 0)
				{
					if(opcionDePausar == 1) // Si el cliente confirma que desea pausar...
					{
						// Busco el ID que quiero pausar.
						if(aviso_buscarIndicePorId(pArrayAviso,limiteAviso,idAvisoAPausar,&indiceAPausar) == 0)
						{
							// Pongo en pausa el aviso.
							pArrayAviso[indiceAPausar].estado = AVISO_PAUSADO; // Pausado.
							printf("\nLa publicación se ha pausado correctamente.\n");
						}
					}
				}
			}
		}
		else
		{
			printf("\nEste aviso ya está pausado o el ID es inexistente.\n"); // En este caso, la función de buscar un índice por ID devuelve -1.
		}
	}
	return retorno;
}

/**
* Función que activa los avisos
* \param pArrayAviso, recibe el array de avisos.
* \param limiteAviso, recibe el limite de los avisos.
* \param pArrayCliente, recibe el array de clientes.
* \param limiteCliente, recibe el limite de los clientes.
* \return (-1) ERROR / 0 OK
*/
int aviso_activar (Aviso * pArrayAviso, int limiteAviso, Cliente * pArrayCliente, int limiteCliente)
{
	int retorno = -1;
	int idAvisoActivar;
	int indiceActivar;
	int opcionDeActivar;

	if (pArrayAviso != NULL && limiteAviso > 0)
	{
		printf("\nEstos son los avisos pausados de todos los clientes:\n");
		aviso_imprimirPorEstado(pArrayAviso, limiteAviso, pArrayCliente, limiteCliente, AVISO_PAUSADO); // Llamo a la función que imprime avisos por estado, en este caso PAUSADO.
		if(	utn_getNumberInt("\nIngrese el ID del aviso que quiere activar:\n","\nError, ID inválido.\n",&idAvisoActivar,2,0,9999) == 0 &&
			aviso_buscarIndicePorId(pArrayAviso,limiteAviso,idAvisoActivar,&indiceActivar) != -1) // Si me devuelve algo distinto a -1, es porque valido correctamente y el ID correspondiente a ese índice existe.
		{
			if(pArrayAviso[indiceActivar].estado == AVISO_PAUSADO) // Si el estado del índice que quiero activar está pausado...
			{
				printf("\nEstos son los datos del cliente al que corresponde ese aviso:\n");
				if(aviso_imprimirPorId(pArrayAviso, limiteAviso, pArrayCliente, limiteCliente, idAvisoActivar) == 0) // Le muestro los datos del cliente al que corresponden ese aviso llamando a la función que imprime los avisos por ID.
				{
					if(utn_getNumberInt("\n¿Desea activar esta publicación? [1 - SI] - [2 - NO]\n", "Error, ingrese: [1 - SI] - [2 - NO].\n", &opcionDeActivar, 2, 1, 2) == 0)
					{
						if(opcionDeActivar == 1)
						{
							// Si el cliente quiere activar la publicación...
							pArrayAviso[indiceActivar].estado = AVISO_ACTIVO; // Pongo el estado del aviso en activo, en la posición del índice. a activar.
							printf("\nLa publicación se ha activado correctamente.\n");
						}
					}
				}
			}
		}
		else
		{
			printf("\nEste aviso ya está activo o el ID es inexistente.\n"); // En este caso, la función de buscar un índice por ID devuelve -1.
		}
	}
	return retorno;
}

/**
* Función que imprime los avisos.
* \param pArrayAviso, recibe el array de avisos.
* \param limiteAviso, recibe el limite de los avisos.
* \param pArrayCliente, recibe el array de clientes.
* \param limiteCliente, recibe el limite de los clientes.
* \param idAviso, recibe el ID del aviso.
* \return (-1) ERROR / 0 OK
*/
int aviso_imprimir (Aviso * pArrayAviso, int limiteAviso, Cliente * pArrayCliente, int limiteCliente)
{
	int retorno = -1;
	int indiceCliente;
	char strEstado[10];
	if (pArrayAviso != NULL && limiteAviso > 0 && pArrayCliente != NULL && limiteCliente > 0)
	{
		for (int i = 0 ; i < limiteAviso ; i++) // Recorro el array de avisos.
		{
			if(pArrayAviso[i].isEmpty == FALSE)
			{
				if(pArrayAviso[i].estado == AVISO_PAUSADO) // Si el estado del aviso está pausado...
				{
					sprintf(strEstado,"Pausado"); // Cargo la cadena strEstado con "Pausado".
				}
				else // Sino, está activo, por lo tanto...
				{
					sprintf(strEstado,"Activo"); // Cargo la cadena strEstado con "Activo".
				}
				cliente_buscarIndicePorId(pArrayCliente, limiteCliente, pArrayAviso[i].idCliente, &indiceCliente); // Llamo a la función que busca en mi array de clientes el índice por ID del cliente.
				printf("\nID del cliente: %d - ID del aviso: %d - Nombre del cliente: %s - Apellido del cliente: %s - CUIT: %s - Número de rubro: %d - Texto del aviso: %s - Estado del aviso: %s", pArrayCliente[indiceCliente].idCliente, pArrayAviso[i].idAviso, pArrayCliente[indiceCliente].nombre, pArrayCliente[indiceCliente].apellido, pArrayCliente[indiceCliente].cuit, pArrayAviso[i].numeroDeRubro, pArrayAviso[i].textoDelAviso, strEstado);
			}
		}
		retorno = 0;
	}
	return retorno;
}

/**
* Función que imprime los avisos por ID.
* \param pArrayAviso, recibe el array de avisos.
* \param limiteAviso, recibe el limite de los avisos.
* \param pArrayCliente, recibe el array de clientes.
* \param limiteCliente, recibe el limite de los clientes.
* \param idAviso, recibe el ID del aviso.
* \return (-1) ERROR / 0 OK
*/
int aviso_imprimirPorId (Aviso * pArrayAviso, int limiteAviso, Cliente * pArrayCliente, int limiteCliente, int idAviso)
{
	int retorno = -1;
	int indiceCliente;

	if (pArrayAviso != NULL && limiteAviso > 0 && pArrayCliente != NULL && limiteCliente > 0)
	{
		for(int i ; i < limiteAviso ; i++) // Recorro el array de avisos.
		{
			if(pArrayAviso[i].idAviso == idAviso) // Si la posición i de mi array de avisos en el campo idAviso coincide el ID del aviso indicado.
			{
				cliente_buscarIndicePorId(pArrayCliente, limiteCliente, pArrayAviso[i].idCliente, &indiceCliente); // Llamo a la función que busca en mi array de clientes el índice por ID del cliente.
				printf("\nID del cliente: %d - ID del aviso: %d - Nombre del cliente: %s - Apellido del cliente: %s - CUIT: %s - Número de rubro: %d - Texto del aviso: %s", pArrayCliente[indiceCliente].idCliente, pArrayAviso[i].idAviso, pArrayCliente[indiceCliente].nombre, pArrayCliente[indiceCliente].apellido, pArrayCliente[indiceCliente].cuit, pArrayAviso[i].numeroDeRubro, pArrayAviso[i].textoDelAviso);
			}
		}
		retorno = 0;
	}
	return retorno;
}

/**
* Función que imprime todos los avisos activos por ID del cliente.
* \param pArrayAviso, recibe el array de avisos.
* \param limiteAviso, recibe el limite de los avisos.
* \param pArrayCliente, recibe el array de clientes.
* \param limiteCliente, recibe el limite de los clientes.
* \param idCliente, recibe el ID del cliente.
* \return (-1) ERROR / 0 OK
*/
int aviso_imprimirAvisoActivoPorIdCliente (Aviso * pArrayAviso, int limiteAviso, Cliente * pArrayCliente, int limiteCliente, int idCliente)
{
	int retorno = -1;
	int indiceCliente;
	int contadorAvisosActivos = 0;
	char strEstado[10]; // Me declaro esta variable para luego copiar "Activo"en strEstado.

	if (pArrayAviso != NULL && limiteAviso > 0 && pArrayCliente != NULL && limiteCliente > 0)
	{
		for(int i = 0 ; i < limiteAviso ; i++) // Recorro el array de avisos.
		{
			if(pArrayAviso[i].idCliente == idCliente) // Si la posición i de mi array de avisos en el campo idCliente coincide el ID del cliente indicado...
			{
				if(pArrayAviso[i].estado == AVISO_ACTIVO) // Si el estado del aviso está activo...
				{
					sprintf(strEstado,"Activo"); // Cargo la cadena strEstado con "Activo".
					contadorAvisosActivos++; // Y aumento el contador de avisos activos.
					cliente_buscarIndicePorId(pArrayCliente, limiteCliente, pArrayAviso[i].idCliente, &indiceCliente); // Llamo a la función que busca en mi array de clientes el índice por ID del cliente.
					printf("\nNúmero de rubro: %d - Texto del aviso: %s - Estado: %s\n", pArrayAviso[i].numeroDeRubro, pArrayAviso[i].textoDelAviso, strEstado); // Imprimo
				}
			}
		}
		printf("\nLa cantidad de avisos activos que posee son: %d\n", contadorAvisosActivos); // Le muestro al usuario la cantidad de avisos activos que posee.
		retorno = 0;
	}
	return retorno;
}

/**
* Función que imprime todos los avisos por ID del cliente.
* \param pArrayAviso, recibe el array de avisos.
* \param limiteAviso, recibe el limite de los avisos.
* \param pArrayCliente, recibe el array de clientes.
* \param limiteCliente, recibe el limite de los clientes.
* \param idCliente, recibe el ID del cliente.
* \return (-1) ERROR / 0 OK
*/
int aviso_imprimirTodosLosAvisosPorIdCliente (Aviso * pArrayAviso, int limiteAviso, Cliente * pArrayCliente, int limiteCliente, int idCliente)
{
	int retorno = -1;
	int indiceCliente;
	char strEstado[10]; // Me declaro esta variable para luego copiar "Activo" o "Pausado" en strEstado.

	if (pArrayAviso != NULL && limiteAviso > 0 && pArrayCliente != NULL && limiteCliente > 0)
	{

		for(int i = 0 ; i < limiteAviso ; i++) // Recorro el array de avisos.
		{
			if(pArrayAviso[i].idCliente == idCliente) // Si la posición i de mi array de avisos en el campo idCliente coincide el ID del cliente indicado...
			{
				cliente_buscarIndicePorId(pArrayCliente, limiteCliente, pArrayAviso[i].idCliente, &indiceCliente); // Llamo a la función que busca en mi array de clientes el índice por ID del cliente.
				if(pArrayAviso[i].estado == AVISO_ACTIVO) // Si el estado del aviso está activo...
				{
					sprintf(strEstado,"Activo"); // Cargo la cadena strEstado con "Activo".
				}
				else if (pArrayAviso[i].estado == AVISO_PAUSADO) // En cambio si el estado del aviso está pausado...
				{
					sprintf(strEstado,"Pausado"); // Cargo la cadena strEstado con "Pausado".
				}
				printf("\nNúmero de rubro: %d - Texto del aviso: %s - Estado: %s\n", pArrayAviso[i].numeroDeRubro, pArrayAviso[i].textoDelAviso, strEstado); // Imprimo.
			}
		}
		retorno = 0;
	}
	return retorno;
}

/**
* Función que cuenta la cantidad de avisos por ID del cliente.
* \param pArrayAviso, recibe el array de avisos.
* \param limiteAviso, recibe el limite de los avisos.
* \param pArrayCliente, recibe el array de clientes.
* \param limiteCliente, recibe el limite de los clientes.
* \param idCliente, recibe el ID del cliente.
* \return (-1) ERROR / 0 OK
*/
int aviso_contarAvisosPorIdCliente (Aviso * pArrayAviso, int limiteAviso, Cliente * pArrayCliente, int limiteCliente, int idCliente)
{
	int contadorAvisos = 0; // Hago un contador de avisos.

	if (pArrayAviso != NULL && limiteAviso > 0 && pArrayCliente != NULL && limiteCliente > 0)
	{
		for(int i = 0 ; i < limiteCliente ; i++) // Recorro mi array de clientes
		{
			if(pArrayAviso[i].idCliente == idCliente) // Si la posición i de mi array de avisos en el campo idCliente coincide el ID del cliente indicado...
			{
				contadorAvisos++; // Aumento el contador de avisos.
			}
		}
	}
	return contadorAvisos;
}

/**
* Función que imprime los avisos por estado.
* \param pArrayAviso, recibe el array de avisos.
* \param limiteAviso, recibe el limite de los avisos.
* \param pArrayCliente, recibe el array de clientes.
* \param limiteCliente, recibe el limite de los clientes.
* \param estadoAviso, recibe el estado por el cuál quiere imprimir, si pausado o activo.
* \return (-1) ERROR / 0 OK
*/
int aviso_imprimirPorEstado (Aviso * pArrayAviso, int limiteAviso, Cliente * pArrayCliente, int limiteCliente, int estadoAviso)
{
	int retorno = -1;
	int indiceCliente;
	char strEstado[10];

	if (pArrayAviso != NULL && limiteAviso > 0 && pArrayCliente != NULL && limiteCliente > 0)
	{
		for(int i ; i < limiteAviso ; i++)
		{
			if(pArrayAviso[i].estado == estadoAviso && pArrayAviso[i].isEmpty == FALSE)
			{
				cliente_buscarIndicePorId(pArrayCliente, limiteCliente, pArrayAviso[i].idCliente, &indiceCliente);
				if(pArrayAviso[i].estado == AVISO_PAUSADO)
				{
					sprintf(strEstado,"Pausado"); // Cargo la cadena strEstado con "Pausado".
				}
				else
				{
					sprintf(strEstado,"Activo"); // Cargo la cadena strEstado con "Pausado".

				}
				printf("\nID del cliente: %d - ID del aviso: %d - Nombre del cliente: %s - Apellido del cliente: %s - CUIT: %s - Número de rubro: %d - Texto del aviso: %s - Estado del aviso: %s\n", pArrayCliente[indiceCliente].idCliente, pArrayAviso[i].idAviso, pArrayCliente[indiceCliente].nombre, pArrayCliente[indiceCliente].apellido, pArrayCliente[indiceCliente].cuit, pArrayAviso[i].numeroDeRubro, pArrayAviso[i].textoDelAviso, strEstado);
			}
		}
		retorno = 0;
	}
	return retorno;
}

/**
* Función que busca un lugar libre en el array de avisos, devuelve el índice por valor de retorno.
* \param pArrayAviso, recibe el array de avisos.
* \param limiteAviso, recibe el limite de los avisos.
* \return (-1) ERROR / 0 OK
*/
int aviso_buscarLibre (Aviso * pArrayAviso, int limiteAviso)
{
	int retorno = -1;
	int i;

	if (pArrayAviso != NULL && limiteAviso > 0)
	{
		for (i = 0 ; i < limiteAviso ; i++) // Recorro el array de avisos.
		{
			if(pArrayAviso[i].isEmpty == TRUE) // Si el array de avisos en la posición i está vacío...
			{
				retorno = i; // Devuelvo i por valor de retorno.
				break;
			}
		}
	}
	return retorno;
}

/**
* Función que busca un lugar libre en el array de avisos, devuelve el valor por referencia
* \param pArrayAviso, recibe el array de avisos.
* \param limiteAviso, recibe el limite de los avisos.
* \param pIndice, es el puntero al índice que se está buscando, devuelve el índice por valor de referencia.
* \return (-1) ERROR / 0 OK
*/
int aviso_buscarLibreRef (Aviso * pArrayAviso, int limiteAviso, int * pIndice)
{
	int retorno = -1;
	int i ;

	if (pArrayAviso != NULL && limiteAviso > 0 && pIndice != NULL)
	{
		for ( i = 0 ; i < limiteAviso ; i++)
		{
			if(pArrayAviso[i].isEmpty == TRUE) // Si el array de avisos en la posición i está vacío...
			{
				*pIndice = i; // Devuelvo por valor de referencia esa posición
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

/**
* Función que busca el índice en el array de avisos por ID.
* \param pArrayAviso, recibe el array de avisos.
* \param limiteAviso, recibe el limite de los avisos.
* \param idBuscado, recibe el ID que se está buscando.
* \param pIndice, es el puntero al índice que se está buscando, devuelve el índice por valor de referencia.
* \return (-1) ERROR / 0 OK
*/
int aviso_buscarIndicePorId (Aviso * pArrayAviso, int limiteAviso, int idBuscado, int * pIndice)
{
	int retorno = -1;
	int i;

	if (pArrayAviso != NULL && limiteAviso > 0 && pIndice != NULL && idBuscado >= 0)
	{
		for (i = 0; i < limiteAviso ; i++) // Recorro el array de avisos
		{
			if(pArrayAviso[i].isEmpty == FALSE && pArrayAviso[i].idAviso == idBuscado) // Si la posición i del array no está vacía, y además coincide en el campo idAviso con el idBuscado...
			{
				*pIndice = i; // Devuelvo i por valor de referencia.
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

/**
* Función que borra un índice del array de avisos por ID.
* \param pArrayAviso, recibe el array de avisos.
* \param limiteAviso, recibe el limite de los avisos.
* \param idABorrar, recibe el ID que va a ser borrado.
* \return (-1) ERROR / 0 OK
*/
int aviso_borrarPorId(Aviso * pArrayAviso, int limiteAviso, int idABorrar)
{
	int retorno = -1;

	for (int i = 0 ; i < limiteAviso ; i++)
	{
		if(pArrayAviso[i].idCliente == idABorrar) // Si el array de avisos, en la posición i del campo idCliente coincide con el idABorrar...
		{
			pArrayAviso[i].isEmpty = TRUE; // Entonces modifico mi flag de isEmpty e indico que ahora sí está vacío.
		}
	}
	retorno = 0;
	return retorno;
}
