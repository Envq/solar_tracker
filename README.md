# Solar tracker 1 axis
This is my implementation of a simple solar tracker in Arduino Nano for "Electronic devices and sensors" Course


## Schematic:
0. Arduino Nano

1. MOTOR:
    - 5V --> MOTOR+
    - GND --> MOTOR-
    - IN1 --> D9    (output)
    - IN2 --> D10   (output)
    - IN3 --> D11   (output)
    - in4 --> D12   (output)

2. PHOTORESISTORS:
    - 5V --> photoresistor1
    - photoresistor1 --> A7   (input)
    - photoresistor1 --> photoresistor2
    - photoresistor2 --> GND
