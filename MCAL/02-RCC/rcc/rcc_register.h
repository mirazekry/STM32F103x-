#ifndef RCC_REGISTER_H
#define RCC_REGISTER_H

#define BASE_ADDRESS	0x40021000

typedef struct
{
	u32 CR;
	u32 CFGR;
	u32 CIR;
	u32 APB2RSTR;
	u32 APB1RSTR;
	u32 AHBENR;
	u32 APB2ENR;
	u32 APB1ENR;
	u32 BDCR;
	u32 CSR;
}RCCstruct;

static volatile RCCstruct* RCC = (volatile RCCstruct*) BASE_ADDRESS;

#endif