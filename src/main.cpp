#include <stdio.h>
#include <iostream>
#include <../include/server.h>

using namespace std;

void A(server lo){

    char* msg=lo.getall();

    cout<<msg<<endl;

    msg="Oui! Moi aussi.";

    lo<<msg;

    double hi;

    lo>>hi;

    cout<<hi<<endl;

    hi=9.6548;

    lo<<hi;

    cout<<hi<<endl;

    lo.file_sender("/home/cani/cdadd");
    lo.file_reader("/home/cani/test02");

    printf("fin\n");

    exit(0);
}

int main()
{
    new server(A);
    return 0;
}
