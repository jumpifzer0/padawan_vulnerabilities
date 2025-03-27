#include <thread>

#include "ChatClient.h"

using namespace std;

int main(){
    ChatClient* client = new ChatClient();

    client->connectToServer("127.0.0.1",8079);

    // Thread that has a while loop to keep receiving
    thread t1([client]{
        client->pollingRecv();
    });

    // Thread that has a while loop to check fgets and then send
    thread t2([client]{
            client->pollingSend();
    });

    t1.join();
    t2.join();

    return 0;
}