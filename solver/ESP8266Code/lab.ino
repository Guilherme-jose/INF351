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
enum Action { UP, DOWN, LEFT, RIGHT };



#include <queue>
#include <vector>
#include <tuple>

struct Node {
    int x, y;
    int g, h;
    Node* parent;

    Node(int x, int y, int g, int h, Node* parent = nullptr)
        : x(x), y(y), g(g), h(h), parent(parent) {}

    int f() const {
        return g + h;
    }

    bool operator>(const Node& other) const {
        return f() > other.f();
    }
};

std::vector<std::pair<int, int>> reconstruct_path(Node* node) {
    std::vector<std::pair<int, int>> path;
    while (node != nullptr) {
        path.push_back({node->x, node->y});
        node = node->parent;
    }
    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<std::pair<int, int>> a_star(int startX, int startY, int endX, int endY) {
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> openSet;
    std::vector<std::vector<bool>> closedSet(mazeHeight, std::vector<bool>(mazeWidth, false));

    auto heuristic = [](int x1, int y1, int x2, int y2) {
        return abs(x1 - x2) + abs(y1 - y2);
    };

    openSet.emplace(startX, startY, 0, heuristic(startX, startY, endX, endY));

    while (!openSet.empty()) {
        Node current = openSet.top();
        openSet.pop();

        if (current.x == endX && current.y == endY) {
            return reconstruct_path(&current);
        }

        closedSet[current.y][current.x] = true;

        std::vector<std::pair<int, int>> neighbors = {
            {current.x, current.y - 1}, {current.x, current.y + 1},
            {current.x - 1, current.y}, {current.x + 1, current.y}
        };

        for (auto& neighbor : neighbors) {
            int nx = neighbor.first;
            int ny = neighbor.second;

            if (nx >= 0 && nx < mazeWidth && ny >= 0 && ny < mazeHeight && maze[ny][nx] != '#' && !closedSet[ny][nx]) {
                int g = current.g + 1;
                int h = heuristic(nx, ny, endX, endY);
                openSet.emplace(nx, ny, g, h, new Node(current));
            }
        }
    }

    return {}; // Return empty path if no solution is found
}




void lab_start() {
    generateMaze();
    x = 0;
    y = 0;
    draw();
    std::vector<std::pair<int, int>> path = a_star(0, 0, mazeWidth - 2, mazeHeight - 2);
    lab_loop(path);
}

void lab_loop(std::vector<std::pair<int, int>> path) {
    for (auto step : path) {
        int nextX = step.first;
        int nextY = step.second;

        if (nextX == x && nextY == y - 1) {
            move("up");
        } else if (nextX == x && nextY == y + 1) {
            move("down");
        } else if (nextX == x - 1 && nextY == y) {
            move("left");
        } else if (nextX == x + 1 && nextY == y) {
            move("right");
        }

        delay(500); // Add delay to visualize the movement
    }
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
    maze[mazeHeight - 2][mazeWidth - 2] = 'E';
}


void move(String direction) {
    if(direction == "up" && y > 0 && maze[y - 1][x] != '#') {
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
        Serial.print("(");
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

