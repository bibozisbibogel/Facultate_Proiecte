/*
    Proiect Pacanea
    Autor: Stoian Cristian Georgian
*/
#include <bits/stdc++.h>
using namespace std;
void pacanea()
{
    int contor=0;
    srand(time(NULL));
    int result=rand()%100;
    int try_;
    cout<<"insert a number between 0-99"<<'\n';
    while(true)
    {
        cin>>try_;
        contor++;
        while(try_<0 || try_>=99){
            cout<<"esti pe langa, mai baga o fisa"<<'\n';
            cin>>try_;
        }
        if(try_==result){
            cout<<"felicitari, ai castigat din "<<contor<<" incercari"<<'\n';
            break;
        }
        if(abs(result-try_)<5)
            cout<<"fierbinte"<<'\n';
        else
            if(abs(result-try_)<10)
                cout<<"caldut"<<'\n';
            else
                if(abs(result-try_)<20)
                    cout<<"esti pe drumul cel bun"<<'\n';
        if(abs(result-try_)>=20)
            cout<<"rece, frate"<<'\n';
    }
}
int main (){
    pacanea();
    return 0;
}

