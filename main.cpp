#include <cstdlib>
#include <iostream>

////////////////////////////////////////////////////////////////////////
// COMPILAZIONE:
// g++ -Wall *cpp
////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include "aux.h"

using namespace std;

int menu() 
{
  int scelta = -1;
  while ((scelta<0)||(scelta>11))
  { 
    cout << "--------------------------------------------------------------------------\n";
    cout << "                                  MENU                                    \n";
    cout << "--------------------------------------------------------------------------\n";
    cout << "1. Inserimento del genogramma da file\n";
    cout << "2. Inserimento persona nel genogramma\n";
    cout << "3. Inserimento della relazione madre\n";
    cout << "4. Inserimento della relazione padre\n";
    cout << "5. Inserimento della relazione coppia\n";
    cout << "6. Inserimento della relazione figlio ad una coppia\n";
    cout << "7. Setta data di nascita\n";
    cout << "8. Setta data di morte\n";
    cout << "9. Cancella persona\n";
    cout << "10. Controlla validità del genogramma\n";
    cout << "11. Stampa del genogramma\n";
    cout << "0. Uscita\n";
    cout << "\nFornisci la tua scelta ---> ";
    cin >> scelta;
    cout << "--------------------------------------------------------------------------\n";
    if (!cin) {cout << "Hai inserito una stringa al posto di un numero\n"; return 0;}
    if ((scelta>=0)&&(scelta<=11)) return scelta;
      cout << "\nScelta non valida\n";
  }
  return -1;
}


int main() {
	
  genogram::Genogram gm = genogram::createEmptyGenogram();  

  string nomefile;
  int scelta = 0;
	
  while (true) {

    scelta = menu();

    if (scelta == 0) break;
	
	genogram::Name n1,n2,n3;
    genogram::Gender g;
	genogram::day d;
	genogram::month m;
	genogram::year y;
	char letter;

	switch (scelta)
    {

      case 1:{
		 gm = genogram::createEmptyGenogram(); 
                                      
        cout << "\nInserisci il nome del file: ";
        cin >> nomefile;
        ifstream ifs(nomefile.c_str()); 
        if (!ifs) {cout << "\nErrore apertura file, verifica di avere inserito un nome corretto\n";}
        else 
		{
         for(;;) 
		 {	
			ifs >> letter;
			if(letter == 'P')
			{
           		ifs >> n1;
				ifs >> g;
				genogram::AddPerson(n1, g, gm);
				ifs >> d;
				if(d != 0)
				{
					ifs >> letter;	
					ifs >> m;
					ifs >> letter;
					ifs >> y;
					genogram::SetBorn(n1, d, m, y, gm);
		
				} else if(d==0)
						{
							ifs.clear();
							continue;
						}

				ifs >> d ;
				if(d != 0)
				{
					ifs >> letter;	
					ifs >> m;
					ifs >> letter;
					ifs >> y;
					genogram::SetDeath(n1, d, m, y, gm);
					continue;
		
				} else if(d==0)
						{
							ifs.clear();
							continue;
						}
			
			}
		

			if(letter == 'R'){
				ifs >> n1;
				ifs >> letter;
				ifs >> n2;
				switch(letter){
					case 'M':
					genogram::AddRelMother(n1, n2, gm);
					break;
				
					case 'F':
					genogram::AddRelFather(n1, n2, gm);
					break;
		
					case 'C':
					genogram::AddRelCouple(n1, n2, gm);
					break;
				}
				continue;
			}
		
			break;

		 } 
        }
      } 
      break;
	  
	  case 2:
		
		cout<<"\nInserisci nome: ";
		cin>>n1;
		cout<<"Inserisci genere: ";
		cin>>g;	
		if (!genogram::AddPerson(n1,g,gm))
	    cout << "\nNome gia' presente nel genogramma, nodo non inserito\n";
	  break;
	
	  case 3:
	
		cout << "\nInserisci nome della madre: ";
        cin >> n1;
        cout << "\nInserisci nome del figlio/a': ";
        cin >> n2;
        if (!genogram::AddRelMother(n1, n2, gm))
	   cout << "\nNomi non presenti nel genogramma o relazione tra le due persone gia' presente nel genogramma,relazione non inserita\n";
      break;
	
	  case 4:
	
		cout << "\nInserisci nome del padre: ";
        cin >> n1;
        cout << "\nInserisci nome del figlio/a': ";
        cin >> n2;
        if (!genogram::AddRelFather(n1, n2, gm))
	   cout << "\nNomi non presenti nel genogramma o relazione tra le due persone gia' presente nel genogramma,relazione non inserita\n";
      break;
	
	  case 5:
	
		cout<<"\nInserisci nome dell'uomo: ";
        cin >> n1;
        cout << "\nInserisci nome della donna: ";
        cin >> n2;
        if (!genogram::AddRelCouple(n1, n2, gm))
	   cout << "\nNomi non presenti nel genogramma o relazione tra le due persone gia' presente nel genogramma,relazione non inserita\n";
      break;
	
	  case 6:
	
		cout<<"\nInserisci nome del padre: ";
        cin >> n1;
        cout << "\nInserisci nome della madre: ";
        cin >> n2;
		cout<<"\nInserisci nome del figlio della coppia: ";
        cin >> n3;
        if (!genogram::AddRelChildToCouple(n1, n2, n3, gm))
	   cout << "\nNomi non presenti nel genogramma o relazione gia' presente nel genogramma,relazione non inserita\n";
      break;
	
	  case 7:
	
		cout<<"\nInserisci nome della persona: ";
        cin >> n1;
        cout << "\nInserisci giorno: ";
        cin >> d;
		cout << "\nInserisci mese: ";
		cin >> m;
		cout << "\nInserisci anno: ";
		cin >> y;
        if (!genogram::SetBorn(n1, d, m, y, gm))
	   cout << "\nNome non presenti nel genogramma o data gia' presente nel genogramma,data non inserita\n";
      break;
	
	  case 8:
	
		cout<<"\nInserisci nome della persona: ";
        cin >> n1;
        cout << "\nInserisci giorno: ";
        cin >> d;
		cout << "\nInserisci mese: ";
		cin >> m;
		cout << "\nInserisci anno: ";
		cin >> y;
        if (!genogram::SetDeath(n1, d, m, y, gm))
	   cout << "\nNome non presenti nel genogramma o data gia' presente nel genogramma,data non inserita\n";
      break;
	
	  case 9:
		
		cout<<"\nInserisci nome della persona: ";
        cin >> n1;
		if(!genogram::DeletePerson(n1, gm) )
		cout << "\nNome non presenti nel genogramma, persona non cancellata\n";
		
	  break;
	  
	  case 10:
	
		if(!IsValid(gm) )
			cout<<"Genogramma non valido\n"<<endl;
	  	else
			cout<<"\nGenogramma valido\n"<<endl;
	  break;

	  case 11:
		printGenogram(gm);
	  break;
		
	 default: return 0;
	}
  }
}
		

