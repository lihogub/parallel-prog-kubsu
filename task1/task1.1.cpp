#include <iostream>
#include <stack>
#include <fstream>
using namespace std;

void print(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int choice(int* prob, int vars) {
    int* arr = new int[1000];
    int i = 0;
    for (int var = 0; var < vars; var++) {
        for (int j = 0; j < prob[var]; j++) {
            arr[i+j] = var;
        }
        i += prob[var];
    }
    return arr[rand() % 1000];
}

stack<char> parStack;
int ops = 0;

struct State {
    bool stated = false;
    char value;
    int prob[3][6] = {0};
    char getChar() {
        if (value == '?') 
            return (rand()%2) ? '+' : '-';
        return value;
    };
    void count() {
        if ((value == '?') || (value == '[')) ops++;
    };
    void init() {
        if (value == '(') {
            parStack.push('(');
        } else if (value == '[') {
            parStack.push('[');
        } else if ((value == ')') || (value == ']')) {
            parStack.pop();
        }
    };
    int nextState() {
        if (stated) {
            if (parStack.empty()) {
                return choice(prob[0], 6);
            } else if (parStack.top() == '(') {
                return choice(prob[1], 6);
            } else if (parStack.top() == '[') {
                return choice(prob[2], 6);
            }
        }
        return choice(prob[0], 6);
    };

};


int main() {
    srand(time(0));
    int tgt;
    int p;
    int q;
    int r;
    
    cout << "N:";
    cin >> tgt;

    cout << "P:";
    double _p;
    cin >> _p;
    p = (int)(_p*1000);

    cout << "R:";
    double _r;
    cin >> _r;
    r = (int)(_r*1000);

    cout << "Q:";
    double _q;
    cin >> _q;
    q = (int)(_q*1000);

    State* states[6];

    State* plus_minus = new State;
    states[0] = plus_minus;
    plus_minus->value = '?';
    plus_minus->prob[0][1] = 1000 - p;
    plus_minus->prob[0][2] = p;

    State* round_open_bracket = new State;
    states[2] = round_open_bracket;
    round_open_bracket->value = '(';
    round_open_bracket->prob[0][1] = 1000 - p;
    round_open_bracket->prob[0][2] = p;

    State* square_open_bracket = new State;
    states[3] = square_open_bracket;
    square_open_bracket->value = '[';
    square_open_bracket->prob[0][1] = 1000 - p;
    square_open_bracket->prob[0][2] = p;

    State* round_close_bracket = new State;
    states[4] = round_close_bracket;
    round_close_bracket->stated = true;
    round_close_bracket->value = ')';
    round_close_bracket->prob[0][0] = 1;
    round_close_bracket->prob[1][0] = 1000 - q;
    round_close_bracket->prob[1][4] = q;
    round_close_bracket->prob[2][0] = 1000 - q;
    round_close_bracket->prob[2][5] = q;

    State* square_close_bracket = new State;
    states[5] = square_close_bracket;
    square_close_bracket->stated = true;
    square_close_bracket->value = ']';
    square_close_bracket->prob[0][0] = 1;
    square_close_bracket->prob[1][0] = 1000 - q;
    square_close_bracket->prob[1][4] = q;
    square_close_bracket->prob[2][0] = 1000 - q;
    square_close_bracket->prob[2][5] = q;

    State* ident = new State;
    states[1] = ident;
    ident->stated = true;
    ident->value = 'a';
    ident->prob[0][0] = 1000 - r;
    ident->prob[0][3] = r;

    ident->prob[1][0] = 1000 - r - q;
    ident->prob[1][3] = r;
    ident->prob[1][4] = q;

    ident->prob[2][0] = 1000 - r - q;
    ident->prob[2][3] = r;
    ident->prob[2][5] = q;
    
    string S;
    while (true) {
        ops = 0;
        S = "";
        while (parStack.size()) parStack.pop();
        int st_index = 0;
        while (true) {
            st_index = states[st_index]->nextState();
            states[st_index]->init();
            states[st_index]->count();
            S += states[st_index]->getChar();
            if (ops >= tgt && (st_index == 1 || st_index == 4)) break;
        }
        if (parStack.size() || ops != tgt) continue;
        break;
    }
    ofstream file("task1.txt", ios::out);
    file << S;
    file.close();
    return 0;
}