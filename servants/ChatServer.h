//
// Created by howorang on 08.05.17.
//

#ifndef ICEHELLO_CHATSERVER_H
#define ICEHELLO_CHATSERVER_H

#include "chat.h"
#include <string>

using namespace Chat;

class ChatServerI : public virtual ChatServer {

public:

    virtual void LogIn(const UserPrx&, const ::Ice::Current& = ::Ice::Current());

    virtual UserPrx getUserByName(const ::std::string&, const ::Ice::Current& = ::Ice::Current());

    virtual Groups GroupList(const ::Ice::Current& = ::Ice::Current());

    virtual GroupServerPrx getGroupServerByName(const ::std::string&, const ::Ice::Current& = ::Ice::Current());

    virtual void CreateGroup(const ::std::string&, const ::Ice::Current& = ::Ice::Current());

    virtual void DeleteGroup(const ::std::string&, const ::Ice::Current& = ::Ice::Current());

    virtual void registerServer(const GroupServerManagerPrx&, const ::Ice::Current& = ::Ice::Current());

    virtual void unregisterServer(const GroupServerManagerPrx&, const ::Ice::Current& = ::Ice::Current());

private:
    struct GroupServerManagerLoad;

    Groups groups;
    Users users;
    std::vector<std::string> userNames;
    std::map<GroupServerManagerPrx, GroupServerManagerLoad> groupServersManagers;

    GroupServerManagerPrx getLeastLoadedServerManager();

    GroupServerManagerPrx getHostingServerManager(std::string groupName);

    bool groupExists(std::string name);

    struct GroupServerManagerLoad {
        int groupCount;
        std::vector<std::string> groupNames;
    };

    friend bool comparator(std::pair<GroupServerManagerPrx, GroupServerManagerLoad> i, std::pair<GroupServerManagerPrx, GroupServerManagerLoad> j);
};

bool comparator(std::pair<GroupServerManagerPrx, ChatServerI::GroupServerManagerLoad> i,
                std::pair<GroupServerManagerPrx, ChatServerI::GroupServerManagerLoad> j);

#endif //ICEHELLO_CHATSERVER_H
