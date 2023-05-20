#ifndef Q2_H
#define Q2_H
#include<fstream>
#include<sstream>
#include<algorithm>
#include<vector>
namespace q2{
    struct Patient{
        std::string name;
        size_t age;
        size_t smokes;
        size_t area_q;
        size_t alkhol;
    };

    inline std::vector<std::string> split(std::string line, char delim){
        std::istringstream iss(line);
        std::string token;
        std::vector<std::string> tokens;

        while(std::getline(iss, token, delim)){
            tokens.push_back(token);
        }

        return tokens;
    }

    inline std::vector<Patient> read_file(std::string filename){
        // open the file
        std::ifstream input(filename);
        if(!input.is_open()){
            std::cerr << "failed to open the file" << std::endl;
            std::exit(EXIT_FAILURE);
        }
        // getline
        std::string line;

        std::getline(input, line);
        std::getline(input, line); // skip the first two lines
        
        std::vector<Patient> patients;
        while(std::getline(input, line)){
            std::vector<std::string> tokens = split(line, ',');
            tokens[0].erase(std::remove(tokens[0].begin(), tokens[0].end(), ' '), tokens[0].end());
            tokens[1].erase(std::remove(tokens[1].begin(), tokens[1].end(), ' '), tokens[1].end());
            std::string name = tokens[0] + " " + tokens[1];
            size_t age = std::stoi(tokens[2]);
            size_t smokes = std::stoi(tokens[3]);
            size_t areaQ = std::stoi(tokens[4]);
            size_t alkhol = std::stoi(tokens[5]);
            patients.emplace_back(name, age, smokes, areaQ, alkhol);
        }
        return patients;
    }

    inline void sort(std::vector<Patient>& patients){
        std::sort(patients.begin(), patients.end(), [](const Patient& p1, const Patient& p2){
            return 3*p1.age + 5*p1.smokes + 2* p1.area_q + 4*p1.alkhol >
                   3*p2.age + 5*p2.smokes + 2* p2.area_q + 4*p2.alkhol;
        });
    }

}
#endif //Q2_H