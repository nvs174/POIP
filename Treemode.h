#ifndef TREEMODE
#define TREEMODE
#include "Mode.h"
#include <array>

template <auto& ... pins>

class TreeMode: public Mode
{
public: 
  void Update() override
  {
    
    leds[i++]->Toggle(); 
    
   if (i == leds.size())
   {
    i = 0;
   }
  }
  
  void Clear() override
{
  
  for (int i = 0; i < leds.size(); i++) 
  {
    leds[i]->LedSetLow();
  }
  i = 0;
}
private:
  std::size_t i = 0;
  std::array<Ipin*, sizeof ...(pins)> leds = {static_cast<Ipin*> (&pins)...};
};

#endif