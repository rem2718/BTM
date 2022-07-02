#ifndef BTM_h
#define BTM_h

#include "Arduino.h"
#include <Vector.h>

class BTM
{
public:
  class Message
  {
  public:
    Message();
    Message(Vector<String> *_startSymbols, Vector<String> *_data);
    Vector<String> *mStartSymbols; // vector for the start symbols for each data
    Vector<String> *mData;         // the data for the message
  };
  BTM();
  BTM(HardwareSerial *_serial);
  Message createMessage(Vector<String> *_startSymbols, Vector<String> *_data); // creating messages
  void sendMessage(Message message);                                           // sending messages
  bool receiveMessage(Message message);                                        // receiving messages, returning true if the message is correct

private:
  HardwareSerial *serial;
  bool readData(String text);           // setting the data to their vector
  void setMessageInfo(Message message); // setting the vectors for the active message
  const char START_CHAR = '?';
  const char END_CHAR = ';';
  const char MID_CHAR = '&';
  Vector<String> *startSymbols;
  Vector<String> *data;
  Message *prevMessage; // var to check whether the message changed or not
};

#endif
