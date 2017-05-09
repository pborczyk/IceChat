#include <Ice/Ice.h>
#include <servants/GroupServerManager.h>
#include "chat.h"

using namespace Chat;

class IceChatClient : virtual public Ice::Application {
public:
    virtual int run(int, char*[]) {

        std::cout << "Podaj port: ";
        std::string port;
        std::cin >> port;
        std::string proxyDef = "tcp -p ";
        proxyDef.append(port);
        
        ChatServerPrx chatServerPrx = chatServerPrx.uncheckedCast(communicator() -> propertyToProxy("ChatServer.Proxy"));
        Ice::ObjectAdapterPtr objectAdapter = communicator() -> createObjectAdapterWithEndpoints("GroupServerManagerAdapter", proxyDef);
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