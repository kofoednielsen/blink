#!/bin/bash
export HOME=/root
cd /root/arduino/blink
while true then 
  do
  echo 0 > /sys/class/leds/led0/brightness
  echo "Running pipeline"
  echo "Pulling newest version.."
  git pull origin main
  echo "Compiling.."
  arduino-cli compile --fqbn arduino:avr:uno blink
  echo "Uploading.."
  arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno blink
  echo "Done."
  echo 1 > /sys/class/leds/led0/brightness
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
