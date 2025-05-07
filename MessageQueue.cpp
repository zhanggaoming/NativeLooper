//
// Created by lbrd on 2025/4/30.
//

#include "MessageQueue.h"
#include <unistd.h>
#include "Util.h"
#include "NativeHandler.h"
#include "Message.h"

MessageQueue::MessageQueue(bool quitAllowed) : mQuitAllowed(quitAllowed), fdVal(1) {

    eventFd = eventfd(1, 0);

    epollFd = epoll_create(10);

    struct epoll_event epollEvent;
    epollEvent.data.fd = eventFd;
    epollEvent.events = EPOLLIN;
    epoll_ctl(epollFd, EPOLL_CTL_ADD, eventFd, &epollEvent);
}

MessageQueue::~MessageQueue() {

    if (eventFd) {
        close(eventFd);
    }

    if (epollFd) {
        close(epollFd);
    }

}

bool MessageQueue::enqueueMessage(Message *msg) {

    if (msg->target == nullptr) {
        throw std::runtime_error("Message must have a target");
    }

    std::lock_guard<std::mutex> lock(mutex);

    bool needWake = false;

    //只做普通消息，单链表插入逻辑
    if (mMessages == nullptr || mMessages->when > msg->when) {
        msg->next = mMessages;
        mMessages = msg;
        needWake = true;
    } else {

        Message *p = mMessages;
        Message *pre = nullptr;
        while (p != nullptr && p->when < msg->when) {
            pre = p;
            p = p->next;
        }
        pre->next = msg;
        msg->next = p;

        needWake = mBlocked;
    }


    if (needWake) {
        nativeWake();
    }

    return true;
}


Message *MessageQueue::next() {

    long nextPollTimeoutMillis = 0;

    for (;;) {
        //epoll_wait
        nativePollOnce(nextPollTimeoutMillis);

        std::lock_guard<std::mutex> lock(mutex);

        //拿下一个msg
        if (mMessages == nullptr) {
            nextPollTimeoutMillis = -1;
            mBlocked = true;
        } else {

            long now = Util::getCurrentTimeMillis();
            Message *p = mMessages;

            if (p->when < now) {
                mMessages = mMessages->next;
                p->next = nullptr;
                p->markInUse();
                return p;
            } else {
                nextPollTimeoutMillis = p->when - now;
            }
            mBlocked = false;
        }
        MY_PRINTF("nextPollTimeoutMillis=%ld",nextPollTimeoutMillis);
    }
}

void MessageQueue::nativePollOnce(long timeout) {
    struct epoll_event eventItems[1];
    int eventCount = epoll_wait(epollFd, eventItems, 1, timeout);
    if (eventCount > 0) {
        eventfd_t value;
        eventfd_read(eventFd, &value);
    }
}


void MessageQueue::nativeWake() {
    eventfd_write(eventFd, fdVal++);
}