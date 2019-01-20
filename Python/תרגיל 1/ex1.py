############################################################
####################### Ex1 solution #######################
############################################################

def addFullName(var):
	"Adds first name and last name before and after the string"
	return "Asaf "+var.rstrip('\n')+" Samuel\n"

fileName = raw_input('Enter file name (with extention): ')

fileRead = open(fileName, 'r')
content = fileRead.readlines()
fileRead.close()

newContent = map(addFullName, content)

fileWrite = open("new_"+fileName, 'w')
fileWrite.writelines(newContent)
fileWrite.close()