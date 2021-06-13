#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;
int main() {
  stringstream ss;
  ss << "hello" << endl;
  ss << "world";

  string message = ss.str();
  send(client, message.c_str(),
}