import socket
 
UDP_IP = "127.0.0.1"
#UDP_IP = "192.168.4.2"
#UDP_PORT = 10086
#UDP_PORT = 3333
UDP_PORT = 8888

 
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP
sock.bind((UDP_IP, UDP_PORT))

while True:
 data, addr = sock.recvfrom(1024) # buffer size is 1024 bytes
 #print ("received message: " + data)
 print(data)

