//
// Created by howorang on 08.05.17.
//

#ifndef ICECHAT_USER_H
#define ICECHAT_USER_H

#include "chat.h"
#include <string>

using namespace Chat;

class UserI : public virtual User {

public:
    UserI(std::string name);

    virtual ::std::string getName(const ::Ice::Current& = ::Ice::Current());

    virtual void receiveText(const ::std::string&, const ::Chat::UserPrx&, const ::Chat::GroupServerPrx&, const ::Ice::Current& = ::Ice::Current());

    virtual void receivePrivateText(const ::std::string&, const ::Chat::UserPrx&, const ::Ice::Current& = ::Ice::Current());

private:

    std::string name;
};

#endif //ICECHAT_USER_H
