#include "BTM.h"

BTM::Message::Message() // empty constructor
{
}
BTM::Message::Message(Vector<String> *_startSymbols, Vector<String> *_data) // full argument constructer
{
  mData = _data;
  mStartSymbols = _startSymbols;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
BTM::BTM() // empty constructor
{
}
BTM::BTM(HardwareSerial *_serial) // full argument constructor
{
  serial = _serial;
}

BTM::Message BTM::createMessage(Vector<String> *_startSymbols, Vector<String> *_data)
{
  BTM::Message message(_startSymbols, _data);
  return message;
}

void BTM::sendMessage(BTM::Message message)
{
  setMessageInfo(message);
  String messageBuffer = "";
  messageBuffer += START_CHAR;
  for (int i = 0; i < (*data).size(); i++)
  {
    char lastChar = (i != (*data).size() - 1) ? MID_CHAR : END_CHAR; // lastChar is always MID_CHAR except for the last data
    messageBuffer += (*startSymbols)[i] + (*data)[i] + lastChar;
  }
  serial->println(messageBuffer);
}

void BTM::setMessageInfo(BTM::Message message)
{
  if (&message != prevMessage) // it wont set it if its the same as the previous
  {
    prevMessage = &message;
    startSymbols = message.mStartSymbols;
    data = message.mData;
  }
}
bool BTM::receiveMessage(BTM::Message message)
{
  setMessageInfo(message);
  char nextChar;
  String messageBuffer = "";
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
        messageBuffer += nextChar;
      }
    } while (nextChar != END_CHAR); // read till the end of the message
    if (messageBuffer.length() > 1) // if its not only END_CHAR
    {
      setMessageInfo(message);
      messageBuffer = messageBuffer.substring(0, messageBuffer.length() - 1); // cutting the END_CHAR off
      return readData(messageBuffer);
    }
  }
  return false;
}

bool BTM::readData(String text)
{
  int index1 = 0;
  int index2 = 0;
  int i = 0;
  bool correct = true; // condition to keep track of all the data if they are set correctly or not
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
      correct = false;
    }
    i++;
  }
  return correct;
}
