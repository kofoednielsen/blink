while true then 
  do
  echo "HTTP/1.1 200 OK" | nc -lN 1234
  echo "Running pipeline"
  git pull origin main
  arduino-cli compile --fqbn arduino:avr:uno blink
  arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno blink
done
