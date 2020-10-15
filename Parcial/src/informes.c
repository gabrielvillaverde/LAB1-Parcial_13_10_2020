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
	int buffer;
	int nuevoMaximo;
	int flag = FALSE;

	Cliente auxCliente;

	if (pArrayCliente != NULL && limiteCliente > 0)
	{
		for (int i = 0 ; i < limiteCliente ; i++)
		{
			if(pArrayCliente[i].isEmpty == FALSE) // Si la posición "i" del array de clientes NO está vacía...
			{
				buffer = aviso_contarAvisosPorIdCliente(pArrayAviso, limiteAviso, pArrayCliente[i].idCliente); // Me guardo en buffer lo que devuelve la función de contar avisos por ID
				if(flag == FALSE)
				{
					nuevoMaximo = buffer; // Indico que el nuevo máximo es lo que guarda la variable buffer, que obtuvo de contar avisos por ID del cliente.
					auxCliente = pArrayCliente[i]; // Le asigno a mi variable auxiliar el valor de la posición i del array de clientes.
					flag = TRUE;
				}
				else if(buffer > nuevoMaximo) // Ahora, si lo que obtiene buffer es mayor al máximo existente...
				{
					nuevoMaximo = buffer; // Guardo en mi variable nuevoMaximo el valor de buffer.
					auxCliente = pArrayCliente[i]; // Le asigno a mi variable auxiliar el valor de la posición i del array de clientes.
				}
			}
		}
		printf("\nEl cliente con más avisos es %s %s, con %d avisos", auxCliente.nombre, auxCliente.apellido, nuevoMaximo); // Imprimo los campos correspondientes de mi variable auxiliar auxCliente, junto con el nuevo máximo.
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
		for (int i = 0 ; i < limiteAviso ; i++)
		{
			if(pArrayAviso[i].isEmpty == FALSE && pArrayAviso[i].estado == AVISO_PAUSADO)
			{
				contadorAvisosPausados++;
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
	int nuevoMaximoCantidadDeOcurrencias;
	int rubroConMasAvisos;

	if (pArrayAviso != NULL && limiteAviso > 0)
	{
		// Inicializo el array de rubros en 0.
		for (int indiceRubros = 1; indiceRubros < 1000; indiceRubros++)
		{
			rubros[indiceRubros] = 0;
		}



		// Recorro el array de avisos
		for (int indiceAviso = 0 ; indiceAviso < limiteAviso ; indiceAviso++)
		{
			if(pArrayAviso[indiceAviso].isEmpty == FALSE) // Si el índice en el array de avisos no está vacío...
			{
				// El rubro del aviso actual va a ser el índice del array de rubros
				// En la posicion de ese rubro contabilizo la cantidad de ocurrencias
				int numeroRubro = pArrayAviso[indiceAviso].numeroDeRubro; // Cada número de rubro que encuentro mientras recorro el array de avisos, lo tomo como índice.
				rubros[numeroRubro]++; // Aumenta el contador
			}
		}
		// Termino de recorrer el array de avisos



		// Calculo el máximo recorriendo el array de rubros
		for (int indiceRubros = 1 ; indiceRubros < SIZE_RUBROS ; indiceRubros++)
		{
			if(flag == FALSE) // Si la bandera está en FALSE...
			{
				nuevoMaximoCantidadDeOcurrencias = rubros[indiceRubros]; // Entro al if e indico que en el array de rubros el nuevo máximo es indiceRubros.
				rubroConMasAvisos = indiceRubros; // Indico que el rubro con más avisos es la posición indiceRubros.
				flag = TRUE; // Levanto la flag.
			}
			if(rubros[indiceRubros] > nuevoMaximoCantidadDeOcurrencias) // Si en el array de rubros, el indiceRubros es mayor al nuevoMaximo que tenía anteriormente...
			{
				flag = TRUE;
				nuevoMaximoCantidadDeOcurrencias = rubros[indiceRubros]; // Le asigno a mi nuevo máximo el valor que tiene rubros[indiceRubros]
				rubroConMasAvisos = indiceRubros; // Indico que el rubro con más avisos es la posición indiceRubros.
			}
		}
		//Termino de recorrer el array de rubros
		retorno = 0;
		printf("\nEl rubro con más avisos es %d con una cantidad de: %d \n", rubroConMasAvisos, nuevoMaximoCantidadDeOcurrencias);
	}
	return retorno;
}
