#ifndef CHATCLIENT_H
#define CHATCLIENT_H


#include "../padawan_dll/padawan.h"
#include "base_client.h"

class ChatClient : public base_client {
    public:
        int bufsize;
        int bufsize_w_padding;

        ChatClient();
        ~ChatClient();

        void pollingSend();
        void pollingRecv();
        void pollingDisplay();
};

#endif // CHATCLIENT_H