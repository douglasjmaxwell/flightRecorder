#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <ostream>
#include <iostream>
#include <math.h>
#include "IMU.h"
#include <wiringPi.h>
#include <bits/stdc++.h>

#define NUM_THREADS 1
 
using namespace std;

int main(int argc, char **argv) {
  pid_t pid;
  int accRaw[3];
  float adj = 16000.0 / 65535.0;
  
  IMU berryIMU = IMU();

  // init gpio interface
  wiringPiSetup();
  pinMode (25,OUTPUT);
  
  // pid = fork();

  // if (pid == 0)
  // {
  //   cout << "forked pid: " << getpid() << endl;
  //   unsigned long int timestamp = time(NULL);
  //   char* filename = (char *)tmpName.c_str();
  //   char *args[] = {"/home/pi/picam/picam" NULL};
  //   int err = execvp(args[0],args);
  //   std::cout << "return code:" << err << std::endl;
  // }
  // else
  // {
  //   cout << "pid: " << pid << endl;
  //   cout << "getpid: " << getpid() << endl;
  // }
  
  // std::cout << "starting sleep to allow raspivid to start" <<  std::endl;
  // std::this_thread::sleep_for(std::chrono::seconds(2));
  // std::cout << "sending sigusr1 to raspivid to pause" <<  std::endl;
  // int status = kill(pid,SIGUSR1);

  // turn on LED
  digitalWrite(25, HIGH);
  float magAcc = 0.0;
  float xx = 0.0;
  float yy = 0.0;
  float zz = 0.0;
  while (magAcc < 2.0)
  {
    berryIMU.readACC(accRaw);
    float xx = pow((accRaw[0] * adj),2.0);
    float yy = pow((accRaw[1] * adj),2.0);
    float zz = pow((accRaw[2] * adj),2.0);
    magAcc = sqrt(xx + yy +zz) / 1000.0;
  }
  
  std::cout << "telling picam to start recording" <<  std::endl;
  system("touch /home/pi/picam/hooks/start_record");
  std::cout << "starting sleep" <<  std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(30));
  std::cout << "finished sleep"  << std::endl;
  system("touch /home/pi/picam/hooks/stop_record");
 
  // turn off LED
  digitalWrite(25, LOW);
  return EXIT_SUCCESS;
}

