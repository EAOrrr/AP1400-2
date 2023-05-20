#ifndef Q3_H
#define Q3_H
#include<sstream>
#include<fstream>
#include<queue>
#include<vector>
namespace q3{
    inline std::vector<std::string> split(std::string line, char delim){
        std::istringstream iss(line);
        std::string token;
        std::vector<std::string> tokens;

        while(std::getline(iss, token, delim)){
            tokens.push_back(token);
        }

        return tokens;
    }

    struct Flight{
        std::string flight_number;
        size_t duration;
        size_t connections;
        size_t connection_times;
        size_t price;
    };

    inline std::priority_queue<Flight, std::vector<Flight>, std::function<bool(const Flight&, const Flight&)>> 
            gather_flights(std::string filename){
        std::ifstream input(filename);
        if(!input.is_open()){
            std::cerr << "failed to open the file" << std::endl;
            std::exit(EXIT_FAILURE);
        }

        std::string line;
        auto comp = [](const Flight& f1, const Flight &f2){
            return f1.connection_times+f1.duration+ 3* f1.price >
                    f2.connection_times + f2.duration + 3* f2.price;
        };
        std::priority_queue<Flight, std::vector<Flight>, std::function<bool(const Flight&, const Flight&)>> pq{comp};
        while(std::getline(input, line)){
            std::vector<std::string> tokens = split(line, '-');

            std::string name = tokens[1].substr(tokens[1].find(':')+1);
            name.erase(std::remove(name.begin(), name.end(), ' '), name.end());
            
            // for simple numbers
            size_t connections = stoi(tokens[3].substr(tokens[3].find(':')+1));
            size_t price = stoi(tokens[5].substr(tokens[5].find(':')+1));

            // for time
            std::string durationStr = tokens[2].substr(tokens[2].find(':')+1);
            durationStr.erase(std::remove(durationStr.begin(), durationStr.end(), ' '), durationStr.end());
            size_t DhourPosition = durationStr.find('h');
            size_t duration = stoi(durationStr.substr(0, DhourPosition)) * 60;
            if(durationStr.length() > DhourPosition+1) 
                duration += stoi(durationStr.substr(DhourPosition+1));

            // for connectionTime
            std::string connectionStr = tokens[4].substr(tokens[4].find(':')+1);
            std::vector<std::string> connectionVec = split(connectionStr, ',');
            size_t connection_time = 0;
            for(auto& connection: connectionVec){
                connection.erase(std::remove(connection.begin(), connection.end(), ' '), connection.end());
                size_t ChourPosition = connection.find('h');
                connection_time += stoi(connection.substr(0, ChourPosition)) * 60;
                if(connection.length() > ChourPosition+1)
                    connection_time += stoi(connection.substr(ChourPosition+1));
            }
            pq.emplace(name, duration, connections, connection_time, price);
        }
        return pq;
    }
    
}
#endif //Q3_H