
#include "BTM.h"


String sm[2] = {"x=", "y="}; // start symbols arr for the receiving message
String data1[2];             // data arr for the receiving message
String data2[2];             // data arr for the sending message
size_t mSize = 0;            // the size has to be of type size_t

// creating vectors for each array
Vector<String> startSymbols(sm, mSize);
Vector<String> coordinates(data1, mSize);
Vector<String> signs(data2, mSize);

BTM btm(&Serial1); // I am only using Serial1
byte recMessage;   // receiving message
byte sendMessage;  // sending message

void setup()
{
  Serial1.begin(9600);
  recMessage = btm.createMessage(&startSymbols, &coordinates);
  sendMessage = btm.createMessage(&startSymbols, &signs);
}

void loop()
{

  if (btm.receiveMessage() == recMessage) // if a correct message received
  {
    signs[0] = coordinates[0].toInt() >= 0 ? "positive" : "negative"; // you have to set the data before sending
    signs[1] = coordinates[1].toInt() >= 0 ? "positive" : "negative";
    btm.sendMessage(sendMessage); // sending the data

  }
}
