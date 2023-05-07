#include "client.h"
#include "server.h"

Client::Client(const std::string id, const Server& server):id(id), server(&server){
    crypto::generate_key(public_key, private_key);
}

std::string Client::get_id()const{
    return id;
}

std::string Client::get_publickey()const{
    return public_key;
}

double Client::get_wallet() const{
    return server->get_wallet(id);
}

std::string Client::sign(const std::string& txt) const{
    return crypto::signMessage(private_key, txt);
}

bool Client::transfer_money(const std::string& receiver, double value)const{
    const std::string trx = id+"-"+receiver+"-"+std::to_string(value);
    return server->add_pending_trx(trx, sign(trx));
}

size_t Client::generate_nonce()const{
    static std::mt19937_64 gen;
    return gen();
}