#include "GroupServer.h"

::std::string GroupServerI::
Name(const ::Ice::Current &) {
    return std::__cxx11::string();
}

::Chat::Users GroupServerI::
UserList(const ::Ice::Current &) {
    return Chat::Users();
}

void GroupServerI::
SendMessage(const ::std::string &, const ::Chat::UserPrx &, const ::Ice::Current &) {

}

void GroupServerI::
Leave(const ::Chat::UserPrx &, const ::Ice::Current &) {

}

void GroupServerI::
join(const ::Chat::UserPrx &, const ::Ice::Current &) {

}
