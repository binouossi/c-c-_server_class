#include "server.h"

server::server()
{
    int listenfd = 0,sock = 0;
    struct sockaddr_in serv_addr;
    char sendBuff[1025];
   //      int numrv;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);// creation de la socket serveur
    printf("socket retrieve success\n");

    memset(&serv_addr, '0', sizeof(serv_addr));

    memset(sendBuff, '0', sizeof(sendBuff));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000);

    bind(listenfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr));// on attache la socket a l'address du serveur

    if(listen(listenfd, 10) == -1)
    {// starting listen
        printf("Failed to listen\n");
    }

    while(1)
    {
        this->sock = accept(listenfd, (struct sockaddr*)NULL ,NULL); // accept awaiting request

        this->communicator();
        close(this->sock);
        sleep(1);
    }
}

void server::communicator()
{
    this->stringsender("Message from server client");

    this->lire();

    char username[strlen(this->lu)];

    strcpy(username,this->lu);

    std::cout<<username<<std::strlen(username)<<std::endl;

    std::cout<<"debut"<<std::endl;

    this->lire();
   /*  int f=0,g=0;

   this->receive_int(&f);
   this->receive_int(&g);

    std::cout<<f<<std::endl;
    std::cout<<g<<std::endl;*/

    char img[strlen(this->lu)];

    std::strcpy(img,this->lu);

    std::cout<<img<<std::strlen(img)<<std::endl;

    std::cout<<"fin"<<std::endl;



/*
    char name[1024];
//    this->lire(name,1024);
/*std::cout<<name<<std::endl;

char* gi=name;

//this->viderBuffer();

//std::cout<<gi<<std::endl;




//    uid_t id=this->get_id(name);

    char img[1024];
    this->lire(img,1024);
  //  this->viderBuffer();
    //printf("%d",strlen(img));


//    IplImage img=this->IplImageRecv();
 /*   int val=this->analyse(id,&img);
    this->sender(val);*/

 //   free(lui);
}



int server::stringsender(char fi[])
{
    int a=strlen(fi);

    this->send_int(a);

    int n=write(this->sock,fi,std::strlen(fi));

    if(n<0)
        std::cout<<"error while sending"<<std::endl;
    return n;
}

int server::analyse(uid_t uid, IplImage* im)
{
/*    verifier* verif= new verifier(uid);
   // IplImage im = this->IplImagerecv();
    int val=verif->verifyFace(im);
    return val;*/
}


IplImage server::IplImageRecv()
{
    cv::Mat  img = cv::Mat::zeros(IMAGE_WIDTH,IMAGE_HEIGHT, CV_8UC3);
    int  imgSize = img.total()*img.elemSize();
    uchar sockData[imgSize];

     //Receive data here
       int bytes;

       for (int i = 0; i < imgSize; i += bytes) {
       if ((bytes = recv(this->sock, sockData +i, imgSize  - i, 0)) == -1) {
      //   quit("recv failed", 1);
        }
       }

     // Assign pixel value to img

     int ptr=0;
     for (int i = 0;  i < img.rows; i++) {
      for (int j = 0; j < img.cols; j++) {
       img.at<cv::Vec3b>(i,j) = cv::Vec3b(sockData[ptr+ 0],sockData[ptr+1],sockData[ptr+2]);
       ptr=ptr+3;
       }
      }
     IplImage im= img;


     cvNamedWindow("Window", CV_WINDOW_AUTOSIZE);

             cvNamedWindow("Window", CV_WINDOW_AUTOSIZE);
            // cvShowImage("Window",im);
             cvWaitKey(520);


     return im;

/*

    QByteArray Data = sock->readAll();

      /* CvSize size;
       size.height = 480;
       size.width = 640;
       IplImage *frame = cvCreateImageHeader(size, IPL_DEPTH_8U, 3);*/


   //    frame->imageData = Data.data();

}
/*
void seveur::sender(/*auto msg*//*)
{
    char* msg="je m'en vers";
    write(this->sock, msg, strlen(msg));
}*/

uid_t server::get_id(char* user)
{/*
    struct passwd *userStruct;
    userStruct = getpwnam(user);
    uid_t userID=userStruct->pw_uid;
    return userID;*/
}

void server::viderBuffer() {
    int c = 0;
    while (c != '\n' && c != EOF)
        {
                c = getchar();
         }
 }


void server::lire()
{
    int n = 0;

    this->receive_int(&n);

//    std::cout<<n<<std::endl;

    char recvBuff[n+1];

    memset(recvBuff, 0 ,sizeof(recvBuff));

    this->lu=(char*)std::realloc(this->lu,(n*sizeof(char))+1);

    if(this->lu==NULL)
    {
        std::cout<<"Allocation error"<<std::endl;
        return;
    }


    int a=0;
    recvBuff[0]='\0';
    this->lu[0]='\0';
    /*while((n= read(this->sock, recvBuff, sizeof(recvBuff)-1)) > 0) {
            recvBuff[n]='\0';    // explicit null termination: updated based on comments
            std::strcat(this->lu,recvBuff) ;
            recvBuff[0]='\0';        // clear the buffer : I am 99% sure this is not needed now
    a=a+n;
    }*/

   // recvBuff[a]='\0';
this->readLine(this->lu,n);
      if( n < 0)
      {
        printf("\n Read Error \n");
      }

   //  return recvBuff;

}



char* server::charReader()
{
    char* recv;
    return recv;
}

/*IplImage server::MatToIplImage(/*Mate img)
{

}
*/


int server::send_int(int num)
{
    int32_t conv = htonl(num);
    char *data = (char*)&conv;
    int left = sizeof(conv);
    int rc;
    do {
        rc = write(this->sock, data, left);
        if (rc < 0) {
            if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
                // use select() or epoll() to wait for the socket to be writable again
            }
            else if (errno != EINTR) {
                return -1;
            }
        }
        else {
            data += rc;
            left -= rc;
        }
    }
    while (left > 0);
    return 0;
}



int server::receive_int(int *num)
{
    int32_t ret;
    char *data = (char*)&ret;
    int left = sizeof(ret);
    int rc;
    do {
        rc = read(this->sock, data, left);
   //     std::cout<<"sent"<<std::endl;

        if (ret <= 0) {
            if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
                // use select() or epoll() to wait for the socket to be readable again
            }
            else if (errno != EINTR) {
                return -1;
            }
        }
        else {
            data += rc;
            left -= rc;
        }
    }
    while (left > 0);
    *num = ntohl(ret);
    return 0;
}




int server::readLine(char data[],int maxlen)
{
   size_t len = 0;
   while (len < maxlen)
   {
      char c;
      int ret = read(this->sock, &c, 1);
      if (ret < 0)
      {
          data[len] = 0;
          return len; // EOF reached
      }
      if (c == '\n')
      {
          data[len] = 0;
          return len; // EOF reached
      }
      data[len++] = c;
   }
}

