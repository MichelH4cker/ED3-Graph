#ifndef __DB_FILE_HPP__
#define __DB_FILE_HPP__

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

#include "main.hpp"

/**
 * @brief retorna o valor do proxRRN disponível do arquivo de dados
 * 
 * @param file 
 * @return int 
 */
int getProxRRN(char *file);

/**
 * @brief dado um RRN, o ponteiro vai até ele
 *
 * @param RRN RRN
 * @param fp ponteiro para arquivo
 */
void goToRRNdb(int RRN, FILE *fp);

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
 * @brief mostra no terminal a struct register_db. essa função é usada apenas para debug
 *
 * @param register_db registro a ser mostrado no terminal
 */
void printRegisterDB(register_db register_db);

#endif
