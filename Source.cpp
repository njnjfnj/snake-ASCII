#include <iostream>
#include <thread>
#include <string>
#include <Windows.h>
#include <deque>
#include <algorithm>
#include <conio.h>
#include <ctime>
using namespace std;
using namespace this_thread;
using namespace chrono; // You have to switch your language to English to play this game

const bool T = true;
const bool F = false;

class snake {
private:
	class node {
	private:
		string* map;
	public:
		char body;
		int x;
		int y;
		node(char body, int x, int y, string* map) {
			this->body = body;
			this->x = x;
			this->y = y;
			this->map = map;
		}
		void place() {
			map[y].insert(map[y].begin() + x, body);
			map[y].erase(map[y].begin() + (x + 1));
		}
	};
	class X {
		string* map;
		char body = 'X';
	public:		
		int x; // (map[0].size() - 2)
		int y; // (map->size() - 2)
		X(string* map) { this->map = map; }
		void place() {
			srand(time(NULL));
			while (true) {
				x = rand() % 19 + 1;
				y = rand() % 7 + 1;
				if (*(map[y].begin() + x) == ' ') {
					map[y].insert(map[y].begin() + x, body);
					map[y].erase(map[y].begin() + (x + 1));
					break;
				}
			}
		}
	};
	enum vects {
		right,
		left, 
		up, 
		down
	};
	vects vect = vects::right;
	string* map;
	deque<node> head;
public:
	int res = 0;
	snake(string* map) {
		this->map = map;
		head.push_back(node('&', 10, 4, map));
		head.push_back(node('#', 9, 4, map));
		head.push_back(node('#', 8, 4, map));
		for_each(head.begin(), head.end(), [](node i) {
			i.place();
		});
	}
	void update() {
		for_each(head.begin(), head.end(), [](node i) {
			i.place();
		});
	}
	void replace(bool &chek) {
		int time = 800;
		X x(map);
		x.place();
		map[0].push_back(res);
		while (!chek) {
			sleep_for(milliseconds(time));
			switch (vect) {
			case snake::right:
				if (*(map[head[0].y].begin() + head[0].x + 1) == 'X') {
					head.push_back(node('#', head[0].x + 1, head[0].y, map)), ++res;
					x.place();
					if (time > 200) time -= 20;
				}
				map[head[head.size() - 1].y].insert(map[head[head.size() - 1].y].begin() + head[head.size() - 1].x, ' ');
				map[head[head.size() - 1].y].erase(map[head[head.size() - 1].y].begin() + (head[head.size() - 1].x + 1));
				head[0].body = '#';
				for (size_t i = head.size() - 1; i != 0; --i) {
					head[i] = head[i - 1];
				}
				if (*(map[head[0].y].begin() + head[0].x + 1) == '|' || *(map[head[0].y].begin() + head[0].x + 1) == '#') chek = T;
				head[0].x += 1;
				head[0].body = '&';
				update();
				break;
			case snake::left:
				if (*(map[head[0].y].begin() + head[0].x - 1) == 'X') {
					head.push_back(node('#', head[0].x - 1, head[0].y, map)), ++res;
					x.place();
					if (time > 200) time -= 20;
				}
				map[head[head.size() - 1].y].insert(map[head[head.size() - 1].y].begin() + head[head.size() - 1].x, ' ');
				map[head[head.size() - 1].y].erase(map[head[head.size() - 1].y].begin() + (head[head.size() - 1].x + 1));
				head[0].body = '#';
				for (size_t i = head.size() - 1; i != 0; --i) {
					head[i] = head[i - 1];
				}
				if (*(map[head[0].y].begin() + head[0].x - 1) == '|' || *(map[head[0].y].begin() + head[0].x - 1) == '#') chek = T;
				head[0].x -= 1;
				head[0].body = '&';
				update();
				break;
			case snake::up:
				if (*(map[head[0].y - 1].begin() + head[0].x) == 'X') {
					head.push_back(node('#', head[0].x, head[0].y - 1, map)), ++res;
					x.place();
					if (time > 200) time -= 20;
				}
				map[head[head.size() - 1].y].insert(map[head[head.size() - 1].y].begin() + head[head.size() - 1].x, ' ');
				map[head[head.size() - 1].y].erase(map[head[head.size() - 1].y].begin() + (head[head.size() - 1].x + 1));
				head[0].body = '#';
				for (size_t i = head.size() - 1; i != 0; --i) {
					head[i] = head[i - 1];
				}
				if (*(map[head[0].y - 1].begin() + head[0].x) == '-' || *(map[head[0].y - 1].begin() + head[0].x) == '#') chek = T;
				head[0].y -= 1;
				head[0].body = '&';
				update();
				break;
			case snake::down:
				if (*(map[head[0].y + 1].begin() + head[0].x) == 'X') {
					head.push_back(node('#', head[0].x, head[0].y + 1, map)), ++res;
					x.place();
					if (time > 200) time -= 20;
				}
				map[head[head.size() - 1].y].insert(map[head[head.size() - 1].y].begin() + head[head.size() - 1].x, ' ');
				map[head[head.size() - 1].y].erase(map[head[head.size() - 1].y].begin() + (head[head.size() - 1].x + 1));
				head[0].body = '#';
				for (size_t i = head.size() - 1; i != 0; --i) {
					head[i] = head[i - 1];
				}
				if (*(map[head[0].y + 1].begin() + head[0].x) == '-' || *(map[head[0].y + 1].begin() + head[0].x) == '#') chek = T;
				head[0].y += 1;
				head[0].body = '&';
				update();
				break;
			}
		}
	}
	void change_vec(bool& chek) {
		while (!chek) {
			if (_kbhit()) {
				int key = _getch();
				switch (key) {
				case 119: //W
					if(vect != vects::down) vect = vects::up;
					break;
				case 97: // A
					if (vect != vects::right) vect = vects::left;
					break;
				case 115: // S
					if (vect != vects::up) vect = vects::down;
					break;
				case 100: // D
					if (vect != vects::left) vect = vects::right;
					break;
				}
			}
		}
	}
};

void translation(string* map, int x_size, bool& chek) {
	COORD cord;
	cord.X = 0;
	cord.Y = 0;
	while (!chek) {
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
		for (size_t i = 0; i < x_size; i++) {
			cout << map[i] << endl;
		}
	}
}

int main() {
	string map[]{
		"----------------------",  // 22
		"|                    |",
		"|                    |",
		"|                    |",
		"|                    |",
		"|                    |",
		"|                    |",
		"|                    |",
		"----------------------" // 9
	};
	bool chek = F; 
	snake a(map);

	thread th1([&map, &chek]() { translation(map, size(map), chek); });
	thread th2([&map, &chek, &a]() { a.change_vec(chek); });
	a.replace(chek);
	th1.join();
	th2.join();

	cout << endl << "result: " << a.res << endl;
	system("pause");
	return 0;
}
