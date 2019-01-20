############################################################
####################### Ex3 solution #######################
############################################################

import time

class Event:
	def __init__(self, name, place, date):
		self.name = name
		self.place = place
		self.date = date
		
	def toString(self):
		return self.name + ',' + self.place + ',' + time.strftime("%d/%m/%Y %H:%M", self.date)
		
def showTodayEvents(list):
	"display all events that occur today"
	current = time.localtime(time.time())
	for event in list:
		if time.strftime("%d/%m/%Y", event.date) == time.strftime("%d/%m/%Y", current):
			print event.toString()

def showAllEvents(list):
	"display all aviables events"
	for event in list:
		print event.toString()

def addEvent(list):
	"add new event to the list"
	current = time.localtime(time.time())
	name = raw_input("Enter event's name: ")
	place = raw_input("Enter event's place: ")
	
	flag = True
	while flag:
		str = raw_input("Enter event's date and hour (i.e: day/month/year hour:min): ")
		date = time.strptime(str, "%d/%m/%Y %H:%M")
			
		if (date.tm_year < current.tm_year) or (date.tm_year == current.tm_year and date.tm_mon< current.tm_mon) or (date.tm_year == current.tm_year and date.tm_mon == current.tm_mon and date.tm_mday < current.tm_mday):
			print "the date has already passed!"

		else:
			flag = False

	list.append(Event(name,place,date))
	print "successfully added new event!"

def removeOldEvents(list):
	"remove all previous events from the list"
	current = time.localtime(time.time())
	for e in list:
		if (e.date.tm_year < current.tm_year) or (e.date.tm_year == current.tm_year and e.date.tm_mon< current.tm_mon) or (e.date.tm_year == current.tm_year and e.date.tm_mon == current.tm_mon and e.date.tm_mday < current.tm_mday):
			list.remove(e)
		
# read from file
file = open('events.txt', 'r')
content = file.readlines()
file.close()

# creates list
events = []
for line in content:
	data = line.rstrip('\n').split(',')
	events.append(Event(data[0],data[1],time.strptime(data[2], "%d/%m/%Y %H:%M")))

# user's acctions
removeOldEvents(events)
while True:
		answer = raw_input("Options:\n1) Display today's events\n2) Display all events\n3) Add event\n4) Exit\n")
		if answer == '3':
			addEvent(events)
			
		elif answer == '2':
			showAllEvents(events)
			
		elif answer == '1':
			showTodayEvents(events)
		
		elif answer == '4':
			break

# save events to file
newLines = []
for e in events:
	newLines.append(e.toString()+'\n')
file = open('events.txt', 'w')
file.writelines(newLines)
file.close()