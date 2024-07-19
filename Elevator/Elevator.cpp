#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Elevator
{
    enum Direction { UP, DOWN };
    Direction direction;

    vector<int> requests = {};
    int min_floor;
    int max_floor;
    int current_floor = 0;
    size_t passengers = 0;
    size_t capacity;

public:
    Elevator(int min_floor, int max_floor, size_t capacity) :
        min_floor(min_floor),
        max_floor(max_floor),
        capacity(capacity)
    {}

    void start_elevator();

private:
    void set_request();
    int check_request(int floor) const;
    int is_valid_request(int floor);
    void set_direction(int floor);
    void emergency_help();
    void call_911();
    void help();
};

void Elevator::set_request()
{
    string dest_floors_str; // stores all floors request
    string dest_floor_str;  // stores single floor in string
    int dest_floor;         // stores single floor as integer

    size_t num_of_reqs = capacity - passengers;
    cout << "\n" << num_of_reqs << " passengers can enter in the elevator right now\n";

    cout << "\nEnter \"GO\" to proceed with current passengers or \"HELP\" for assistance.\n";
    cout << "Enter destination floor number.\n";

    getline(cin, dest_floors_str);
    stringstream sstream(dest_floors_str);

    while (sstream >> dest_floor_str)
    {
        if (dest_floor_str == "GO" || dest_floor_str == "Go" || dest_floor_str == "go" || dest_floor_str == "gO")
        {
            return;
        }
        else if (dest_floor_str == "911")
        {
            call_911();
        }
        else if (dest_floor_str == "HELP" || dest_floor_str == "Help" || dest_floor_str == "help" || dest_floor_str == "hElP")
        {
            help();
        }
        else
        {
            dest_floor = stoi(dest_floor_str);
            if (passengers < capacity)
            {
                int is_valid = is_valid_request(dest_floor);
                if (is_valid == 0)
                {
                    if (passengers == 0)
                    {
                        set_direction(dest_floor);
                    }
                    requests.push_back(dest_floor);
                    passengers++;
                }
            }
            else if (passengers == capacity)
            {
                cout << "Elevator full!! Cannot accept more requests\n";
                return;
            }
        }
    }
}

int Elevator::check_request(int floor) const
{
    if (passengers != 0 && direction == UP && floor < current_floor)
    {
        return 1;
    }
    else if (passengers != 0 && direction == DOWN && floor > current_floor)
    {
        return 2;
    }
    else if (floor > max_floor || floor < min_floor)
    {
        return 3;
    }
    else
    {
        return 0;
    }
}

int Elevator::is_valid_request(int floor)
{
    int issue_num = check_request(floor);

    if (issue_num == 1)
    {
        cout << "Elevator is going UP.\n";
    }
    else if (issue_num == 2)
    {
        cout << "Elevator is going DOWN.\n";
    }
    else if (issue_num == 3)
    {
        cout << "This floor does not exist\n";
    }
    return issue_num;
}

void Elevator::set_direction(int floor)
{
    if (floor > current_floor)
    {
        direction = UP;
    }
    else if (floor < current_floor)
    {
        direction = DOWN;
    }
}

void Elevator::start_elevator()
{
    cout << "\nFLOOR : " << current_floor << "\tNumber of Occupants : " << passengers << "\n";

    // Entering requests for the first time
    set_request();
    sort(requests.begin(), requests.end());
    int next_floor;

    while (!requests.empty())
    {
        if (direction == UP)
        {
            next_floor = requests[0];
        }
        else if (direction == DOWN)
        {
            next_floor = requests[requests.size() - 1];
        }

        auto next_floor_req = find(requests.begin(), requests.end(), next_floor);
        while (next_floor_req != requests.end())
        {
            requests.erase(next_floor_req); // removing next floor's requests
            passengers--;
            next_floor_req = find(requests.begin(), requests.end(), next_floor);
        }
        current_floor = next_floor;

        string dir = (direction == UP) ? "UP" : "DOWN";

        // Entering requests for the current floor
        cout << "\n=======================================================\n"
            "FLOOR : " << current_floor
            << "\tNumber of Occupants : " << passengers
            << "\n\nDIRECTION : " << dir
            << "\tTotal Capacity : " << capacity
            << "\n\nMinimum floor number is " << min_floor
            << "\tMaximum floor number is " << max_floor
            << "\n\n=======================================================\n";

        if (current_floor == max_floor)
        {
            direction = DOWN;
        }
        else if (current_floor == min_floor)
        {
            direction = UP;
        }

        set_request();
        sort(requests.begin(), requests.end());
    }
}

void Elevator::emergency_help()
{
    cout << "\nEMERGENCY BUTTON PRESSED: Sending distress signal for immediate help!\n";
}

void Elevator::call_911()
{
    cout << "\nCALLING 911: Emergency services have been alerted!\n";
}

void Elevator::help()
{
    cout << "\nHELP BUTTON PRESSED: Information on how to use the elevator will be provided.\n";
    cout << "Please refer to the instruction manual located inside the elevator.\n";
}

int main()
{
    string capacity_str, min_floor_num_str, max_floor_num_str;
    int min_floor_num, max_floor_num;
    size_t capacity;

    cout << "Enter minimum floor number, maximum floor number in the building\n";
    cin >> min_floor_num_str;
    cin >> max_floor_num_str;

    min_floor_num = stoi(min_floor_num_str);
    max_floor_num = stoi(max_floor_num_str);

    cout << "Enter capacity for the elevator\n";
    cin >> capacity_str;
    cin.ignore();
    stringstream capacity_stream(capacity_str);
    capacity_stream >> capacity;

    Elevator elevator(min_floor_num, max_floor_num, capacity);
    elevator.start_elevator();

    return 0;
}
