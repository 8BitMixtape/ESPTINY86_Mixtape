'''

	Python Open Sound Control ( OSC ) basic examples



	this script is for python3
	Usage:
	 python3 playMelody.py 


	Yout will find the OSC format description here 
	OSC format description
	http://virchor.sourceforge.net/html/x2051.html

	V0.1 13.November 2018, ChrisMicro

'''


import socket
import time

#UDP_IP = "127.0.0.1"
UDP_IP = "192.168.178.40"

UDP_PORT = 8888

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP

def send(value):
 addressPatternString="/osc1\x00\x00\x00"
 typeTagString=",i\x00\x00"
 byteValues=value.to_bytes(4, byteorder='big')
 byteMESSAGE=addressPatternString.encode()+typeTagString.encode()+byteValues
 sock.sendto(byteMESSAGE, (UDP_IP, UDP_PORT))

for n in range(440,880,10):
 send(n)
 time.sleep(0.1);















