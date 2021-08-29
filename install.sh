#!/bin/bash

#Install script of CppPhysics libraries for linux - Luca Morelli 2021
MISSING_F="0";
echo ""
echo "                                             
           :-..   ......:::::-:.              
         :+#%*=: .:::::::-+*#%#+=             
        :+*###+-::::::::::-+####+:..          
     ....:-+*-   .:::::   .:=*--=++=          
   ......:::: .::      ...:::::::-=-           CppPhysics installer for linux      
 .:....:::::.  ..      ..::::::::::.          
  .....::::.              .:::::::.               Made by Luca Morelli 2021
  ....::::       ....                
 .....::.       -+***=:       :-:       :-:         Libraries for Physics 
 ...... ..    -+*******=:     :-+..     :-+...      
  ... .:::   =*********#*- .::.:--== .::::--=+        Simulation in C++
 ..  .::::    -+*******=:     .::       .::  .
  . .:::::      -+*+*=:        ..        ..              Visit: 
   ...::::       ....                         
  .....:::...*-            -=---=.             github.com/MorelliLuca/CppPhysics
 .:....:::=+#%%*-. .::::::==-:::-=:           
  .......:-+*#*+-:::------:::::::=:           
   ........::+. :::::.:::::::::::=.           
     .........  ::::::::::::::::::.           
       ......:.. .::::::::::::::.             
         . .. .   .     .......               
                                  "
echo "Checking package for missing files..."
if [ ! -f lib/VectorAlgebra.hpp ] 
  then echo "Error: VectorAlgebra.hpp is missing"
  MISSING_F="1"
fi
if [ ! -f lib/Particle.hpp ] 
  then echo "Error: VectorAlgebra.hpp is missing"
  MISSING_F="1"
fi
if [ "$MISSING_F" -gt "0" ]
then echo "Please download again the package"
exit
fi
if [ "$EUID" -ne 0 ]
  then echo "Please run as root (sudo ./install.sh)"
  exit
fi  
read -p "Do you want to install CppPhysics libraries?[y/n]" choice
if [ "$choice" == "y" ] 
then
  echo "Checking for preinstalled version..."
  if [ ! -d /usr/include/CppPhysics ]
    then echo "Installing CppPhysics..."
    mkdir /usr/include/CppPhysics
    else echo "Updating CppPhysics..."
  fi
  cp lib/VectorAlgebra.hpp /usr/include/CppPhysics/VectorAlgebra.hpp
  cp lib/Particle.hpp /usr/include/CppPhysics/Particle.hpp
else exit
fi
