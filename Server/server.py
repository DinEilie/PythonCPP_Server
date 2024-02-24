from logger import log_message
import socket


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


def server_run(host, port):
    log_message('INFO', 'SocketHandler', 'Starting server')
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        log_message('INFO', 'SocketHandler', 'Binding socket to server')
        s.bind((host, port))
        log_message('INFO', 'SocketHandler', f'Server is now listening on port: {port}')
        s.listen()
        conn, addr = s.accept()
        log_message('INFO', 'SocketHandler', f'Server accepted new connection from address: {addr}')
        while conn:
            print("con!")
            while True:
                print("response con!")
                data = conn.recv(1024)
                text = data.decode('utf-8')
                print(text)
                replydata = bytearray('Shalom from server!', 'utf-8')
                conn.send(replydata)
