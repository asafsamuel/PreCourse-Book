############################################################
###################### HTTP solution #######################
############################################################

from socket import *

base_path = raw_input('Enter files lcoation for website: ').replace('\\','/')
server_s = socket(AF_INET, SOCK_STREAM)
server_s.bind(('0.0.0.0',80))
server_s.listen(5)
print 'Server is running...'

# communication with client
while True:
	(client_s, client_addr) = server_s.accept()
	command = client_s.recv(1000)
	cmd_tockens = command.split(' ')

	if len(cmd_tockens) >= 2 and cmd_tockens[0] == 'GET':
		try:
			file = open(base_path + cmd_tockens[1], 'r').read()
			data = 'HTTP/1.0 200 Document follows\n' + 'Content-Length: '+str(len(file))+'\n' + '\n'+file		
		except:
			data = 'HTTP/1.0 404 Not Found\n\n'
		client_s.sendall(data)
	client_s.close()