#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <netdb.h>

/* autres includes (eventuellement) */

#define ERROR_EXIT(str) {perror(str);exit(EXIT_FAILURE);}
#define MACHINE_NAME_SIZE 40
#define MAX_PROCESS 40
#define MAXCO 20
#define ARG_SIZE 20
#define BUF_SIZE 500

typedef struct son{
  int pipeOut;
  int pipeErr;
  pid_t pid;
  int rank;
} son_t;

/* definition du type des infos */
/* de connexion des processus dsm */
struct dsm_proc_conn  {
   int rank;
   /* a completer */
};
typedef struct dsm_proc_conn dsm_proc_conn_t; 

/* definition du type des infos */
/* d'identification des processus dsm */
struct dsm_proc {   
  pid_t pid;
  dsm_proc_conn_t connect_info;
};
typedef struct dsm_proc dsm_proc_t;

int creer_socket(int prop, char * ipad, char * port);

int line_count(FILE* fi);

void read_file(FILE* fichier, char * machines[MAX_PROCESS][MACHINE_NAME_SIZE]);

void getip(struct sockaddr_in * client, char * ipad);

void getport(struct sockaddr_in * client, char * port);

int send_all(int fd, void *buffer, int size);

int recv_all(int fd, void *buffer, int size);

