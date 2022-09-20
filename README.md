# BLUETOOTH MODULE LIBRARY

A simple library to handle sending/receiving messages using hardware/software Serial on Arduino

## INSTALL THE LIBRARY

1.Download BTM.zip file

2.In Arduino IDE go to _Sketch>Include library>Add .ZIP Library_

3.Locate BTM.zip and click on it

## IMPORT THE LIBRARY

-Just write at the begining of your code:

```
#include <BTM.h>
```

## NOTES:

-Create BTM for each serial you will use:

```
  //BTM constructor, Param: the serial youre using
  BTM btm(&Serial)
```

-The format for the messages is **?id=i&xy&xy;** i for id, x for start symbols and, y for data (_to change the const characters check and modify BTM.h_)

-The symbols/data can be in any length

-You can use any number of data

-Create Message for each collection of data youre sending/receiving(_this class takes only vectors_):

```
  //Message constructor, Params: a Vector for start Symbols in your message, A vector for your data
  byte message = btm.createMessage(&startSymbols1, &data);
```

-The max number for messages is 10(_you might change it(MAX_SIZE) in BTM.h_)

-The IDs of the messages depends on the order of messages creation(_first messge created: 0, second: 1 third: 2...and so on_)

-Start symbols can be shared across messages(_they are read-only vectors_)

-Data arrays have to be unique for each message

-all data are string you can convert them to any type using(_.toInt()/.toFloat()/..._)

-You can check a simple **example** for receiving coordinates(x,y) and sending their signs in _simpleExample.ino_ file, and another one for receiveing two different messages in _twoMessagesExample.ino_ file.

## BTM Methods

| Method             | Params                                                    | Return              | Description                                                                                                                   |
| ------------------ | --------------------------------------------------------- | ------------------- | ----------------------------------------------------------------------------------------------------------------------------- |
| **createMessage**  | start symbols (Vector\<String\>), data (Vector\<String\>) | message's id (byte) | dont use message constructor, use this instead                                                                                |
| **receiveMessage** | none                                                      | message's id (byte) | return the message's id if it recieve a full correct message using the start symbols given in the **message** or -1 otherwise |
| **sendMessage**    | message's id (byte)                                       | void                | send the data in the correct format using the start symbols/data given in the **message**                                     |

## THANK YOU!

Hope this simple library help you :)

Made by: _@rem2718_

For any suggestions/comments/questions email me at: rem.e2.718@gmail.com
