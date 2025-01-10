const int mazeWidth = 16;
const int mazeHeight = 16;

char maze[mazeHeight][mazeWidth] = {
    {'S', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {'#', '#', '#', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' '},
    {' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', '#', ' '},
    {' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' '},
    {' ', '#', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', ' ', '#', ' ', '#', ' '},
    {' ', '#', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', ' '},
    {' ', '#', ' ', '#', ' ', '#', '#', ' ', '#', '#', '#', '#', '#', ' ', '#', ' '},
    {' ', '#', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', '#', ' ', '#', ' ', '#', ' ', '#', '#', '#', '#', '#', '#', '#', '#', ' '},
    {' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', '#', '#', '#', '#', '#', ' '},
    {' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' '},
    {' ', '#', ' ', '#', ' ', '#', ' ', '#', '#', '#', '#', '#', '#', ' ', '#', ' '},
    {' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' '},
    {' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', 'E'}
    };

int x = 0, y = 0;

void lab_start() {
    draw();
}

void lab_loop() {
  if (Serial.available()) {
    String dir = Serial.readString();
    dir.trim();
    if (dir == "up" || dir == "down" || dir == "left" || dir == "right") {
      move(dir);
      Serial.println(" ");
      String m = get_leds();
      for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
          Serial.print(m[i * 8 + j]);
        }
      Serial.println();
    }
    }
  }
}

void move(String direction) {
    if (direction == "up" && y > 0 && maze[y - 1][x] != '#') {
        y--;
    } else if (direction == "down" && y < mazeHeight - 1 && maze[y + 1][x] != '#') {
        y++;
    } else if (direction == "left" && x > 0 && maze[y][x - 1] != '#') {
        x--;
    } else if (direction == "right" && x < mazeWidth - 1 && maze[y][x + 1] != '#') {
        x++;
    }

    if (maze[y][x] == 'E') {
        Serial.println("You have reached the end!");
    } else {
        Serial.print("Current position: (");
        Serial.print(x);
        Serial.print(", ");
        Serial.print(y);
        Serial.println(")");
    }
    draw();
}

String get_leds() {
    int startX = max(0, x - 4);
    int startY = max(0, y - 4);
    int endX = min(mazeWidth, x + 4);
    int endY = min(mazeHeight, y + 4);

    String result = "";
    for (int i = y - 4; i < y+4; i++) {
        for (int j = x - 4; j < x + 4; j++) {
          if(i == y && j == x) result += "x";
          else if (i < startY || i >= endY || j < startX || j >= endX) result += 'o';
          else result += maze[i][j];
        }
    }
    return result;
}

void draw() {
    pixels.clear();
    String draw_map = get_leds();
    for (int i = 0; i < 8; i++) {
        if(i%2 == 1) {
            for (int j = 0; j < 8; j++) {
                if (draw_map[i * 8 + j] == 'x') {
                    pixels.setPixelColor(i * 8 + j, pixels.Color(255, 0, 0)); // Red for current position
                } else if (draw_map[i * 8 + j] == '#' || draw_map[i * 8 + j] == 'o') {
                    pixels.setPixelColor(i * 8 + j, pixels.Color(0, 0, 255)); // Blue for walls
                } else if (draw_map[i * 8 + j] == 'E') {
                    pixels.setPixelColor(i * 8 + j, pixels.Color(0, 255, 0)); // Green for end
                } else {
                    pixels.setPixelColor(i * 8 + j, pixels.Color(0, 0, 0)); // Off for empty spaces
                }
            }
        } else {
            for (int j = 7; j >= 0; j--) {
                if (draw_map[i * 8 + j] == 'x') {
                    pixels.setPixelColor(i * 8 + (7 - j), pixels.Color(255, 0, 0)); // Red for current position
                } else if (draw_map[i * 8 + j] == '#' || draw_map[i * 8 + j] == 'o') {
                    pixels.setPixelColor(i * 8 + (7 - j), pixels.Color(0, 0, 255)); // Blue for walls
                } else if (draw_map[i * 8 + j] == 'E') {
                    pixels.setPixelColor(i * 8 + (7 - j), pixels.Color(0, 255, 0)); // Green for end
                } else {
                    pixels.setPixelColor(i * 8 + (7 - j), pixels.Color(0, 0, 0)); // Off for empty spaces
                }
            }
        } 
    }
    pixels.show();
}