#include <fstream>
#include <string>
#include <iostream>
#include <list>
#include "robots.h"

using namespace std;

int main(int argc, char *argv[]) {
  if (argc != 2) {
    cout << "Usage: " << argv[0] << " FILENAME" << endl;
    exit(1);
  }
  const char *filename = argv[1];
  ifstream f(filename);
  string line;
  // getline returns a stream reference (basically a stream) but while
  // takes an int, so it calls a streams method to convert it to int
  // which returns the status of the getline operation -- tricky, eh?
  list<string> lines;
  while (getline(f, line)) {
    if (line == "") continue;
    lines.push_back(line);
    if (lines.size() == 3) {
      list<string>::iterator it = lines.begin();
      process_robots(*it++, *it++, *it++);
      lines.clear();
    }
  }
  // don't need to close f because it should be handled by the destructor
  return 0; // 0 is success
}
