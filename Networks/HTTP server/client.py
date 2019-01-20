############################################################
########### My Client (telnet doesn't work...) #############
############################################################

from socket import *

s = socket(AF_INET, SOCK_STREAM)
s.connect(('127.0.0.1',80))
print 'client conncted...'
data = raw_input('>>> ')
s.sendall(data)
print s.recv(1000)
s.close()
