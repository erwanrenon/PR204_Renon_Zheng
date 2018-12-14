#include "common_impl.h"

int send_all(int fd, void *buffer, int size){
  ssize_t ret = 0;
  do{
    ret += write(fd,(char *)buffer+ret,size-ret);
  } while(ret != size);
  return 0;
}

int recv_all(int fd, void *buffer, int size){
  ssize_t ret = 0;
  do{
    ret += read(fd,(char *)buffer+ret,size-ret);
  } while(ret != size);
  return 0;
}

int creer_socket(int prop, char * ipad, char * port)
{

	/* fonction de creation et d'attachement */
	/* d'une nouvelle socket */
	/* renvoie le numero de descripteur */
	/* et modifie le parametre port_num */

	int fd = 0;
	struct sockaddr_in sin;

	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_family=AF_INET;

	fd = socket(AF_INET, SOCK_STREAM, 0);
	if ( fd == -1 ){
		perror("socket()");
		exit(0);
	}

	int bnd = bind(fd, (struct sockaddr*)&sin, sizeof(sin));
	if ( bnd == -1 ){
		perror("bind()");
		exit(0);
	}



	int sinsize = sizeof(sin);
	int getsk = getsockname(fd, (struct sockaddr*)&sin, (socklen_t *)(&sinsize));
	if (getsk == -1 ){
		perror("getsockname()");
		exit(0);
	}

	getport(&sin, port);
	getip(&sin, ipad);

	printf("port : %s\n",port);
	printf("adresse ip : %s\n",ipad);
	return fd;
}


/* compte le nombre de lignes d'un fichier */
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

/* remplis un tableau de chaînes de caractère correspondant au nom des machines */
void read_file(FILE* fichier, char * machines[MAX_PROCESS][MACHINE_NAME_SIZE]){
	char chaine[MACHINE_NAME_SIZE] = "";
	memset(chaine,0,MACHINE_NAME_SIZE);
	rewind(fichier);
	int i = 0;
	if (fichier != NULL)
	{
		while (fgets(chaine, MACHINE_NAME_SIZE, fichier)!=NULL)
		{
			printf("%s", chaine); // On affiche la chaîne qu'on vient de lire
			strtok(chaine,"\n");
			strcpy((char *)machines[i],chaine);
			memset(chaine,0,MACHINE_NAME_SIZE);
			i++;
		}
	}
}

void getip(struct sockaddr_in * client, char * ipad) {


	struct sockaddr_in* pV4Addr = client;
	struct in_addr ipaddr = pV4Addr->sin_addr;
	inet_ntop( AF_INET, &ipaddr, ipad, INET_ADDRSTRLEN);

}

void getport(struct sockaddr_in * client, char * port) {
	int p = ntohs(client->sin_port);
	sprintf(port, "%d", p);

}

/* Vous pouvez ecrire ici toutes les fonctions */
/* qui pourraient etre utilisees par le lanceur */
/* et le processus intermediaire. N'oubliez pas */
/* de declarer le prototype de ces nouvelles */
/* fonctions dans common_impl.h */
