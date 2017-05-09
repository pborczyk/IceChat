#include "chat.h"

using namespace Chat;
#ifndef ICECHAT_GROUP_SERVER_H
#define ICECHAT_GROUP_SERVER_H

class GroupServerI : public virtual Chat::GroupServer {
public:

    GroupServerI();

    virtual void join(const UserPrx&, const ::Ice::Current& = ::Ice::Current());

    virtual void Leave(const UserPrx&, const ::Ice::Current& = ::Ice::Current());

    virtual void SendMessage(const ::std::string& message, const UserPrx& sender, const ::Ice::Current& = ::Ice::Current());

    virtual Users UserList(const ::Ice::Current& = ::Ice::Current());

    virtual ::std::string Name(const ::Ice::Current& = ::Ice::Current());

private:

    Users users;

};

#endif //ICECHAT_GROUP_SERVER_H