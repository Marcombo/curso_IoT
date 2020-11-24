import time
from paho.mqtt import client as mqtt_client

broker = "xxx"
port = 1883
topic = "data"
user="xxx"
passwd="xxx"

mqtt_test = mqtt_client.Client("test")
mqtt_test.username_pw_set(user,passwd)
mqtt_test.connect(broker,port)
i=0
while True:
	mqtt_test.publish(topic,i)
	i = i + 1
	if i>9:
		i=0
	time.sleep(1)
