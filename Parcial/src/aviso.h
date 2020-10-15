/*
 * aviso.h
 *
 *  Created on: 6 oct. 2020
 *      Author: Hzkr
 */

#ifndef AVISO_H_
#define AVISO_H_

#define SIZE_TEXTO_AVISO 64
#define TRUE 1
#define FALSE 0
#define AVISO_PAUSADO 0
#define AVISO_ACTIVO 1

#include "cliente.h" // Si no lo incluyo, no reconoce el tipo de dato Cliente en mis funciones.

typedef struct
{
	int numeroDeRubro;
	char textoDelAviso [SIZE_TEXTO_AVISO];
	int isEmpty;
	int estado;
	int idAviso;
	int idCliente; // Nos permite relacionar con la otra entidad
} Aviso;

int aviso_init(Aviso * pArrayAviso, int limiteAviso);
// int aviso_alta (Aviso * pArrayAviso, int limiteAviso, Cliente * pArrayCliente, int limiteCliente);
int aviso_alta (Aviso * pArrayAviso, int limiteAviso, Cliente * pArrayCliente, int limiteCliente, int * indiceAvisos);
int aviso_altaForzada(Aviso * pArrayAviso, int limiteAviso, int numeroDeRubro, char * textoDelAviso, int idCliente, int estadoAviso);
// int aviso_baja (Aviso * pArrayAviso, int limiteAviso, Cliente * pArrayCliente, int limiteCliente);
// int aviso_modificar (Aviso * pArrayAviso, int limiteAviso, Cliente * pArrayCliente, int limiteCliente);
int aviso_pausar (Aviso * pArrayAviso, int limiteAviso, Cliente * pArrayCliente, int limiteCliente);
int aviso_activar (Aviso * pArrayAviso, int limiteAviso, Cliente * pArrayCliente, int limiteCliente);
int aviso_imprimir (Aviso * pArrayAviso , int limiteAviso, Cliente * pArrayCliente, int limiteCliente);
int aviso_imprimirPorIdAviso (Aviso * pArrayAviso, int limiteAviso, Cliente * pArrayCliente, int limiteCliente, int idAviso);
int aviso_imprimirPorEstado (Aviso * pArrayAviso, int limiteAviso, Cliente * pArrayCliente, int limiteCliente, int estadoAviso);
int aviso_imprimirAvisoActivoPorIdCliente (Aviso * pArrayAviso, int limiteAviso, Cliente * pArrayCliente, int limiteCliente, int idCliente);
int aviso_imprimirTodosLosAvisosPorIdCliente (Aviso * pArrayAviso, int limiteAviso, Cliente * pArrayCliente, int limiteCliente, int idCliente);
int aviso_contarAvisosPorIdCliente (Aviso * pArrayAviso, int limiteAviso, int idCliente);
int aviso_contarAvisosActivosPorIdCliente (Aviso * pArrayAviso, int limiteAviso, int idCliente, int estadoAviso);
int aviso_contarAvisosPorEstadoPorIdCliente (Aviso * pArrayAviso, int limiteAviso, int idCliente, int estadoAviso);
int aviso_buscarLibre (Aviso * pArrayAviso, int limiteAviso);
int aviso_buscarLibreRef (Aviso * pArrayAviso, int limiteAviso, int * pIndice);
int aviso_buscarIndicePorId (Aviso * pArrayAviso, int limiteAviso, int idBuscado, int * pIndice);
int aviso_borrarPorIdCliente(Aviso * pArrayAviso, int limiteAviso, int idClienteABorrar);

#endif /* AVISO_H_ */
