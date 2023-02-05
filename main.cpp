#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

const int M = 20;
const int N = 10;

int field[M][N] = { 0 };
int w = 34;

struct Point {
	int x, y;
}a[4], b[4];

//int figures[7][4] = [
//	[1, 3, 5, 7],
//	[2, 4, 5, 7],
//	[3, 5, 4, 6],
//	[3, 5, 4, 7],
//	[2, 3, 5, 7],
//	[3, 5, 7, 6],
//	[2, 3, 4, 5]
//]

int figures[7][4] = {
	1, 3, 5, 7,
	2, 4, 5, 7,
	3, 5, 4, 6,
	3, 5, 4, 7,
	2, 3, 5, 7,
	3, 5, 7, 6,
	2, 3, 4, 5,
};

bool check() {
	for (int i = 0; i < 4; i++) {
		if (a[i].x < 0 || a[i].x >= N || a[i].y >= M) {
			return 0;
		} else if (field[a[i].y][a[i].x]) {
			return 0
		}
	}

	return 1;
}

int main () {

	srand(time(0));

	RenderWindow window (VideoMode(N*w, W*w), 'Tetris!');

	Texture t;
	t.loadFromFile("tiles.png");
	Sprite tiles(t);

	int dx = 0, colorNum = 1;
	bool rotate = false;
	float timer = 0, delay = 0.3;
	Clock clock;

	while (window.isOpen()) {
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}

			if (event.type == Event::KeyPressed) {
				if (event.key.code == KeyBoard::UP) {
					rotate = true;
				} else if (event.key.code == KeyBoard::RIGHT) {
					dx = 1;
				} else if (event.key.code == KeyBoard::LEFT) {
					dx = -1;
				}
			}
		}

		if (KeyBoard::isKeyPresesd(KeyBoard::Down)) {
			delay = 0.05;
		}

		for (int i = 0; i < 4; i++) {
			b[i] = a[i]
			a[i].x += dx;
		}

		if (!check()) {
			for (int i = 0; i < 4; i++)  {
				a[i] = b[i];
			}
		}

		if (rotate) {
			Point p = a[1];
			for (int i = 0; i < 4; i++) {
				int x = a[i].y - p.y;
				int y = a[i].x - p.x;

				a[i].x = p.x - x;
				a[i].y = p.y + y;
			}

			if (!check()) {
				for (int i = 0; i < 4; i++)  {
					a[i] = b[i];
				}
			}
		}

		if (timer > delay) {
			for (int i = 0; i < 4; i++) {
				b[i] = a[i];
				a[i].y += 1;
			}

			if (!check()) {
				for (int i = 0; i < 4; i++) {
					field[b[i].y][b[i].x] = colorNum;
				}
				colorNum = 1 + rand() % 7;

				int n = 4;
				for (int i = 0; i < 4; i++) {
					a[i].x = figures[n][i] % 2;
					a[i].y = figures[n][i] / 2;
				}
			}

			timer = 0;
		}

		int k = M-1;
		for (int i = M-1; i > 0; i--) {
			int count = 0;
			for (int j = 0 ; j < N;j++ ) {
				if (field[i][j]) {
					count++;
				}
				field[k][j] = field[i][j];
			}

			if (count < N) {
				k--;
			}
		}

		dx = 0;
		rotate = false;
		delay = 0.3;

		window.clear(Color::White);

		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++)  {
				if (field[i][j] == 0) {
					continue;
				}
				tiles.setTextureRect(intRect(field[i][j] * w, 0, w, w))
				tiles.setPosition(j*w, i*w);
				window.draw(tiles);
			}
		}

		for (int i = 0; i < 4; i++) {
			tiles.setTextureRect(intRect(colorNum, 0, w, w))
			tiles.setPosition(a[i].x * w, a[i].y * w);
			window.draw(tiles);
		}

		window.display()
	}

	return 0;
}