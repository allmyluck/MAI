import socket, time, persistqueue, os, shutil, collections, threading, math, quemodule

quit = False
host = socket.gethostbyname(socket.gethostname()) # в клиенте
print(host)
port = 9090
s = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
s.bind((host,port))
quemodule.check()
f = open('St.txt', 'w')

print("[ Server Started ]")

while not quit:
	try:
		data, addr= s.recvfrom(1024)
		itsatime = time.strftime("%Y-%m-%d-%H.%M.%S", time.localtime()) # берем время для того чтобы на сервере отображалось время отправки сообщения
		# тут добавление в клиентs
		print("["+addr[0]+"]=["+str(addr[1])+"]=["+itsatime+"]/",end="") # принтим сообщение и время серверу
		print(data.decode("utf-8"))
	except KeyboardInterrupt:
		quemodule.check()
		f.write("1")
		quit = True
		print("\n[ Server Stopped ]")
s.close()

