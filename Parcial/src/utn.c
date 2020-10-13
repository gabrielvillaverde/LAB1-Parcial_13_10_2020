/*
 * utn.c
 *
 *  Created on: 9 sep. 2020
 *      Author: Hzkr
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int isNumber(char cadena[]);
static int getInt(int* pResultado);
static int myGets(char array[], int longitud);
static int utn_itIsAValidName(char array[], int limite);
static int isOnlyLettersAndSpace(char cadena[]);
static int isAlphNum(char cadena[]);
static int getFloat(float* pResultado);
static int isNumberFloat(char cadena[]);
static int isCuit(char cadena[]);

#define LIMITE_BUFFER_STRING 1000

/**
 * \brief Lee de stdin hasta que encuentra un '\n' o hasta que haya copiado en cadena un maximo de 'longitud -1' caracteres.
 * \param pResultado Puntero al espacio de memoria donde se copiará la cadena obtenida
 * \param longitud Define el tamaño de cadena
 * \return Retorna 0 EXITO / (-1) ERROR
 */
static int myGets(char array[], int longitud)
{
	fflush(stdin);
	fgets(array, longitud, stdin);
	array[strlen(array)-1]= '\0';
	return 0;
}

/**
 * Función que obtiene un número entero
 *\param mensaje es el puntero del mensaje que se le pide al usuario.
 *\param mensajeError es el puntero del mensaje de error que se le muestra al usuario.
 *\param pResultado es el puntero que guarda lo escrito en buffer y lo escribe en la dirección de memoria de una variable externa de la función
 *\param minimo es el valor mínimo entre todas las opciones que el usuario tiene para ingresar.
 *\param maximo es el valor maximo entre todas las opciones que el usuario tiene para ingresar.
 *\param reintentos es la cantidad de reintentos que el usuario tiene para hacer.
 *\return retorna como valor por defecto un -1 para indicar error, si el número ingresado está entre el rango del mínimo y el máximo, devuelve un return en 0.
 */
int utn_getNumberInt(char* pMensaje, char* pMensajeError, int* pResultado, int reintentos, int minimo, int maximo)
{
	int retorno = -1;
	int buffer;

	if(		pMensaje != NULL &&
			pMensajeError != NULL &&
			pResultado != NULL &&
			reintentos >= 0 &&
			minimo <= maximo)
	{
		do
		{
			printf("%s", pMensaje);
			fflush(stdin);
			if(getInt(&buffer) == 0 && buffer >= minimo && buffer <= maximo)
			{
				*pResultado = buffer;
				retorno = 0;
				break;
			}
			else
			{
				printf("%s", pMensajeError);
				reintentos--;
			}
		}
		while(reintentos >= 0);
		if(reintentos < 0)
		{
			printf("\nNo quedan intentos.\n");
		}
	}
	return retorno;
}

/**
 * Función que se encarga de obtener un número entero
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \return Retorna 0 (EXITO) si se obtiene un numero entero y -1 (ERROR) si no
 */
static int getInt(int* pResultado)
{
	int retorno = -1;
	char buffer[LIMITE_BUFFER_STRING];
	fflush(stdin);

	fgets(buffer, LIMITE_BUFFER_STRING, stdin);
	buffer[strlen(buffer)-1]= '\0';
	if(isNumber(buffer))
	{
		retorno = 0;
		*pResultado = atoi(buffer);
	}
	return retorno;
}

/**
 * Función que verifica si la cadena ingresada es numérica
 * \param cadena Cadena de caracteres a ser analizada
 * \return Retorna 1 (vardadero) si la cadena es numerica y 0 (falso) si no lo es
 */
static int isNumber(char cadena[])
{
	int retorno = 1;
	int i = 0;

	if(cadena[0] == '-')
	{
		i = 1;
	}
	for( ; cadena[i] != '\0'; i++)
	{
		if(cadena[i] < '0' || cadena[i] > '9')
		{
			retorno = 0;
			break;
		}
	}
	return retorno;
}

/**
 * Función que obtiene un número flotante
 *\param mensaje es el puntero del mensaje que se le pide al usuario.
 *\param mensajeError es el puntero del mensaje de error que se le muestra al usuario.
 *\param pResultado es el puntero que guarda lo escrito en buffer y lo escribe en la dirección de memoria de una variable externa de la función
 *\param minimo es el valor mínimo entre todas las opciones que el usuario tiene para ingresar.
 *\param maximo es el valor maximo entre todas las opciones que el usuario tiene para ingresar.
 *\param reintentos es la cantidad de reintentos que el usuario tiene para hacer.
 *\return retorna como valor por defecto un -1 para indicar error, si el número ingresado está entre el rango del mínimo y el máximo, devuelve un return en 0.
 */
int utn_getNumberFloat(char* pMensaje, char* pMensajeError, float* pResultado, int reintentos, float minimo, float maximo)
{
	int retorno = -1;
	float bufferFloat;

	if(pResultado != NULL && pMensaje != NULL && pMensajeError != NULL && minimo <= maximo && reintentos >= 0)
	{
		do
		{
			printf("%s\n", pMensaje);
			fflush(stdin);
			if(getFloat(&bufferFloat) == 0 && bufferFloat >= minimo && bufferFloat <= maximo)
			{
				*pResultado = bufferFloat;
				retorno = 0;
				break;
			}
			else
			{
				printf("%s\n", pMensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);
		if(reintentos < 0)
		{
			printf("No attempts left.\n");
		}
	}
	return retorno;
}

/**
 * Función que verifica si la cadena ingresada es flotante
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \return Retorna 0 (EXITO) si se obtiene un numero flotante y -1 (ERROR) si no
 *
 */
static int getFloat(float* pResultado)
{
	int retorno = -1;
	char buffer[LIMITE_BUFFER_STRING];
	fflush(stdin);

	fgets(buffer, LIMITE_BUFFER_STRING, stdin);
	buffer[strlen(buffer)-1]= '\0';
	if(isNumberFloat(buffer))
	{
		retorno = 0;
		*pResultado = atof(buffer);
	}
	return retorno;
}

/**
 * Función que verifica si la cadena ingresada es numerica, y puede contener un signo/punto en el primer índice
 * \param cadena char Cadena de caracteres a ser analizada
 * \return 1 EXITO / (0) ERROR
 */
static int isNumberFloat(char cadena[])
{
	int retorno = 1;
	int i = 0;
	int flagPunto = 0;

	if(cadena[0] == '-')
	{
		i = 1;
	}
	for( ; cadena[i] != '\0'; i++)
	{
		if((cadena[i] < '0' || cadena[i] > '9') && (cadena[i] != '.'))
		{
			retorno = 0;
			break;
		}
		if(cadena[i] == '.')
		{
			flagPunto++;
		}
		if(flagPunto > 1)
		{
			retorno = 0;
			break;
		}
	}
	return retorno;
}

/**
* Función que solicita un nombre al usuario
* \param char* pMensaje es el mensaje que se le muestra al usuario
* \param char* pMensajeError es el mensaje de error que se le muestra al usuario
* \param char* pResultado es el puntero al espacio de memoria donde se dejará el valor obtenido
* \param int reintentos es la cantidad de oportunidades que tiene el usuario para ingresar el dato
* \param limite indica la cantidad máxima de caracteres que puede recibir el nombre
 * return (-1) ERROR / 0 OK
 */
int utn_getName(char* pMensaje, char* pMensajeError, char* pResultado, int reintentos, int limite)
{
	char bufferString[LIMITE_BUFFER_STRING];
	int retorno = -1;
	if(pMensaje != NULL && pMensajeError != NULL && pResultado != NULL && reintentos >= 0 && limite > 0)
	{
		do
		{
			printf("%s", pMensaje);
			if(	(myGets(bufferString, LIMITE_BUFFER_STRING)== 0) &&
				(strnlen(bufferString, sizeof(bufferString)-1) <= limite) &&
				(utn_itIsAValidName(bufferString, limite) != 0))
			{
				strncpy(pResultado, bufferString, limite);
				retorno = 0;
				break;
			}
			else
			{
				printf("%s", pMensajeError);
				reintentos--;
			}
		}while(reintentos>=0);
		if(reintentos < 0)
		{
			printf("No attempts left.\n");
		}
	}
	return retorno;
}

/**
* Función que verifica una cadena como parámetro para determinar si es nombre valido
* \param char cadena[], cadena a analizar
* \param limite indica la cantidad maxima del nombre
 * return (1) Es válido / (0) No es un nombre valido
 */
static int utn_itIsAValidName(char array[], int limite)
{
	int retorno = 1; // TODO OK

	for(int i = 0; i <= limite && array[i] != '\0'; i++)
	{
		if(isOnlyLettersAndSpace(array) == 0)
		{
			retorno = 0;
			break;
		}
	}
	return retorno;
}

/**
 * Función que verifica si la cadena ingresada son letras
 * \param cadena Cadena de caracteres a ser analizada
 * \return 1 EXITO / (0) ERROR
 */
static int isOnlyLettersAndSpace(char cadena[])
{
	int retorno = 1;
	int i;

	for(i=0 ; cadena[i] != '\0'; i++)
	{
		if((cadena[i] < 'A' || cadena[i] > 'Z') &&
			(cadena[i] < 'a' || cadena[i] > 'z') &&
			(cadena[i] != ' ') &&
			(cadena[i] < 'á' || cadena[i] > 'ú') &&
			(cadena[i] != 'é'))
		{
			retorno = 0;
			break;
		}
	}
	return retorno;
}

/*
* Función que solicita un char al usuario
* \param char* pMensaje, Es el mensaje mostrado al usuario
* \param char* pMensajeError, Es el mensaje de error a ser mostrado al usuario
* \param char* pResultado, puntero al espacio de memoria donde se dejara el valor obtenido
* \param int reintentos, cantidad de oportunidades para ingresar el dato
* \param char minimo, valor minimo admitido
* \param char maximo, valor maximo admitido
 * return (-1) ERROR / 0 OK
 */
int utn_getChar(char* pMensaje, char* pMensajeError, char* pResultado, int reintentos, int limite)
{
	int retorno = -1;
	char bufferString[LIMITE_BUFFER_STRING];

	if(pMensaje != NULL && pResultado != NULL && pMensajeError != NULL && reintentos >= 0 && limite > 0 )
	{
		do
		{
			printf("%s", pMensaje);
			if(	(myGets(bufferString, LIMITE_BUFFER_STRING)== 0) &&
				(strnlen(bufferString, sizeof(bufferString)-1) <= limite))
			{
				strncpy(pResultado, bufferString, limite);
				retorno = 0;
				break;
			}
			else
			{
				printf("%s", pMensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);
		if(reintentos < 0)
		{
			printf("No quedan más intentos\n");
		}
	}
	return retorno;
}

/*
* Función que solicita numeros, letras y espacio al usuario
* \param char* pMensaje, Es el mensaje mostrado al usuario
* \param char* pMensajeError, Es el mensaje de error a ser mostrado al usuario
* \param char* pResultado, puntero al espacio de memoria donde se dejara el valor obtenido
* \param int reintentos, cantidad de oportunidades para ingresar el dato
* \param int limite, cantidad de espacio que puede almacenar la variable
 * return (-1) ERROR / 0 OK
 */
int utn_getAlphaNum(char* pMensaje, char* pMensajeError, char* pResultado, int reintentos, int limite)
{
	int retorno = -1;
	char bufferString[LIMITE_BUFFER_STRING];

	if(pMensaje != NULL && pResultado != NULL && pMensajeError != NULL && reintentos >= 0 && limite > 0 )
	{
		do
		{
			printf("%s", pMensaje);
			if(	(myGets(bufferString, LIMITE_BUFFER_STRING) == 0) &&
				(strnlen(bufferString, sizeof(bufferString)-1) <= limite) &&
				(isAlphNum(bufferString) == 1))
			{
				strncpy(pResultado, bufferString, limite);
				retorno = 0;
				break;
			}
			else
			{
				printf("%s", pMensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);
		if(reintentos < 0)
		{
			printf("\nNo quedan más intentos.\n");
		}
	}
	return retorno;
}

/**
 * Función que verifica si la cadena son numeros, letras con o sin tilde y un espacio
 * \param cadena, Cadena de caracteres a ser analizada
 * \return 1 EXITO / (0) ERROR
 */
static int isAlphNum(char cadena[])
{
	int retorno = 1; // Todo OK.
	int i;

	for(i=0 ; cadena[i] != '\0' ; i++)
	{
		if((cadena[i] < 'A' || cadena[i] > 'Z') &&
			(cadena[i] < 'a' || cadena[i] > 'z') &&
			(cadena[i] != ' ') &&
			(cadena[i] != '.') &&
			(cadena[i] != '-') &&
			(cadena[i] != ',') &&
			(cadena[i] < 'á' || cadena[i] > 'ú') &&
			(cadena[i] != 'é') &&
			(cadena[i] < '0' || cadena[i] > '9'))
		{
			retorno = 0; // ERROR.
			break;
		}
	}
	return retorno;
}

/**
 * Función que obtiene un CUIT
 * \param pMensaje - Es el mensaje que se le muestra al usuario para que ingrese el CUIT
 * \param pMensajeError - Es el mensaje de error que se le muestra al usuario
 * \param pResultado - Es el puntero que guarda lo escrito en bufferString y lo escribe en la dirección de memoria de una variable externa de la función
 * \param reintentos - Es la cantidad de reintentos que tiene el usuario para ingresar el CUIT
 * \param limite - Indica la cantidad máxima de caracteres que puede recibir
 * \return - 1 (EXITO) / 0 (ERROR)
 */
int utn_getCuit(char* pMensaje, char* pMensajeError, char* pResultado, int reintentos, int limite)
{
	int retorno = -1;
	char bufferString[LIMITE_BUFFER_STRING];

	if(pMensaje != NULL && pResultado != NULL && pMensajeError != NULL && reintentos >= 0 && limite > 0 )
	{
		do
		{
			printf("%s", pMensaje);
			if(	(myGets(bufferString, LIMITE_BUFFER_STRING) == 0) &&
				(strnlen(bufferString, sizeof(bufferString)-1) <= limite) &&
				(isCuit(bufferString) == 1))
			{
				strncpy(pResultado, bufferString, limite);
				retorno = 0;
				break;
			}
			else
			{
				printf("%s", pMensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);
		if(reintentos < 0)
		{
			printf("\nNo quedan más intentos.\n");
		}
	}
	return retorno;
}

/**
 * Función que verifica si la cadena son números, y guines
 * \param cadena - Cadena de caracteres a ser analizada
 * \return - 1 (EXITO) / 0 (ERROR)
 */
static int isCuit(char cadena[])
{
	int retorno = 1; // Todo OK.
	int i;

	for(i=0 ; cadena[i] != '\0' ; i++)
	{
		if(	(cadena[i] != '-') &&
			(cadena[i] < '0' || cadena[i] > '9'))
		{
			retorno = 0; // ERROR.
			break;
		}
	}
	return retorno;
}
