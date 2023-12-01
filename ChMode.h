ifndef CHESSMODE
#define CHESSMODE
#include "Mode.h"
#include <array>

template <auto& ... pins>

class ChessMode: public Mode
{

public: 
    
void Update() override
{
 
  
  
  if (flag == true) 
  {
   for (i = 0; i < leds.size(); i++) 
    {
      if (i % 2 == 0)
      {
        leds[i]->Toggle();
      }
    
    }
   flag = false;
  }
  else 
  {
    for (i = 0; i < leds.size(); i++) 
    {
      if (i % 2 != 0)
      {
        leds[i]->Toggle();
      }
  
    }
    flag = true;
  
  }
 
}

void Clear() override
{
 flag = false;
 for (i = 0; i < leds.size(); i++) 
 {
   leds[i]->LedSetLow();
 }
 i = 0;
}

  
private:
  
bool flag;
std:: size_t i = 0;
std:: array<Ipin*, sizeof ... (pins) > leds = {&pins ... };

};


#endif
