############################################################
###################### SMTP solution #######################
############################################################

from socket import *
import sys

s = socket(AF_INET, SOCK_STREAM)
s.connect((raw_input("Server's address: "),25))

if '220' != s.recv(1000)[:3]:
	sys.exit("Invalid server's address!")

s.send('HELO '+raw_input("Local hostname: ")+'\r\n')
if '250' != s.recv(1000)[:3]:
	sys.exit("Invalid local hostname!")

s.send('MAIL FROM: <'+raw_input("Your email: ")+'>\r\n')
if '250' != s.recv(1000)[:3]:
	sys.exit("Invalid source email!")
	
s.send('RCPT TO: <'+raw_input("To: ")+'>\r\n')
if '250' != s.recv(1000)[:3]:
	sys.exit("Invalid destination email!")

s.send('DATA\r\n')
if '354' != s.recv(1000)[:3]:
	sys.exit("Cannot send email!")

s.send('Subject: '+raw_input("Subject: ")+'\r\n')
data = raw_input('Message data [end with "." on a single line]:\n')
while(data != '.'):
	s.send(data+'\r\n')
	data = raw_input()

s.send(".\r\n")
if '250' != s.recv(1000)[:3]:
	sys.exit("Server didn't accept the message!")

s.send('QUIT\r\n')
s.close()