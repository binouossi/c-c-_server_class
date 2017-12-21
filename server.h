#ifndef SERVER_H
#define SERVER_H

//a supprimer pour eviter les redefinition
#define IMAGE_SIZE 230400
#define IMAGE_WIDTH 320
#define IMAGE_HEIGHT 240
#define PORT 5000

// labrary

#include <unistd.h>
#include <arpa/inet.h>
#include <wait.h>

#include <opencv/cv.h>
#include <opencv/highgui.h>



class server
{
public:
    server(/*void (*communicator)(int)*/);
    void communicator();
//    IplImage MatToIplImage(/*Mat im*/);
    void lire();
    void envoie(std::string msg);



private:
        const struct sockaddr_in* addr;
        int sock;
  //      void sender(/*auto*/);
        char* charReader();
        IplImage *IplImageRecv();
        int analyse(uid_t id, IplImage* im);
        uid_t get_id(char* user);
       /* char sendBuff[1025];
        char recvBuff[1024];*/
        void viderBuffer();
        int receive_int(int *num);
        int send_int(int num);
        int stringsender(char[]);
        char* lu=NULL;

        int readLine(char data[],int maxlen);

/*



        QTcpServer *serveur;
        QList<QTcpSocket *> clients;
        quint16 tailleMessage;
        std::string etat;

*/

};

//#endif  SEVEUR_H


/*

class server
{
public:
    server();
};
*/
#endif  SERVER_H
