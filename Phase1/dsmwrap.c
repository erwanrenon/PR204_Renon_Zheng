#include "common_impl.h"

int main(int argc, char **argv)
{   


	char * ipad = malloc(sizeof(char)*100);
	char * port = malloc(sizeof(char)*ARG_SIZE);
	memset(ipad,'\0',sizeof(*ipad));
	memset(port,'\0',sizeof(*port));

   /* processus intermediaire pour "nettoyer" */
   /* la liste des arguments qu'on va passer */
   /* a la commande a executer vraiment */
   
   /* creation d'une socket pour se connecter au */
   /* au lanceur et envoyer/recevoir les infos */
   /* necessaires pour la phase dsm_init */   

	int sock = creer_socket(0, ipad, port);
   
   /* Envoi du nom de machine au lanceur */

	printf("salut dude\n");
	fflush(stdout);

   /* Envoi du pid au lanceur */

   /* Creation de la socket d'ecoute pour les */
   /* connexions avec les autres processus dsm */

   /* Envoi du numero de port au lanceur */
   /* pour qu'il le propage à tous les autres */
   /* processus dsm */

   /* on execute la bonne commande */
   return 0;
}
