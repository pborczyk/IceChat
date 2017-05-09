#include <Ice/Ice.h>
#include <servants/ChatServer.h>
#include "chat.h"

using namespace Chat;

class IceChatClient : virtual public Ice::Application {
public:
    virtual int run(int, char*[]) {
        Ice::ObjectAdapterPtr objectAdapter = communicator() -> createObjectAdapter("ChatServer");
        ChatServerPtr chatServer = new ChatServerI();
        objectAdapter -> add(chatServer, Ice::stringToIdentity("chat_server"));
        objectAdapter -> activate();
        communicator() -> waitForShutdown();
        printf("shutdown");
        
        
        return 0;
    }
};

int
main(int argc, char* argv[])
{
    IceChatClient app;
    return app.main(argc, argv, "ice.config");
}