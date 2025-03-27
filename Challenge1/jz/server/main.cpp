#include "ChatServer.h"
#include "MessageQueue.h"

#include <thread>

using namespace std;

int main(){
    MessageQueue *mq = new MessageQueue();
    ChatServer* server = new ChatServer(mq);

    // on-going client connection catching
    // this thread will have a for loop to create new threads (upon accept) to handleClient
    thread t1([server]() {
        server->pollingClientConnections();
    });

    // on-going sending of message
    // it has a while loop inside that will keep trying to do mq->dequeue(), which has a condition variable to check for any new messages when enqueue is called.
    thread t2([server,mq]{
        server->broadcastMessage(mq);
    });

    // thread cleanup
    t1.join();
    t2.join();


    delete mq;
    delete server;

    return 0;

}