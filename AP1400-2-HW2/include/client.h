#ifndef CLIENT_H
#define CLIENT_H
#include"server.h"
#include<string>
#include<random>
#include"crypto.h"

class Server;
class Client
{
public:
	Client(const std::string id, const Server& server);
	std::string get_id() const;
	std::string get_publickey() const;
	double get_wallet() const;
	std::string sign(const std::string& txt) const;
	bool transfer_money(const std::string& receiver, double value) const;
	size_t generate_nonce()const;
private:
	Server const* const server;
	const std::string id;
	std::string public_key;
	std::string private_key;
};


#endif //CLIENT_H