//
// Created by lbrd on 2025/4/30.
//

#ifndef NATIVELOOPER_NATIVEHANDLER_H
#define NATIVELOOPER_NATIVEHANDLER_H



class MessageQueue;
class NativeLooper;
class Message;

// 使用 typedef 定义函数指针类型别名
typedef void (*CallBack)(Message *msg);



class NativeHandler {

private:
    CallBack mCallBack;
    NativeLooper &mLooper;
    MessageQueue &mQueue;


public:
    NativeHandler();

    NativeHandler(CallBack callBack);

    NativeHandler(NativeLooper &looper, CallBack callBack);

    void dispatchMessage(Message *msg);

    void sendMessageDelay(Message *message, long delay);

    void sendMessageAtTime(Message *message, long when);

    void sendMessage(Message *message);
};




#endif //NATIVELOOPER_NATIVEHANDLER_H
