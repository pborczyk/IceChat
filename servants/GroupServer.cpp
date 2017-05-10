#include "GroupServer.h"
#include "Ice/Ice.h"

::std::string GroupServerI::
Name(const ::Ice::Current & current) {
    std::cout << "test";
    return name;
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
        UserDoesNotExist e;
        throw e;
    }

    for (it = users.begin();it < users.end(); it++) {
        UserPrx prx = *it;
        std::cout << "GONNA CRASH";
        prx ->receiveText(message, sender, groupServerPrx);
    }
    
    std::cout << "TEST";

}

void GroupServerI::
Leave(const UserPrx & userPrx, const ::Ice::Current &) {

    if(!(std::find(users.begin(), users.end(), userPrx) != users.end())) {
        UserDoesNotExist e;
        throw e;
    }

    users.erase( std::remove( users.begin(), users.end(), userPrx ), users.end() );
}

void GroupServerI::
join(const UserPrx & userPrx, const ::Ice::Current & current) {

    if((std::find(users.begin(), users.end(), userPrx) != users.end())) {
        UserAlreadyRegistered e;
        throw e;
    }
    
    users.push_back(userPrx);
}

GroupServerI::GroupServerI(std::string name) {
    this -> name = name;
}
