#include "GroupServer.h"
#include "Ice/Ice.h"

::std::string GroupServerI::
Name(const ::Ice::Current &) {
    return std::__cxx11::string();
}

Users GroupServerI::
UserList(const ::Ice::Current &) {
    return users;
}

void GroupServerI::
SendMessage(const ::std::string & message, const UserPrx & sender, const ::Ice::Current & current) {
    GroupServerPrx groupServerPrx = GroupServerPrx::uncheckedCast(current.adapter->createProxy(current.id));


}

void GroupServerI::
Leave(const UserPrx & userPrx, const ::Ice::Current &) {
    users.erase( std::remove( users.begin(), users.end(), userPrx ), users.end() );
}

void GroupServerI::
join(const UserPrx & userPrx, const ::Ice::Current &) {
    users.push_back(userPrx);
}
