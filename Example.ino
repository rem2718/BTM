
#include "BTM.h"

/*
-A simple example for receiving coordinates(x,y) and sending their signs(positive, negative)
-The format for the messages is ?xy&xy; x for start symbols, y for data
-Create Message for each collection of data youre sending/receiving(this class takes only vectors
*/

String sm1[2] = {"x=", "y="}; // start symbols arr for the receiving message
String sm2[3] = {"a=", "b="}; // start symbols arr for the sending message
String data1[2];              // data arr for the receiving message
String data2[3];              // data arr for the sending message
size_t mSize = 2;             // the size has to be of type size_t

// creating vectors for each array
Vector<String> startSymbols1(sm1, mSize);
Vector<String> startSymbols2(sm2, mSize);
Vector<String> coordinates(data1, mSize);
Vector<String> signs(data2, mSize);

BTM btm(&Serial1);        // I am only using Serial1
BTM::Message RecMessage;  // receiving message
BTM::Message SendMessage; // sending message

void setup()
{
  Serial1.begin(9600);
  RecMessage = btm.createMessage(&startSymbols1, &coordinates);
  SendMessage = btm.createMessage(&startSymbols2, &signs);
}

void loop()
{
  if (btm.receiveMessage(RecMessage)) // if a correct message received
  {
    signs[0] = coordinates[0].toInt() >= 0 ? "positive" : "negative"; // you have to set the data before sending
    signs[1] = coordinates[1].toInt() >= 0 ? "positive" : "negative";
    btm.sendMessage(SendMessage); // sending the data
  }
}
