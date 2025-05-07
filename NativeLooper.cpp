//
// Created by zgm on 2025/4/30.
//

#include "NativeLooper.h"
#include "MessageQueue.h"
#include "NativeHandler.h"
#include "Message.h"

NativeLooper::NativeLooper(bool quitAllowed) {
    mQueue = new MessageQueue(quitAllowed);
}

void NativeLooper::loop() {

   NativeLooper *me= myLooper();

    if (me== nullptr){
        throw std::runtime_error("No Looper; Looper.prepare() wasn't called on this thread.");
    }

    if (me->mInLoop){
        return;
    }

    me->mInLoop= true;

    for (;;) {
       Message *msg= me->mQueue->next();

        if (msg == nullptr){
            return;
        }

        msg->target->dispatchMessage(msg);

        msg->recycleUnchecked();
    }

}

void NativeLooper::prepare(bool quitAllowed) {
    if (pthread_getspecific(sThreadLocal) != nullptr) {
        throw std::runtime_error("Only one Looper may be created per thread");
    }
    pthread_setspecific(sThreadLocal, new NativeLooper(quitAllowed));
}

void NativeLooper::prepare() {
    prepare(false);
}

NativeLooper *NativeLooper::myLooper() {
    return static_cast<NativeLooper *>(pthread_getspecific(sThreadLocal));
}

MessageQueue& NativeLooper::messageQueue(){
    return *mQueue;
}

const pthread_key_t NativeLooper::sThreadLocal = [] {
    pthread_key_t key;
    pthread_key_create(&key, nullptr); //
    return key; //
}();