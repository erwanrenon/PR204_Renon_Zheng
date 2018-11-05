#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define TAILLE_MAX 20

int line_count(FILE* fi){
  //compte le nb de lignes d'un fichier existant
  int compteur      = 0;
  int current_carac = 0;
  rewind(fi); //place le curseur en début de ligne
  if (fi != NULL){
    do {
      current_carac=fgetc(fi);

      if (current_carac == '\n'){
          compteur ++;
        }

    }while( current_carac != EOF);
  }
  return compteur;
}

void read_file(FILE* fichier){
  char chaine[TAILLE_MAX] = "";
  rewind(fichier);
  if (fichier != NULL)
    {
      while (fgets(chaine, TAILLE_MAX, fichier)!=NULL)
        {
          printf("%s", chaine); // On affiche la chaîne qu'on vient de lire
        //  memset(chaine,0,TAILLE_MAX);
        }
    }
}

int main(int argc, char** argv){
  FILE* fi=fopen("./machine_file","r");
  read_file(fi);
  fclose(fi);
  return 0;
}
