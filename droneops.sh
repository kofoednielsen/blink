#!/bin/bash

export RED=18
export GREEN=23
export BLUE=24

# export status led pints to userspace
echo $RED > /sys/class/gpio/export  
echo $GREEN > /sys/class/gpio/export  
echo $BLUE > /sys/class/gpio/export  

# Sets status led pins as an output
echo "out" > /sys/class/gpio/gpio$RED/direction
echo "out" > /sys/class/gpio/gpio$GREEN/direction
echo "out" > /sys/class/gpio/gpio$BLUE/direction

# turn all off
echo "1" > /sys/class/gpio/gpio$RED/value
echo "1" > /sys/class/gpio/gpio$GREEN/value
echo "1" > /sys/class/gpio/gpio$BLUE/value

set_status_color() {
	echo "1" > /sys/class/gpio/gpio$RED/value
	echo "1" > /sys/class/gpio/gpio$GREEN/value
	echo "1" > /sys/class/gpio/gpio$BLUE/value

	if [$1]
	then
		echo "0" > /sys/class/gpio/gpio$1/value
	fi
}


export HOME=/root
cd /root/arduino/blink
while true then 
  do
  set_status_color $BLUE
  echo "Running pipeline"
  echo "Pulling newest version.."
  git pull origin main
  echo "Compiling.."
  arduino-cli compile --fqbn arduino:avr:uno blink
  arduino-cli compile --fqbn arduino:avr:uno blink
  echo "Uploading.."
  arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno blink
  echo "Done."
  set_status_color $GREEN
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
done
