#ifndef SERVER_H
#define SERVER_H


#define IMAGE_SIZE 230400
#define IMAGE_WIDTH 320
#define IMAGE_HEIGHT 240



#include <sys/socket.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>

//#include <security/pam_modules.h>
//#include <security/_pam_macros.h>
//#include <security/_pam_types.h>


#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

//#include <QtNetwork>
//#include <QObject>

#include <unistd.h>
#include <errno.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <time.h>
#include <assert.h>
#include <ctype.h>
//#include <QString>

//#include <QWidget>
//#include <QByteArray>



//#include <pwd.h> /* getpwdid */
#include <opencv/cv.h>
#include <opencv/highgui.h>

//#include     <X11/Xlib.h>
//#include     <X11/Xutil.h>

//#define DEFAULT_USER "nobody"
//#define PAM_SM_AUTH
//#define PAM_SM_ACCOUNT
//#define PAM_SM_SESSION
//#define PAM_SM_PASSWORD

/*
#include "pam_face_authentication.h"
#include "pam_face_defines.h"
#include "webcamImagePaint.h"
#include "opencvWebcam.h"
#include "detector.h"
#include "verifier.h"
*/



class server//: public QObject
{
//    Q_OBJECT

public:
    server();
    void communicator();
//    IplImage MatToIplImage(/*Mat im*/);
    void lire();
    void envoie(std::string msg);


/*private slots:
    void newconnexion();
    void datarecv();
    void endClient();
*/

private:
        const struct sockaddr_in* addr;
        int sock;
  //      void sender(/*auto*/);
        char* charReader();
        IplImage IplImageRecv();
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
