#include <iostream>
#include <string>
#include <math.h>

using namespace std;



string * OddajTablice(string tablica, char kropka){

    static string r[4];
    for(int i=0;i<4;i++){
        r[i]="";
    }

    int licznik=0;

    for(int i=0; i<tablica.length(); i++){
        if(licznik>=4){
            r[0]="256";
            break;
        }
        if(tablica[i]!=kropka){
            r[licznik]+=tablica[i];
        }
        else{
            licznik++;
        }

    }

    return r;

}

bool CzyDaneZgodne(string *p){

    int x=0;
    for(int i=0;i<4;i++){
        x=stoi(*(p+i));
        if(x<0||x>255){
            return false;
        }
    }

    return true;

}

bool CzyMaskaZgodna(string mazga){
    for(int i=0;i<mazga.length();i++){
        if(mazga[i]=='0'&&mazga[i+1]=='1'){
            return false;
        }
    }

    return true;

}



string StringToBin(string p){

        string wynik="00000000";
        int x=stoi(p);
        int licznik=7;
        while(true){

            if(licznik==-1&&(x==0||x==1)){
                break;
            }
            if(x%2==1){
                wynik[licznik]='1';
            }
            else{
                wynik[licznik]='0';
            }

            x=x/2;
            licznik--;




        }

    return wynik;

}

string AdresSieciowy(string ajpi[], string mazga[]){

    string wynik="00000000.00000000.00000000.00000000";
    int licznik=0;



    for(int i=0;i<4;i++){
        string x=StringToBin(ajpi[i]);
        string y=StringToBin(mazga[i]);
        for(int j=0;j<8;j++){
            if(y[j]=='1'&&x[j]=='1'){
                wynik[licznik]='1';
            }
            else{
                wynik[licznik]='0';
            }
            licznik++;
        }
        wynik[licznik]='.';
        licznik++;


    }
    return wynik;
}

string AdresRozgl(string ajpi[], string mazga[]){

    string wynik="00000000.00000000.00000000.00000000";
    int licznik=0;



    for(int i=0;i<4;i++){
        string x=StringToBin(ajpi[i]);
        string y=StringToBin(mazga[i]);
        for(int j=0;j<8;j++){
            if(y[j]=='1'){
                wynik[licznik]=x[j];
            }
            else{
                wynik[licznik]='1';
            }
            licznik++;
        }
        wynik[licznik]='.';
        licznik++;


    }
    return wynik;
}

string Klasa(string ajpi[]){
    string x=StringToBin(ajpi[0]);
    if(x[0]!='1'){
        return "Klasa A";
    }
    else if(x[1]!='1'){
        return "Klasa B";
    }
    else if(x[2]!='1'){
        return "Klasa C";
    }
    else if(x[3]!='1'){
        return "Klasa D";
    }
    else{
        return "Klasa E";
    }

    return "Error?";
}

int IloscPodsieciDlaKlasowej(string ajpi, string klasa){
    string mazga="";
    if(klasa=="Klasa A"){
        mazga="11111111000000000000000000000000";
    }
    else if(klasa=="Klasa B"){
        mazga="11111111111111110000000000000000";
    }
    else if(klasa=="Klasa C"){
        mazga="11111111111111111111111100000000";
    }
    else if(klasa=="Klasa D"||klasa=="Klasa E"){
        return 0;
    }
    int licznikMasek=0;
    int licznikIpa=0;
    for(int i=0;i<mazga.length();i++){
        if(mazga[i]=='1'){
            licznikMasek++;
        }
        if(ajpi[i]=='1'){
            licznikIpa++;
        }
    }
    int x=licznikIpa-licznikMasek;
    int y=pow(2,x);
    return y;
    

}

int Hostow(string mazga){

    int licznikMasek=0;
     for(int i=0;i<mazga.length();i++){
        if(mazga[i]=='0'){
            licznikMasek++;
        }
    }

    return pow(2,licznikMasek)-2;

}




int main(){

    string ip ="";
    string maska="";
    string ajpi[4];
    string mazga[4];
    string ipBin="";
    string MaskBin="";

    cout<<"Podaj IP:"<<endl;
    cin>>ip;
    string *ipek=OddajTablice(ip,'.');
    if(CzyDaneZgodne(ipek)){
        cout<<"IP zgodne"<<endl;
        for(int i=0;i<4;i++){
            ajpi[i]=*(ipek+i);
        }
        ipBin=StringToBin(ajpi[0])+StringToBin(ajpi[1])+StringToBin(ajpi[2])+StringToBin(ajpi[3]);
        cout<<"IP w formie binarnej: "<<ipBin<<endl;
    }
    else{
        cout<<"Zle IP"<<endl;
        return 0;
    }

    cout<<"Podaj maske:"<<endl;
    cin>>maska;
    string *masek=OddajTablice(maska,'.');
    if(CzyDaneZgodne(masek)){
        for(int i=0;i<4;i++){
            mazga[i]=*(masek+i);
        }
        MaskBin=StringToBin(mazga[0])+StringToBin(mazga[1])+StringToBin(mazga[2])+StringToBin(mazga[3]);
        if(CzyMaskaZgodna(MaskBin)){
            cout<<"Maska zgodna"<<endl;
             cout<<"Maska w formie binarnej: "<<MaskBin<<endl;
        }
        else{
        cout<<"Zla Maska"<<endl;
        return 0;
        }
       
    }
    else{
        cout<<"Zla Maska"<<endl;
        return 0;
    }


     cout<<"Adres Sieciowy: "<<AdresSieciowy(ajpi,mazga)<<endl;
     cout<<"Adres Rozgloszeniowy: "<<AdresRozgl(ajpi,mazga)<<endl;
     cout<<"Klasa adresu IP: "<<Klasa(ajpi)<<endl;
     cout<<"Ilosc podsieci adresu IP dla maski klasowej: "<<IloscPodsieciDlaKlasowej(MaskBin,Klasa(ajpi))<<endl;
     cout<<"Ilosc hostow: "<<Hostow(MaskBin)<<endl;
     






    return 0;
}
