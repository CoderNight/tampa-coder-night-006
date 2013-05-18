#include <string>
#include "decommissionator.h"

using namespace std;

class RobotsVsLasers
{
  public:
    RobotsVsLasers();
    ~RobotsVsLasers();
  private:
    bitset<MAX_LASERS> laserStringToBitset(string lasers);
    int findPositionOfEntry(string belt);
};
