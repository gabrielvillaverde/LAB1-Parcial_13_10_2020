/*
 * utn.h
 *      Author: Hzkr
 */

#ifndef UTN_H_
#define UTN_H_

	int utn_getNumberInt(char* pMensaje, char* pMensajeError, int* pResultado, int reintentos, int minimo, int maximo);
	int utn_getNumberFloat(char* pMensaje, char* pMensajeError, float* pResultado, int reintentos, float minimo, float maximo);
	int utn_getChar(char* pMensaje, char* pMensajeError, char* pResultado, int reintentos, int limite);
	int utn_getName(char* pMensaje, char* pMensajeError, char* pResultado, int reintentos, int limite);
	int utn_getAlphaNum(char* pMensaje, char* pMensajeError, char* pResultado, int reintentos, int limite);
	int utn_getCuit(char* pMensaje, char* pMensajeError, char* pResultado, int reintentos, int limite);

#endif /* UTN_H_ */
