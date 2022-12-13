#include "db_file.hpp"

int getProxRRN(char *file){
       FILE *fp = fopen(file, "rb");
       header_db header_db = readHeaderDB(fp);
       return header_db.proxRRN;
}

int registerHasBenRemoved(register_db register_db){
       return register_db.removido == '1' ? 1 : 0;
}

void goToRRNdb(int RRN, FILE *fp){
    fseek(fp, DISK_PAGE_BIN_SIZE + RRN * REGISTER_DB_SIZE, SEEK_SET);
}

header_db readHeaderDB(FILE *fp){
       header_db header_db;

       fseek(fp, 0, SEEK_SET);
       fread(&header_db.status, sizeof(header_db.status), 1, fp);
       fread(&header_db.topo, sizeof(header_db.topo), 1, fp);
       fread(&header_db.proxRRN, sizeof(header_db.proxRRN), 1, fp);
       fread(&header_db.nroRegRem, sizeof(header_db.nroRegRem), 1, fp);
       fread(&header_db.nroPagDisco, sizeof(header_db.nroPagDisco), 1, fp);
       fread(&header_db.qttCompacta, sizeof(header_db.qttCompacta), 1, fp);

       return header_db;
}

void fwriteHeaderDB(FILE *fp, header_db header_param){
       fseek(fp, 0, SEEK_SET);
       fwrite(&header_param.status, sizeof(header_param.status), 1, fp);
       fwrite(&header_param.topo, sizeof(header_param.topo), 1, fp);
       fwrite(&header_param.proxRRN, sizeof(header_param.proxRRN), 1, fp);
       fwrite(&header_param.nroRegRem, sizeof(header_param.nroRegRem), 1, fp);
       fwrite(&header_param.nroPagDisco, sizeof(header_param.nroPagDisco), 1, fp);
       fwrite(&header_param.qttCompacta, sizeof(header_param.qttCompacta), 1, fp);
}

void printHeaderDB(header_db header_db){
       printf("========================\n");
       printf("   CABEÇALHO BINÁRIO    \n");
       printf("- status:      %c\n", header_db.status);
       printf("- topo:        %d\n", header_db.topo);
       printf("- proxRRN:     %d\n", header_db.proxRRN);
       printf("- nroRegRem:   %d\n", header_db.nroRegRem);
       printf("- nroPagDisco: %d\n", header_db.nroPagDisco);
       printf("- qttCompacta: %d\n", header_db.qttCompacta);
       printf("========================\n");       
}

void readVariableField(FILE *fp, char *string){
       int i = 0;
       char c;
       fread(&c, sizeof(char), 1, fp);
       while (c != '|'){
              string[i] = c;
              fread(&c, sizeof(char), 1, fp);
              i++;
       }
       string[i] = '\0';
}

register_db readRegisterDB(FILE *fp){
       register_db register_db;
       fread(&register_db.removido, sizeof(register_db.removido), 1, fp);
       if (register_db.removido == '1') {
              return register_db;
       }
       fread(&register_db.encadeamento, sizeof(register_db.encadeamento), 1, fp);
       fread(&register_db.idConecta, sizeof(register_db.idConecta), 1, fp);  
       fread(register_db.siglaPais, 2, 1, fp);
       register_db.siglaPais[2] = '\0';
       fread(&register_db.idPoPsConectado, sizeof(register_db.idPoPsConectado), 1, fp);
       fread(&register_db.unidadeMedida, sizeof(register_db.unidadeMedida), 1, fp);
       fread(&register_db.velocidade, sizeof(register_db.velocidade), 1, fp);
       readVariableField(fp, register_db.nomePoPs);
       readVariableField(fp, register_db.nomePais);
       return register_db;
}

void fwriteVariableField(FILE *fp, char *string){
       int i = 0;
       char PIPE = '|';
       char c = string[0];
       while (c != '\0' && c != PIPE && i < 21){
              i++;
              fwrite(&c, sizeof(char), 1, fp);
              c = string[i];
       }
}

void fwriteRegisterDB(FILE *fp, register_db reg_bin){
       // ESCREVE CAMPOS FIXOS
       fwrite(&reg_bin.removido, sizeof(reg_bin.removido), 1, fp);
       fwrite(&reg_bin.encadeamento, sizeof(reg_bin.encadeamento), 1, fp);
       fwrite(&reg_bin.idConecta, sizeof(reg_bin.idConecta), 1, fp);  
       fwrite(reg_bin.siglaPais, 2, 1, fp);
       fwrite(&reg_bin.idPoPsConectado, sizeof(reg_bin.idPoPsConectado), 1, fp);
       fwrite(&reg_bin.unidadeMedida, sizeof(reg_bin.unidadeMedida), 1, fp);
       fwrite(&reg_bin.velocidade, sizeof(reg_bin.velocidade), 1, fp);

       // ESCREVE CAMPO VARIÁVEIS
       char PIPE = '|';
       fwriteVariableField(fp, reg_bin.nomePoPs);
       fwrite(&PIPE, sizeof(PIPE), 1, fp);
       fwriteVariableField(fp, reg_bin.nomePais);
       fwrite(&PIPE, sizeof(PIPE), 1, fp);

       // COMPLETA COM LIXO
       char TRASH = '$';
       int trashAmount = REGISTER_DB_SIZE - FIX_FIELD_SIZE - (strlen(reg_bin.nomePoPs) + strlen(reg_bin.nomePais)) - 2 * PIPE_SIZE;

       for (int i = 0; i < trashAmount; i++){
              fwrite(&TRASH, sizeof(TRASH), 1, fp);
       }
}

void printRegisterDB(register_db register_db){
    printf("========================\n");
    printf("    REGISTRO BINÁRIO    \n");
    printf("- removido: %c\n", register_db.removido);
    printf("- encadeamento: %d\n", register_db.encadeamento);
    printf("- idConecta: %d\n", register_db.idConecta);
    printf("- siglaPais: %s\n", register_db.siglaPais);
    printf("- idPoPsConectado: %d\n", register_db.idPoPsConectado);
    printf("- unidadeMedida: %c\n", register_db.unidadeMedida);
    printf("- velocidade: %d\n", register_db.velocidade);    
    printf("- nomePoPs: %s\n", register_db.nomePoPs);
    printf("- nomePais: %s\n", register_db.nomePais);
    printf("========================\n");
}

void searchRegisterDBremoved (FILE *fp, header_db *header_param) {
       int searchedRRN = header_param->topo;
       goToRRNdb(header_param->topo, fp);
       
       char removido;
       fread(&removido, sizeof(removido), 1, fp);
       fread(&header_param->topo, sizeof(header_param->topo), 1, fp);
       goToRRNdb(searchedRRN, fp);
}
