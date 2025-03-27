#ifndef BASE_LISTENING_SERVER_H
#define BASE_LISTENING_SERVER_H

#include <stdio.h>
#include <winsock2.h>
#include <string.h>
#include <thread>
#include "../padawan_dll/padawan.h"

class base_client{
    public:
        SOCKET clientSocket;

        base_client();
        ~base_client();
        void connectToServer(char* server_ip, unsigned short server_port);

    private:
        // These will be called when the constructor is used. 
        void initializeSocket();
        void createSocket();


        void cleanupSocket();

};

#endif // BASE_LISTENING_SERVER_H