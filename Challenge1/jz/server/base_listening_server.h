#ifndef BASE_LISTENING_SERVER_H
#define BASE_LISTENING_SERVER_H

#include <string>
#include <winsock2.h>

using namespace std;

class base_listening_server{

    public: 
        SOCKET serverSocket;
        string server_ip;
        int server_port;
        int backlog; // Max pending connections

        base_listening_server();
        ~base_listening_server();

        void initialiseSocket();

};


#endif /* BASE_LISTENING_SERVER_H */