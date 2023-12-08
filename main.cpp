#include "rccregisters.hpp"     // for RCC
#include "gpioaregisters.hpp"   // for GPIOA
#include "gpiocregisters.hpp"   // for GPIOC
#include "Pin3.h"               // for pin
#include "Treemode.h"           // for metod pins
#include "ChMode.h"             // for metod pins
#include "Gerland.h"            // for metod pins
#include "AllMode.h"            // for metod pins
#include "Button2.h"            // for button
#include "tim5registers.hpp"    // for TIM5




//std::uint32_t SystemCoreClock = 16'000'000U;
std::uint32_t SystemCoreClock = 8'000'000U;

using tMec = std::uint32_t;


//TIM5::CR1::CEN::Enable::Set();

//void delay(int cycles)
void delay(tMec period)
{
  
  const auto timerValue = static_cast<std::uint32_t>(period * (SystemCoreClock / 1000U - 1U));
  STK::LOAD::Write(timerValue);
  STK::CTRL::ENABLE::Enable::Set();
  while (not STK::CTRL::COUNTFLAG::Overflow::IsSet()) 
  {
  }
  STK::CTRL::ENABLE::Disable::Set();
  
  
  
  /*for(int i = 0; i < cycles; ++i)    
  {   
    asm volatile("");
  }*/    
}

void LowSetLed() 
{
  GPIOA::ODR::ODR5::Low::Set();
  GPIOC::ODR::ODR9::Low::Set();
  GPIOC::ODR::ODR8::Low::Set();
  GPIOC::ODR::ODR5::Low::Set();
}

Pin<GPIOA, 5>  pin1;
Pin<GPIOC, 9>  pin2;
Pin<GPIOC, 8>  pin3;
Pin<GPIOC, 5>  pin4;

Button<GPIOC, 13> btn;

AllMode<pin1, pin2, pin3, pin4> allMode;
TreeMode<pin1,pin2, pin3, pin4> treemode;
ChessMode<pin1,pin2, pin3, pin4> chessmode;

Gerland<allMode,treemode, chessmode> gerland;

int main()
{

  RCC::APB1ENR::TIM5EN::Enable::Set();  
  // Подать тактирование на порт А
  RCC::AHB1ENR::GPIOAEN::Enable::Set() ;
  // Подать тактирование на порт А
  RCC::AHB1ENR::GPIOCEN::Enable::Set() ;
  // Порт  А.5 на вывод
  GPIOA::MODER::MODER5::Output::Set() ;
  // Порта С.5,С.8,С.9 на вывод
  GPIOC::MODER::MODER5::Output::Set() ;
  GPIOC::MODER::MODER8::Output::Set() ;
  GPIOC::MODER::MODER9::Output::Set() ;
  
  //GPIOC::MODER::MODER13::Output::Set(); // вкдючили кнопку
  GPIOC::MODER::MODER13::Input::Set();
  //GPIOC::ODR::ODR13::High::Set();
 
  
  for(;;)
  {
     gerland.Update();
    if(btn.IsPressed())
    {
      gerland.Clear();
      gerland.NextMode();
    }
    delay(100);
    
     }
  
  return 1;
}

