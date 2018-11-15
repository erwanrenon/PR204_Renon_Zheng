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
		int port_num = 0;
		int fd;
		int i;
		char * machines[MAX_PROCESS][MACHINE_NAME_SIZE];
		char ** arg_ssh = malloc(ARG_SIZE*sizeof(char)*(argc-2));


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

		fd = creer_socket(0, &port_num);

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


				char arg[ARG_SIZE];
				int j;
				for (j=2; j<argc; j++){
					printf("salut\n");
					fflush(stdout);
					memset(arg,0,ARG_SIZE*sizeof(char));

					strcpy(arg, argv[j]);

					strcpy((char *)&arg_ssh[j-2],arg);
					printf("arg ssh : %s\n",arg_ssh[j-2]);
					fflush(stdout);
				}

				/* jump to new prog : */
				/* execvp("ssh",newargv); */

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

