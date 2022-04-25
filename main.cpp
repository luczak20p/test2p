#include <iostream>
#include <string>

using namespace std;



string * OddajTablice(string tablica, char kropka){

    static string r[4];
    for(int i=0;i<4;i++){
        r[i]="";
    }

    int licznik=0;

    for(int i=0; i<tablica.length(); i++){
        if(licznik>=4){
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



int main(){

    string ip ="";
    string maska="";
    string ajpi[4];
    string mazga[4];

    cout<<"Podaj IP:"<<endl;
    cin>>ip;
    string *ipek=OddajTablice(ip,'.');
    if(CzyDaneZgodne(ipek)){
        cout<<"IP zgodne"<<endl;
        for(int i=0;i<4;i++){
            ajpi[i]=*(ipek+i);
        }
    }
    else{
        cout<<"Zle IP"<<endl;
        return 0;
    }

    cout<<"Podaj maske:"<<endl;
    cin>>maska;
    string *masek=OddajTablice(maska,'.');
    if(CzyDaneZgodne(masek)){
        cout<<"Maska zgodna"<<endl;
        for(int i=0;i<4;i++){
            mazga[i]=*(masek+i);
        }
    }
    else{
        cout<<"Zla Maska"<<endl;
        return 0;
    }

     cout<<StringToBin(ajpi[0])<<endl;

     cout<<"Adres Sieciowy: "<<AdresSieciowy(ajpi,mazga)<<endl;
     cout<<"Adres Rozgloszeniowy: "<<AdresRozgl(ajpi,mazga)<<endl;
     //nie zrobilem liczenia hostów
     cout<<"Klasa adresu IP: "<<Klasa(ajpi)<<endl;







    return 0;
}
