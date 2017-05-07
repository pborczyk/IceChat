#include "chat.h"

using namespace Chat;
#ifndef ICECHAT_GROUP_SERVER_MANGER_H
#define ICECHAT_GROUP_SERVER_MANGER_H


class GroupServerManagerI : public virtual GroupServerManager {
    virtual GroupServerPrx CreateGroup(const ::std::string&, const ::Ice::Current& = ::Ice::Current());

    virtual Groups ListGroups(const ::Ice::Current& = ::Ice::Current());

    virtual void DeleteGroup(const ::std::string&, const ::Ice::Current& = ::Ice::Current());

    virtual GroupServerPrx getGroupServerByName(const ::std::string&, const ::Ice::Current& = ::Ice::Current());


};


#endif //ICECHAT_GROUP_SERVER_MANGER_H