#include "chat.h"


class GroupServerI : public virtual Chat::GroupServer {

    virtual void join(const ::Chat::UserPrx&, const ::Ice::Current& = ::Ice::Current());

    virtual void Leave(const ::Chat::UserPrx&, const ::Ice::Current& = ::Ice::Current());

    virtual void SendMessage(const ::std::string&, const ::Chat::UserPrx&, const ::Ice::Current& = ::Ice::Current());

    virtual ::Chat::Users UserList(const ::Ice::Current& = ::Ice::Current());

    virtual ::std::string Name(const ::Ice::Current& = ::Ice::Current());


};