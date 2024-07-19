class Elevator:
    class Direction:
        UP = 1
        DOWN = 2

    def __init__(self, min_floor, max_floor, capacity):
        self.direction = None
        self.requests = []
        self.min_floor = min_floor
        self.max_floor = max_floor
        self.current_floor = 0
        self.passengers = 0
        self.capacity = capacity

    def start_elevator(self):
        print(f"\nFLOOR : {self.current_floor}\tNumber of Occupants : {self.passengers}\n")
        self.set_request()
        self.requests.sort()
        while self.requests:
            if self.direction == self.Direction.UP:
                next_floor = self.requests[0]
            elif self.direction == self.Direction.DOWN:
                next_floor = self.requests[-1]

            while next_floor in self.requests:
                self.requests.remove(next_floor)
                self.passengers -= 1

            self.current_floor = next_floor

            dir_str = "UP" if self.direction == self.Direction.UP else "DOWN"

            print("\n=======================================================\n"
                  f"FLOOR : {self.current_floor}\tNumber of Occupants : {self.passengers}\n\n"
                  f"DIRECTION : {dir_str}\tTotal Capacity : {self.capacity}\n\n"
                  f"Minimum floor number is {self.min_floor}\tMaximum floor number is {self.max_floor}\n\n"
                  "=======================================================\n")

            if self.current_floor == self.max_floor:
                self.direction = self.Direction.DOWN
            elif self.current_floor == self.min_floor:
                self.direction = self.Direction.UP

            self.set_request()
            self.requests.sort()

    def set_request(self):
        dest_floors_str = input(f"\n{self.capacity - self.passengers} passengers can enter in the elevator right now\n"
                                "Enter 'GO' if no one enters from the floor\n"
                                "Or to exit from program if elevator is idle\n"
                                "Enter destination floor number.\n"
                                "Press 'HELP' for emergency help.\n")
        sstream = dest_floors_str.split()

        for dest_floor_str in sstream:
            if dest_floor_str.upper() == "GO":
                return
            elif dest_floor_str.upper() == "HELP":
                self.emergency_help()
            else:
                dest_floor = int(dest_floor_str)
                if self.passengers < self.capacity:
                    is_valid = self.is_valid_request(dest_floor)
                    if is_valid == 0:
                        if self.passengers == 0:
                            self.set_direction(dest_floor)
                        self.requests.append(dest_floor)
                        self.passengers += 1
                elif self.passengers == self.capacity:
                    print("Elevator full!! Cannot accept more requests\n")
                    return

    def emergency_help(self):
        print("\nEMERGENCY BUTTON PRESSED: Sending distress signal for immediate help!\n")

    def check_request(self, floor):
        if self.passengers != 0 and self.direction == self.Direction.UP and floor < self.current_floor:
            return 1
        elif self.passengers != 0 and self.direction == self.Direction.DOWN and floor > self.current_floor:
            return 2
        elif floor > self.max_floor or floor < self.min_floor:
            return 3
        else:
            return 0

    def is_valid_request(self, floor):
        issue_num = self.check_request(floor)
        if issue_num == 1:
            print("Elevator is going UP.\n")
        elif issue_num == 2:
            print("Elevator is going DOWN.\n")
        elif issue_num == 3:
            print("This floor does not exist\n")
        return issue_num

    def set_direction(self, floor):
        if floor > self.current_floor:
            self.direction = self.Direction.UP
        elif floor < self.current_floor:
            self.direction = self.Direction.DOWN


if __name__ == "__main__":
    min_floor_num = int(input("Enter minimum floor number in the building\n"))
    max_floor_num = int(input("Enter maximum floor number in the building\n"))
    capacity = int(input("Enter capacity for the elevator\n"))

    elevator = Elevator(min_floor_num, max_floor_num, capacity)
    elevator.start_elevator()
