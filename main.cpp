#include <unistd.h>

#include "NativeHandler.h"
#include "NativeLooper.h"
#include "Message.h"
#include "Util.h"

#define WHAT_PRINT_HELLO 0
#define WHAT_PRINT_BYE 1
#define WHAT_PRINT_HI 2

typedef void *(*ThreadRun)(void *);

void *testSendMessage(void *args) {

    MY_PRINTF("testSendMessage");

    NativeHandler *handler = static_cast<NativeHandler *>(args);

    Message *message = Message::obtain();
    message->what = WHAT_PRINT_BYE;
    handler->sendMessageDelay(message, 5000);

    Message *message1 = Message::obtain();
    message1->what = WHAT_PRINT_HELLO;
    handler->sendMessageDelay(message1, 9000);

    sleep(2);

    Message *message2 = Message::obtain();
    message2->what = WHAT_PRINT_HI;
    handler->sendMessage(message2);

    return 0;
}


void handleMessage(Message *message) {

    switch (message->what) {
        case WHAT_PRINT_HELLO:

            MY_PRINTF("hello!!");
            break;

        case WHAT_PRINT_BYE:

            MY_PRINTF("bye!!");

            break;
        case WHAT_PRINT_HI:

            MY_PRINTF("hi!!");

            break;

        default:
            break;

    }


}


int main() {


    NativeLooper::prepare();


    NativeHandler handler = NativeHandler(handleMessage);

    pthread_t test_thread;
    pthread_create(&test_thread, nullptr, static_cast<ThreadRun>(testSendMessage), &handler);

    NativeLooper::loop();


    return 0;
}
