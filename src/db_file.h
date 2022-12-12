#ifndef __DB_FILE_H__
#define __DB_FILE_H__

#define REGISTER_DB_SIZE 64
#define DISK_PAGE_BIN_SIZE 960
#define FIX_FIELD_SIZE 20
#define VARIABLE_FIELD_SIZE 22
#define PIPE_SIZE 1

typedef struct {
	char status;	 // 1 btye
	int topo;		 // 4 btyes
	int proxRRN;	 // 4 bytes
	int nroRegRem;	 // 4 bytes
	int nroPagDisco; // 4 bytes
	int qttCompacta; // 4 bytes
					 // total: 21
} header_db;

typedef struct {
	char removido;	  // 1 byte		//campos
	int encadeamento; // 4 bytes		//auxiliares

	int idConecta;		 // 4 bytes
	char siglaPais[3];	 // 2 bytes
	int idPoPsConectado; // 4 bytes
	char unidadeMedida;	 // 1 byte
	int velocidade;		 // 4 bytes

	char nomePoPs[22]; // campos de tamanho
	char nomePais[22]; // variavel
} register_db;

#include "main.h"

/**
 * @brief lê o registro e retorna se ele está removido logicamente
 * 
 * @param register_db struct que contém o registro lido no arquivo de dados 
 * @return int 1 para removido e 0 para não removido
 */
int registerHasBenRemoved(register_db register_db);

/**
 * @brief dado um RRN, o ponteiro vai até ele
 *
 * @param RRN RRN
 * @param fp ponteiro para arquivo
 */
void goToRRNdb(int RRN, FILE *fp);

/**
 * @brief retorna um inteiro que guarda o valor do RRN atual do ponteiro
 *
 * @param fp ponteiro do arquivo
 * @return int RRN atual do ponteiro
 */
int returnBinCurrentRRN(FILE *fp);

/**
 * @brief lê arquivo e retorna struct do cabeçalho contendo todos os campos
 *
 * @param fp ponteiro para arquivo
 * @return header_db armazena campos do cabeçalho
 */
header_db readHeaderDB(FILE *fp);

/**
 * @brief escreve no arquivo de dados o header passado como parâmetro
 *
 * @param fp ponteiro para arquivo de dados
 * @param header_param header contendo as novas informações a serem escritas
 */
void fwriteHeaderDB(FILE *fp, header_db header_param);

/**
 * @brief mostra no terminal a struct header_db. essa função é usada apenas para debug
 *
 * @param header_db cabeçalho a ser mostrado no terminal
 */
void printHeaderDB(header_db header_db);

/**
 * @brief lê no arquivo os campos de tamanho variável
 *
 * @param fp ponteiro para o arquivo
 * @param string string a ser lida
 */
void readVariableField(FILE *fp, char *string);

/**
 * @brief lê o registro do arquivo de dados
 *
 * @param fp ponteiro para arquivo
 * @return register_db armazena o registro
 */
register_db readRegisterDB(FILE *fp);

/**
 * @brief escreve os campos de tamanho variável no arquivo de dados
 *
 * @param fp ponteiro para o arquivo de dados
 * @param string campo de tamanho variável
 * @return int número de bytes escritos 
 */
void fwriteVariableField(FILE *fp, char *string);

/**
 * @brief escreve um registro no arquivo de dados
 *
 * @param fp ponteiro para o arquivo de dados
 * @param register_db registro a ser escrito no arquivo de dados
 */
void fwriteRegisterDB(FILE *fp, register_db register_db);

/**
 * @brief mostra no terminal a struct register_db. essa função é usada apenas para debug
 *
 * @param register_db registro a ser mostrado no terminal
 */
void printRegisterDB(register_db register_db);

/**
 * @brief vai até o RRN do registro removido armazenado no cabeçalho
 *
 * @param fp ponteiro para arquivo de dados
 * @param header cabeçalho do arquivo de dados, utilizado para coleta de informações
 */
void searchRegisterDBremoved(FILE *fp, header_db *header_param);

#endif