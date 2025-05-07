//
// Created by lbrd on 2025/4/30.
//

#ifndef NATIVELOOPER_MESSAGEQUEUE_H
#define NATIVELOOPER_MESSAGEQUEUE_H


#include <pthread.h>
#include <iostream>
#include <mutex>
#include <sys/eventfd.h>
#include <sys/epoll.h>
#include <atomic>

class Message;

class MessageQueue {

private:
    std::atomic<int> fdVal;
    Message *mMessages;

    const bool mQuitAllowed;

    std::mutex mutex;

    eventfd_t eventFd;

    int epollFd;

    bool mBlocked= false;

public:

    MessageQueue(bool quitAllowed);

    ~MessageQueue();

    bool enqueueMessage(Message *msg);

    Message* next();

    void nativeWake();

    void nativePollOnce(long timeout);

};

#endif //NATIVELOOPER_MESSAGEQUEUE_H
