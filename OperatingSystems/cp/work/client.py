import socket, threading, time, string,persistqueue, quemodule #библиотеки
shutdown = False
join = False


alias = input("Name: ")
while shutdown == False:
	if join == False:
		join = quemodule.Connect(alias)
	else:
		try:
			message = input()
			if message == "/recieve":
				quemodule.Recieve(alias) # считываем сообщение
			elif message == "/quit":
				quemodule.Unconnect(alias)
				shutdown = True
			elif message == "/clear":
				quemodule.DeleteAllQueue()
			else:
				extime = input("ExpirationTime(sec): ")
				priority = input("Priority:3(low),2(middle),1(high): ")
				pers = input("Pers Yes or No: ")
				quemodule.Send(alias,message,extime,priority,pers)
			time.sleep(0.2)
		except Exception as err:
			print(err)
			quemodule.Unconnect(name)
			shutdown = True			