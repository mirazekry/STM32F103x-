#ifndef RCC_INTERFACE_H
#define RCC_INTERFACE_H

u8 rcc_u8Clock (u8 clockSource);

u8 rcc_u8PllEnable (u8 pllmul, u8 pllsrc);

void rcc_voidEnablePeripheral (u8 peripheral);

void rcc_voidDisablePeripheral (u8 peripheral);

void rcc_setMCO(u8 mcosrc);

void rcc_AHBprescaler(u8 prescaler);

void rcc_APB2prescaler(u8 prescaler);

void rcc_APB1prescaler(u8 prescaler);



#endif