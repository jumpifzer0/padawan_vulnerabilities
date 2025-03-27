#ifndef CHATSERVER_H
#define CHATSERVER_H

#include "../padawan_dll/padawan.h"
#include "base_listening_server.h"
#include "MessageQueue.h"

using namespace std;


class ChatServer : public base_listening_server {
    public:
        MessageQueue *mq;
        set<SOCKET> clients;
        mutex clientsMutex;
        int buf_size;
        int buf_size_w_padding;
    
        ChatServer(MessageQueue* mq);
        ~ChatServer();
        void handleClient(SOCKET clientSocket, MessageQueue *mq);
        void broadcastMessage(MessageQueue* mq);
        void pollingClientConnections();
};


#endif /* CHATSERVER_H */