while true then 
  do
  echo "HTTP/1.1 200 OK" | nc -lN 1234 > /dev/null
  echo "Running pipeline"
  echo "Pulling newest version.."
  git pull origin main
  echo "Compiling.."
  arduino-cli compile --fqbn arduino:avr:uno blink
  echo "Uploading.."
  arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno blink
  echo "Done."
done
