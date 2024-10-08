#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>
#include <memory>


using namespace std;

const int BOARD_WIDTH = 80;
const int BOARD_HEIGHT = 25;

class Figure {
public:
    virtual std::vector<std::vector<char>> draw() const = 0;
    virtual ~Figure() = default;
    virtual bool operator==(const Figure& other) const = 0;

    vector<int> positon() const {
        return coordinates;
    };
    void setRange(vector<int> r) {
        range = r;
    };
    vector<int> getRange() const {
        return range;
    };
    void setColor(char c) {
        color = c;
    }

protected:
    vector<int> coordinates;
    vector<int> range; // max-x,max-y
    char color;
    bool fill;
};

class Triangle : public Figure {
private:
    int height;

public:
    Triangle(bool f,char c,int h, int _x, int _y) : height(h) {
        coordinates.push_back(_x);
        coordinates.push_back(_y);
        fill = f;
        color = c;
    }
    bool operator==(const Figure& other) const override {
        const Triangle* otherTriangle = dynamic_cast<const Triangle*>(&other);
        if (otherTriangle) {
            return (height == otherTriangle->height && coordinates[0] == otherTriangle->coordinates[0] && coordinates[1] == otherTriangle->coordinates[1]);
        }
        else {
            return false;
        }
    }

    std::vector<std::vector<char>> draw() const override {
        std::vector<std::vector<char>> triangle(height, std::vector<char>(2 * height - 1, ' '));
        if (!fill) {

            for (int i = 0; i < height; ++i) {
                int leftMost = height - 1 - i;
                int rightMost = height - 1 + i;
                triangle[i][leftMost] = color;
                triangle[i][rightMost] = color;
            }

            for (int j = 0; j < 2 * height - 1; ++j) {
                triangle[height - 1][j] = color;
            }
            return triangle;
        }
        else {
            for (int i = 0; i < height; ++i) {
                int leftMost = height - 1 - i;
                int rightMost = height - 1 + i;

                for (int k = leftMost; k <= rightMost; ++k) {
                    triangle[i][k] = color;
                }

            }

            for (int j = 0; j < 2 * height - 1; ++j) {
                triangle[height - 1][j] = color;
            }
            return triangle;
        
        }
    }



   
    int getHeigh() {
        return height;
    }
};

class Rectangle : public Figure {
private:
    int height;

public:
    Rectangle(bool f, char c, int h, int _x, int _y) : height(h) {
        coordinates.push_back(_x);
        coordinates.push_back(_y);
        fill = f;
        color = c;
    }

    bool operator==(const Figure& other) const override {
        const Rectangle* otherRectangle = dynamic_cast<const Rectangle*>(&other);
        if (otherRectangle) {
            return (height == otherRectangle->height && coordinates[0] == otherRectangle->coordinates[0] && coordinates[1] == otherRectangle->coordinates[1]);
        }
        else {
            return false;
        }
    }

    std::vector<std::vector<char>> draw() const override {
        std::vector<std::vector<char>> triangle(2 * height - 1, std::vector<char>(2 * height - 1, ' '));
        if (!fill) {

            for (int i = 0; i < height; ++i) {
                int leftMost = height - 1 - i;
                int rightMost = height - 1 + i;
                triangle[i][leftMost] = color;
                triangle[i][rightMost] = color;

            }

            for (int i = height; i < 2 * height - 1; ++i) {
                int leftMost = i - height + 1;
                int rightMost = 3 * height - i - 3;
                triangle[i][leftMost] = color;
                triangle[i][rightMost] = color;
            }
        }
        else {
            for (int i = 0; i < height; ++i) {
                int leftMost = height - 1 - i;
                int rightMost = height - 1 + i;
                for (int j = leftMost; j <= rightMost; ++j) {
                    triangle[i][j] = color;
                }

            }

            for (int i = height; i < 2 * height - 1; ++i) {
                int leftMost = i - height + 1;
                int rightMost = 3 * height - i - 3;
                for (int j = leftMost; j <= rightMost; ++j) {
                    triangle[i][j] = color;
                }
            }

        }

        return triangle;
    }



    
    int getHeigh() {
        return height;
    }
};


class Circle : public Figure {
private:
    int rad;

public:
    Circle(bool f, char c, int r, int _x, int _y) : rad(r) {
        coordinates.push_back(_x);
        coordinates.push_back(_y);
        fill = f;
        color = c;
    }

    bool operator==(const Figure& other) const override {
        const Circle* otherCircle = dynamic_cast<const Circle*>(&other);
        if (otherCircle) {
            return (rad == otherCircle->rad && coordinates[0] == otherCircle->coordinates[0] && coordinates[1] == otherCircle->coordinates[1]);
        }
        else {
            return false;
        }
    }

    std::vector<std::vector<char>> draw() const override {
        std::vector<std::vector<char>> circle(rad * 2 + 1, std::vector<char>(rad * 2 + 1, ' '));
        double aspect_ratio = 1;
        if (!fill) {

            for (int i = -rad; i <= rad; i++) {
                for (int j = -rad; j <= rad; j++) {
                    double distance = sqrt(pow(i * aspect_ratio, 2) + pow(j, 2));

                    if (distance >= rad - 0.5 && distance <= rad + 0.5) {
                        circle[i + rad][j + rad] = color;
                    }
                }
            }
            return circle;
        }
        else {
            for (int i = -rad; i <= rad; i++) {
                for (int j = -rad; j <= rad; j++) {
                    double distance = sqrt(pow(i * aspect_ratio, 2) + pow(j, 2));

                    if (distance <= rad) {  
                        circle[i + rad][j + rad] = color;
                    }
                }
            }
            return circle;

        }
    }



   
    int getRadius() {
        return rad;
    }
};

class Square : public Figure {
private:
    int width, height;
    int side = 0;


public:
    const string typeName = "Square";
    Square(bool f, char c, int s, int _x, int _y) : side(s) {
        coordinates.push_back(_x);
        coordinates.push_back(_y);
        fill = f;
        color = c;
    }

    Square(bool f, char c, int w, int h, int _x, int _y) : width(w), height(h) {
        coordinates.push_back(_x);
        coordinates.push_back(_y);
        fill = f;
        color = c;
    }


    bool operator==(const Figure& other) const override {
        const Square* otherSquare = dynamic_cast<const Square*>(&other);
        if (otherSquare) {
            if (side != 0) {
                return (coordinates[0] == otherSquare->coordinates[0] && coordinates[1] == otherSquare->coordinates[1] && side == otherSquare->side);
            }
            else {
                return (height == otherSquare->height && coordinates[0] == otherSquare->coordinates[0] && coordinates[1] == otherSquare->coordinates[1] && width == otherSquare->width);

            }

        }
        return false;
    }

    std::vector<std::vector<char>> draw() const override {
        if (!fill) {
            if (side != 0) {
                std::vector<std::vector<char>> square(side, std::vector<char>(side, ' '));
                for (int i = 0; i < side; i++) {
                    if (i == 0 || i == side - 1) {
                        for (int j = 0; j < side; j++) {
                            square[i][j] = color;
                        }
                    }
                    else {
                        for (int k = 0; k < side; k++) {
                            if (k == 0 || k == side - 1) {
                                square[i][k] = color;
                            }
                            else {
                                square[i][k] = ' ';
                            }
                        }
                    }
                }
                return square;
            }
            else {
                std::vector<std::vector<char>> rectangle(height, std::vector<char>(width, ' '));
                for (int i = 0; i < height; i++) {
                    for (int j = 0; j < width; j++) {
                        if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                            rectangle[i][j] = color;
                        }
                    }
                }
                return rectangle;

            }
        }
        else {  
            if (side != 0) {  
                std::vector<std::vector<char>> filledSquare(side, std::vector<char>(side, color)); 
                return filledSquare;
            }
            else { 
                std::vector<std::vector<char>> filledRectangle(height, std::vector<char>(width, color)); 
                return filledRectangle;
            }
        }
    }



    
    int getSide() {
        return side;
    }

    string getSides() {
        return to_string(height) + " " + to_string(width);
    }
};

struct Board {
    std::vector<std::vector<char>> grid;

    Board() : grid(BOARD_HEIGHT, std::vector<char>(BOARD_WIDTH, ' ')) {}

    void print() {
        for (auto& row : grid) {
            cout << "|";
            for (char c : row) {
                std::cout << c;
            }
            cout << "|";
            std::cout << "\n";
        }
    }

    void placeShape(Figure& shape, int x, int y) {
        std::vector<std::vector<char>> shapeGrid = shape.draw();

        vector<int> range;
        range.push_back(shapeGrid.size() + x);
        range.push_back(shapeGrid[0].size() + y);
        shape.setRange(range);

        for (int i = 0; i < shapeGrid.size(); ++i) {
            for (int j = 0; j < shapeGrid[i].size(); ++j) {
                if (shapeGrid[i][j] != ' ' && x + i < BOARD_HEIGHT && y + j < BOARD_WIDTH) {
                    grid[x + i][y + j] = shapeGrid[i][j];
                }
            }
        }
    }
    void reset() {
        for (int i = 0; i < BOARD_HEIGHT; i++) {
            for (int j = 0; j < BOARD_WIDTH; j++) {
                grid[i][j] = ' ';
            }
        }

    }
    std::vector<std::vector<char>> getGrid() {
        return grid;
    }
    void setGrid(std::vector<std::vector<char>>& temp_grid) {
        for (int i = 0; i < BOARD_HEIGHT; i++) {
            for (int j = 0; j < BOARD_WIDTH; j++) {
                grid[i][j] = temp_grid[i][j];
            }
        }

    }
    bool checkGrid(int x, int y) {
        if (grid[x][y] == ' ') {
            return false;
        }
        return true; 
    }

};

class CLI {
public:
    Board board;
    vector<shared_ptr<Figure>> Figures;
    int selected;

    void start() {
        while (1) {
            auto input = user_input();
            if (input.empty()) continue;

            string command = input[0];

            if (command == "add") {
                add(input);
            }

            else if (command == "list") {
                list();
            }

            else if (command == "draw") {
                draw();
            }
            else if (command == "select") {
                if (input.size() == 2) {
                    select(stoi(input[1]));
                }
                else {
                    select(stoi(input[1]),stoi(input[2]));
                }
            }

            else if (command == "undo") {
                if (!Figures.empty()) {
                    Figures.pop_back();
                    board.reset();
                }
            }

            else if (command == "clear") {
                clear();
            }

            else if (command == "save") {
                save();
            }

            else if (command == "shapes") {
                shapes();
            }

            else if (command == "load") {
                load();
            }

            else if (command == "exit") {
                break;
            }

            else {
                cout << "Unknown command" << endl;
            }
        }
    }

    void select(int x) {
        if (x >= 0 && x < Figures.size()) {
            selected = x;
            list(x);
        }
        else {
            cout << "shape was not found" << endl;
        }
        
    }

    void select(int x, int y) {
        if (board.checkGrid(x, y)) {
            int ID = 0;
            for (auto& fig : Figures) {
                vector<int> min_pos = fig->positon();
                vector<int> max_pos = fig->getRange();
                if (min_pos[0] <= x && x <= max_pos[0] && min_pos[1] <= y && y <= max_pos[1]) {
                    selected = ID;
                    list(ID);
                    return;
                }
                ID++;
            }
        }
        else {
            cout << "shape was not found" << endl;
        }

    }

    void save() {

        auto grid = board.getGrid();
        string input;

        cout << "Enter path to file: ";
        getline(cin, input);
        cout << endl;

        std::ofstream output_file(input);

        for (const auto& row : grid) {
            for (char c : row) {
                output_file << c;
            }
            output_file << '\n';
        }
    }

    void list() {
        int ID = 0;
        for (auto& fig : Figures) {
            Circle* circle = dynamic_cast<Circle*>(fig.get());
            Square* square = dynamic_cast<Square*>(fig.get());
            Triangle* triangle = dynamic_cast<Triangle*>(fig.get());
            Rectangle* rectangle = dynamic_cast<Rectangle*>(fig.get());
            auto coordinates = fig->positon();
            
            if (circle != nullptr) {
                cout << "ID " << ID << " Circle radius " << circle->getRadius() << " coordanates " << coordinates[0] << " " << coordinates[1] << endl;

            }

            if (square != nullptr) {
                if (square->getSide() != 0) {
                    cout << "ID " << ID << " Square side " << square->getSide() << " coordanates " << coordinates[0] << " " << coordinates[1] << endl;
                }
                else
                {
                    cout << "ID " << ID << " Square sides " << square->getSides() << " coordanates " << coordinates[0] << " " << coordinates[1] << endl;
                }

            }
            if (triangle != nullptr) {
                cout << "ID " << ID << " Triangle height " << triangle->getHeigh() << " coordanates " << coordinates[0] << " " << coordinates[1] << endl;

            }
            if (rectangle != nullptr) {
                cout << "ID " << ID << " Rectangle side " << triangle->getHeigh() << " coordanates " << coordinates[0] << " " << coordinates[1] << endl;

            }


            ID++;

        }


    }

    void list(int ID) {

        auto fig = Figures[ID];
        Circle* circle = dynamic_cast<Circle*>(fig.get());
        Square* square = dynamic_cast<Square*>(fig.get());
        Triangle* triangle = dynamic_cast<Triangle*>(fig.get());
        Rectangle* rectangle = dynamic_cast<Rectangle*>(fig.get());
        auto coordinates = fig->positon();

        if (circle != nullptr) {
            cout << "ID " << ID << " Circle radius " << circle->getRadius() << " coordanates " << coordinates[0] << " " << coordinates[1] << endl;

        }

        if (square != nullptr) {
            if (square->getSide() != 0) {
                cout << "ID " << ID << " Square side " << square->getSide() << " coordanates " << coordinates[0] << " " << coordinates[1] << endl;
            }
            else
            {
                cout << "ID " << ID << " Square sides " << square->getSides() << " coordanates " << coordinates[0] << " " << coordinates[1] << endl;
            }

        }
        if (triangle != nullptr) {
            cout << "ID " << ID << " Triangle height " << triangle->getHeigh() << " coordanates " << coordinates[0] << " " << coordinates[1] << endl;

        }
        if (rectangle != nullptr) {
            cout << "ID " << ID << " Rectangle side " << triangle->getHeigh() << " coordanates " << coordinates[0] << " " << coordinates[1] << endl;

        }
    
    }

    void load() {
        string input;

        cout << "Enter path to file: ";
        getline(cin, input);
        cout << endl;


        ifstream input_stream(input);
        if (!input_stream) {
            cerr << "Error opening file: " << input << endl;
            return;
        }

        std::vector<std::vector<char>> grid;
        string line;
        while (getline(input_stream, line)) {
            vector<char> row;


            for (char c : line) {
                if (c == ' ' || c == '*') { //change !!!!!!!!
                    row.push_back(c);
                }
            }

            grid.push_back(row);
        }

        input_stream.close();

        clear();

        board.setGrid(grid);

    }


    void clear() {
        while (!Figures.empty()) {
            Figures.pop_back();
        }
        board.reset();
    }

    void draw() {
        for (auto& fig : Figures) {
            auto cords = fig->positon();
            board.placeShape(*fig, cords[0], cords[1]);
        }
        board.print();
    }
    void add(vector<string> input) {
        shared_ptr<Figure> newFigure = nullptr;
        bool fill = (input[1] == "fill") ? true : false;
        char color = input[2][0];

        if (input[3] == "circle") {
            int rad = stoi(input[4]);
            int x = stoi(input[5]);
            int y = stoi(input[6]);

            newFigure = make_shared<Circle>(fill, color,rad, x, y);


        }
        else if (input[3] == "triangle") {
            int height = stoi(input[4]);
            int x = stoi(input[5]);
            int y = stoi(input[6]);

            newFigure = make_shared<Triangle>(fill,color,height, x, y);
        }

        else if (input[3] == "square") {
            if (input.size() == 8) { 
                int width = stoi(input[4]);
                int height = stoi(input[5]);
                int x = stoi(input[6]);
                int y = stoi(input[7]);

                newFigure = (make_shared<Square>(fill, color, width, height, x, y));
            }
            else if (input.size() == 7) { 
                int side = stoi(input[4]);
                int x = stoi(input[5]);
                int y = stoi(input[6]);

                newFigure = (make_shared<Square>(fill, color, side, x, y));
            }

        }

        else if (input[3] == "rectangle") {
            int side = stoi(input[4]);
            int x = stoi(input[5]);
            int y = stoi(input[6]);

            newFigure = (make_shared<Rectangle>(fill, color, side, x, y));
        }

        if (newFigure != nullptr) {
            if (!sameShape(*newFigure)) {
                Figures.emplace_back(newFigure);
            }
            else {
                cout << "This figure already on the board" << endl;
            }

        }


    }

    void shapes() {
        cout << "circle radius coordinates" << endl;
        cout << "triangle heigh coordinates" << endl;
        cout << "square side / (wight, heigh) coordinates" << endl;
        cout << "rectangle heigh coordinates" << endl;
    }

    vector<string> user_input() {
        string line;
        cout << "Input: ";
        getline(cin, line);
        stringstream ss(line);
        string token;
        vector<string> row;
        char delimiter = ' ';

        while (getline(ss, token, delimiter)) {
            row.push_back(token);
        }

        return row;
    }

    bool sameShape(Figure& fig) {
        for (auto& f : Figures) {
            if (*f == fig) {
                return true;
            }
        }
        return false;
    }
};

int main() {
    CLI cli;
    cli.start();
    return 0;
}
