############################################################
####################### Ex2 solution #######################
############################################################

def enterAccount(dic,accountNum,password):
	"checks if account_number and password are correct"
	if not dicCunsomer.has_key(account) or dicCunsomer[account][1] != password:
		return False	
	return True

def makeDecitions(dicCunsomer, accountNum):
	while True:
		answer = raw_input('Select an option:\n1) check balance\n2) withdraw cash\n3) deposite cash\n4) change password\n5) exit\n')

		if answer == '1':
			print 'Balance: %s' %dicCunsomer[accountNum][2]
			
		elif answer == '2':
			cash = raw_input('enter an amount: ')
			dicCunsomer[accountNum][2] = str(int(dicCunsomer[accountNum][2]) - int(cash))
		
		elif answer == '3':
			cash = raw_input('enter an amount: ')
			dicCunsomer[accountNum][2] = str(int(dicCunsomer[accountNum][2]) + int(cash))
		
		elif answer == '4':
			newPass = raw_input('enter new password: ')
			dicCunsomer[accountNum][1] = newPass
		
		elif answer == '5':
			return

file = open('customers.txt', 'r')
content = file.readlines()
file.close()

# creates dictionary
dicCunsomer = {}
for line in content:
	data = line.rstrip('\n').split(',')
	dicCunsomer[data[1]] = [data[0],data[2],data[3]]

# gets and updates customers acctions
while True:
	account = raw_input('Enter account number: ')
	if account == '-1':
		break
	
	password =  raw_input('Enter password: ')
	if enterAccount(dicCunsomer,account,password):
		makeDecitions(dicCunsomer, account)
	else:
		print 'Wrong account number or password!'
		
# update customers file
newLines = []
for key in dicCunsomer.keys():
	newLines.append(dicCunsomer[key][0]+','+key+','+dicCunsomer[key][1]+','+dicCunsomer[key][2]+'\n')

file = open('customers.txt', 'w')
file.writelines(newLines)
file.close()