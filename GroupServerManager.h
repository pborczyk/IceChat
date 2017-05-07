#include "chat.h"

class GroupServerManagerI : public virtual Chat::GroupServerManager {
    virtual ::Chat::GroupServerPrx CreateGroup(const ::std::string&, const ::Ice::Current& = ::Ice::Current());

    virtual ::Chat::Groups ListGroups(const ::Ice::Current& = ::Ice::Current());

    virtual void DeleteGroup(const ::std::string&, const ::Ice::Current& = ::Ice::Current());

    virtual ::Chat::GroupServerPrx getGroupServerByName(const ::std::string&, const ::Ice::Current& = ::Ice::Current());


};
