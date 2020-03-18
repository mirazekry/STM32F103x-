void delay_ms(u32 time)
{
  const u32 ctr = time * 666;
  for (volatile u32 i = 0; i < ctr; i++)
  {
  }
}

void delay_us(u32 time)
{
  const u32 ctr = (time * 666)/1000;
  for (volatile u32 i = 0; i < ctr; i++)
  {
  }
}
