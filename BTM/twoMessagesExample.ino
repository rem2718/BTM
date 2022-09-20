#include <BTM.h>
/*
  -A simple example for receiving different messages
  -here you dont need to use another device, use the serial monitor to send messages
  -try these: ?id=0&a=first&b=second; | ?id=1&w=red;
*/

String sm1[2] = {"a=", "b="}; // start symbols arr for the first message
String sm2[1] = {"w="};       // start symbols arr for the second message
String data1[2];              // data arr for the first message
String data2[1];              // data arr for the second message
size_t mSize = 0;             // the size has to be of type size_t

// creating vectors for each array
Vector<String> startSymbols1(sm1, mSize);
Vector<String> startSymbols2(sm2, mSize);
Vector<String> nums(data1, mSize);
Vector<String> colors(data2, mSize);

BTM btm(&Serial);
byte message1; // receiving message
byte message2; // sending message

void setup()
{
  Serial.begin(9600);
  message1 = btm.createMessage(&startSymbols1, &nums);
  message2 = btm.createMessage(&startSymbols2, &colors);
}

void loop()
{
  byte id = btm.receiveMessage();
  if (id == message1)
    Serial.println(nums[0] + ", " + nums[1]);
  else if (id == message2)
    Serial.println("color: " + colors[0]);
}
