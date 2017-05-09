//
// Created by howorang on 08.05.17.
//

#include "User.h"
#include "Ice/Ice.h"

UserI::UserI(std::string name) {
    this->name = name;
}

::std::string UserI::getName(const ::Ice::Current & current) {
    return name;
}

void UserI::receiveText(const ::std::string & message, const ::Chat::UserPrx & sender, const ::Chat::GroupServerPrx & groupServerPrx,
                        const ::Ice::Current & current) {
    std::string senderUserName = sender -> getName();
    std::string groupName = groupServerPrx -> ice_getIdentity().name;
    std::cout << "Wiadomosc" << std::endl;
    std::cout <<  groupName << " " << senderUserName << " " << message << std::endl;
}

void UserI::receivePrivateText(const ::std::string & message, const ::Chat::UserPrx & sender,
                               const ::Ice::Current & current) {
    std::string senderUserName = sender -> getName();
    std::cout << "PRIV: " << senderUserName << " " << message << std::endl;
}


