#include "GroupServer.h"

::std::string GroupServerI::
Name(const ::Ice::Current &) {
    return std::__cxx11::string();
}

Users GroupServerI::
UserList(const ::Ice::Current &) {
    return users;
}

void GroupServerI::
SendMessage(const ::std::string & message, const UserPrx & sender, const ::Ice::Current &) {
}

void GroupServerI::
Leave(const UserPrx &, const ::Ice::Current &) {

}

void GroupServerI::
join(const UserPrx &, const ::Ice::Current &) {

}
