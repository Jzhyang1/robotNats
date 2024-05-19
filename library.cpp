#include "library.h"
#include "firmware.h"



struct motion {
    char type;  //M=move, T=turn, D=delay
    int amount;
};

int target_tmillis = 0;
Vector<motion> traversal_path;
int traversal_position = 9999;
double traversal_speed;
int start_time;




void set_path(String path) {
    for (int i = 0; i < path.size(); ++i) {
        char dir = path[i];
        int amt = 0;
        while(i+1 < path.size() && isDigit(path[i+1])) {
            amt = amt * 10 + (path[i+1] - '0');
            ++i;
        }

        switch (dir)
        {
        case 'L': case 'l':
            traversal_path.push_back({'T', amt == 0 ? 90 : amt});
            traversal_path.push_back({'D', KILL_TMILLI});
            break;
        case 'R': case 'r':
            traversal_path.push_back({'T', amt == 0 ? -90 : -amt});
            traversal_path.push_back({'D', KILL_TMILLI});
            break;
        case 'F': case 'f':
            traversal_path.push_back({'M', amt == 0 ? 50 : amt});
            traversal_path.push_back({'D', KILL_TMILLI});
            break;
        case 'B': case 'b':
            traversal_path.push_back({'M', amt == 0 ? -50 : -amt});
            traversal_path.push_back({'D', KILL_TMILLI});
            break;
        case 'D': case 'd':
            traversal_path.push_back({'D', amt == 0 ? 1000 : amt});
            break;
        }
    }
}

/* @brief do set_target after set_path
*/
void set_target(int tmillis) {
    target_tmillis = tmillis;

    int lo = MIN_SPEED;
    int hi = MAX_SPEED;
    while(lo < hi) {
        int mid = (lo + hi)/2; 
        //robot goes too slow
        if(target_tmillis < sum_durations(mid)) lo = mid + 1;
        //robot goes too fast
        else if(target_tmillis > sum_durations(mid)) hi = mid - 1;
        //hit
        else lo = hi = mid;
    }

    traversal_speed = lo;
}

int sum_durations(int speed) {
    int tmillis = 0;
    for(motion m: traversal_path) {
        if(m.type == 'M') tmillis += translation_duration(m.amount, speed);
        else if(m.type == 'T') tmillis += turn_duration(m.amount);
        else if(m.type == 'D') tmillis += m.amount;
    }
    return tmillis;
}











int turn_duration(int amount) {
    if(amount < 0) return right_turn_millis(-amount);
    else return left_turn_millis(amount);
}

int translation_duration(int amount, int speed) {
    if(amount < 0) return backward_millis(-amount, speed);
    else return forward_millis(amount, speed);
}

void start() {
    //this will be useful for corrections
    start_time = millis();

    traversal_position = 0;
}

void next_motion(){
    if(traversal_position >= traversal_path.size()) return;
    motion m = traversal_path[traversal_position];
    int start_tmilli = millis();
    int stop_tmilli = start_tmilli;
    double initial_orientation = get_rotation_vector();

    switch (m.type)
    {
    case 'T':
    {
        int left_right_sign = m.amount > 0 ? 1 : -1;
        power_left_motor(-TURN_SPEED * left_right_sign); 
        power_right_motor(TURN_SPEED * left_right_sign);
        stop_tmilli += turn_duration(m.amount);

        double target_orientation = (int)(initial_orientation + m.amount) % 360;
        while(stop_tmilli > millis()) {
            //TODO PID stuff
            delay(1);
        }
    } break;
    case 'M':
    {
        int front_back_sign = m.amount > 0 ? 1 : -1;
        power_left_motor(traversal_speed * front_back_sign);
        power_right_motor(traversal_speed * front_back_sign);
        stop_tmilli += translation_duration(m.amount, traversal_speed);

        while(stop_tmilli > millis()) {
            //TODO PID stuff
            delay(1);
        }
    } break;
    case 'D':
    {
        stop_tmilli = m.amount;
    } break;


    default:
        break;
    }

    unpower_both_motors();
    ++traversal_position;
}

void correct_turn() {

}