//
// Created by lbrd on 2025/4/30.
//

#include "NativeHandler.h"
#include "NativeLooper.h"
#include "MessageQueue.h"
#include "Message.h"
#include "Util.h"


NativeHandler::NativeHandler() : NativeHandler(nullptr) {

}

NativeHandler::NativeHandler(CallBack callBack) : NativeHandler(*NativeLooper::myLooper(), callBack) {

}


NativeHandler::NativeHandler(NativeLooper &looper, CallBack callBack)
        : mLooper(looper), mCallBack(callBack), mQueue(mLooper.messageQueue()) {

}


void NativeHandler::dispatchMessage(Message *msg) {
    if (mCallBack){
        mCallBack(msg);
    }
}

void NativeHandler::sendMessage(Message *message) {
    sendMessageAtTime(message,0);
}

void NativeHandler::sendMessageAtTime(Message *message, long when) {
    message->target= this;
    message->when=when;
    mQueue.enqueueMessage(message);
}


void NativeHandler::sendMessageDelay(Message *message, long delay) {
    sendMessageAtTime(message,Util::getCurrentTimeMillis()+delay);
}