#!/bin/bash

# Function to start a container on a specific CPU core
start_container() {
  name=$1
  core=$2
  # Check if the container exists
  if docker ps -a --format '{{.Names}}' | grep -q "$name"; then
    # If the container is not running, remove it
    if ! docker ps --format '{{.Names}}' | grep -q "$name"; then
      docker rm "$name"
    else
      echo "Container $name is already running."
      return
    fi
  fi
  # Start the container on the specified CPU core
  echo "Starting $name on core $core..."
  docker run -d --name "$name" --cpuset-cpus="$core" ekslitri/httpserver
  sleep 10  # Allow the container to initialize
}

# Function to retrieve container CPU usage
cpu_usage() {
  name=$1
  # Get the CPU usage percentage of the container
  docker stats "$name" --no-stream --format "{{.CPUPerc}}" | sed 's/%//'
}

# Function to refresh all active containers
refresh_containers() {
  echo "Fetching the latest image..."
  docker pull ekslitri/httpserver

  # Map container names to CPU cores
  declare -A core_map=( ["srv1"]=0 ["srv2"]=1 ["srv3"]=2 )

  # Iterate through each container and refresh if running
  for name in srv1 srv2 srv3; do
    if docker ps --format '{{.Names}}' | grep -q "$name"; then
      echo "Stopping $name for refresh..."
      docker stop "$name"
      docker rm "$name"
      echo "Restarting $name..."
      start_container "$name" "${core_map[$name]}"
    fi
  done
}

# Main loop logic
last_check=$(date +%s)
while true; do
  # Ensure srv1 is running
  start_container srv1 0
  echo "Inspecting srv1..."
  if docker ps --format '{{.Names}}' | grep -q srv1; then
    usage1=$(cpu_usage srv1)
    sleep 20
    usage2=$(cpu_usage srv1)
    # Check if srv1 is heavily loaded
    if (( $(echo "$usage1 > 80" | bc -l) && $(echo "$usage2 > 80" | bc -l) )); then
      echo "srv1 is heavily loaded for 2 consecutive checks. Inspecting srv2..."
      # Start srv2 if not running
      if ! docker ps --format '{{.Names}}' | grep -q srv2; then
        start_container srv2 1
      fi
    fi
  fi

  # Check srv2 status
  if docker ps --format '{{.Names}}' | grep -q srv2; then
    usage1=$(cpu_usage srv2)
    sleep 20
    usage2=$(cpu_usage srv2)
    # Check if srv2 is heavily loaded
    if (( $(echo "$usage1 > 80" | bc -l) && $(echo "$usage2 > 80" | bc -l) )); then
      echo "srv2 is heavily loaded for 2 consecutive checks. Inspecting srv3..."
      # Start srv3 if not running
      if ! docker ps --format '{{.Names}}' | grep -q srv3; then
        start_container srv3 2
      fi
    # Check if srv2 is idle
    elif (( $(echo "$usage1 < 10" | bc -l) && $(echo "$usage2 < 10" | bc -l) )); then
      echo "srv2 is idle for 2 consecutive checks. Stopping it..."
      docker stop srv2
      docker rm srv2
    fi
  fi

  # Check srv3 status
  if docker ps --format '{{.Names}}' | grep -q srv3; then
    usage1=$(cpu_usage srv3)
    sleep 20
    usage2=$(cpu_usage srv3)
    # Check if srv3 is idle
    if (( $(echo "$usage1 < 10" | bc -l) && $(echo "$usage2 < 10" | bc -l) )); then
      echo "srv3 is idle for 2 consecutive checks. Stopping it..."
      docker stop srv3
      docker rm srv3
    fi
  fi

  # Check for new image version every 10 minutes
  current_time=$(date +%s)
  if (( current_time - last_check >= 600 )); then
    echo "Checking for new image version..."
    if docker pull ekslitri/httpserver | grep -q 'Downloaded newer image'; then
      echo "New image version detected. Refreshing containers..."
      declare -A core_map=( ["srv1"]=0 ["srv2"]=1 ["srv3"]=2 )
      # Refresh each running container
      for name in srv1 srv2 srv3; do
        if docker ps --format '{{.Names}}' | grep -q "$name"; then
          echo "Refreshing $name..."
          docker stop "$name"
          docker rm "$name"
          start_container "$name" "${core_map[$name]}"
          sleep 10  # Ensure at least one container is active before refreshing the next
        fi
      done
    fi
    last_check=$current_time
  fi

  sleep 20
done