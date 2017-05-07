#include "chat.h"

using namespace Chat;

class GroupServerManagerI : public virtual GroupServerManager {
    virtual GroupServerPrx CreateGroup(const ::std::string&, const ::Ice::Current& = ::Ice::Current());

    virtual Groups ListGroups(const ::Ice::Current& = ::Ice::Current());

    virtual void DeleteGroup(const ::std::string&, const ::Ice::Current& = ::Ice::Current());

    virtual GroupServerPrx getGroupServerByName(const ::std::string&, const ::Ice::Current& = ::Ice::Current());


};
