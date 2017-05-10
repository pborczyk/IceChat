//
// Created by howorang on 07.05.17.
//

#include "servants/GroupServer.h"
#include "servants/GroupServerManager.h"
#include "Ice/Ice.h"


GroupServerPrx GroupServerManagerI::
CreateGroup(const ::std::string & name, const ::Ice::Current & current) {

    Ice::Identity id;
    id.name = name;

    if(current.adapter ->find(id) != NULL) {
        NameAlreadyExists e;
        throw e;
    }

    GroupServerPtr newGroupServer = new GroupServerI(name);
    GroupServerPrx newServerProxy = newServerProxy.uncheckedCast(current.adapter -> add(newGroupServer, id));
    groups.push_back(newServerProxy);
    
    std::cout << "Dodano grupe " << name << std::endl;
    
    return newServerProxy;
}

void GroupServerManagerI::
DeleteGroup(const ::std::string & name, const ::Ice::Current & current) {
    Ice::Identity id;
    id.name = name;

    if(current.adapter ->find(id) == NULL) {
        NameDoesNotExist e;
        throw e;
    }
    current.adapter -> remove(id);

    std::vector<GroupServerPrx>::iterator it;
    for (it = groups.begin();it < groups.end(); it++) {
        GroupServerPrx prx = *it;
        if(prx ->ice_getIdentity() == id) {
            groups.erase( std::remove( groups.begin(), groups.end(), prx ), groups.end() );
            break;
        }
    }
}

Groups GroupServerManagerI::
ListGroups(const ::Ice::Current &) {
    return groups;
}

GroupServerPrx GroupServerManagerI::
getGroupServerByName(const ::std::string & name, const ::Ice::Current & current) {
    Ice::Identity id;
    id.name = name;
    GroupServerPrx groupServerPrx = groupServerPrx.uncheckedCast(current.adapter -> createProxy(id));
    return groupServerPrx;
}
