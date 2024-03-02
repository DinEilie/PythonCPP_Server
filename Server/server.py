from logger import log_message
import socket
import struct
import uuid


def server_initialize(file_name, default_port):
    log_message('INFO', 'Server', 'Initializing server')
    try:
        log_message('INFO', 'FileHandler', 'Searching for \'port.info\' file')
        with open(file_name, 'r') as file:
            log_message('INFO', 'FileHandler', 'File is found')
            log_message('INFO', 'FileHandler', 'Reading port from file')
            port = file.readline().strip()
        log_message('INFO', 'FileHandler', f'Current port is: {port}')
        return int(port)
    except Exception as error:
        port = default_port
        log_message('ERROR', 'FileHandler', f'An error occurred while reading port from file:\n{error}')
        log_message('INFO', 'Server', f'The server will listen on port: {port}')
        return port

def read_exact(sock, size):
    """Read an exact amount of bytes from a socket."""
    data = b''
    while len(data) < size:
        packet = sock.recv(size - len(data))
        if not packet:
            return None  # Connection closed or error
        data += packet
    return data


def server_run(host, port):
    log_message('INFO', 'SocketHandler', 'Starting server')
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        log_message('INFO', 'SocketHandler', 'Binding socket to server')
        s.bind((host, port))
        log_message('INFO', 'SocketHandler', f'Server is now listening on port: {port}')
        s.listen()
        conn, addr = s.accept()
        log_message('INFO', 'SocketHandler', f'Server accepted new connection from address: {addr}')
        try:
            while True:
                # Accept the fixed-size header
                header_size = 16 + 1 + 2 + 4  # ClientID + Version + Code + PayloadSize
                header_data = read_exact(conn, header_size)

                if not header_data:
                    log_message('ERROR', 'SocketHandler', 'Failed to receive header from incoming request')
                    break  # Exit the loop, which triggers the socket to close
                
                # Read header bytes in little-endian order
                client_id = struct.unpack('<16s', header_data[:16])[0]
                version = struct.unpack('<B', header_data[16:17])[0]
                code = struct.unpack('<H', header_data[17:19])[0]
                payload_size = struct.unpack('<I', header_data[19:23])[0]

                # Read payload
                if code == 1025 and payload_size == 255: # Valid register payload
                    payload = read_exact(conn, payload_size)
                    if not payload:
                        log_message('ERROR', 'SocketHandler', 'Failed to receive payload from incoming request')
                        break;  # Exit the loop, which triggers the socket to close
                    
                    name = payload[:255].decode('ascii', 'ignore').rstrip('\x00')
                    log_message('INFO', 'SocketHandler', f'A new register request was received by {name}')

                # Since we want to close the socket right after reading the header, break here
                break

        finally:
            # Ensure the connection is closed gracefully
            conn.close()
            log_message('INFO', 'SocketHandler', 'Connection closed')
