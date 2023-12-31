import paho.mqtt.client as mqtt

TEMPERATURE_TOPIC = "topic_sensor_temperature"
HUMIDITY_TOPIC = "topic_sensor_humidity"
LED_TOPIC = "topic_on_off_led"

class IoTDevice:
    def __init__(self, broker, port):
        self.client = mqtt.Client()
        self.client.on_connect = self.on_connect
        self.client.on_message = self.on_message

        self.temperature = None
        self.humidity = None

        self.client.connect(broker, port, 60)
        self.client.loop_start()

    def on_connect(self, client, userdata, flags, rc):
        print(f"Conectado com código de resultado {rc}")
        client.subscribe(TEMPERATURE_TOPIC)
        client.subscribe(HUMIDITY_TOPIC)
        client.subscribe(LED_TOPIC)

    def on_message(self, client, userdata, msg):
        if msg.topic == TEMPERATURE_TOPIC:
            self.temperature = float(msg.payload.decode().replace("C", ""))
            print(f"Temperatura atual: {self.temperature}°C")
        elif msg.topic == HUMIDITY_TOPIC:
            self.humidity = float(msg.payload.decode())
            print(f"Umidade atual: {self.humidity}%")
        elif msg.topic == LED_TOPIC:
            if msg.payload == b"1":
                print("Alarme ligado")
            elif msg.payload == b"0":
                print("Alarme desligado")

    def turn_on_alarm(self):
        self.client.publish(LED_TOPIC, "1")
        print("Ligando o alarme")

    def turn_off_alarm(self):
        self.client.publish(LED_TOPIC, "0")
        print("Desligando o alarme")

    def run(self):
        while True:
            print("Escolha uma opção:")
            print("1 - Ativar Alarme")
            print("0 - Desativar Alarme")
            option = input()

            if option == "1":
                self.turn_on_alarm()
            elif option == "0":
                self.turn_off_alarm()
            else:
                break

        self.client.loop_stop()

if __name__ == "__main__":
    iot_device = IoTDevice("broker.hivemq.com", 1883)
    iot_device.run()