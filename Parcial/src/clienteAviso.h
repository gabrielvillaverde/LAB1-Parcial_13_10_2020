/*
 * clienteAviso.h
 *
 *  Created on: 11 oct. 2020
 *      Author: Hzkr
 */

#ifndef CLIENTEAVISO_H_
#define CLIENTEAVISO_H_

#include "cliente.h"
#include "aviso.h"

int clienteAviso_baja (Aviso * pArrayAviso, int limiteAviso, Cliente * pArrayCliente, int limiteCliente);
int clienteAviso_avisosActivosImprimir (Cliente * pArrayCliente, int limiteCliente, Aviso * pArrayAviso, int limiteAviso);
int clienteAviso_calcularClienteConMasAvisos (Cliente * pArrayCliente, int limiteCliente, Aviso * pArrayAviso, int limiteAviso);

#endif /* CLIENTEAVISO_H_ */
