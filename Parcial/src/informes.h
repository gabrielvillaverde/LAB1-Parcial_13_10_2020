/*
 * informes.h
 *
 *  Created on: 10 oct. 2020
 *      Author: Hzkr
 */

#ifndef INFORMES_H_
#define INFORMES_H_

#include "cliente.h"
#include "aviso.h"

int informes_calcularClienteConMasAvisos (Cliente * pArrayCliente, int limiteCliente, Aviso * pArrayAviso, int limiteAviso);
int informes_calcularCantidadDeAvisosPausados (Aviso * pArrayAviso, int limiteAviso);
int informes_calcularRubroConMasAvisos (Aviso * pArrayAviso, int limiteAviso);

#endif /* INFORMES_H_ */
