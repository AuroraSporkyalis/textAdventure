// text adventure
// Jenelle Harrington, CISP 360
// 05/19/2021
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
using namespace std;

class Weapon {
	private:
	string weapon_name;
	int damage;
	public:
};

class Player {
	public:
		string player_name;
};
// Specification A1 - Monster class
class Monster {
	private:
		string mon_description;
		string mon_name;
	public:
		// Specification B3 - More monsters
		string monTypes[2][5] = {
			{"A pair of glowing red eyes stares out from a corner of the room that seems to draw in the shadows...",
			"A set of robes floats in the center of the room, they turn towards you.","A giant wheel of cheese rolls towards you! If only you had a cheese knife!",
			"What was that sound?","A skeleton in a cloak and breastplate is charging towards you, brandishing a large sword."},
			{"It's a shadow demon!", "It's a remnant of a malicious wizard!", "It's a giant wheel of cheese!", "It's a giant spider!", "It's a skeleton warrior!"}};
		Monster();
		void displayInfo();
};

Monster::Monster() {
	unsigned seed;
	seed = time(0);
	srand(seed); 
	int random_num = rand() % 5;

	mon_description = monTypes[0][random_num];
	mon_name = monTypes[1][random_num];
}

void Monster::displayInfo() {
	cout << mon_description << endl;
	cout << mon_name << endl;
}

class Room {
	public:
		string room_name, room_description;
		int room_id;
		bool visited, occupied;
		void setInfo();
		void displayInfo();
		void start();
};
void Room::setInfo() {
	string descriptions[6] = {"It's a small stone room.\nThere are doors in every direction",
		"The room has a damp smell.\nThere is only a door on the Southern wall leading back where you came.",
		"Something feels strange in this room.\nThere is only a door on the Eastern wall leading back where you came.",
		"The room reminds you of something, but you aren't sure what.\nThere is only a door on the Northern wall leading back where you came.",
		"You can feel a slight breeze in this room, though you cannot tell from where.\nThere is a door leading back to the East, and a door to the South.",
		"The room is brightly lit by light coming through an opening to the west.\nThere is a door behind you to the North."};
	room_description = descriptions[room_id];
}
void Room::displayInfo() {
	cout << "Room title: " << room_name << endl;
	cout << room_description << endl;
}

static void move(int moves);
void combat();

void Room::start() {
	// Specification C4 – Abbreviated Room Description
	if (visited == false) {
		displayInfo();
	}
	else {
		cout << room_name << endl;
	}
	if (occupied == true) {
		Monster monster1;
		monster1.displayInfo();
		combat();
	}
	move(1);	
}

void programGreeting();

int main() {
	Player adventurer;
	programGreeting();
	cout << "You are standing near a sealed stone doorway, long overgrown.\nYou hear a disembodied voice\n'Welcome adventurer. Tell me your name to enter the dungeon and see what fate awaits you...'\n";
	// Specification C2 - Player Name
	getline(cin, adventurer.player_name);
	cout << "You speak your name, and quickly fade into unconsciousness...\n";
	cout << "You awaken on a cold stone floor.\nThe air is slightly damp, and the room is illuminated by torches mounted on the walls.\n";
	cout << "As you stand you hear the voice again, this time only an echoing whisper, 'Good luck " << adventurer.player_name << ", followed by a small chuckle.\n";
	cout << "You take one of the torches and begin your journey.\nYou may move in any of the 4 cardinal directions using your N, S, E, and W keys.\n\n";
	move(0);
}

static void move(int moves) {
	char input;
	const int ROOM_NUM = 6;
	// Specification C1 - Five Rooms
	// Specification A3 - Another room
	static Room rooms[ROOM_NUM];

	for (int i = 0; i < ROOM_NUM; i++) {
		// Specification A2 - Random Occupation
		rooms[i].occupied = rand() % 2;
		rooms[i].room_id = i;
		rooms[i].setInfo();
	}
	rooms[0].room_name = "Center room.";
	rooms[1].room_name = "Northern room.";
	rooms[2].room_name = "Eastern room.";
	rooms[3].room_name = "Southern room.";
	rooms[4].room_name = "Western room.";
	rooms[5].room_name = "South western room.";

	Room nextRoom;
	static Room currentRoom;
	if (moves == 0) {
		currentRoom = rooms[0];
		currentRoom.start();
		currentRoom.visited = true;
	}

	cout << "Enter your command to look around or keep going.\n";
	cin >> input;
	input = toupper(input);
	// Specification C3 - Input Validation
	while (input != 'L' && input != 'N' && input != 'S' && input != 'E' && input != 'W' && input != 'D') {
		cout << "That isn't a valid option. You may examine the room using L, drop your torch with D, or travel in the 4 cardinal directions.\n";
		cin.clear();
		cin >> input;
	}
	// Specification C5 - Detailed Look
	if (input == 'L') {
		currentRoom.displayInfo();
		move(1);
	}
	// Specification B1 - Another command
	else if (input == 'D') {
		cout << "You drop your torch.\nWhy would you drop your torch in a dungeon?\nYou realize your mistake and pick up your torch before it goes out.\n";
		move(1);
	}
	else {
	moves = 1;
		if (currentRoom.room_id == rooms[0].room_id) {
			currentRoom.visited = true;
			switch(input) {
				case 'N': {
					nextRoom = rooms[1];
					currentRoom = nextRoom;
					rooms[0].visited = true;
					currentRoom.start();
				}
				break;
				case 'S': {
					nextRoom = rooms[3];
					currentRoom = nextRoom;
					rooms[0].visited = true;
					currentRoom.start();
				}
				break;
				case 'E': {
					nextRoom = rooms[2];
					currentRoom = nextRoom;
					rooms[0].visited = true;
					currentRoom.start();
				}
				case 'W': {
					nextRoom = rooms[4];
					currentRoom = nextRoom;
					rooms[0].visited = true;
					currentRoom.start();
				}
			}
		}
		if (currentRoom.room_id == rooms[1].room_id) {
			while (input != 'S') {
				cout << "You cannot go that way. Enter a valid command.\n";
				cin.clear();
				cin >> input;
				input = toupper(input);
			}
			nextRoom = rooms[0];
			currentRoom = nextRoom;
			rooms[1].visited = true;
			currentRoom.start();
		}
		if (currentRoom.room_id == rooms[2].room_id) {
			while (input != 'W') {
				cout << "You cannot go that way. Enter a valid command.\n";
				cin.clear();
				cin >> input;
				input = toupper(input);
			}
		   nextRoom = rooms[0];
		   currentRoom = nextRoom;
		   rooms[2].visited = true;
		   currentRoom.start();
		}
		if (currentRoom.room_id == rooms[3].room_id) {
			while (input != 'N') {
				cout << "You cannot go that way. Enter a valid command.\n";
				cin.clear();
				cin >> input;
				input = toupper(input);
			}
			nextRoom = rooms[0];
			currentRoom = nextRoom;
			rooms[3].visited = true;
			currentRoom.start();
		}
		if (currentRoom.room_id == rooms[4].room_id) {
			while (input != 'S' && input != 'E') {
				cout << "You cannot go that way. Enter a valid command.\n";
				cin.clear();
				cin >> input;
				input = toupper(input);
			}
			if (input == 'S') {
				nextRoom = rooms[5];
				rooms[4].visited = true;
				currentRoom = nextRoom;
				currentRoom.start();
			}
			else if (input == 'E') {
				nextRoom = rooms[0];
				rooms[4].visited = true;
				currentRoom = nextRoom;
				currentRoom.start();
			}
		}
		if (currentRoom.room_id == rooms[5].room_id) {
			while (input != 'N' && input != 'W') {
				cout << "You cannot go that way. Enter a valid command.\n";
				cin.clear();
				cin >> input;
				input = toupper(input);
			}
			if (input == 'W') {
				cout << "You have reached the exit of the dungeon.\n";
				cout << "You can hear the eerie voice from before speak\n'Congratulations on surviving the dungeon.'\n";
				cout << "The game is now over.\n";
				exit(0);
			}
			else if (input == 'S') {
				nextRoom = rooms[4];
				rooms[5].visited = true;
				currentRoom = nextRoom;
				currentRoom.start();
			}
		}
	}
}
void combat() {
	const string RED = "\033[31m", RESET = "\033[0m";
	int input;
	int win = rand() % 6;
	// Specification B2 - Monster encounters
	cout << "Will you attempt to fight the monster or flee?\nIf you fight, you may perish, or you may be rewwarded.\n1. Fight\n2. Flee\n";
	cin >> input;
	while (input != 1 && input != 2) {
		cout << "Please enter a valid selection: ";
	}
	if (input == 1) {
		if (win > 1) {
			cout << "You swung your torch wildly and defeated the monster.\nYou collect a small amount of gold.\n";
		}
		else {
			cout << "You've met with a terrible fate, haven't you...\n" << RED << "This seems to be the end of your adventure." << RESET << "\nCould have been worse. Could have been killed by a giant wheel of cheese.\n";
			exit(0);
		}
	}
}
void programGreeting() {
	cout << "\nThis program will probably do things.\n";
	cout << "(Warning: developer will not be held responsible for any injuries or casualties that take place in the dungeon.)\n";
	cout << "Jenelle Harrington.\nMay 19, 2021\n" << string(30, '-') << endl;
}