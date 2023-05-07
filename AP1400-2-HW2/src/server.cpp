#include "server.h"

extern std::vector<std::string> pending_trxs{};
Server::Server()=default;
std::shared_ptr<Client> Server::get_client(const std::string& id) const{
    for(auto& elem: clients){
        if(elem.first->get_id() == id){
            return elem.first;
        }
    }
    return nullptr;
}

double Server::get_wallet(const std::string& id) const{
    for(auto& elem: clients){
        if(elem.first->get_id() == id){
            return elem.second;
        }
    }
    return 0;
}

std::shared_ptr<Client> Server::add_client(const std::string& id){
    auto client_pointer = get_client(id);
    
    
    if(client_pointer != nullptr ){
        // balbal
        static std::mt19937_64 gen;
        std::uniform_int_distribution distr(0, 9999);
        std::string num = std::to_string(distr(gen));
        std::string new_id(4-num.length(), '0');
        new_id = id + new_id + num;
        std::shared_ptr<Client> new_client_p(new Client(new_id, *this));
        clients[new_client_p] = 5.0;
        return new_client_p;
    }
    else{
        std::shared_ptr<Client> new_client_p(new Client(id, *this));
        clients[new_client_p] = 5.0;
        return new_client_p;
    }
}

bool Server::parse_trx(const std::string& trx, std::string& sender, std::string& receiver, double& value){
    std::string segment{};
    std::vector<std::string> parses;
    for(size_t i = 0, len = trx.length(); i < len; i++){
        if(trx[i] == '-'){
            parses.push_back(segment);
            segment.clear();
        }
        else{
            segment = segment + trx[i];
        }
    }
    if(!segment.empty())
        parses.push_back(segment);
    
    if(parses.size() != 3) throw std::runtime_error("invalid trx for invalid size");
    for(std::string& word: parses){
        if(word.empty()) throw std::runtime_error("invalid trx for --");
    }
    value = std::stod(parses[2]);
    sender = parses[0]; receiver = parses[1];
    return true;
}

bool Server::add_pending_trx(const std::string& trx, const std::string& signature)const{
    std::string sender, receiver; double value;
    parse_trx(trx, sender, receiver, value);
    // to search whether the sender and the receiver is in the server
    std::shared_ptr<Client> sender_p{get_client(sender)}, receiver_p{get_client(receiver)};
    if(sender_p == nullptr || receiver_p == nullptr){  // if sender of receiver not in the sever
        std::cout << "nullptr";
        return false;
    }
    if(crypto::verifySignature(sender_p->get_publickey(), trx, signature) && get_wallet(receiver) >= value){
        pending_trxs.push_back(trx);
        // show_pending_transactions();
        return true;
    }
    return false;
}

size_t Server::mine(){
    // // generate the mempool
    // show_wallets(*this);
    std::string mempool{};
    for(std::string& transaction:pending_trxs){
        mempool = mempool+transaction;
    }
    bool success = false;
    while(!success){
        for(auto& client: clients){
            // asks each Client for a nonce and calculates the sha256 of the final string
            std::string mempool_final(mempool);
            size_t nonce = client.first->generate_nonce();
            mempool_final += std::to_string(nonce);
            // calculates the sha256 of the final string
            std::string hash(crypto::sha256(mempool_final));
            std::cout << "hash: " << hash << std::endl;
            /* For each nonce if the generated sha256 
            has 4 zeros in a row 
            in the first 10 numbers, 
            then the mine is successful and
            the client who called the correct nonce 
            will be awarded with 6.25 coins. */
            if(hash.substr(0, 10).find("000") != std::string::npos){
                client.second += 6.25;
                for(auto& transaction: pending_trxs){
                    std::string sender, receiver; double value;
                    parse_trx(transaction, sender, receiver, value);
                    clients[get_client(sender)] -= value;
                    clients[get_client(receiver)] += value;
                }
                pending_trxs.clear();
                return nonce;
            }
        }
    }
    return 0;
}

void  show_wallets(const Server& server)
{
	std::cout << std::string(20, '*') << std::endl;
	for(const auto& client: server.clients)
		std::cout << client.first->get_id() <<  " : "  << client.second << std::endl;
	std::cout << std::string(20, '*') << std::endl;
}

void  show_pending_transactions()
{
	std::cout  <<  std::string(20, '*') <<  std::endl;
	for(const  auto& trx : pending_trxs)
		std::cout << trx <<  std::endl;
	std::cout  <<  std::string(20, '*') <<  std::endl;
}
