import os
import shutil

def main():
  folder=input("Please enter the driver name")
  os.mkdir(folder)
  os.chdir(folder)
  config = folder+'_config.h'
  private = folder+'_private.h'
  register = folder+'_register.h'
  interface = folder+'_interface.h'
  program = folder+'_program.c'
  
  configFile=open(config,'w+')  
  privateFile=open(private,'w+')
  registerFile=open(register,'w+')
  interfaceFile=open(interface,'w+')
  programFile=open(program,'w+')
  
  c='#ifndef '+config[:-2].upper()+ '_H\n#define '+config[:-2].upper()+'_H\n\n#endif'
  configFile.write(c)
  p='#ifndef '+private[:-2].upper()+ '_H\n#define '+private[:-2].upper()+'_H\n\n#endif'
  privateFile.write(p)
  r='#ifndef '+register[:-2].upper()+ '_H\n#define '+register[:-2].upper()+'_H\n\n#endif'
  registerFile.write(r)
  i='#ifndef '+interface[:-2].upper()+ '_H\n#define '+interface[:-2].upper()+'_H\n\n#endif'
  interfaceFile.write(i)
  p='#include "std_types.h"\n#include "bit_math.h"\n'+'#include "'+config+'"\n'+'#include "'+private+'"\n'+'#include "'+register+'"\n'+'#include "'+interface+'"\n'
  programFile.write(p)
  
  
main()