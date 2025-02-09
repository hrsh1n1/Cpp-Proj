#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;
using namespace sf;

const int WIDTH = 800;
const int HEIGHT = 600;

Color NODE_COLOR = Color::White;
Color TEXT_COLOR = Color::Black;
Color HIGHLIGHT_COLOR = Color::Red;


Font font;

// Stack 
stack<int> stk;
vector<int> stackElements;

// Queue 
queue<int> q;
vector<int> queueElements;

// Linked List Node
struct ListNode {
    int value;
    ListNode* next;
    ListNode(int v) : value(v), next(nullptr) {}
};

ListNode* head = nullptr;

// Binary Tree Node
struct TreeNode {
    int value;
    TreeNode* left, * right;
    TreeNode(int v) : value(v), left(nullptr), right(nullptr) {}
};

TreeNode* root = nullptr;

// Function to draw a circle (used for Linked List and Binary Tree)
void drawCircle(RenderWindow& window, int x, int y, int value, bool highlight = false) {
    CircleShape node(25);
    node.setPosition(x, y);
    node.setFillColor(highlight ? HIGHLIGHT_COLOR : NODE_COLOR);
    node.setOutlineThickness(2);
    node.setOutlineColor(Color::Black);
    window.draw(node);

    // Display text inside node
    Text text(to_string(value), font, 20);
    text.setPosition(x + 10, y + 5);
    text.setFillColor(TEXT_COLOR);
    window.draw(text);
}

// Function to draw Stack
void drawStack(RenderWindow& window) {
    int x = WIDTH - 100, y = HEIGHT - 50;
    for (int i = stackElements.size() - 1; i >= 0; i--) {
        drawCircle(window, x, y, stackElements[i]);
        y -= 60;
    }
}

// Function to draw Queue
void drawQueue(RenderWindow& window) {
    int x = 100, y = HEIGHT / 2;
    for (int i = 0; i < queueElements.size(); i++) {
        drawCircle(window, x, y, queueElements[i]);
        x += 60;
    }
}

// Function to draw Linked List
void drawLinkedList(RenderWindow& window) {
    int x = 100, y = HEIGHT / 3;
    ListNode* temp = head;
    while (temp) {
        drawCircle(window, x, y, temp->value);
        temp = temp->next;
        x += 60;
    }
}

// Function to draw Binary Tree
void drawBinaryTree(RenderWindow& window, TreeNode* node, int x, int y, int depth = 1) {
    if (!node) return;
    drawCircle(window, x, y, node->value);
    if (node->left) {
        Vertex line[] = {
            Vertex(Vector2f(x + 25, y + 25), Color::White),
            Vertex(Vector2f(x - 50, y + 75), Color::White)
        };
        window.draw(line, 2, Lines);
        drawBinaryTree(window, node->left, x - 50, y + 75, depth + 1);
    }
    if (node->right) {
        Vertex line[] = {
            Vertex(Vector2f(x + 25, y + 25), Color::White),
            Vertex(Vector2f(x + 100, y + 75), Color::White)
        };
        window.draw(line, 2, Lines);
        drawBinaryTree(window, node->right, x + 100, y + 75, depth + 1);
    }
}

// Stack Operations
void pushStack(int value) {
    stk.push(value);
    stackElements.push_back(value);
}

void popStack() {
    if (!stk.empty()) {
        stk.pop();
        stackElements.pop_back();
    }
}

// Queue Operations
void enqueue(int value) {
    q.push(value);
    queueElements.push_back(value);
}

void dequeue() {
    if (!q.empty()) {
        q.pop();
        queueElements.erase(queueElements.begin());
    }
}

// Linked List Operations
void insertLinkedList(int value) {
    ListNode* newNode = new ListNode(value);
    if (!head) head = newNode;
    else {
        ListNode* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
    }
}

void deleteLinkedList() {
    if (head) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

// Binary Tree Operations
TreeNode* insertBinaryTree(TreeNode* node, int value) {
    if (!node) return new TreeNode(value);
    if (value < node->value) node->left = insertBinaryTree(node->left, value);
    else node->right = insertBinaryTree(node->right, value);
    return node;
}

void insertBinaryTree(int value) {
    root = insertBinaryTree(root, value);
}

// Main Function
int main() {
    RenderWindow window(VideoMode(WIDTH, HEIGHT), "Data Structure Visualization");

    // Load font
    if (!font.loadFromFile("arial.ttf")) {
        cout << "Error loading font\n";
        return 1;
    }

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        // Keyboard Inputs
        if (Keyboard::isKeyPressed(Keyboard::S)) pushStack(rand() % 100);
        if (Keyboard::isKeyPressed(Keyboard::D)) popStack();
        if (Keyboard::isKeyPressed(Keyboard::Q)) enqueue(rand() % 100);
        if (Keyboard::isKeyPressed(Keyboard::E)) dequeue();
        if (Keyboard::isKeyPressed(Keyboard::L)) insertLinkedList(rand() % 100);
        if (Keyboard::isKeyPressed(Keyboard::R)) deleteLinkedList();
        if (Keyboard::isKeyPressed(Keyboard::B)) insertBinaryTree(rand() % 100);

        window.clear(Color::Black);

        // Draw Data Structures
        drawStack(window);
        drawQueue(window);
        drawLinkedList(window);
        drawBinaryTree(window, root, WIDTH / 2, 50);

        window.display();
    }

    return 0;
}
