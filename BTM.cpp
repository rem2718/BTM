#include "BTM.h"

// empty constructor
BTM::Message::Message()
{
}
// full argument constructer
BTM::Message::Message(Vector<String> *_startSymbols, Vector<String> *_data)
{
  mData = _data;
  mStartSymbols = _startSymbols;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

// empty constructor
BTM::BTM()
{
}
// full argument constructor
BTM::BTM(HardwareSerial *_serial)
{
  serial = _serial;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

// creating messages, and returning the id of the message
byte BTM::createMessage(Vector<String> *_startSymbols, Vector<String> *_data)
{
  if (messageList.empty()) // it sets once at the begining
    messageList.setStorage(storage_arr);
  BTM::Message message(_startSymbols, _data); // creating a new message
  message.id = count;                         // setting its id
  messageList.push_back(message);             // adding it to messageList
  return count++;
}

// setting the attributes of the active message
void BTM::setMessageInfo(byte id)
{
  if (id != prevID) // it wont set a message if its the same as the previous
  {
    prevID = id;
    startSymbols = messageList[id].mStartSymbols;
    data = messageList[id].mData;
  }
}
// sending messages using its id
void BTM::sendMessage(byte id)
{
  setMessageInfo(id); // setting the new message
  String messageBuffer = (String)START_CHAR + "id=" + (String)id + (String)MID_CHAR;
  for (int i = 0; i < (*data).size(); i++)
  {
    char lastChar = (i != (*data).size() - 1) ? MID_CHAR : END_CHAR; // lastChar is always MID_CHAR except for the last data
    messageBuffer += (*startSymbols)[i] + (*data)[i] + lastChar;
  }
  serial->println(messageBuffer);
}

// receiving messages, and returning the id of the message or -1 if its incorrect message
byte BTM::receiveMessage()
{
  char nextChar;
  String messageBuffer = "";
  int i1;
  int i2;
  if (serial->available())
  { // if receives any char
    do
    {
      nextChar = serial->read();
    } while (nextChar != START_CHAR);
    do
    {
      if (serial->available())
      {
        nextChar = serial->read();
        messageBuffer += (String)nextChar;
      }
    } while (nextChar != END_CHAR);                                    // read till the end of the message
    if (messageBuffer.length() > 1 && messageBuffer.startsWith("id=")) // if its not only END_CHAR or didnt start with the id
    {
      i1 = 3;
      i2 = messageBuffer.indexOf(MID_CHAR).toInt();
      byte id = (byte)(messageBuffer.substring(i1, i2));
      if (id < messageList.size()) // if id is not out of range
      {
        i1 = messageBuffer.indexOf(MID_CHAR) + 1;
        i2 = messageBuffer.length() - 1;
        messageBuffer = messageBuffer.substring(i1, i2); // cutting the END_CHAR and the id part off
        return readData(messageBuffer, id);
      }
    }
  }
  return -1;
}

// setting the data to their vector
byte BTM::readData(String text, byte id)
{
  int index1 = 0;
  int index2 = 0;
  int i = 0;
  byte correctID = id; // for return statement
  setMessageInfo(id);
  for (String elem : *startSymbols)
  {
    if (text.startsWith(elem))
    {
      index1 = elem.length();
      index2 = (i != (*startSymbols).max_size() - 1) ? text.indexOf(MID_CHAR) : -1;
      (*data)[i] = (text.substring(index1, index2));
      text = text.substring(index2 + 1);
    }
    else
    {
      correctID = -1; // incorrect message
    }
    ++i;
  }
  return correctID;
}