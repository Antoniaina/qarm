#!/bin/bash

PID=$(pgrep -f "qemu-system-arm.*-M lm3s6965evb")

if [ -z "$PID" ]; then
	exit 1
else 
	kill -9 $PID
fi
