#ifndef Q4_H
#define Q4_H
#include<numeric>
namespace q4{
    struct Vector2D
    {
    double x{};
    double y{}; 
    };

    struct Sensor
    {
        Vector2D pos;
        double accuracy{};    
    };

    inline Vector2D kalman_filter(std::vector<Sensor> sensors){
        Sensor sum = std::accumulate(sensors.begin(), sensors.end(), Sensor{{0, 0}, 0},
             [](const Sensor& s1, const Sensor &s2){
                return Sensor{{s1.pos.x + s2.pos.x * s2.accuracy, s1.pos.y + s2.pos.y *s2.accuracy}, s1.accuracy+s2.accuracy};
             });
        return Vector2D{sum.pos.x /sum.accuracy, sum.pos.y/sum.accuracy};
    }
}
#endif //Q4_H