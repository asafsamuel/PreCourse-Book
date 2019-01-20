############################################################
####################### Ex4 solution #######################
############################################################

import sys
import math

def extractRightNum(inx, exce):
	i = 0
	for c in exce[inx+1:]:
		if c in ["+","*","/","^","%","!","@","$","&"] or ((c == '-' or c == '~') and i != 0):
			break
		else:
			i = i+1
	return (exce[inx+1:inx+1+i], i)
	
def extractLeftNum(inx, exce):
	i = 0
	for c in exce[:inx][::-1]:
		if c == '-':
			if i == len(exce[:inx])-1 or exce[:inx][::-1][i+1] in ["+","-","*","/","^","%","!","@","$","&"]:
				i = i+1
			break
		elif c in ["+","*","/","^","!","%","@","$","&"]:
			break
		else:
			i = i+1	
	return (exce[inx-i:inx], inx-i)

def myCalc(expression):
	"calculate the expression by the rules"
	if len(expression) == 0:
		raise SyntaxError()
	
	#Parenthesis
	count = 0
	lCount = 0
	startIndex = -1
	finishIndex = -1
	for i in expression:
		if i == '[':
			if count == 0:
				startIndex = lCount
			count = count + 1
		elif i == ']':
			count = count - 1

		if count < 0:
			raise SyntaxError()
		elif count == 0 and startIndex != -1:
			return myCalc(expression[:startIndex] + myCalc(expression[startIndex+1:lCount]) + expression[lCount+1:])
		lCount = lCount + 1

	#Not
	index = expression.find('~')
	if index != -1:
		num,i = extractRightNum(index, expression)
		return myCalc(expression[:index] + str(-int(num)) + expression[index+1+i:])
	
	#Min & Max & Avg
	temp = filter(lambda a: a != -1, [expression.find('$'), expression.find('&'), expression.find('@')])
	if len(temp) != 0:
		index = min(temp)
		rightNum,i = extractRightNum(index, expression)	#right num	
		leftNum,j = extractLeftNum(index, expression)	#left num
		if expression[index] == '@':	#avg
			return myCalc(expression[:j] + str((int(rightNum)+int(leftNum))/2) + expression[index+1+i:])
		elif expression[index] == '$':	#max
			return myCalc(expression[:j] + str(max(int(rightNum),int(leftNum))) + expression[index+1+i:])
		else:	#min
			return myCalc(expression[:j] + str(min(int(rightNum),int(leftNum))) + expression[index+1+i:])
	
	#Modulo & Factorial
	temp = filter(lambda a: a != -1, [expression.find('%'), expression.find('!')])
	if len(temp) != 0:
		index = min(temp)
		leftNum, j = extractLeftNum(index, expression)
		if expression[index] == '%': #modulo
			rightNum, i = extractRightNum(index, expression)
			return myCalc(expression[:j] + str((int(leftNum)%int(rightNum))) + expression[index+1+i:])
		else:	# factorial
			return myCalc(expression[:j] + str(math.factorial(int(leftNum))) + expression[index+1+j:])
	
	#Exponentiation
	index = expression.find("^")
	if index != -1:
		rightNum, i = extractRightNum(index, expression)
		leftNum, j = extractLeftNum(index, expression)
		return myCalc(expression[:j] + str((int(leftNum)**int(rightNum))) + expression[index+1+i:])
	
	#Multiplication & Division
	temp = filter(lambda a: a != -1, [expression.find('*'), expression.find('/')])
	if len(temp) != 0:
		index = min(temp)
		rightNum, i = extractRightNum(index, expression)
		leftNum, j = extractLeftNum(index, expression)
		if expression[index] == '*': #multiplication
			return myCalc(expression[:j] + str((int(leftNum)*int(rightNum))) + expression[index+1+i:])
		else:	# division
			return myCalc(expression[:j] + str((int(leftNum)/int(rightNum))) + expression[index+1+i:])
	
	#Addition & Subtraction
	index1 = expression.find('+')
	index2 = -1
	count = 0
	for c in expression:
		if c == '-':
			if count != 0 and expression[count-1] not in ["+","-","*","/","^","%","!","@","$","&"]:
				index2 = count
				break
		count = count+1
	
	index = max(index1, index2)
	if index != -1:
		rightNum, i = extractRightNum(index, expression)
		leftNum, j = extractLeftNum(index, expression)
		if expression[index] == '+': #addition
			return myCalc(expression[:j] + str((int(leftNum)+int(rightNum))) + expression[index+1+i:])
		else:	#subtraction
			return myCalc(expression[:j] + str((int(leftNum)-int(rightNum))) + expression[index+1+i:])
			
	return expression
	
	
while True:
	string = raw_input(">>> ")
	string = string.replace(' ',"")
	if string == 'exit':
		sys.exit()
	
	print myCalc(string)
