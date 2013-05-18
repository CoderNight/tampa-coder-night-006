#include <bitset>

#define MAX_LASERS 256

using namespace std;

class Decommissionator
{
  public:
    Decommissionator(bitset<MAX_LASERS> northLasers, bitset<MAX_LASERS> southLasers, int positionOfEntry);
    ~Decommissionator();
    string annihilate();
  private:
    bitset<MAX_LASERS> northLasers;
    bitset<MAX_LASERS> southLasers;
    bitset<MAX_LASERS> maskOne;
    bitset<MAX_LASERS> maskTwo;
    int positionOfEntry;
    int simulateLaserFire(int direction);
    bitset<MAX_LASERS> filterLasersByDirection(bitset<MAX_LASERS> lasers, int direction);
    bitset<MAX_LASERS> makeMask(string parity);
};
