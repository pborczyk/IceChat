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
        for (it = groups.begin(); it < groups.end(); it++) {
            GroupServerPrx groupServerPrx = groupServerPrx.checkedCast(*it);
            std::cout << i + 1 << ":" << groupServerPrx->Name() << std::endl;
            i++;
        }
    }

    virtual int run(int, char *[]) {
        std::cout << "Podaj port: ";
        std::string port;
        std::cin >> port;
        std::string proxyDef = "tcp -p ";
        proxyDef.append(port);
        
        ChatServerPrx chatServerPrx = chatServerPrx.uncheckedCast(communicator()->propertyToProxy("ChatServer.Proxy"));
        Ice::ObjectAdapterPtr objectAdapter = communicator()->createObjectAdapterWithEndpoints("Client", proxyDef);
        std::string username = prompt_for_input("Podaj nick: ");
        UserPtr newUser = new UserI(username);
        objectAdapter->add(newUser, Ice::stringToIdentity(username));
        objectAdapter->activate();
        Ice::ObjectPrx userPrx_raw = objectAdapter->createProxy(Ice::stringToIdentity(username));
        UserPrx userPrx = userPrx.uncheckedCast(userPrx_raw);
        UserPrx reciever;

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
                    std::cout << "Wysłano";
                    break;
                }

                case 4:
                    std::string reciverName = prompt_for_input("Podaj nick: ");
                    try {
                        reciever = reciever.uncheckedCast(chatServerPrx->getUserByName(reciverName));
                        std::string privateMessage = prompt_for_input("Podaj wiadomosc: ");
                        reciever->receivePrivateText(privateMessage, userPrx);
                        std::cout << "Wyslano" << std::endl;
                    } catch (const IceUtil::NullHandleException &) {
                        std::cout << "Nie ma takiego uzytkownika" << std::endl;
                    }

                    break;
            }
        }
        communicator()->waitForShutdown();

        printf("shutdown");
        return 0;
    }
};

void group_menu() {
    std::cout << "1.Dodaj grupę" << std::endl;
    std::cout << "2.Wejdz do grupy" << std::endl;
    std::cout << "3.Napisz cos na grupie" << std::endl;
    std::cout << "4.Wyslij wiadomosc prywatna" << std::endl;
}

std::string prompt_for_input(std::string message) {
    std::string input;
    std::cout << message;
    std::cin >> input;
    return input;
}

int
main(int argc, char *argv[]) {
    IceChatClient app;
    return app.main(argc, argv, "ice.config");
}