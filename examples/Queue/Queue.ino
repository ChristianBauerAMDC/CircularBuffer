#include <CircularBuffer.h>
#include <Arduino.h>


CircularBuffer<int> queue(10);

uint32_t t = 0;

bool UP = true;
int nextNum = 0;


#define BUTTON_PIN 3

void setup() {
	Serial.begin(9600);
	//pinMode(BUTTON_PIN, INPUT);
	t = millis();
}

// enqueue button press dequeueing every 2 seconds
void loop() {
	//if (digitalRead(BUTTON_PIN) == HIGH) {
	//	queue.push(millis());
	//}


	if (millis() - t >= 1000) {
		t = millis();

		// Reverse direction if queue is either full or empty
		if (UP)
		{
			if (queue.available() <= 0)
			{
				UP = false;
			}
		}
		else
		{
			if (queue.size() <= 0)
			{
				UP = true;
			}
		}

		if (UP)
		{
			nextNum++;
			Serial.print("Enqueing element:");
			Serial.println(nextNum);
			queue.enqueue(nextNum);
		}
		else
		{
			auto element = queue.dequeue();
			nextNum--;
			Serial.print("Dequeued element: ");
			Serial.println(element);
		}

		Serial.println("Queue now contains:");
		// Print queue items
		for (size_t i = 0; i < queue.size(); i++)
		{
			Serial.print(queue[i], DEC);
		}
		Serial.println();


	}
}
