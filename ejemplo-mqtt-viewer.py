import paho.mqtt.client as mqtt
import time

def on_message(client,userdata,message):
	data = str(message.payload.decode("utf-8"))
	topic = str(message.topic)
	print(topic,data)

broker_user = "xxxx"
broker_password = "xxxx"
broker_address = "xxxx"
broker_port = 1883
broker_topic = "xxxx"

#print("creating new instance")
mqttclient = mqtt.Client("mqttviewer") #create new instance
mqttclient.username_pw_set(broker_user,broker_password)

#print("connecting to broker")
mqttclient.connect(broker_address,port=broker_port) #connect to broker
mqttclient.loop_start()

#print("Subscribing to topic")
mqttclient.subscribe(broker_topic)
mqttclient.on_message=on_message        #attach function to callback

try:
	while True:
		time.sleep(1)

except KeyboardInterrupt:
	print("bye")
	mqttclient.disconnect()
	mqttclient.loop_stop()
