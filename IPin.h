#ifndef IPIN
#define IPIN

class Ipin
{
public:
  virtual void Toggle() const = 0;
  
  virtual void LedSetLow() const = 0;
};
 
#endif