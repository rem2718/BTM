#ifndef BTM_h
#define BTM_h

#include "Arduino.h"
#include <Vector.h>
/*

  -Create BTM for each serial you will use
  -The format for the messages is ?id=i&xy&xy; i for id, x for start symbols and, y for data (to change the const characters modify BTM.h)
  -The symbols/data can be in any length
  -You can use any number of data
  -Create Message for each collection of data youre sending/receiving(this class takes only vectors)
  -Start symbols can be shared across messages(they are read-only vectors)
  -Data arrays have to be unique for each message
  -all data are string you can convert them to any type using(.toInt()/.toFloat()/...)

*/
class BTM
{
  public:
    BTM();                                                                    // empty constructor
    BTM(Stream *_serial);                                             // full argument constructor
    byte createMessage(Vector<String> *_startSymbols, Vector<String> *_data); // creating messages, and returning the id of the message
    void sendMessage(byte id);                                                // sending messages using its id
    byte receiveMessage();                                                    // receiving messages, and returning the id of the message or -1 if its incorrect message

  private:
    class Message
    {
      public:
        Message();                                                     // empty constructor
        Message(Vector<String> *_startSymbols, Vector<String> *_data); // full argument constructor
        byte id;                                                       // id for the message
        Vector<String> *mStartSymbols;                                 // vector for the start symbols for each data
        Vector<String> *mData;                                         // the data for the message
    };
    byte readData(String text, byte id); // setting the data to their vector
    void setMessageInfo(byte id);        // setting the vectsors for the active message
    Stream *serial;
    const char START_CHAR = '?';
    const char END_CHAR = ';';
    const char MID_CHAR = '&';
    const static byte MAX_SIZE = 10;
    Message storage_arr[MAX_SIZE]; // storage array for messageList
    Vector<Message> messageList;   // list to hold all the messages
    byte prevID = -1;              // var to check whether the message changed or not
    byte count;
    Vector<String> *startSymbols;
    Vector<String> *data;
};

#endif
