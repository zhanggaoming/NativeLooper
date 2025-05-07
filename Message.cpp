//
// Created by lbrd on 2025/4/30.
//

#include "Message.h"

#define MAX_MESSAGE_POOL_SIZE 50

Message* Message::messagePool = nullptr;
int Message::poolSize = 0;
std::mutex Message::mutex;

void Message::markInUse() {
    flags |= FLAG_IN_USE;
}

bool Message::isInUse() {
    return flags & FLAG_IN_USE;
}

void Message::recycle() {
    std::lock_guard<std::mutex> lock(mutex);

    if (isInUse()) {
        throw std::runtime_error("his message cannot be recycled because it is still in use.");
    }

   recycleUnchecked();

}

void Message::recycleUnchecked() {
    if (poolSize < MAX_MESSAGE_POOL_SIZE) {
        flags = FLAG_IN_USE;
        what = 0;
        arg1 = 0;
        arg2 = 0;
        when = 0;
        target = nullptr;
        next = messagePool;
        messagePool = this;
        poolSize++;
    }
}

Message* Message::obtain() {
    std::lock_guard<std::mutex> lock(mutex);

    if (messagePool) {

        Message *msg = messagePool;

        messagePool = msg->next;

        msg->flags = 0;
        poolSize--;

        return msg;
    }

    return new Message();
}