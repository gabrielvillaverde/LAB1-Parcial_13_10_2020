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
* Funci�n que genera un nuevo ID para cada aviso.
* \return ID del aviso.
*/
static int aviso_generarNuevoId (void)
{
	static int id = 0;
	id = id+1;
	return id;
}

/**
* Funci�n que inicializa el array de avisos
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
			pArrayAviso[i].isEmpty = TRUE; // Indico que est�n vac�as TODAS las posiciones del array de avisos.
		}
		retorno = 0;
	}
	return retorno;
}

/**
* Funci�n que da de alta los avisos
* \param pArrayAviso, recibe el array de avisos.
* \param limiteAviso, recibe el limite de los avisos.
* \param pArrayCliente, recibe el array de clientes.
* \param limiteCliente, recibe el limite de los clientes.
* \param indiceAvisos, recibe el �ndice de avisos, el cu�l por los avisos hardcodeados lo inicio en 6.
* \return (-1) ERROR / 0 OK
*/
int aviso_alta (Aviso * pArrayAviso, int limiteAviso, Cliente * pArrayCliente, int limiteCliente, int * indiceAvisos)
{
	int retorno = -1;
	int indice;

	Aviso bufferAviso; // Me creo una variable auxiliar del tipo Aviso.

	if (pArrayAviso != NULL && limiteAviso > 0 && pArrayCliente != NULL && limiteCliente > 0) // Verifico lo que recibo como par�metro.
	{
		if (aviso_buscarLibreRef (pArrayAviso, limiteAviso, &indice) == 0) // Si encontr� un lugar libre en mi array de avisos...
		{
			// Le solicito los datos al usuario y los guardo en cada campo del auxiliar bufferAviso.
			if (utn_getNumberInt("\nIngrese el ID del cliente:\n", "\nError, intente nuevamente.\n", &bufferAviso.idCliente, 2, 0, 9999) == 0 &&
				cliente_buscarIndicePorId(pArrayCliente, limiteCliente, bufferAviso.idCliente, &indice) != -1 && // Si la funci�n de buscar un �ndice por ID me devuelve algo distinto a -1, es porque encontr� un ID.
				utn_getNumberInt("\nIngrese el n�mero de rubro:\n", "\nError, ingrese un n�mero de rubro v�lido entre 0 y 9999.\n",&bufferAviso.numeroDeRubro, 2, 0, 9999) == 0 &&
				utn_getAlphaNum("\nIngrese el texto del aviso:\n", "\nError, ingrese un texto v�lido de m�ximo 64 caracteres:\n", bufferAviso.textoDelAviso, 2, SIZE_TEXTO_AVISO) == 0)
			{
				pArrayAviso[*indiceAvisos] = bufferAviso; // Guardo en el indice de avisos lo que contiene la variable auxiliar bufferAviso.
				pArrayAviso[*indiceAvisos].idAviso = aviso_generarNuevoId(); // Genero un nuevo ID de aviso.
				printf("\nEl ID generado para este aviso es el: %d\n", pArrayAviso[*indiceAvisos].idAviso);
				pArrayAviso[*indiceAvisos].isEmpty = FALSE; // Indico que ese �ndice de mi array de avisos ya no est� vac�o.
				pArrayAviso[*indiceAvisos].estado = AVISO_ACTIVO; // Lo cargo como un aviso activo ya que as� lo pide la consigna.
				*indiceAvisos = *indiceAvisos + 1; // Aumento el contador del �ndice de avisos en 1 y retorno por valor de referencia.
				retorno = 0;
			}
			else
			{
				printf("\nError, ese ID no existe.\n"); // Muestra este mensaje si la funci�n de buscarIndicePorId devuelve un -1, es decir, no existe el �ndice que se corresponde al ID ingresado.
			}
		}
	}
	return retorno;
}

/**
* Funci�n de hardcode. Obligo a mi programa a que inicialice con valores cargados por m� previamente.
* \param pArrayAviso, recibe el array de avisos.
* \param limiteAviso, recibe el limite de los avisos.
* \param numeroDeRubro, recibe el n�mero de rubro.
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
		pArrayAviso[indice].numeroDeRubro = numeroDeRubro; // Asigno en el �ndice de mi array de avisos el n�mero de Rubro. No hace falta strncpy porque se trata de un entero.
		pArrayAviso[indice].idCliente = idCliente;
		strncpy(pArrayAviso[indice].textoDelAviso, textoDelAviso, SIZE_TEXTO_AVISO); // Uso la funci�n de strncpy para copiar en el �ndice del array de avisos el texto del aviso ya que se trata de un char.
		pArrayAviso[indice].idAviso = aviso_generarNuevoId(); // Genero un nuevo ID.
		pArrayAviso[indice].isEmpty = FALSE; // Indico que ese �ndice ya no est� vac�o.
		pArrayAviso[indice].estado = estadoAviso;
		retorno = 0;
	}
	return retorno;
}

/**
* Funci�n que pausa los avisos
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
		aviso_imprimirPorEstado(pArrayAviso, limiteAviso, pArrayCliente, limiteCliente, AVISO_ACTIVO); // Llamo a la funci�n que imprime avisos por estado, en este caso PAUSADO.
		if(	utn_getNumberInt("\nIngrese el ID del aviso que quiere pausar:\n","\nError, ID inv�lido.\n",&idAvisoAPausar,2,0,9999) == 0 &&
			aviso_buscarIndicePorId(pArrayAviso,limiteAviso,idAvisoAPausar,&indiceAPausar) != -1) // Si me devuelve algo distinto a -1, es porque valido correctamente y el ID correspondiente a ese �ndice existe.
		{
			printf("\nEstos son los datos del cliente al que corresponde ese aviso:.\n");
			if(aviso_imprimirPorId(pArrayAviso, limiteAviso, pArrayCliente, limiteCliente, idAvisoAPausar) == 0) // Le muestro los datos del cliente al que corresponden ese aviso llamando a la funci�n que imprime los avisos por ID.
			{
				if(utn_getNumberInt("\n�Desea pausar esta publicaci�n? [1 - SI] - [2 - NO]\n", "Error, ingrese: [1 - SI] - [2 - NO].\n", &opcionDePausar, 2, 1, 2) == 0)
				{
					if(opcionDePausar == 1) // Si el cliente confirma que desea pausar...
					{
						// Busco el ID que quiero pausar.
						if(aviso_buscarIndicePorId(pArrayAviso,limiteAviso,idAvisoAPausar,&indiceAPausar) == 0)
						{
							// Pongo en pausa el aviso.
							pArrayAviso[indiceAPausar].estado = AVISO_PAUSADO; // Pausado.
							printf("\nLa publicaci�n se ha pausado correctamente.\n");
						}
					}
				}
			}
		}
		else
		{
			printf("\nEste aviso ya est� pausado o el ID es inexistente.\n"); // En este caso, la funci�n de buscar un �ndice por ID devuelve -1.
		}
	}
	return retorno;
}

/**
* Funci�n que activa los avisos
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
		aviso_imprimirPorEstado(pArrayAviso, limiteAviso, pArrayCliente, limiteCliente, AVISO_PAUSADO); // Llamo a la funci�n que imprime avisos por estado, en este caso PAUSADO.
		if(	utn_getNumberInt("\nIngrese el ID del aviso que quiere activar:\n","\nError, ID inv�lido.\n",&idAvisoActivar,2,0,9999) == 0 &&
			aviso_buscarIndicePorId(pArrayAviso,limiteAviso,idAvisoActivar,&indiceActivar) != -1) // Si me devuelve algo distinto a -1, es porque valido correctamente y el ID correspondiente a ese �ndice existe.
		{
			if(pArrayAviso[indiceActivar].estado == AVISO_PAUSADO) // Si el estado del �ndice que quiero activar est� pausado...
			{
				printf("\nEstos son los datos del cliente al que corresponde ese aviso:\n");
				if(aviso_imprimirPorId(pArrayAviso, limiteAviso, pArrayCliente, limiteCliente, idAvisoActivar) == 0) // Le muestro los datos del cliente al que corresponden ese aviso llamando a la funci�n que imprime los avisos por ID.
				{
					if(utn_getNumberInt("\n�Desea activar esta publicaci�n? [1 - SI] - [2 - NO]\n", "Error, ingrese: [1 - SI] - [2 - NO].\n", &opcionDeActivar, 2, 1, 2) == 0)
					{
						if(opcionDeActivar == 1)
						{
							// Si el cliente quiere activar la publicaci�n...
							pArrayAviso[indiceActivar].estado = AVISO_ACTIVO; // Pongo el estado del aviso en activo, en la posici�n del �ndice. a activar.
							printf("\nLa publicaci�n se ha activado correctamente.\n");
						}
					}
				}
			}
		}
		else
		{
			printf("\nEste aviso ya est� activo o el ID es inexistente.\n"); // En este caso, la funci�n de buscar un �ndice por ID devuelve -1.
		}
	}
	return retorno;
}

/**
* Funci�n que imprime los avisos.
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
				if(pArrayAviso[i].estado == AVISO_PAUSADO) // Si el estado del aviso est� pausado...
				{
					sprintf(strEstado,"Pausado"); // Cargo la cadena strEstado con "Pausado".
				}
				else // Sino, est� activo, por lo tanto...
				{
					sprintf(strEstado,"Activo"); // Cargo la cadena strEstado con "Activo".
				}
				cliente_buscarIndicePorId(pArrayCliente, limiteCliente, pArrayAviso[i].idCliente, &indiceCliente); // Llamo a la funci�n que busca en mi array de clientes el �ndice por ID del cliente.
				printf("\nID del cliente: %d - ID del aviso: %d - Nombre del cliente: %s - Apellido del cliente: %s - CUIT: %s - N�mero de rubro: %d - Texto del aviso: %s - Estado del aviso: %s", pArrayCliente[indiceCliente].idCliente, pArrayAviso[i].idAviso, pArrayCliente[indiceCliente].nombre, pArrayCliente[indiceCliente].apellido, pArrayCliente[indiceCliente].cuit, pArrayAviso[i].numeroDeRubro, pArrayAviso[i].textoDelAviso, strEstado);
			}
		}
		retorno = 0;
	}
	return retorno;
}

/**
* Funci�n que imprime los avisos por ID.
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
			if(pArrayAviso[i].idAviso == idAviso) // Si la posici�n i de mi array de avisos en el campo idAviso coincide el ID del aviso indicado.
			{
				cliente_buscarIndicePorId(pArrayCliente, limiteCliente, pArrayAviso[i].idCliente, &indiceCliente); // Llamo a la funci�n que busca en mi array de clientes el �ndice por ID del cliente.
				printf("\nID del cliente: %d - ID del aviso: %d - Nombre del cliente: %s - Apellido del cliente: %s - CUIT: %s - N�mero de rubro: %d - Texto del aviso: %s", pArrayCliente[indiceCliente].idCliente, pArrayAviso[i].idAviso, pArrayCliente[indiceCliente].nombre, pArrayCliente[indiceCliente].apellido, pArrayCliente[indiceCliente].cuit, pArrayAviso[i].numeroDeRubro, pArrayAviso[i].textoDelAviso);
			}
		}
		retorno = 0;
	}
	return retorno;
}

/**
* Funci�n que imprime todos los avisos activos por ID del cliente.
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
			if(pArrayAviso[i].idCliente == idCliente) // Si la posici�n i de mi array de avisos en el campo idCliente coincide el ID del cliente indicado...
			{
				if(pArrayAviso[i].estado == AVISO_ACTIVO) // Si el estado del aviso est� activo...
				{
					sprintf(strEstado,"Activo"); // Cargo la cadena strEstado con "Activo".
					contadorAvisosActivos++; // Y aumento el contador de avisos activos.
					cliente_buscarIndicePorId(pArrayCliente, limiteCliente, pArrayAviso[i].idCliente, &indiceCliente); // Llamo a la funci�n que busca en mi array de clientes el �ndice por ID del cliente.
					printf("\nN�mero de rubro: %d - Texto del aviso: %s - Estado: %s\n", pArrayAviso[i].numeroDeRubro, pArrayAviso[i].textoDelAviso, strEstado); // Imprimo
				}
			}
		}
		printf("\nLa cantidad de avisos activos que posee son: %d\n", contadorAvisosActivos); // Le muestro al usuario la cantidad de avisos activos que posee.
		retorno = 0;
	}
	return retorno;
}

/**
* Funci�n que imprime todos los avisos por ID del cliente.
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
			if(pArrayAviso[i].idCliente == idCliente) // Si la posici�n i de mi array de avisos en el campo idCliente coincide el ID del cliente indicado...
			{
				cliente_buscarIndicePorId(pArrayCliente, limiteCliente, pArrayAviso[i].idCliente, &indiceCliente); // Llamo a la funci�n que busca en mi array de clientes el �ndice por ID del cliente.
				if(pArrayAviso[i].estado == AVISO_ACTIVO) // Si el estado del aviso est� activo...
				{
					sprintf(strEstado,"Activo"); // Cargo la cadena strEstado con "Activo".
				}
				else if (pArrayAviso[i].estado == AVISO_PAUSADO) // En cambio si el estado del aviso est� pausado...
				{
					sprintf(strEstado,"Pausado"); // Cargo la cadena strEstado con "Pausado".
				}
				printf("\nN�mero de rubro: %d - Texto del aviso: %s - Estado: %s\n", pArrayAviso[i].numeroDeRubro, pArrayAviso[i].textoDelAviso, strEstado); // Imprimo.
			}
		}
		retorno = 0;
	}
	return retorno;
}

/**
* Funci�n que cuenta la cantidad de avisos por ID del cliente.
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
			if(pArrayAviso[i].idCliente == idCliente) // Si la posici�n i de mi array de avisos en el campo idCliente coincide el ID del cliente indicado...
			{
				contadorAvisos++; // Aumento el contador de avisos.
			}
		}
	}
	return contadorAvisos;
}

/**
* Funci�n que imprime los avisos por estado.
* \param pArrayAviso, recibe el array de avisos.
* \param limiteAviso, recibe el limite de los avisos.
* \param pArrayCliente, recibe el array de clientes.
* \param limiteCliente, recibe el limite de los clientes.
* \param estadoAviso, recibe el estado por el cu�l quiere imprimir, si pausado o activo.
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
				printf("\nID del cliente: %d - ID del aviso: %d - Nombre del cliente: %s - Apellido del cliente: %s - CUIT: %s - N�mero de rubro: %d - Texto del aviso: %s - Estado del aviso: %s\n", pArrayCliente[indiceCliente].idCliente, pArrayAviso[i].idAviso, pArrayCliente[indiceCliente].nombre, pArrayCliente[indiceCliente].apellido, pArrayCliente[indiceCliente].cuit, pArrayAviso[i].numeroDeRubro, pArrayAviso[i].textoDelAviso, strEstado);
			}
		}
		retorno = 0;
	}
	return retorno;
}

/**
* Funci�n que busca un lugar libre en el array de avisos, devuelve el �ndice por valor de retorno.
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
			if(pArrayAviso[i].isEmpty == TRUE) // Si el array de avisos en la posici�n i est� vac�o...
			{
				retorno = i; // Devuelvo i por valor de retorno.
				break;
			}
		}
	}
	return retorno;
}

/**
* Funci�n que busca un lugar libre en el array de avisos, devuelve el valor por referencia
* \param pArrayAviso, recibe el array de avisos.
* \param limiteAviso, recibe el limite de los avisos.
* \param pIndice, es el puntero al �ndice que se est� buscando, devuelve el �ndice por valor de referencia.
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
			if(pArrayAviso[i].isEmpty == TRUE) // Si el array de avisos en la posici�n i est� vac�o...
			{
				*pIndice = i; // Devuelvo por valor de referencia esa posici�n
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

/**
* Funci�n que busca el �ndice en el array de avisos por ID.
* \param pArrayAviso, recibe el array de avisos.
* \param limiteAviso, recibe el limite de los avisos.
* \param idBuscado, recibe el ID que se est� buscando.
* \param pIndice, es el puntero al �ndice que se est� buscando, devuelve el �ndice por valor de referencia.
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
			if(pArrayAviso[i].isEmpty == FALSE && pArrayAviso[i].idAviso == idBuscado) // Si la posici�n i del array no est� vac�a, y adem�s coincide en el campo idAviso con el idBuscado...
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
* Funci�n que borra un �ndice del array de avisos por ID.
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
		if(pArrayAviso[i].idCliente == idABorrar) // Si el array de avisos, en la posici�n i del campo idCliente coincide con el idABorrar...
		{
			pArrayAviso[i].isEmpty = TRUE; // Entonces modifico mi flag de isEmpty e indico que ahora s� est� vac�o.
		}
	}
	retorno = 0;
	return retorno;
}
