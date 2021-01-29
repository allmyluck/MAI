import socket, time, persistqueue,  os, shutil, math, operator
path = os.path.join(os.path.abspath(os.path.dirname(__file__)), 'myqueue') 
q = persistqueue.SQLiteQueue(path, auto_commit=True)
# connect
host = ""
server = (host,9090)
host = socket.gethostbyname(socket.gethostname()) # это наш айпи
port = 0
s = socket.socket(socket.AF_INET,socket.SOCK_DGRAM) 
s.bind((host,port)) # передаем ему айпи
s.setblocking(0) # не уверен, что это нужно, но она предотвращает возможные ошибки
# connect

def SortThird(val):
	return val[2]


def check ():
	global q
	q = persistqueue.SQLiteQueue(path, auto_commit=True)
	i = q.qsize()
	while (i > 0):
		dat, dr, pr, vrem, exptime, pers = q.get()
		if pers == "Yes":
			q.put((dat,dr,pr,vrem,exptime,pers))
		i = i - 1
	


def delete (q): # время жизни сообщений(высчитываю не совсем корректно но это бетка)
	try:
		i = q.qsize()
		size = i
		while (i > 0):
			clock = time.strftime("%d%M%S", time.localtime()) # время сейчас
			clock = int(clock)
			dat, dr, pr, vrem, exptime, pers = q.get()
			a = int(math.fabs(int(clock) - int(vrem))) # разница времени сообщения и время сейчас
			if (a < int(exptime)): # если больше n секунд, сам тут в ифе выбираешь, то сообщение удаляется из персистентноц очереди
				q.put((dat, dr, pr, vrem, exptime,pers))
			i = i - 1
		return 0
	except:
		return 0


def sort (q):
	try:
		i = q.size
		size = i
		nlist = []
		while(i > 0):
			dat, dr, pr, vrem, exptime, pers = q.get()
			nlist.append((dat, dr, pr, vrem, exptime,pers))
			i = i - 1
		nlist.sort(key = SortThird)
		nlist.reverse()
		while(size > 0):
			dat, dr, pr, vrem, exptime, pers = nlist.pop()
			q.put((dat, dr, pr, vrem, exptime, pers))
			size = size - 1
		return 0
	except:
		return 0


def Connect(name):
	message = '/connect:' + name
	s.sendto((message).encode("utf-8"),server)
	return True


def Unconnect(name):
	message = '/unconnect:' + name
	s.sendto((message).encode("utf-8"),server)


# main functions


def Send(name, message, extime, priority, pers):
	global q
	clock = time.strftime("%d%M%S", time.localtime()) # для времени жизни сообщений
	q.put((message, name, priority, clock, extime, pers))
	message = '/send:' + str(message) + ',name:' + str(name)
	s.sendto((message).encode("utf-8"),server)

	
def Recieve(name):
	f = open('St.txt', 'r')
	if (f.read(1) == "1") :
		print("Server Closed")
		return 0
	global q
	q = persistqueue.SQLiteQueue(path, auto_commit=True)
	try:
		sort(q)
		delete(q)
		i = q.qsize()
		while(i > 0):
			dat, dr, pr, vrem, exptime, pers = q.get()
			if(name != dr):
				forprint = str(dat) + ',/name:' + str(dr) + ',/priority:' + str(pr) + ',/time:' + str(exptime)
				print(forprint)
				q.put((dat,dr,pr,vrem,exptime,pers))
			elif (name == dr):
				q.put((dat,dr,pr,vrem,exptime,pers))
			i = i - 1
	except Exception as err:
		print(err)
		print("Error in recieve")


def DeleteQueue():
	global q
	i = q.qsize()
	while (i > 0): # очищаем нашу очередь
		dat, dr, pr, vrem, exptime, pers = q.get()
		if(name != dr):
			q.put((dat,dr,pr,vrem,exptime,pers))
		i = i - 1


def DeleteAllQueue():
	global q
	DeleteQueue()

# main functions