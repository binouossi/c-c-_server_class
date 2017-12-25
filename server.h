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

using namespace std;

class server
{
public:
    server(void (*communicator)(server));
    char* lire();
    int receive_int(int *num);
    int send_int(int num);
    int stringsender(char[]);
    IplImage *IplImageRecv();
    int IplImagesender(IplImage* im);


private:
        const struct sockaddr_in* addr;
        int sock;
  //      void sender(/*auto*/);
        int analyse(uid_t id, IplImage* im);
        uid_t get_id(char* user);
        void viderBuffer();

        char* lu=NULL;
        int readLine(char data[],int maxlen);


};

#endif  SERVER_H
