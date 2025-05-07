//
// Created by lbrd on 2025/5/6.
//

#ifndef NATIVELOOPER_MESSAGE_H
#define NATIVELOOPER_MESSAGE_H

#include <mutex>

#define FLAG_IN_USE  1<<0

class NativeHandler;

class Message {

protected:
    static Message *messagePool;
    static int poolSize;
    static std::mutex mutex;
public:
    int what;
    int arg1;
    int arg2;
    long when;
    NativeHandler *target;
    Message *next;
    int flags;

    Message() {

    }

    ~Message() {

    }

    static Message* obtain();

    void recycleUnchecked();

    void markInUse();

    void recycle();

    bool isInUse();
};


#endif //NATIVELOOPER_MESSAGE_H
