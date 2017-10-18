#include <stdio.h>

// Formatos válidos
enum FORMATS { ppm };

/*
 * Verificação do conteudo do arquivo
void Debug(FILE *file) {
  printf("\n");
  char str[250];

  printf("Parseando");
  if (file) {
    while (fscanf(file, "%s", str) != EOF)
      printf("%s", str);
    fclose(file);
  }

  printf("\n");
}
*/

// Upload de arquivo e criação de temporário
FILE *FileUpload() {
  char ch, path[100];
  FILE *file, *tmp_file;

  // Upload do arquivo de imagem do olho a ser testado
  printf("Arquivo de imagem do olho (jpeg): ");
  scanf("%s", path);
  file = fopen(path, "r");
  printf("\n");

  // Previnir erro ao não encontrar um arquivo
  while ( file  == NULL ) { 
    printf("Arquivo não encontrado, por favor tente novamente: ");
    scanf("%s", path);
    file = fopen(path, "r");
    printf("\n");
  }

  // Criar arquivo temporário que possa ser alterado
  printf("Copiando... ");
  tmp_file = fopen("img_teste.ppm", "w");

  while( ( ch = fgetc(file) ) != EOF )
    fputc(ch, tmp_file);
  printf("OK!\n");

  return tmp_file;
}
