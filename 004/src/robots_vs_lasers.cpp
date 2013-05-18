#include "robots_vs_lasers.h"
#include <iostream>

using namespace std;

#define ROBOT_SYMBOL 'X'
#define LASER_SYMBOL '|'

enum
{
  NORTH_LASERS,
  CONVEYOR_BELT,
  SOUTH_LASERS,
  BLANK_LINE
};

//
// Parses what's given on stdin, and creates a `Decommissionator` for each
// layout in the input, printing the output of `Decommissionator::annihilate()`.
//
RobotsVsLasers::RobotsVsLasers()
{
  int lineIndex = NORTH_LASERS;
  int positionOfEntry;
  bitset<MAX_LASERS> northLasers;
  bitset<MAX_LASERS> southLasers;
  string line;

  while (!getline(cin, line).eof()) {
    switch (lineIndex) {
      case NORTH_LASERS:
        northLasers = laserStringToBitset(line);
        break;
      case SOUTH_LASERS:
        southLasers = laserStringToBitset(line);
        break;
      case CONVEYOR_BELT:
        positionOfEntry = findPositionOfEntry(line);
        break;
      case BLANK_LINE:
        lineIndex = -1;
        break;
    }
    if (lineIndex == SOUTH_LASERS)
    {
      Decommissionator decommissionator (northLasers, southLasers, positionOfEntry);
      cout << decommissionator.annihilate() << endl;
    }
    lineIndex++;
  };
}

RobotsVsLasers::~RobotsVsLasers()
{
  // Nothing to do here? Everything is done on the stack.
}

//
// Given a line of text input, returns a bitset representing an array of lasers,
// with the bits flipped on where a laser is present.
//
bitset<MAX_LASERS> RobotsVsLasers::laserStringToBitset(string lasers)
{
  bitset<MAX_LASERS> bits;
  string::iterator it;
  for (it = lasers.begin(); it < lasers.end(); it++) {
    if (*it == LASER_SYMBOL)
    {
      bits.set(distance(lasers.begin(), it));
    }
  }
  return bits;
}

//
// Returns the position where the robot will enter the conveyor given a line
// of text input.
//
int RobotsVsLasers::findPositionOfEntry(string belt)
{
  return (int)belt.find(ROBOT_SYMBOL);
}
