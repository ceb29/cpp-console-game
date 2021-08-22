#include <time.h>

class Game_Time {
    unsigned long long int millis;
    clock_t timer;
    float clock_millis;

public:
    Game_Time(clock_t time);
    unsigned long long int get_millis(void);
    void clear_millis(void);
    void update_time(void);
};