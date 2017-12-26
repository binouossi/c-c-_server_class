#include "server.h"

int sigflag;

int resquiescat(){wait(NULL);sigflag = 1;}

server::server(void (communicator)(server))
{
    int listenfd = 0;

      struct sockaddr_in serv_addr;

      sigset(SIGCHLD, (sighandler_t)resquiescat);

      listenfd = socket(AF_INET, SOCK_STREAM, 0);// creation de la socket serveur
      printf("socket retrieve success\n");

      serv_addr.sin_family = AF_INET;
      serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
      serv_addr.sin_port = htons(PORT);

      if(bind(listenfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr))<0)
      {// on attache la socket a l'address du serveur
          perror("Face_server bind fail");
          exit(1);
      }

      if(listen(listenfd, 10) == -1)
      {// starting listen
          perror("Failed to listen\n");
          exit(1);
      }

      while(1)
        {
          sigflag = 0;
          int childpid;
          // accept awaiting request
          if(this->sock = accept(listenfd, (struct sockaddr*)NULL ,NULL)<0)
          {
              if(sigflag == 1)continue;
              perror("accept error in Face_serverd");
              exit(1);
          }

          if((childpid = fork()) < 0)
          {
              perror("fork error in Face_serveurd");
              exit(1);
          }
          else if (childpid == 0)
          {
              close(listenfd);
            (*communicator)(*this);
          }

          close(this->sock);
       }
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

IplImage* server::IplImageRecv()
{
    int H=NULL,W=NULL;
    this->receive_int(&H);
    this->receive_int(&W);


//    std::cout<<H<<" et "<<H<<std::endl;


    if(W==0||W==NULL)
        W=IMAGE_WIDTH;

    if(H==0||H==NULL)
      H=IMAGE_HEIGHT;

    cv::Mat  img = cv::Mat::zeros(H,W, CV_8UC3);

       int  imgSize = img.total()*img.elemSize();
       uchar sockData[imgSize];

      //Receive data here
       int bytes=0;

       for (int i = 0; i < imgSize; i = i + bytes) {
       if ((bytes = recv(this->sock, sockData +i, imgSize  - i, 0)) == -1)
       {
           perror("Image reception failed");
           return NULL;
        }
       }

     int ptr=0;
     for (int i = 0;  i < img.rows; i++)
     {
      for (int j = 0; j < img.cols; j++)
      {
       img.at<cv::Vec3b>(i,j) = cv::Vec3b(sockData[ptr+ 0],sockData[ptr+1],sockData[ptr+2]);
       ptr=ptr+3;
      }
     }

     IplImage* im= cvCreateImage(cvSize(img.cols, img.rows), 8, 3);

     IplImage tmp=img;

     cvCopy(&tmp,im);

     return im;
}

int server::IplImagesender(IplImage* im)
{
    this->send_int(im->height);

    this->send_int(im->width);

    int bytes=0;
    cv::Mat frame=cv::Mat(im,true);
    frame = (frame.reshape(0,1)); // to make it continuous

    int  imgSize = frame.total()*frame.elemSize();

    // Send data here
    bytes = send(this->sock, frame.data, imgSize, 0);

    return bytes;
}

char* server::lire()
{

    int n = NULL;
    this->receive_int(&n);

    if(n==0||n==NULL)
    {
        return NULL;
    }

//    std::cout<<n<<std::endl;

    this->lu=(char*)std::realloc(this->lu,(n*sizeof(char)));

    if(this->lu==NULL)
    {
        std::cout<<"Allocation error"<<std::endl;
        return NULL;
    }

    this->lu[0]='\0';

    int a=this->readLine(this->lu,n);

      if( a < n-1)
      {
        cout<<"Read Error"<<endl;
        return NULL;
      }

      this->lu[n]='\0';
      return this->lu;
}

int server::send_int(int num)
{
    char buf[10] = "";

    sprintf( buf , "%d" , num );

    send( this->sock , buf , sizeof buf , 0 );

    return 0;
}

int server::receive_int(int *num)
{
    char buf[10] = "";

    recv( sock , buf , sizeof buf , 0 );

    sscanf( buf , "%d" , num );


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
