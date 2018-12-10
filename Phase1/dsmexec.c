#include "common_impl.h"
/* variables globales */




/* un tableau gerant les infos d'identification */
/* des processus dsm */
dsm_proc_t *proc_array = NULL; 

/* le nombre de processus effectivement crees */
volatile int num_procs_creat = 0;

/* il manque des arguments */
void usage(void)
{
	fprintf(stdout,"Usage : dsmexec machine_file executable arg1 arg2 ...\n");
	fflush(stdout);
	exit(EXIT_FAILURE);
}

void sigchld_handler(int sig)
{
	/* on traite les fils qui se terminent */
	/* pour eviter les zombies */
}


int main(int argc, char *argv[])
{
	if (argc < 3){
		usage();
	} else {

		pid_t pid;
		int num_procs = 0;
		int fd;
		int i;
		char * hostname[ARG_SIZE];
		char * machines[MAX_PROCESS][MACHINE_NAME_SIZE];
		char ** argu_ssh = malloc(ARG_SIZE*sizeof(char)*(argc));

		gethostname(hostname,ARG_SIZE);

		/* Mise en place d'un traitant pour recuperer les fils zombies*/
		/* XXX.sa_handler = sigchld_handler; */


		/* lecture du fichier de machines */

		FILE* fi=fopen(argv[1],"r");

		/* 1- on recupere le nombre de processus a lancer */

		num_procs=line_count(fi);

		printf("nombre de lignes : %d\n", num_procs);
		fflush(stdout);

		/* 2- on recupere les noms des machines : le nom de */
		/* la machine est un des elements d'identification */

		read_file(fi, machines);

		printf("première machine : %s\n", (char *)machines[0]);
		fflush(stdout);

		/* creation de la socket d'ecoute */
		/* + ecoute effective */

		char * ipad = malloc(sizeof(char)*100);
		char * port = malloc(sizeof(char)*ARG_SIZE);
		memset(ipad,'\0',sizeof(*ipad));
		memset(port,'\0',sizeof(*port));

		fd = creer_socket(0, ipad, port);

		printf("ipad : %s\n", ipad);
		fflush(stdout);

		printf("socket num : %d\n", fd);

		int lst = listen(fd, MAXCO);
		if ( lst== -1 ){
			perror("listen()");
			exit(0);
		}



		/* creation des fils */
		for(i = 0; i < num_procs ; i++) {

			/* creation du tube pour rediriger stdout */

			/* creation du tube pour rediriger stderr */

			pid = fork();
			if(pid == -1) ERROR_EXIT("fork");

			if (pid == 0) { /* fils */

				/* redirection stdout */

				/* redirection stderr */

				/* Creation du tableau d'arguments pour le ssh */


				strcpy((char *)argu_ssh, "ssh");
				strcpy((char *)(argu_ssh + ARG_SIZE*sizeof(char)), machines[i]);
				strcpy((char *)(argu_ssh + 2*ARG_SIZE*sizeof(char)), hostname);
				strcpy((char *)(argu_ssh + 3*ARG_SIZE*sizeof(char)),port);
				strcpy((char *)(argu_ssh + 4*ARG_SIZE*sizeof(char)),"dswrap");

				//				char socket[10];
				//				memset(socket,'\0',sizeof(socket));
				//				sprintf(socket, "%d", fd);




				int j;
				char arg[ARG_SIZE];

				for (j=2; j<argc; j++){

					memset(arg,0,ARG_SIZE*sizeof(char));

					strcpy(arg, argv[j]);

					strcpy((char *)(argu_ssh + (j+3)*ARG_SIZE*sizeof(char)),arg);

				}

				for(i=0; i<8; i++){

					printf("arguments ssh : %s\n", (argu_ssh+i*ARG_SIZE*sizeof(char)));

				}
				/* jump to new prog : */


				/* execvp("ssh",newargv); */

				execvp("ssh",argu_ssh);

			} else  if(pid > 0) { /* pere */
				/* fermeture des extremites des tubes non utiles */
				num_procs_creat++;
				wait(NULL);
			}

		}


		for(i = 0; i < num_procs ; i++){

			/* on accepte les connexions des processus dsm */

			/*  On recupere le nom de la machine distante */
			/* 1- d'abord la taille de la chaine */
			/* 2- puis la chaine elle-meme */

			/* On recupere le pid du processus distant  */

			/* On recupere le numero de port de la socket */
			/* d'ecoute des processus distants */
		}

		/* envoi du nombre de processus aux processus dsm*/

		/* envoi des rangs aux processus dsm */

		/* envoi des infos de connexion aux processus */

		/* gestion des E/S : on recupere les caracteres */
		/* sur les tubes de redirection de stdout/stderr */
		/* while(1)
         {
            je recupere les infos sur les tubes de redirection
            jusqu'à ce qu'ils soient inactifs (ie fermes par les
            processus dsm ecrivains de l'autre cote ...)

         };
		 */

		/* on attend les processus fils */

		/* on ferme les descripteurs proprement */

		/* on ferme la socket d'ecoute */
	}
	exit(EXIT_SUCCESS);
}

