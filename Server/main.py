from logger import log_message
from server import server_initialize, server_run
import socket
import os
print("Current Working Directory:", os.getcwd())


# Configurations
host = ''
filePortInfo = 'port.info'
defaultPort = 1256

# Start server
currentPort = server_initialize(filePortInfo, defaultPort)
server_run(host, currentPort)
