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
    generateMaze();
    x = 0;
    y = 0;
    draw();
}

void generateMaze() {
    // Initialize the maze with walls
    for (int i = 0; i < mazeHeight; i++) {
        for (int j = 0; j < mazeWidth; j++) {
            maze[i][j] = '#';
        }
    }

    // Create a path using Depth-First Search (DFS)
    int stack[mazeHeight * mazeWidth][2];
    int top = -1;
    int cx = 0, cy = 0;
    maze[cy][cx] = ' ';
    stack[++top][0] = cx;
    stack[top][1] = cy;

    while (top >= 0) {
        cx = stack[top][0];
        cy = stack[top][1];
        int directions[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
        bool moved = false;

        // Shuffle directions to create a random path
        for (int i = 0; i < 4; i++) {
            int r = random(4);
            int temp[2] = {directions[i][0], directions[i][1]};
            directions[i][0] = directions[r][0];
            directions[i][1] = directions[r][1];
            directions[r][0] = temp[0];
            directions[r][1] = temp[1];
        }

        for (int i = 0; i < 4; i++) {
            int nx = cx + directions[i][0] * 2;
            int ny = cy + directions[i][1] * 2;
            if (nx >= 0 && nx < mazeWidth && ny >= 0 && ny < mazeHeight && maze[ny][nx] == '#') {
                maze[cy + directions[i][1]][cx + directions[i][0]] = ' ';
                maze[ny][nx] = ' ';
                stack[++top][0] = nx;
                stack[top][1] = ny;
                moved = true;
                break;
            }
        }

        if (!moved) {
            top--;
        }
    }

    // Set start and end points
    maze[0][0] = 'S';
    maze[mazeHeight - 1][mazeWidth - 1] = 'E';
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
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
            pixels.setPixelColor(i * 8 + j, pixels.Color(0, 255, 0)); // Green for win
            }
        }
        pixels.show();
        delay(1000);
        lab_start();
    } else {
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