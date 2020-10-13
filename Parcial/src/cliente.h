/*
 * cliente.h
 *
 *  Created on: 1 oct. 2020
 *      Author: Hzkr
 */

#ifndef CLIENTE_H_
#define CLIENTE_H_

#define SIZE_NOMBRE 50
#define SIZE_APELLIDO 50
#define SIZE_CUIT 14
#define TRUE 1
#define FALSE 0

typedef struct
{
	char nombre [SIZE_NOMBRE];
	char apellido [SIZE_APELLIDO];
	char cuit [SIZE_CUIT];
	int idCliente;
	int isEmpty;
} Cliente;

int cliente_init(Cliente * pArrayCliente, int limiteCliente);
int cliente_alta (Cliente * pArrayCliente, int limiteCliente);
int cliente_altaForzada(Cliente * pArrayCliente, int limiteCliente, char * nombre, char * apellido, char * cuit);
//int cliente_baja (Cliente * pArrayCliente, int limiteCliente);
int cliente_modificar (Cliente * pArrayCliente, int limiteCliente);
int cliente_imprimir (Cliente * pArrayCliente , int limiteCliente);
int cliente_buscarLibre (Cliente * pArrayCliente, int limiteCliente);
int cliente_buscarLibreRef (Cliente * pArrayCliente, int limiteCliente, int * pIndice);
int cliente_buscarIndicePorId (Cliente * pArrayCliente, int limiteCliente, int idBuscado, int * pIndice);

#endif /* CLIENTE_H_ */
