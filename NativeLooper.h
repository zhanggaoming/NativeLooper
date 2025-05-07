//
// Created by lbrd on 2025/4/30.
//

#ifndef NATIVELOOPER_NATIVELOOPER_H
#define NATIVELOOPER_NATIVELOOPER_H


#include "pthread.h"

class MessageQueue;

class NativeLooper {

private:
    MessageQueue *mQueue;
    static const pthread_key_t sThreadLocal;
    bool mInLoop = false;

    NativeLooper(bool quitAllowed);

    ~NativeLooper();

public:

    static NativeLooper *myLooper();

    static void prepare();

    static void prepare(bool quitAllowed);

    static void loop();

    MessageQueue &messageQueue();
};




#endif //NATIVELOOPER_NATIVELOOPER_H
