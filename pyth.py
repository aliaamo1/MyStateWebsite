#!/usr/bin/python
import cgi
import cgitb
import csv
cgitb.enable()

print "Content-Type: text/html"
print

form=cgi.FieldStorage()
sessionID=form["sessionID"].value
if form.has_key("newfriend") == True:
	newfriend = form["newfriend"].value
	
	f=open("members.csv", "r")
	userInfo=[]
	for line in f.readlines():
		userInfo.append(line.split(",")) 
	
	friendfound = False
	for user in userInfo:
		if user[1] == newfriend:
			friendfound = True
	
	f.close()
	if friendfound == True:
		for user in userInfo:
			if user[1] == sessionID:
				#print "<p>**" + user[3] + "**</p>"
				if user[3] == " \n":
					user[3] = user[3][:-2] + form["newfriend"].value + " " + "\n"
				else:
					user[3] = user[3][:-1] + form["newfriend"].value + " " + "\n"

		f=open("members.csv", "w")
		for user in userInfo:
			f.write(user[0] + "," + user[1] + "," + user[2] + "," + user[3])
		f.close()

	else:
		print "User does not exist."

elif form.has_key("StatusUpdate") == True:
	status = form["StatusUpdate"].value
	f=open("topics.csv", "a")
	f.write(sessionID + "\n" + status + "\n")
	f.close()

#############################################

print "<html>"
print "<body>"
print "<h2>" + sessionID + "</h2>"
print "<a href='../triWel.html'> Logout </a><br>"

print "<h2>Current users:</h2>"
f=open("members.csv", "r")
for line in f.readlines():
	items=line.split(",") #where item[0] = real name, item[1] = username, item[2] = password, item[3] = list of friends
	print "<p>" + items[1] + "</p>"
f.close()

f=open("members.csv", "r")
info=[]
users =[] # a list of the current usernames
dict = {} #They keys = username, value = user's friends
for aline in f.readlines():
	info.append(aline.split(","))

print "<br>"
for user in info: #populating the dictionary with keys and values 
	dict[user[1]] = user[3].strip("\n")
	users.append(user[1])
	print "<br>"
f.close()
#print dict
#print users 

print "<h2>Friend updates: </h2>"
print "</p>"
f=open("topics.csv", "r")
lines = f.readlines()
usersAndMessages=[]
UsrMessages={} #this dictionary includes users and their corresponding messages


for i in range(0,len(lines),2):
	personWhoPosted = lines[i]
	usersAndMessages.append(personWhoPosted.strip("\n"))
	message = lines[i+1]
	usersAndMessages.append(message.strip("\n"))

#populating the dictionary of user: messages
for j in users:
	message = ""
	for i in range(len(usersAndMessages)):
		if usersAndMessages[i]==j:
			message= message + usersAndMessages[i+1] + " "
			UsrMessages[j]= message
	
	
print UsrMessages
print "</p>"

f.close()

print "<form action='pyth.py' method='get'>"
print "<input type='hidden' name='sessionID' value='" + sessionID + "'>"
print "Add friend: <input type='text' name='newfriend'>"
print "<input type='submit' value='Submit'>"
print "</form>"
print "<form action='pyth.py' method='get'>"
print "<input type='hidden' name='sessionID' value='" + sessionID + "'>"
print "Update Status: <input type='text' name='StatusUpdate'>"
print "<input type='submit' value='Submit'>"
print "</form>"
print "</body>"
print "</html>"
