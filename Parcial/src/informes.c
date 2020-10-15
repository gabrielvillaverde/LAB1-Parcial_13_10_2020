/*
 * informes.c
 *
 *  Created on: 10 oct. 2020
 *      Author: Hzkr
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utn.h"
#include "cliente.h"
#include "aviso.h"
#include "informes.h"

#define SIZE_RUBROS 1000

/**
* Función que calcula el cliente con más avisos
* \param pArrayCliente, recibe el array de clientes
* \param limiteCliente, recibe el limite de los clientes
* \param pArrayAviso, recibe el array de avisos
* \param limiteAviso, recibe el limite de los avisos
 * return (-1) ERROR / 0 OK
 */
int informes_calcularClienteConMasAvisos (Cliente * pArrayCliente, int limiteCliente, Aviso * pArrayAviso, int limiteAviso)
{
	int retorno = -1;
	int cantidadAvisosPorIdCliente;
	int maximaCantidadAvisos;
	int flag = FALSE;

	Cliente auxCliente;

	if (pArrayCliente != NULL && limiteCliente > 0 && pArrayAviso != NULL && limiteAviso > 0)
	{
		for (int i = 0 ; i < limiteCliente ; i++) // Recorro el array de clientes...
		{
			if(pArrayCliente[i].isEmpty == FALSE) // Si el índice del array de clientes NO está vacío...
			{
				cantidadAvisosPorIdCliente = aviso_contarAvisosPorIdCliente(pArrayAviso, limiteAviso, pArrayCliente[i].idCliente); // Me guardo en la variable auxiliar lo que devuelve la función de contar avisos por ID de cliente.
				if(flag == FALSE)
				{
					maximaCantidadAvisos = cantidadAvisosPorIdCliente; // Indico que la máxima cantidad de avisos es lo que guarda la variable auxiliar, que obtuvo de contar avisos por ID del cliente.
					auxCliente = pArrayCliente[i]; // Le asigno a mi otra variable auxiliar el índice del array de clientes.
					flag = TRUE; // Levanto la bandera.
				}
				else if(cantidadAvisosPorIdCliente > maximaCantidadAvisos) // Ahora, si en la próxima iteración cantidadAvisosPorIdCliente es mayor a la máxima cantidad de avisos existente...
				{
					maximaCantidadAvisos = cantidadAvisosPorIdCliente; // Guardo en mi variable maximaCantidadAvisos el valor de cantidadAvisosPorIdCliente.
					auxCliente = pArrayCliente[i]; // Le asigno a mi otra variable auxiliar el índice del array de clientes.
				}
			}
		}
		printf("\nEl cliente con más avisos es %s %s, con %d avisos", auxCliente.nombre, auxCliente.apellido, maximaCantidadAvisos); // Imprimo los campos correspondientes de mi variable auxiliar auxCliente, junto con el nuevo máximo.
		retorno = 0;
	}
	return retorno;
}

/**
* Función que calcula el cliente con más avisos POR ESTADO
* \param pArrayCliente, recibe el array de clientes
* \param limiteCliente, recibe el limite de los clientes
* \param pArrayAviso, recibe el array de avisos
* \param limiteAviso, recibe el limite de los avisos
* \param estadoAviso, recibe el estado (ACTIVO/PAUSADO)
* \return (-1) ERROR / 0 OK
*/
int informes_calcularClienteConMasAvisosPorEstado (Cliente * pArrayCliente, int limiteCliente, Aviso * pArrayAviso, int limiteAviso, int estadoAviso)
{
	int retorno = -1;
	int cantidadAvisosPorEstadoPorIdCliente;
	int maximaCantidadAvisosPorEstado;
	int flag = FALSE;
	char strEstado[10];

	Cliente auxCliente;

	if (pArrayCliente != NULL && limiteCliente > 0 && pArrayAviso != NULL && limiteAviso > 0)
	{
		for (int i = 0 ; i < limiteCliente ; i++) // Recorro el array de clientes...
		{
			if(pArrayCliente[i].isEmpty == FALSE) // Si el índice del array de clientes NO está vacío...
			{
				cantidadAvisosPorEstadoPorIdCliente = aviso_contarAvisosPorEstadoPorIdCliente(pArrayAviso, limiteAviso, pArrayCliente[i].idCliente, estadoAviso); // Me guardo en la variable auxiliar lo que devuelve la función de contar avisos por estado por ID de cliente.
				if(flag == FALSE)
				{
					maximaCantidadAvisosPorEstado = cantidadAvisosPorEstadoPorIdCliente; // Indico que la máxima cantidad de avisos es lo que guarda la variable auxiliar, que obtuvo de contar avisos por ID del cliente.
					auxCliente = pArrayCliente[i]; // Le asigno a mi otra variable auxiliar el índice del array de clientes.
					flag = TRUE; // Levanto la bandera.
				}
				else if(cantidadAvisosPorEstadoPorIdCliente > maximaCantidadAvisosPorEstado) // Ahora, si en la próxima iteración cantidadAvisosPorIdCliente es mayor a la máxima cantidad de avisos existente...
				{
					maximaCantidadAvisosPorEstado = cantidadAvisosPorEstadoPorIdCliente; // Guardo en mi variable maximaCantidadAvisos el valor de cantidadAvisosPorIdCliente.
					auxCliente = pArrayCliente[i]; // Le asigno a mi otra variable auxiliar el índice del array de clientes.
				}
			}
		}
		if(estadoAviso == AVISO_ACTIVO) // Si el estado del aviso está activo...
		{
			sprintf(strEstado,"activos"); // Cargo la cadena strEstado con "Activos".
		}
		else if (estadoAviso == AVISO_PAUSADO) // En cambio si el estado del aviso está pausado...
		{
			sprintf(strEstado,"pausados"); // Cargo la cadena strEstado con "Pausados".
		}
		printf("\nEl cliente con más avisos %s es %s %s, con %d avisos", strEstado, auxCliente.nombre, auxCliente.apellido, maximaCantidadAvisosPorEstado); // Imprimo los campos correspondientes de mi variable auxiliar auxCliente, junto con el nuevo máximo.
		retorno = 0;
	}
	return retorno;
}


/**
* Función que calcula la cantidad de avisos pausados
* \param pArrayAviso, recibe el array de avisos
* \param limiteAviso, recibe el limite de los avisos
 * return (-1) ERROR / 0 OK
 */
int informes_calcularCantidadDeAvisosPausados (Aviso * pArrayAviso, int limiteAviso)
{
	int retorno = -1;
	int contadorAvisosPausados = 0;

	if (pArrayAviso != NULL && limiteAviso > 0)
	{
		for (int i = 0 ; i < limiteAviso ; i++) // Recorro el array de avisos
		{
			if(pArrayAviso[i].isEmpty == FALSE && pArrayAviso[i].estado == AVISO_PAUSADO) // Si el índice del array de avisos no está vacío y además su estado es pausado...
			{
				contadorAvisosPausados++; // Aumento el contador de avisos pausados.
			}
		}
		printf("\nLa cantidad de avisos pausados es: %d", contadorAvisosPausados);
		retorno = 0;
	}
	return retorno;
}


/**
* Función que calcula el rubro con más avisos
* \param pArrayAviso, recibe el array de avisos
* \param limiteAviso, recibe el limite de los avisos
 * return (-1) ERROR / 0 OK
 */
int informes_calcularRubroConMasAvisos (Aviso * pArrayAviso, int limiteAviso)
{
	int retorno = -1;
	int rubros[SIZE_RUBROS]; // Declaro un array de rubros máximos
	int flag = FALSE;
	int maximaCantidadDeOcurrencias;
	int rubroConMasAvisos;

	if (pArrayAviso != NULL && limiteAviso > 0)
	{
		// Inicializo el array de rubros en 0.
		for (int indiceRubros = 1 ; indiceRubros < 1000 ; indiceRubros++)
		{
			rubros[indiceRubros] = 0; // Lo inicializo en 0 para luego contar
		}



		// Recorro el array de avisos
		for (int indiceAviso = 0 ; indiceAviso < limiteAviso ; indiceAviso++)
		{
			if(pArrayAviso[indiceAviso].isEmpty == FALSE) // Si el índice en el array de avisos no está vacío...
			{
				// El rubro del aviso actual va a ser el índice del array de rubros
				// En la posicion de ese rubro contabilizo la cantidad de ocurrencias
				int numeroRubro = pArrayAviso[indiceAviso].numeroDeRubro; // Cada número de rubro que encuentro mientras recorro el array de avisos, lo tomo como índice.
				rubros[numeroRubro]++; // Y aumento el contador
			}
		}
		// Termino de recorrer el array de avisos



		// Calculo el máximo recorriendo el array de rubros
		for (int indiceRubros = 1 ; indiceRubros < SIZE_RUBROS ; indiceRubros++)
		{
			if(flag == FALSE) // Si la bandera está en FALSE...
			{
				maximaCantidadDeOcurrencias = rubros[indiceRubros]; // Entro al if e indico que el máximo es indiceRubros.
				rubroConMasAvisos = indiceRubros; // Indico que el rubro con más avisos es la posición indiceRubros.
				flag = TRUE; // Levanto la flag.
			}
			if(rubros[indiceRubros] > maximaCantidadDeOcurrencias) // Si en el array de rubros, el indiceRubros es mayor al nuevoMaximo que tenía anteriormente...
			{
				flag = TRUE;
				maximaCantidadDeOcurrencias = rubros[indiceRubros]; // Le asigno a la máxima cantidad de ocurrencias el valor que tiene rubros[indiceRubros]
				rubroConMasAvisos = indiceRubros; // Indico que el rubro con más avisos es la posición indiceRubros.
			}
		}
		// Termino de recorrer el array de rubros
		retorno = 0;
		printf("\nEl rubro con más avisos es %d con una cantidad de: %d \n", rubroConMasAvisos, maximaCantidadDeOcurrencias);
	}
	return retorno;
}


