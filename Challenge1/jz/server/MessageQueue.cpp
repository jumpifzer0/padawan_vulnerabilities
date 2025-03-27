#include <thread>
#include <queue>
#include <condition_variable>
#include <mutex>
#include <set>


#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>


#include "MessageQueue.h"

MessageQueue::MessageQueue(){

}

void MessageQueue::enqueue(messagePacket& message) {
    unique_lock<mutex> lock(messageMutex);
    messageQueue.push(message);
    lock.unlock();
    messageCV.notify_one();
};


// dequeue will wait using the condition_variable until it is triggered(which will trigger when a message is queued)
messagePacket MessageQueue::dequeue(){
    unique_lock<mutex> lock(messageMutex);
    messageCV.wait(lock,[this]{return !messageQueue.empty();});
    messagePacket msg = messageQueue.front();
    messageQueue.pop();

    return msg;
};