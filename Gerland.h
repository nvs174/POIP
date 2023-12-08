#ifndef GERLAND
#define GERLAND
#include "Mode.h"
#include "ipin.h"
#include <array>

template <auto& ... modes>
class Gerland: public Mode 
{
public:
  void NextMode() 
  {
    if (i == rezhim.size()) 
    {
     i = 0;
    }
    currentMode = rezhim[i];
    i++;
    
     
  }
  
  
  void Update()
  {
    currentMode->Update();
  }

  void Clear() override 
  {
   currentMode->Clear();
  }
  
private:
  std:: size_t i = 0;

  std:: array<Mode*, sizeof ... (modes) > rezhim = {&modes ... };
  
  Mode* currentMode = rezhim[0];

};
#endif
