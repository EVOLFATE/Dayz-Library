#!/bin/bash
# DayZ Server Startup Script Template
# This script helps manage your DayZ server startup

# Configuration
SERVER_DIR="/path/to/your/dayz/server"
SERVER_EXEC="DayZServer"
CONFIG_FILE="serverDZ.cfg"
PORT=2302
PROFILES_DIR="profiles"
LOG_FILE="server.log"

# Mod configuration
MODS="-mod=@CF;@CommunityOnlineTools;@Dabs Framework;@Your_Custom_Mod"

# Additional parameters
PARAMS="-config=$CONFIG_FILE -port=$PORT -profiles=$PROFILES_DIR -dologs -adminlog -netlog -freezecheck"

# CPU affinity (optional - set which CPU cores to use)
CPU_COUNT=$(nproc)
# CPU_AFFINITY="taskset -c 0-3"  # Use cores 0-3

# Change to server directory
cd "$SERVER_DIR" || exit 1

# Print startup info
echo "================================"
echo "DayZ Server Startup"
echo "================================"
echo "Server Directory: $SERVER_DIR"
echo "Config File: $CONFIG_FILE"
echo "Port: $PORT"
echo "Mods: $MODS"
echo "================================"

# Check if server executable exists
if [ ! -f "$SERVER_EXEC" ]; then
    echo "ERROR: Server executable not found: $SERVER_EXEC"
    exit 1
fi

# Check if config file exists
if [ ! -f "$CONFIG_FILE" ]; then
    echo "ERROR: Config file not found: $CONFIG_FILE"
    exit 1
fi

# Create profiles directory if it doesn't exist
if [ ! -d "$PROFILES_DIR" ]; then
    echo "Creating profiles directory..."
    mkdir -p "$PROFILES_DIR"
fi

# Backup previous log
if [ -f "$LOG_FILE" ]; then
    TIMESTAMP=$(date +%Y%m%d_%H%M%S)
    mv "$LOG_FILE" "${LOG_FILE}.${TIMESTAMP}.bak"
    echo "Previous log backed up to ${LOG_FILE}.${TIMESTAMP}.bak"
fi

# Kill any existing server instances
echo "Checking for existing server processes..."
pkill -9 "$SERVER_EXEC" 2>/dev/null
sleep 2

# Start the server
echo "Starting DayZ Server..."
echo "Command: ./$SERVER_EXEC $PARAMS $MODS"
echo "================================"

# Option 1: Start in foreground (with output)
# ./$SERVER_EXEC $PARAMS $MODS 2>&1 | tee -a "$LOG_FILE"

# Option 2: Start as background process
nohup ./$SERVER_EXEC $PARAMS $MODS > "$LOG_FILE" 2>&1 &
SERVER_PID=$!

echo "Server started with PID: $SERVER_PID"
echo "Log file: $LOG_FILE"
echo "To view logs: tail -f $LOG_FILE"
echo "To stop server: kill $SERVER_PID"
echo "================================"

# Optional: Monitor server process
sleep 5
if ps -p $SERVER_PID > /dev/null; then
    echo "✓ Server is running"
else
    echo "✗ Server failed to start. Check $LOG_FILE for errors"
    exit 1
fi
