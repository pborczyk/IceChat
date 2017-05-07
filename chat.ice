module Chat {

interface GroupServer;
interface GroupServerManager;
interface User;

exception NameDoesNotExist{};
exception NameAlreadyExists{};
exception ServerAlreadyRegistered{};
exception ServerDoesNotExist{};
exception UserAlreadyRegistered{};
exception UserDoesNotExist{};

sequence<GroupServer> Groups;
sequence<User> Users; 

interface ChatServer {
	void LogIn(User* callback) throws NameAlreadyExists;
	User* getUserByName(string name);
	Groups GroupList();
	GroupServer* getGroupServerByName(string name) throws NameDoesNotExist;
	void CreateGroup(string name) throws NameAlreadyExists;
	void DeleteGroup(string name) throws NameDoesNotExist;
	void registerServer(GroupServerManager* serverManager) throws ServerAlreadyRegistered;
	void unregisterServer(GroupServerManager* serverManager) throws ServerDoesNotExist;
};

interface GroupServer {
	void join(User* who)  throws UserAlreadyRegistered;
	void Leave(User* who) throws UserDoesNotExist;
	void SendMessage(string message, User* sender) throws UserDoesNotExist;
	Users UserList();
	string Name();
};

interface GroupServerManager {
	GroupServer* CreateGroup(string name) throws NameAlreadyExists;
	Groups ListGroups();
	void DeleteGroup(string name) throws NameDoesNotExist;
	GroupServer* getGroupServerByName(string name) ;
};

interface User {
	string getName();
	void receiveText(string msg, User* sender, GroupServer* gServer);
	void receivePrivateText(string msg, User* sender);
};

};
