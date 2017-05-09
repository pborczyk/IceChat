#include <Ice/Ice.h>
#include <servants/User.h>
#include "chat.h"

using namespace Chat;

void group_menu();
std::string prompt_for_input(std::string message);

class IceChatClient : virtual public Ice::Application {
public:

    GroupServerPrx chosenGroup;

    void display_all_groups(Groups groups) {
        std::vector<GroupServerPrx>::iterator it;
        int i = 0;
        for (it = groups.begin();it < groups.end(); it++) {
            GroupServerPrx groupServerPrx = groupServerPrx.checkedCast(*it);
            std::cout << i + 1 << ":" << groupServerPrx -> Name() << std::endl;
            i++;
        }
    }

    virtual int run(int, char*[]) {
        ChatServerPrx chatServerPrx = chatServerPrx.uncheckedCast(communicator()->propertyToProxy("ChatServer.Proxy"));
        Ice::ObjectAdapterPtr objectAdapter = communicator()->createObjectAdapterWithEndpoints("Client","tcp -p 9998");
        std::string username = prompt_for_input("Podaj nick: ");
        UserPtr newUser = new UserI(username);
        objectAdapter->add(newUser, Ice::stringToIdentity(username));
        objectAdapter->activate();
        Ice::ObjectPrx userPrx_raw = objectAdapter->createProxy(Ice::stringToIdentity(username));
        UserPrx userPrx = userPrx.uncheckedCast(userPrx_raw);

        chatServerPrx->LogIn(userPrx);
        std::cout << "logged in" << std::endl;
        while (1) {
            group_menu();
            int choice;
            std::cin >> choice;
            switch (choice) {
                case 1: {
                    std::string groupName = prompt_for_input("Nazwa grupy: ");
                    chatServerPrx->CreateGroup(groupName);
                    std::cout << "Utworzono";
                    break;
                }

                case 2: {
                    Groups groups = chatServerPrx->GroupList();
                    display_all_groups(groups);
                    std::cout << "Wybierz grupę";
                    int choice;
                    std::cin >> choice;
                    chosenGroup = groups[--choice];
                    chosenGroup->join(userPrx);
                    break;
                }
                case 3: {
                    std::string message = prompt_for_input("Wiadomosc: ");
                    chosenGroup->SendMessage(message, userPrx);
                    break;
                }
            }
        }
        communicator() -> waitForShutdown();

        printf("shutdown");
        return 0;
    }
};

void group_menu() {
    std::cout << "Dodaj grupę: 1" << std::endl;
    std::cout << "Wejdz do grupy: 2" << std::endl;
    std::cout << "Napisz cos na grupie" << std::endl;
}

std::string prompt_for_input(std::string message) {
    std::string input;
    std::cout << message;
    std::cin >> input;
    return input;
}

int
main(int argc, char* argv[])
{
#ifdef ICE_STATIC_LIBS
    Ice::registerIceSSL();
#endif
    IceChatClient app;
    return app.main(argc, argv, "ice.config");
}