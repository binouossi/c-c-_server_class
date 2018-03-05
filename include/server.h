#ifndef SERVER_H
#define SERVER_H

//a supprimer pour eviter les redefinition

#define ADDR
#define OUTPUT stderr
#define PORT 5000

// labrary
#include <unistd.h>
#include <string.h>
#include <sstream>
#include <fstream>
#include <unistd.h>
#include <arpa/inet.h>
#include <wait.h>

using namespace std;

class server
{
public:
    server(void (*communicator)(server));

    char* getall();

    int file_sender(char* path);

    bool file_reader(char* destination);

    template <typename Type>
    stringstream& operator>> (Type& don);

    template <typename Type>
    bool operator<<(Type &data);

protected:


    char* str_reader();

    char* str_reader(int size);

    int int_reader(int *num);

    int int_sender(int num);

    int str_sender(char *fi);

    int str_sender(char* fi, int size);




        const struct sockaddr_in* addr;
        int sock;

};



template <typename Type>
stringstream& server::operator>> (Type& don)
{
    int size=NULL;

    stringstream nin;

    nin.flush();

    this->int_reader(&size);

    char* data= this->str_reader(size);

    nin<<data;

    nin>>don;

    return nin;
}

template <typename Type>
bool server::operator<<(Type &data)
{
    stringstream nout;

    nout<<data;

    char* buf=const_cast<char*>(nout.str().c_str());

    int size=strlen(buf);

    if(this->str_sender(buf,size)<0)
    {
        return false;
    }

    return true;
}



#endif  SERVER_H
