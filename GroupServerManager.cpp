#include <Ice/Ice.h>
#include <servants/GroupServerManager.h>
#include "chat.h"

using namespace Chat;

class IceChatClient : virtual public Ice::Application {
public:
    virtual int run(int, char*[]) {
        ChatServerPrx chatServerPrx = chatServerPrx.uncheckedCast(communicator() -> propertyToProxy("ChatServer.Proxy"));
        Ice::ObjectAdapterPtr objectAdapter = communicator() -> createObjectAdapterWithEndpoints("GroupServerManagerAdapter", "tcp -p 9999");
        GroupServerManagerPtr groupServerManager = new GroupServerManagerI();

        GroupServerManagerPrx groupServerManagerPrx =
                groupServerManagerPrx.uncheckedCast(objectAdapter ->addWithUUID(groupServerManager));
        objectAdapter -> activate();
        chatServerPrx -> registerServer(groupServerManagerPrx);
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