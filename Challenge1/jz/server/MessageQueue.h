#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H

#include <thread>
#include <queue>
#include <condition_variable>
#include <mutex>
#include <set>


#include <string.h>
//#include "padawan.h"  // Include the functions from your code
#include <winsock2.h>
#include <ws2tcpip.h>


typedef struct {
    SOCKET sock;
    char* message;
} messagePacket;

using namespace std;

class MessageQueue {
    public:
        queue<messagePacket> messageQueue;
        mutex messageMutex;
        condition_variable messageCV;

        MessageQueue();
        void enqueue(messagePacket& message);
        messagePacket dequeue();
    };

#endif // MESSAGEQUEUE_H