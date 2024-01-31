#ifndef ListeningSocket_hpp
#define ListeningSocket_hpp

#include <cstdlib>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>

class ListeningSocket
{
    private:
        int _sock;
        int _binding;
        int _backlog;
        int _listening;
        struct sockaddr_in _address;
    public:
        ListeningSocket(int domain, int service, int protocol, int port,
            u_long interface, int bklg);
        void test_connection(int item_to_test);
        int  get_binding();
        struct sockaddr_in get_address();
        int  get_sock();
};

#endif
