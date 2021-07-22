#!/bin/bash
export HOME=/root
cd /root/project/blink

RED=18
GREEN=23
BLUE=24
TEENSY_RESET=4
# export status led pints to userspace
echo $RED > /sys/class/gpio/export  
echo $GREEN > /sys/class/gpio/export  
echo $BLUE > /sys/class/gpio/export  
echo $TEENSY_RESET > /sys/class/gpio/export

# Sets status led pins as an output
echo "out" > /sys/class/gpio/gpio$RED/direction
echo "out" > /sys/class/gpio/gpio$GREEN/direction
echo "out" > /sys/class/gpio/gpio$BLUE/direction
echo "out" > /sys/class/gpio/gpio$TEENSY_RESET/direction

# turn all off
echo "1" > /sys/class/gpio/gpio$RED/value
echo "1" > /sys/class/gpio/gpio$GREEN/value
echo "1" > /sys/class/gpio/gpio$BLUE/value
echo "1" > /sys/class/gpio/gpio$TEENSY_RESET/value

set_status_color() { 
  echo "1" > /sys/class/gpio/gpio$RED/value
  echo "1" > /sys/class/gpio/gpio$GREEN/value
  echo "1" > /sys/class/gpio/gpio$BLUE/value
 
  if [ "$1" != "" ]
  then
    echo "0" > /sys/class/gpio/gpio$1/value
  fi
}

loop() {
  set_status_color $BLUE
  echo "Running pipeline"
  echo "Pulling newest version.."

  git pull origin main
  if [ "$?" != "0" ]
  then
    set_status_color $RED
    return
  fi

  echo "Reset teensy"
  echo "0" > /sys/class/gpio/gpio$TEENSY_RESET/value
  sleep 0.1
  echo "1" > /sys/class/gpio/gpio$TEENSY_RESET/value

  echo "Compiling.."
  arduino-cli compile --fqbn teensy:avr:teensy40
  if [ "$?" != "0" ]
  then
    set_status_color $RED
    return
  fi
  echo "Done."
  set_status_color $GREEN

  SERIAL=`ls /dev/ttyACM*`
  while [ "$SERIAL" == "" ]
  do
    sleep 0.5
    SERIAL=`ls /dev/ttyACM* 2> /dev/null`
  done
  echo "Found serial on $SERIAL"
  nc 192.168.1.77 1337 < $SERIAL &
}

loop

while true then 
  do
  echo "HTTP/1.1 200 OK
Connection: keep-alive
Content-Type: text/html; charset=utf-8
Date: Thu, 10 Jun 2021 21:52:01 GMT
Server: NetCat

<html>
<head>
<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">
<title>Thank you for this request</title>
</head>
<body>
We're happy to be able to serve your needs.
</body>
</html>" | nc -lN 1234 > /dev/null
  loop
done
