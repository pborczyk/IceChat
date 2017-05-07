//
// Created by howorang on 07.05.17.
//

#include "GroupServerManager.h"

void GroupServerManagerI::
DeleteGroup(const ::std::string &, const ::Ice::Current &) {

}

::Chat::Groups GroupServerManagerI::
ListGroups(const ::Ice::Current &) {
    return Chat::Groups();
}

::Chat::GroupServerPrx GroupServerManagerI::
CreateGroup(const ::std::string &, const ::Ice::Current &) {
    return Chat::GroupServerPrx();
}

::Chat::GroupServerPrx GroupServerManagerI::
getGroupServerByName(const ::std::string &, const ::Ice::Current &) {
    return Chat::GroupServerPrx();
}
