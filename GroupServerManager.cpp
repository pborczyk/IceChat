//
// Created by howorang on 07.05.17.
//

#include "GroupServerManager.h"

void GroupServerManagerI::
DeleteGroup(const ::std::string &, const ::Ice::Current &) {

}

Groups GroupServerManagerI::
ListGroups(const ::Ice::Current &) {
    return Chat::Groups();
}

GroupServerPrx GroupServerManagerI::
CreateGroup(const ::std::string &, const ::Ice::Current &) {
    return Chat::GroupServerPrx();
}

GroupServerPrx GroupServerManagerI::
getGroupServerByName(const ::std::string &, const ::Ice::Current &) {
    return Chat::GroupServerPrx();
}
