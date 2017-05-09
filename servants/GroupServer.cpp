#include "GroupServer.h"
#include "Ice/Ice.h"

::std::string GroupServerI::
Name(const ::Ice::Current & current) {
    return current.id.name;
}

Users GroupServerI::
UserList(const ::Ice::Current &) {
    return users;
}

void GroupServerI::
SendMessage(const ::std::string & message, const UserPrx & sender, const ::Ice::Current & current) {
    GroupServerPrx groupServerPrx = GroupServerPrx::uncheckedCast(current.adapter->createProxy(current.id));
    std::vector<UserPrx>::iterator it;

    if(!(std::find(users.begin(), users.end(), sender) != users.end())) {
        throw new UserDoesNotExist();
    }

    for (it = users.begin();it < users.end(); it++) {
        UserPrx prx = *it;
        prx ->receiveText(message, sender, groupServerPrx);
    }

}

void GroupServerI::
Leave(const UserPrx & userPrx, const ::Ice::Current &) {

    if(!(std::find(users.begin(), users.end(), userPrx) != users.end())) {
        throw new UserDoesNotExist();
    }

    users.erase( std::remove( users.begin(), users.end(), userPrx ), users.end() );
}

void GroupServerI::
join(const UserPrx & userPrx, const ::Ice::Current &) {

    if((std::find(users.begin(), users.end(), userPrx) != users.end())) {
        throw new UserAlreadyRegistered();
    }

    users.push_back(userPrx);
}

GroupServerI::GroupServerI() {

}
