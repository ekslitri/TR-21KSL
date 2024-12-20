#!/bin/bash

# Function to send an HTTP request
send_request() {
  curl -i -X GET 127.0.0.1/compute &
}

# Infinite loop to send requests at random intervals between 5 to 10 seconds
while :; do
  send_request
  delay=$((RANDOM % 6 + 5))
  sleep $delay
done
