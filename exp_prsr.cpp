#include <cctype>
#include <iostream>
#include <queue>
#include <stack>

using namespace std;
string infix_to_postfix(string inf);

bool is_operator(char c) {
  return (c == '*' || c == '/' || c == '+' || c == '-');
}

int precedence(char c) {
  if (c == '+' || c == '-')
    return 1;
  else if (c == '*' || c == '/')
    return 2;
  return 0;
}

int main() {
  string infix;
  cout << "Enter an infix expression (e.g., 3 + 4 * 2): ";
  getline(cin, infix);
  string postfix = infix_to_postfix(infix);
  cout << postfix << endl;
  return 0;
}

string infix_to_postfix(string inf) {
  stack<char> operators;
  queue<string> output;

  for (int x = 0; x < inf.length(); x++) {
    char i = inf[x];
    if (i == ' ')
      continue;

    if (isdigit(i)) {
      string num;
      cout << "digit " << i << endl;
      while (x < inf.length() && isdigit(inf[x])) {
        num += inf[x++];
        cout << "num " << num << endl;
      }
      x--;
      output.push(num);
      cout << "pushed in queue: " << num << endl;
    }

    else if (is_operator(i)) {
      while (!operators.empty() &&
             precedence(operators.top()) >= precedence(i)) {
        output.push(string(1, operators.top()));
        operators.pop();
      }
      operators.push(i);
    }
  }
  while (!operators.empty()) {
    output.push(string(1, operators.top()));

    operators.pop();
  }
  string postfix;
  while (!output.empty()) {
    postfix += output.front() + " ";
    output.pop();
  }
  return postfix;
}
