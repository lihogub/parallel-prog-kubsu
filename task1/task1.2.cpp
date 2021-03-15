#include <iostream>
#include <stack>
#include <vector>
#include <fstream>
using namespace std;

struct Node {
    char value;
    bool op = false;
    Node* left = 0;
    Node* right = 0;
};

void readNewChar(char ch, vector<char>* output, stack<char>* st) {
    if (ch >= 'a' && ch <= 'z') {
        output->push_back(ch);
    } else if (ch == '(') {
        st->push('(');
    } else if (ch =='[') {
        st->push('&');
        st->push('[');
    } else if (ch == ']') {
        while (!st->empty()) {
            if (st->top() != '[') {
                output->push_back(st->top());
                st->pop();
            } else {
                st->pop();
                break;
            }
        }
    } else if (ch == ')') {
        while (!st->empty()) {
            if (st->top() != '(') {
                output->push_back(st->top());
                st->pop();
            } else {
                st->pop();
                break;
            }
        }
    } else if (ch == '+' || ch == '-') {
        while (!st->empty() && (st->top() == '+' || st->top() == '-')) {
            output->push_back(st->top());
            st->pop();
        }
        st->push(ch);
    } else if (ch == ' ') {
        while (!st->empty()) {
            output->push_back(st->top());
            st->pop();
        }
    }
}

string RPN(string expression) {
    vector<char>* output = new vector<char>();
    stack<char>* st = new stack<char>();
    for (int i = 0; i < expression.size(); i++)
        readNewChar(expression.at(i), output, st);
    readNewChar(' ', output, st);
    string result = "";
    for (auto ch : *output) result.append(1, ch);
    delete st;
    delete output;
    return result;
}

Node* treeFromRPN(string rpn) {
    int len = rpn.length();
    Node* nodeArray = new Node[len];
    for (int i = 0; i < len; i++) {
        nodeArray[i].value = rpn.at(i);
        if (!(rpn.at(i) >= 'a' && rpn.at(i) <= 'z')) {
            nodeArray[i].op = true;
        }
    }
    stack<Node*>* nodeStack = new stack<Node*>();
    for (int i = 0; i < len; i++) {
        if (nodeArray[i].op) {
            nodeArray[i].right = nodeStack->top();
            nodeStack->pop();
            nodeArray[i].left = nodeStack->top();
            nodeStack->pop();
            nodeStack->push(nodeArray + i);
        } else {
            nodeStack->push(nodeArray + i);
        }
    }
    Node* treeRoot = nodeStack->top();
    delete nodeStack;
    return treeRoot;
}


void discoverTree(Node* root) {
    if (root) {
        cout << '(';
        discoverTree(root->left);
        cout << root->value;
        discoverTree(root->right);
        cout << ')';
    }
}


int main() {
    ifstream file("task1.txt", ios::in);
    string s;
    file >> s;
    string rpn = RPN(s);
    Node* root = treeFromRPN(rpn);
    cout << "tree: ";
    discoverTree(root);
    cout << endl;
    return 0;
}