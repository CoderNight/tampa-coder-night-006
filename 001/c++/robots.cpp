#include <iostream>
#include "robots.h"

using namespace std;

int count_laser(string s, bool parity) {
  int count = 0;
  for (string::iterator it = s.begin(); it != s.end(); it++, parity = !parity) {
    if (parity && *it == '|')
      count++;
  }
  return count;
}

string reverse(string s) {
  return string(s.rbegin(), s.rend());
}

void process_robots(string upper, string middle, string lower) {
  int pos = middle.find('X');
  string upper_east = upper.substr(pos);
  string upper_west = upper.substr(0, pos+1);
  string lower_east = lower.substr(pos);
  string lower_west = lower.substr(0, pos+1);
  int west = count_laser(reverse(upper_west), true) + count_laser(reverse(lower_west), false);
  int east = count_laser(upper_east, true) + count_laser(lower_east, false);
  cout << "GO " << (east < west ? "EAST" : "WEST") << endl;
}
