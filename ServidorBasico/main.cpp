#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#define MY_PORT "6969"
#define MAX_CONNECTIONS 1

void sigchld_handler(int s)
{
    // waitpid() might overwrite errno, so we save and restore it:
    int saved_errno = errno;

    while(waitpid(-1, NULL, WNOHANG) > 0);

    errno = saved_errno;
    (void)s;
}

int main(void) {
    struct addrinfo hints, *servinfo, *p;    //Estructuras con datos sobre las conexiones
    int sockfd, new_fd;                     //Sockets de conexion de escucha y de nueva conexion
    struct sockaddr_storage their_addr;
    socklen_t sin_size;
    struct sigaction sa;
    int yes=1;
    // char s[INET6_ADDRSTRLEN];
    int conexion;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    /*  
        Aquí le especificamos que queremos que el servidor sea un servidor pasivo.
        De esta forma va a estar esperando conexiones entrantes en vez de intentar
        iniciar conexiones salientes.
    */
    hints.ai_flags = AI_PASSIVE; 

    /*
        Vamos a hacer la búsqueda de la dirección local.
    */
    conexion = getaddrinfo(NULL, MY_PORT, &hints, &servinfo);
    if (conexion != 0) {
        std::cout << "getaddrinfo: " << gai_strerror(conexion) << std::endl;
        return 1;
    }

    /*
        Recorremos todos los resultados que nos ha dado y usamos bind con la primera
        dirección que podamos.
    */
    for (p = servinfo; p != NULL; p = p->ai_next) {
        sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (sockfd == -1) {
            std::cout << "Server error: socket" << std::endl;
            continue;
        }
        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,sizeof(int)) == -1) {
            std::cout << "Error: setsockopt" << std::endl;
            exit(1);
        }
        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            std::cout << "Server error: bind" << std::endl;
            continue;
        }
        break;
    }

    freeaddrinfo(servinfo);
    if (p == NULL) {
        std::cout << "Server error: bind not possible" << std::endl;
        exit(1);
    }

    if (listen(sockfd, MAX_CONNECTIONS) == -1) {
        std::cout << "Error: listening" << std::endl;
        exit(1);
    }

    /*
        Ahora vamos a configurar las señales.
    */
    sa.sa_handler = sigchld_handler; //Esta función va a ser la que recoja los procesos hijo y no dejarlos sueltos.
    sigemptyset(&sa.sa_mask); //Es como decir "no queremos evitar que otras cosas sucedan mientras manejamos esto". 
    sa.sa_flags = SA_RESTART; //Con esto hacemos que no se reinicie la accion abruptamente, de esta forma se espera a terminar la acción para reiniciarla.
    if (sigaction(SIGCHLD, &sa, NULL) == -1) { //Le decimos al programa que cuando llegue esa señal, debe seguir las reglas que hemos establecido anteriormente en sa.
        std::cout << "Error: Sigaction" << std::endl;
        exit(1);
    }

    std::cout << "PeiServ: Waiting for new connections..." << std::endl;

    while (1) {
        sin_size = sizeof(their_addr);
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        if (new_fd == -1) {
            std::cout << "Error: Bad connection" << std::endl;
            continue;
        }

        if (!fork()) {
            close(sockfd);
            if (send(new_fd, "Si estás viendo esto funciono!\n", 32, 0) == -1)
                std::cout << "Error: sending msg" << std::endl;
            close(new_fd);
            exit(0);
        }
        close(new_fd);
    }

    (void)p;
    (void)new_fd;
}