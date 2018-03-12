# c/c++ socket server class

## Author
**NAME: _TACOLODJOU Emmanuel_**
**Email: _tacolodjounini@gmail.com_**

## Presentation

This is the server part of a c/c++ library, which makes it easier to use the socket connection. It contains a **class** to initiate communication and methods and operator to send and receive data, over the network


## Usage
This class named **server** and there methods are as follows:

* ### server(\*A())
It create the socket, bind it, and listeen to request from client. It waiting for _any_ address to connect. And the listen port are set up on prtprocessing's **PORT** defined variable. It take as parameter, a fontion that, each forcked process by the server will execute as the rotine. That _routine_ function have to receve a server object as parameters. The routine must return a **void**, and can take other parameters, than the server objet. In that case, you have to modifie it call in the constructor. But, generaly, you don't need to pass other parameters, because, you can initiate the variable in routine function. You'll have an esxample of it utilization in the main file. In the future version you have more feature to handle a complex server management.

## Public methods


* ## bool file_reader(char* destination)
As its name implies, it allows you to receive the contents of a file, from socket, and write it to a file whose name has been passed with the destination parameter. If the file does not exist, it is created. the function returns a boolean. 

* ## int file_sender(char *fi)
As the name suggests, it allows you to send the contents of a file, through the socket. It takes in parameter the path of the file. It returns -2 if the file does not exist and -1 if the send fails. 0 is returned if all goes well.

* ## char* getall()
This method allows you to receive a string from the network. It returns the string received as char * if all is well, and NULL on error.

### Operators

* ## bool operator<<(Type &data)

This operator is similar to the standard output stream operator. It allows you to send primary data types on the network. you could watch it as a network output stream. It only handles the main type, and strings like char *

* ## stringstream& operator>>(Type &data);
This operator is similar to the standard input stream operator. It allows you to receive data from the network. It only handles the primary types and can not receive a string like char *. To obtain strings from the network, you must use the **getall()** function.

## Version (1.00)
This is the beta version

# Licence

This library, is offert as **LGPL Licence**. Than, it's free usefull and shareless. You can sell a software maked with the library.

## Invitation

I invite everyone, to help me, in the development of this class, by sending feedback, and by proposing better algorithms.