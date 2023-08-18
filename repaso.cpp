//Repaso

#include<iostream>
#include<fstream>
using namespace std;

class Paquete{
public:
    int id;
    string origen;
    string destino;
    int peso;
    Paquete *sig;
    Paquete(int, string, string, int, Paquete *);
};

Paquete::Paquete(int _id, string _origen, string _destino, int _peso, Paquete *ptr){
    this ->id =_id;
    this ->origen =_origen;
    this ->destino =_destino;
    this ->peso =_peso;
    this ->sig =ptr;
}

class Paqueteria{
private:
    Paquete *top;
public:
    Paqueteria();
    bool vacia();
    void agregar();
    void eliminar();
    void mostrar();
    void guardar(ofstream &);
    //guardar en orden?
    void recorrer(ofstream &, Paquete *);
    void recuperar(ifstream &);
};

Paqueteria::Paqueteria(){
    this ->top =nullptr;
}

bool Paqueteria::vacia(){
    return top ==nullptr;
}
void Paqueteria::agregar(){
    int id;
    string origen;
    string destino;
    int peso;
    cout <<"\nInserte los siguientes datos del paquete:\nId:\t ";
    cin >>id;
    cin.clear();
    cin.ignore();
    cout <<"Origen:\t ";
    getline(cin, origen);
    cout <<"Destino: ";
    getline(cin, destino);
    cout <<"Peso:\t ";
    cin >>peso;
    cin.clear();
    cin.ignore();
    if((id ==0) ||(origen =="") ||(destino =="") ||(peso ==0)){
        cout <<"\nCampos invalidos...\n\n";
        return;
    }
    Paquete *npaquete =new Paquete(id, origen, destino, peso, top);
    top =npaquete;
    cout <<"\nPaquete agregado...\n\n";
}

void Paqueteria::eliminar(){
    Paquete *aux =top;
    top =top ->sig;
    delete aux;
}

void Paqueteria::mostrar(){
    if(!vacia()){
        Paquete *aux =top;
        cout <<"\nPaquete(s):";
        while(aux){
            cout <<"\n\nId:\t " <<aux ->id;
            cout <<"\nOrigen:\t " <<aux ->origen;
            cout <<"\nDestino: " <<aux ->destino;
            cout <<"\nPeso:\t " <<aux ->peso;
            aux =aux ->sig;
        }
        cout <<endl;
    }
    else
        cout <<"\nLa paqueteria esta vacia...\n\n";
}

void Paqueteria::guardar(ofstream &wr){
    Paquete *aux =top;
    wr.open("data.txt", ios::out);
    if(!vacia())/*{
        while(aux){           //guardar en desorden?
            wr <<aux ->id <<" " <<aux ->origen <<" " <<aux ->destino <<" " <<aux ->peso <<"\n";
            aux =aux ->sig;
        }
    }*/
        recorrer(wr, aux);
    else
        wr <<"";
    wr.close();
}

//guardar en orden?
void Paqueteria::recorrer(ofstream &wr, Paquete *aux){
    if(aux ->sig)
        recorrer(wr, aux ->sig);
    wr <<aux ->id <<" " <<aux ->origen <<" " <<aux ->destino <<" " <<aux ->peso <<"\n";
}

void Paqueteria::recuperar(ifstream &re){
    int id, peso;
    string origen, destino;
    re.open("data.txt", ios::in);
    if(re.fail())
        cout <<"\nNo se pudo abrir ningun archivo...\n\n";
    else{
        re >>id;
        while(!re.eof()){
            re >>origen;
            re >>destino;
            re >>peso;
            Paquete *npaquete =new Paquete(id, origen, destino, peso, top);
            re >>id;
            top =npaquete;
        }
    }
    re.close();
}

int main(){
    int op =0;
    Paqueteria paqueteria;
    ofstream wr;
    ifstream re;
    do{
        cout <<"\n1. Agregar.\t2. Eliminar.\n3. Mostrar.";
        cout <<"\t4. Guardar.\n5. Recuperar.\t6. Salir.\n";
        cin >>op;
        cin.clear();
        cin.ignore();
        switch(op){
        case 1:
            //agregar
            paqueteria.agregar();
            break;
        case 2:
            //eliminar
            if(paqueteria.vacia())
                cout <<"\nLa paqueteria esta vacia...\n\n";
            else{
                paqueteria.eliminar();
                cout <<"\nPaquete eliminado...\n\n";
                paqueteria.mostrar();
            }
            break;
        case 3:
            //mostrar
            paqueteria.mostrar();
            break;
        case 4:
            //guardar
            paqueteria.guardar(wr);
            cout <<"\nDatos guardados...\n\n";
            break;
        case 5:
            //recuperar
            paqueteria.recuperar(re);
            cout <<"\nDatos recuperados...\n\n";
            break;
        case 6:
            cout <<"\nSaliendo...\n";
            break;
        default:
            cout <<"\nOpcion no valida...\n";
            break;
        }
    }while(op !=6);
}
