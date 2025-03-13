#include <cctype>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>

using namespace std;

int precedence(char);
bool is_operator(char);

string infix_to_postfix(string);
double postfix_eval(string);

int main(int argc, char *argv[]) {
  string infix;
  /*cout << "Enter an infix expression (e.g., 3 + 4 * 2): ";*/
  /*getline(cin, infix);*/
  /*string postfix = infix_to_postfix(infix);*/
  /*cout << postfix << endl;*/
  /*cout << postfix_eval(postfix) << endl;*/

  if (argc > 1) {
    stringstream ss;
    for (int i = 1; i < argc; i++) {
      ss << argv[i] << " ";
    }
    infix = ss.str();
    /*cout << infix << " test " << endl;*/
  } else {
    cout << "Terminal calculator (type 'exit' to quit) \n";
    while (1) {
      cout << "> ";
      getline(cin, infix);
      /*cout << infix << " test " << endl;*/
      if (infix == "exit") return 0;
      try {
        string postfix = infix_to_postfix(infix);
        double result = postfix_eval(postfix);
        cout << result << endl;

      } catch (const exception &e) {
        cerr << "Error: " << e.what() << endl;
        /*return 1;*/
      }
    }
  }

  try {
    string postfix = infix_to_postfix(infix);
    double result = postfix_eval(postfix);
    cout << result << endl;
  } catch (const exception &e) {
    cerr << "Error: " << e.what() << endl;
    return 1;
  }
  return 0;
}

int precedence(char c) {
  if (c == '+' || c == '-')
    return 1;
  else if (c == '*' || c == '/')
    return 2;
  return 0;
}

bool is_operator(char c) {
  return (c == '*' || c == '/' || c == '+' || c == '-');
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
      /*cout << "digit " << i << endl;*/
      while (x < inf.length() && isdigit(inf[x])) {
        num += inf[x++];
        /*cout << "num " << num << endl;*/
      }
      x--;
      output.push(num);
      /*cout << "pushed in queue: " << num << endl;*/
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

double postfix_eval(string postfix) {

  stack<double> operands;
  stringstream ss(postfix);
  string token;

  while (ss >> token) {
    /*cout << token << endl;*/
    if (isdigit(token[0]))
      operands.push(stod(token));
    else {
      double b = operands.top();
      operands.pop();
      double a = operands.top();
      operands.pop();

      switch (token[0]) {
      case '+':
        operands.push(a + b);
        break;
      case '-':
        operands.push(a - b);
        break;
      case '*':
        operands.push(a * b);
        break;
      case '/':
        if (b == 0)
          throw runtime_error("Division by zero");
        operands.push(a / b);
        break;
      default:
        throw invalid_argument("invalid operator");
      }
    }
  }

  return operands.top();

  /*double solution;*/
  /*return solution;*/
}
