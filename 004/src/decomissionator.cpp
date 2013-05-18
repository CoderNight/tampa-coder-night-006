#include "decommissionator.h"

using namespace std;

enum
{
  EAST,
  WEST
};

Decommissionator::Decommissionator(bitset<MAX_LASERS> northLasers, bitset<MAX_LASERS> southLasers, int positionOfEntry)
{
  this->northLasers = northLasers;
  this->southLasers = southLasers;
  this->positionOfEntry = positionOfEntry;
  this->maskOne = makeMask("01");
  this->maskTwo = makeMask("10");
}

Decommissionator::~Decommissionator()
{
  // Nothing to do here? All resources are on the stack.
}

string Decommissionator::annihilate()
{
  if (simulateLaserFire(EAST) < simulateLaserFire(WEST))
  {
    return "GO EAST";
  } else {
    return "GO WEST";
  }
}

// Apply masks to cancel out lasers that won't fire
int Decommissionator::simulateLaserFire(int direction)
{
  bitset<MAX_LASERS> north = filterLasersByDirection(northLasers, direction);
  bitset<MAX_LASERS> south = filterLasersByDirection(southLasers, direction);
  north &= direction ? maskTwo : maskOne;
  south &= direction ? maskOne : maskTwo;
  return north.count() + south.count();
}

//
// Shift the bits, trimming off lasers that aren't in the direction we're going.
//
bitset<MAX_LASERS> Decommissionator::filterLasersByDirection(bitset<MAX_LASERS> lasers, int direction)
{
  if (direction == EAST)
  {
    return lasers >> positionOfEntry;
  } else {
    return lasers << MAX_LASERS - positionOfEntry - 1;
  }
}

bitset<MAX_LASERS> Decommissionator::makeMask(string parity)
{
  string maskString;
  for (int i = 0; i < MAX_LASERS / 2; i++) {
    maskString += parity;
  }
  return bitset<MAX_LASERS> (maskString);
}
