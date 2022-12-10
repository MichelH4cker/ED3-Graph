#include "data_file.h"

int registerHasBenRemoved(register_bin register_bin){
    return register_bin.removido == '1' ? 1 : 0;
}

void goToRRNbin(int RRN, FILE *fp){
    fseek(fp, DISK_PAGE_BIN_SIZE + RRN * REGISTER_BIN_SIZE, SEEK_SET);
}

/*
int returnBinCurrentRRN(FILE *fp){
       return ceil((ftell(fp) - DISK_PAGE_BIN_SIZE) / REGISTER_BIN_SIZE);
}*/

header_bin readHeaderBin(FILE *fp){
       header_bin header_bin;

       fseek(fp, 0, SEEK_SET);
       fread(&header_bin.status, sizeof(header_bin.status), 1, fp);
       fread(&header_bin.topo, sizeof(header_bin.topo), 1, fp);
       fread(&header_bin.proxRRN, sizeof(header_bin.proxRRN), 1, fp);
       fread(&header_bin.nroRegRem, sizeof(header_bin.nroRegRem), 1, fp);
       fread(&header_bin.nroPagDisco, sizeof(header_bin.nroPagDisco), 1, fp);
       fread(&header_bin.qttCompacta, sizeof(header_bin.qttCompacta), 1, fp);

       return header_bin;
}

void fwriteHeaderBin(FILE *fp, header_bin header_param){
       fseek(fp, 0, SEEK_SET);
       fwrite(&header_param.status, sizeof(header_param.status), 1, fp);
       fwrite(&header_param.topo, sizeof(header_param.topo), 1, fp);
       fwrite(&header_param.proxRRN, sizeof(header_param.proxRRN), 1, fp);
       fwrite(&header_param.nroRegRem, sizeof(header_param.nroRegRem), 1, fp);
       fwrite(&header_param.nroPagDisco, sizeof(header_param.nroPagDisco), 1, fp);
       fwrite(&header_param.qttCompacta, sizeof(header_param.qttCompacta), 1, fp);
}

void printHeaderBin(header_bin header_bin){
       printf("========================\n");
       printf("   CABEÇALHO BINÁRIO    \n");
       printf("- status:      %c\n", header_bin.status);
       printf("- topo:        %d\n", header_bin.topo);
       printf("- proxRRN:     %d\n", header_bin.proxRRN);
       printf("- nroRegRem:   %d\n", header_bin.nroRegRem);
       printf("- nroPagDisco: %d\n", header_bin.nroPagDisco);
       printf("- qttCompacta: %d\n", header_bin.qttCompacta);
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

register_bin readRegisterBin(FILE *fp){
       register_bin register_bin;
       fread(&register_bin.removido, sizeof(register_bin.removido), 1, fp);
       if (register_bin.removido == '1') {
              return register_bin;
       }
       fread(&register_bin.encadeamento, sizeof(register_bin.encadeamento), 1, fp);
       fread(&register_bin.idConecta, sizeof(register_bin.idConecta), 1, fp);  
       fread(register_bin.siglaPais, 2, 1, fp);
       register_bin.siglaPais[2] = '\0';
       fread(&register_bin.idPoPsConectado, sizeof(register_bin.idPoPsConectado), 1, fp);
       fread(&register_bin.unidadeMedida, sizeof(register_bin.unidadeMedida), 1, fp);
       fread(&register_bin.velocidade, sizeof(register_bin.velocidade), 1, fp);
       readVariableField(fp, register_bin.nomePoPs);
       readVariableField(fp, register_bin.nomePais);
       return register_bin;
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

void fwriteRegisterBin(FILE *fp, register_bin reg_bin){
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
       int trashAmount = REGISTER_BIN_SIZE - FIX_FIELD_SIZE - (strlen(reg_bin.nomePoPs) + strlen(reg_bin.nomePais)) - 2 * PIPE_SIZE;

       for (int i = 0; i < trashAmount; i++){
              fwrite(&TRASH, sizeof(TRASH), 1, fp);
       }
}

void printRegisterBin(register_bin register_bin){
    printf("========================\n");
    printf("    REGISTRO BINÁRIO    \n");
    printf("- removido: %c\n", register_bin.removido);
    printf("- encadeamento: %d\n", register_bin.encadeamento);
    printf("- idConecta: %d\n", register_bin.idConecta);
    printf("- siglaPais: %s\n", register_bin.siglaPais);
    printf("- idPoPsConectado: %d\n", register_bin.idPoPsConectado);
    printf("- unidadeMedida: %c\n", register_bin.unidadeMedida);
    printf("- velocidade: %d\n", register_bin.velocidade);    
    printf("- nomePoPs: %s\n", register_bin.nomePoPs);
    printf("- nomePais: %s\n", register_bin.nomePais);
    printf("========================\n");
}

void searchRegisterBinRemoved (FILE *fp, header_bin *header_param) {
       int searchedRRN = header_param->topo;
       goToRRNbin(header_param->topo, fp);
       
       char removido;
       fread(&removido, sizeof(removido), 1, fp);
       fread(&header_param->topo, sizeof(header_param->topo), 1, fp);
       goToRRNbin(searchedRRN, fp);
}

void showBinFile(FILE *fp){
       fseek(fp, 0, SEEK_END);
       int F_END = returnBinCurrentRRN(fp);

       fseek(fp, 0, SEEK_SET);
       header_bin h_bin = readHeaderBin(fp);
       printHeaderBin(h_bin);
       goToRRNbin(0, fp);

       int RRN = 1;
       while (RRN < F_END){
              goToRRNbin(RRN, fp);
              register_bin register_bin = readRegisterBin(fp);
              printRegisterBin(register_bin);
              RRN++;
       }  
}