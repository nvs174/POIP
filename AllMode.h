#ifndef ALLMODE
#define ALLMODE

#include "Mode.h"
#include <array>

template<auto& ...pins>
class AllMode : public Mode
{
public:
void Update() override
{
for(int i=0; i<leds.size(); ++i)
{
leds[i]->Toggle();
}
}

void Clear() override 
  {
   
    for (int i = 0; i<leds.size(); ++i) 
    {
      leds[i]->LedSetLow();
    
    }
  }
private:
std::size_t i=0;
std::array<Ipin*, sizeof ...(pins)> leds = {static_cast<Ipin*> (&pins)...};
};

#endif