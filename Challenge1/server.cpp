#include <stdio.h>

#include <string.h>
#include "padawan.h"  // Include the functions from your code
#include <winsock2.h>
#include <ws2tcpip.h>

#include <thread>
#include <queue>
#include <condition_variable>
#include <mutex>
#include <set>

#define SERVER_IP "127.0.0.1"  // Localhost
#define SERVER_PORT 8079
#define BACKLOG 5  // Max pending connections
#define BUF_SIZE 1024
#define BUF_SIZE_W_PADDING 1024+8

using namespace std;

bool debug = true;
set<SOCKET> clients; 
mutex clientsMutex; 

typedef struct {
    SOCKET sock;
    char* message;
} messagePacket;

class MessageQueue {
public:
    queue<messagePacket> messageQueue;
    mutex messageMutex;
    condition_variable messageCV;


    void enqueue(messagePacket& message){
        if (debug) printf("enqueue message!\n");
        unique_lock<mutex> lock(messageMutex);
        messageQueue.push(message);
        lock.unlock();
        messageCV.notify_one();
    };
    
    messagePacket dequeue(){
        unique_lock<mutex> lock(messageMutex);
        messageCV.wait(lock,[this]{return !messageQueue.empty();});
        messagePacket msg = messageQueue.front();
        messageQueue.pop();
        if (debug) printf("dequeued message\n");
        return msg;
    };
};

class Server{
    set<SOCKET> clients; 
    mutex clientsMutex; 
    SOCKET serverSocket, clientSocket;
    MessageQueue* mq;

    public:
    Server(MessageQueue* mq){this->mq = mq;};
    void handleClient(SOCKET clientSocket, MessageQueue *mq){
        if (debug) printf("client thread created!\n");
        char recvBuffer[BUF_SIZE_W_PADDING];
        int recv_size;
        if (debug) printf("going to lock the set for client input!\n");
        unique_lock<mutex> lock(clientsMutex); 
        if (debug) printf("going to insert client socket into set!\n");
        clients.insert(clientSocket);
        lock.unlock();
        if (debug) printf("client socket placed into set!\n");
        //format message
        messagePacket mp;
        mp.sock=clientSocket;
        char *c;
        while (true){
            if (debug) printf("trying to receive data from cient!\n");
            int recv_size = ReceiveData(clientSocket, recvBuffer, sizeof(recvBuffer)-1); //TODO:
            if (recv_size > 0) {
                recvBuffer[recv_size] = '\0';  // Null-terminate the string
                
                printCharArray(recvBuffer);
            }
            if (recv_size == 0){
                unique_lock<mutex> lock(clientsMutex); 
                clients.erase(clientSocket); 
                lock.unlock();
                exit(0);
    
            } else if (recv_size == SOCKET_ERROR){
                unique_lock<mutex> lock(clientsMutex); 
                clients.erase(clientSocket); 
                lock.unlock();
            } else{
                if (!validateMsg(recvBuffer)){
                    continue;
                }
                c = new char[BUF_SIZE_W_PADDING];
                // copy data from buffer to here before putting into queue
                strncpy(c,recvBuffer,BUF_SIZE_W_PADDING);
                mp.message = c;
                mq->enqueue(mp); 
            }
    
        }
    
    }
    
    void broadcastMessage(MessageQueue* mq){
        if (debug) printf("handling messages thread created!\n");
        messagePacket data;
        set<SOCKET>::iterator it;
        while (true){
            // consume message from the queue
            data = mq->dequeue();
            if (debug) printf("This is what is received in data! %s\n",data.message);
            unique_lock<mutex> lock(clientsMutex);
            for (it= clients.begin(); it != clients.end(); ++it) {
                if (*it != data.sock){
                    if (SendData(*it, data.message, strlen(data.message)) == 0) {
                        printf("Failed to send data to client\n");
                        clients.erase(*it);
                    }
                }
            }
            lock.unlock();
            delete data.message;
        }
    }

    void initialiseSocket(){
        // Initialize Winsock
        if (!InitWinsock()) {
            return;
        }

        // Create a socket
        serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (serverSocket == INVALID_SOCKET) {
            printf("Socket creation failed with error: %d\n", WSAGetLastError());
            CleanupWinsock();
            return;
        }

        // Bind the socket to the address and port
        if (!BindSocket(&serverSocket, SERVER_IP, SERVER_PORT)) {
            CleanupWinsock();
            return;
        }

        // Listen for incoming connections
        if (!ListenForConnections(&serverSocket, BACKLOG)) {
            CleanupWinsock();
            return;
        }

    }

    void acceptClientConnections(){
        printf("server can start accepting connections!\n");
        while (true){
            // Accept a connection from a client
            printf("server can start accepting connections!\n");
            clientSocket = AcceptConnection(&serverSocket);
            printf("connection accepted!\n");
            if (clientSocket == INVALID_SOCKET) {
                continue;
            }
            thread t1(&Server::handleClient,this,clientSocket,ref(mq));
            t1.detach(); 
        }
    }
    ~Server(){
        // Close the client socket
        CloseSocket(clientSocket);

        // Cleanup Winsock
        CleanupWinsock();
    };
};

int main() {

    MessageQueue *mq = new MessageQueue();
    Server* server = new Server(mq);
   
    server->initialiseSocket();
    printf("Server is listening on %s:%d...\n", SERVER_IP, SERVER_PORT);
    thread t0([server,mq]{
        server->broadcastMessage(mq);
    });
    server->acceptClientConnections();
    t0.join();

    

    delete mq;
    delete server;
    return 0;
}
