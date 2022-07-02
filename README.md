# BLUETOOTH MODULE LIBRARY

A simple library to handle sending/receiving messages using hardware Serial on Arduino

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

-The format for the messages is **?xy&xy;** x for start symbols, y for data (_to change the const characters check and modify BTM.h_)

-The symbols/data can be in any length

-You can use any number of data

-Create Message for each collection of data youre sending/receiving(_this class takes only vectors_):

```
  //Message constructor, Params: a Vector for start Symbols in your message, A vector for your data
  Message message = btm.createMessage(&startSymbols1, &data);
```

-Start symbols can be shared across messages(_they are read-only vectors_)

-Data arrays have to be unique for each message

-all data are string you can convert them to any type using(_.toInt()/.toFloat()/..._)

-You can check a simple **example** for receiving coordinates(x,y) and sending their signs in _Example.ino_ file

## BTM Methods

| Method             | Params                             | Return  | Description                                                                                          |
| ------------------ | ---------------------------------- | ------- | ---------------------------------------------------------------------------------------------------- |
| **createMessage**  | Vector\<String\>, Vector\<String\> | Message | dont use message constructor, use this instead                                                       |
| **receiveMessage** | Message                            | bool    | return correct if it recieve a full correct message using the start symbols given in the **message** |
| **sendMessage**    | Message                            | void    | send the data in the correct format using the start symbols/data given in the **message**            |

## THANK YOU!

Hope this simple library help you :)

Made by: _@rem2718_

For any suggestions/comments/questions email me at: rem.e2.718@gmail.com
