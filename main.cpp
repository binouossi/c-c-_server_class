#include <stdio.h>
#include <iostream>
#include <server.h>

using namespace std;

void A(server lo){
    for(int i=0;i<25;i++)
    {
        char* hi=lo.lire();
        cout<<hi<<endl;
        lo.stringsender("oui! Bonjour toi. Comment va tu?");
        printf("bonjour\n");
        lo.send_int(5);
        int gi=NULL;
        lo.receive_int(&gi);
//        lo.receive_int(gi);
        cout<<gi<<endl;
        cout<<"Fin"<<endl;
    }

    exit(0);
}

int main()
{
    new server(A);
    return 0;
}
