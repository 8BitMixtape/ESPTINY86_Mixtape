'''

	Python Open Sound Control ( OSC ) basic examples



	this script is for python3
	Usage:
	 python3 UDP_OSC_sender.py 


	Yout will find the OSC format description here 
	OSC format description
	http://virchor.sourceforge.net/html/x2051.html

	V0.1 13.November 2018, ChrisMicro

'''


import socket

#UDP_IP = "127.0.0.1"
UDP_IP = "192.168.178.40"

UDP_PORT = 8888

############# very basic example ###############################

# OSC: the string length has always to be a multiple of 4 
addressPatternString="/osc1\x00\x00\x00"
# value format is integer
typeTagString=",i\x00\x00"
# int32_t format for integer
valueString="\x00\x00\x00\x02"

MESSAGE=addressPatternString+typeTagString+valueString


#MESSAGE = "/osc1\x00\x00\x00,i\x00\x00\x00\x00\x00\x01"


print("UDP target IP:", UDP_IP)
print("UDP target port:", UDP_PORT)
print("message:", MESSAGE)

#print MESSAGE as hex string
print(":".join("{:02x}".format(ord(c)) for c in MESSAGE))


sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP
sock.sendto(bytes(MESSAGE, "utf-8"), (UDP_IP, UDP_PORT))


########### send one integer value to osc1 #####################

addressPatternString="/osc1\x00\x00\x00"
typeTagString=",i\x00\x00"

value=440
byteValues=value.to_bytes(4, byteorder='big')

byteMESSAGE=addressPatternString.encode()+typeTagString.encode()+byteValues


print("UDP target IP:", UDP_IP)
print("UDP target port:", UDP_PORT)
print("message:", MESSAGE)
#print MESSAGE as hex string
print(byteMESSAGE.hex())


sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP
sock.sendto(byteMESSAGE, (UDP_IP, UDP_PORT))

########### send one integer value to osc2 ####################

addressPatternString="/osc2\x00\x00\x00"
typeTagString=",i\x00\x00"
#valueString="\x00\x00\x00\x02"
value=440
byteValues=value.to_bytes(4, byteorder='big')

byteMESSAGE=addressPatternString.encode()+typeTagString.encode()+byteValues


print("UDP target IP:", UDP_IP)
print("UDP target port:", UDP_PORT)
print("message:", MESSAGE)
#print MESSAGE as hex string
print(byteMESSAGE.hex())


sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP
sock.sendto(byteMESSAGE, (UDP_IP, UDP_PORT))






