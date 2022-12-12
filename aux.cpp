
#include "aux.h"

using namespace genogram;

/*******************************************************************************************************/
// Struct
/*******************************************************************************************************/

struct Date{
  day gg;
  month mm;
  year aa;
};

struct Sons{
  PersonElem *son;
  Sons *next;
};

struct Relation{
  PersonElem *mother;
  PersonElem *father;
  PersonElem *couple;
  Sons *list;
};


struct genogram::PersonElem{
	Name name;
	Gender gender;
	Relation *adjList;
	PersonElem *next;
	Date* b;
	Date* d;
};

/*******************************************************************************************************/
// Const
/*******************************************************************************************************/

Sons* const emptySons = NULL;
Date* const emptyData = NULL;
const char nodata = '-';

/*******************************************************************************************************/
// Funzioni ausiliarie
/*******************************************************************************************************/

bool isEmpty(const Genogram& gm)
{
	return (gm==emptyGm);
}

PersonElem* getPerson(Name n, const Genogram& gm) {
  for (genogram::Genogram p = gm; p != emptyGm; p = p->next) {
   if (p->name == n) return  p; 
  }
  return emptyGm; 
}


bool isPersonInGenogram(Name n, const Genogram& gm) {
  return (getPerson(n, gm)!=emptyGm);
}

bool checkAge(Name person, Name son, const Genogram& gm) {
	
	PersonElem* p = getPerson(person, gm);
	PersonElem* s = getPerson(son, gm);
	
	int BirthP = p->b->aa;
	int BirthS = s->b->aa;

	if( (BirthS-BirthP) >= 20 ) return true;

  return false;
}

bool checkGenderFather(const Genogram& gm) {
	
	for(genogram::Genogram p = gm; p != emptyGm; p = p->next)
		if(p->adjList->father != emptyGm && p->adjList->father->gender != 'M')
			return false;
	
	return true;
	
}

bool checkGenderMother(const Genogram& gm) {
	
	for(genogram::Genogram p = gm; p != emptyGm; p = p->next)
		if(p->adjList->mother != emptyGm && p->adjList->mother->gender != 'F')
			return false;
	
	return true;
}


bool isDataDeath(PersonElem* p) {

 if(p->d != emptyData) return true;

 return false;

}


bool isDataBorn(PersonElem* p) {

 if(p->b != emptyData) return true;

 return false;

}

bool checkConnection(const Genogram& gm) {
	
	for(genogram::Genogram p = gm; p != emptyGm; p = p->next){
	
		Relation* r = p->adjList;
		
		if( r->mother == emptyGm && r->father == emptyGm && r->couple == emptyGm && r->list == emptySons )
			return false;
	
	}
	
	return true;
}

bool checkDatesDescent(const Genogram& gm) {

	for(genogram::Genogram p = gm; p != emptyGm; p = p->next){

		if( isDataBorn(p) && p->adjList->list != emptySons ){
			Relation* r = p->adjList;
			
			for(Sons* s = r->list; s != emptySons; s = s->next)
			{
				if( isDataBorn(s->son) ){
					if(s->son->b->aa < p->b->aa)
						return false; 
				}
			}
		}
	}

	return true;
}

bool checkDates(const Genogram& gm) {
	
	for(genogram::Genogram p = gm; p != emptyGm; p = p->next){

		if( isDataBorn(p) && isDataDeath(p) ){

			if(p->d->aa < p->b->aa)
				return false;
		
			if(p->d->aa == p->b->aa)
				if(p->d->mm < p->b->mm)
					return false;
	
			if(p->d->mm == p->b->mm)
				if(p->d->gg < p->b->gg)
					return false;
		}
	}
	
	return true;			

}

bool checkBorn(Name person, const Genogram& gm) {
	
	PersonElem* p = getPerson(person, gm);
	if( !isDataBorn(p) ) return true;
 return false;

}

bool isRelationCouple(Name father, Name mother, const Genogram& gm) {
	
 PersonElem* f = getPerson(father, gm);
 PersonElem* m = getPerson(mother, gm);

 Relation* r1 = f->adjList;
 Relation* r2 = m->adjList;

 if(r1->couple == m && r2->couple == f) return true;

 return false;
}	



bool isRelationCInGenogram(Name person, const Genogram& gm) {

 PersonElem* p = getPerson(person, gm);
 Relation* r = p->adjList;

 if(r->couple != emptyGm) return true;

 return false;
}



bool isRelationSInGenogram(Name son, Name parent, const Genogram& gm) {

 PersonElem* s = getPerson(son, gm);
 if (s == emptyGm) return false;
 Relation* r = s->adjList;
 PersonElem* p = getPerson(parent, gm);
 
 if(p->gender == 'F' && r->mother != emptyGm) return true;
 if(p->gender == 'M' && r->father != emptyGm) return true;
 
 return false;
}

bool isRelationPInGenogram(Name parent, Name son, const Genogram& gm) {

 PersonElem* p = getPerson(parent, gm);
 if (p == emptyGm) return false;
 Relation* r = p->adjList;

 for (Sons* s = r->list; s != emptySons; s = s->next) {
    if (s->son->name == son ) return true;
  }
 return false;
}


void addRelationSon(Name son, Name parent, Genogram& gm) {

  Sons* ss = new Sons;
  ss->son = getPerson(son, gm);

  PersonElem* p = getPerson(parent, gm);

  Relation* r = p->adjList;
	
 if (r->list == emptySons) {
    r->list = ss;
    ss->next = emptySons;
  } else {
    ss->next = r->list;
    r->list = ss;
  }


}

void addRelationCouple(Name man, Name woman, Genogram& gm) {

  PersonElem* m = getPerson(man, gm);
  PersonElem* w = getPerson(woman, gm);

  Relation* r1 = m->adjList;
  Relation* r2 = w->adjList;

  r1->couple = w;
  r2->couple = m;

}

void addRelationFather(Name father, Name son, Genogram& gm) {

  PersonElem* f = getPerson(father, gm);
  PersonElem* s = getPerson(son, gm);

  Relation* r = s->adjList;
	
  r->father = f;

}

void addRelationMother(Name mother, Name son, Genogram& gm) {

  PersonElem* m = getPerson(mother, gm);
  PersonElem* s = getPerson(son, gm);

  Relation* r = s->adjList;
	
  r->mother = m;

}

void SelectionSort(Date* &output, int dim)
{
	int min;
	for(int i=0; i<dim-1; ++i)
	{
       min=i;
       for(int j=i; j<dim; ++j)
       {
		 if(output[j].aa < output[min].aa)
			min=j;
		}

		int aux = output[min].aa;
		output[min].aa = output[i].aa ;	
	    output[i].aa = aux;
	}
}


void printAdjList(Name n, const Genogram& gm) {

  PersonElem* p = getPerson(n, gm);
  if (p==emptyGm) return;

  Relation* r = p->adjList;
 
  cout<<"madre: ";
  if( r->mother != emptyGm) 
	 cout<<r->mother->name<<endl;
  else
	 cout<<endl;

  cout<<"padre: ";
  if( r->father != emptyGm)
	 cout<<r->father->name<<endl;
  else
	 cout<<endl;

  cout<<"in coppia con: ";
  if( r->couple != emptyGm)
	 cout<<r->couple->name<<endl;
   else
	 cout<<endl;

  cout<<"figli: ";

  if(r->list == emptySons)
	cout<<endl;
  else
  {
	
  	int dim = 0;
	
	for(Sons* s = r->list; s != emptySons; s = s->next)
	{
		if(isDataBorn(s->son) )
			dim++; 
  	}
	
	if(dim > 0)
	{
  		Date* output = new Date[dim];
	
		int i = 0;

		for(Sons* s = r->list; s != emptySons; s = s->next)
		{

			if(isDataBorn(s->son) ){
				output[i].aa = s->son->b->aa;
				++i;
			}
		}
  		 
	
		SelectionSort(output, dim);

		for(Sons* s = r->list; s != emptySons; s = s->next)
		{
			if(isDataBorn(s->son) ){
				for(int j=0; j<dim; ++j)
				{
					if( output[j].aa == s->son->b->aa ){
							cout<<s->son->name<<" ";
					
				  	}
				}
			}				
			
  		}
	}
	
		
	for(Sons* s = r->list; s != emptySons; s = s->next)
	{
		if(checkBorn(s->son->name, gm) )
			cout<<s->son->name<<" ";
	}
  	
  }
  cout << endl <<endl;
}

void CancellaRelazioni(PersonElem *p, Relation *r, Genogram& gm){
		
	Sons* s = r->list;
	
	if(s->son == p){
		r->list = s->next;
		Sons *q = s;
		delete q;
	}
		else {
	
			Sons *aux = s;
	
			while(aux->next->son != p)
				aux = aux->next;
			Sons *q = aux->next;
			aux->next = q->next;
			delete q;
			r->list = s;
		
		}
}
	

void CancellaPersona(PersonElem *p, Genogram& gm){

	if(gm == p){
		gm = gm->next;
		delete p->adjList;
		delete p;
	} 
	
	else {
	
		PersonElem *cur = gm;

		while(cur->next != p)
			cur = cur->next;
		cur->next = p->next;
		delete p->adjList;
		delete p;
	
	}

}

/*******************************************************************************************************/
// Genogramma
/*******************************************************************************************************/

Genogram genogram::createEmptyGenogram()
{
  return emptyGm;
}

bool genogram::AddPerson(Name n, Gender g, Genogram& gm){
	
	if (isPersonInGenogram(n, gm))
       return false;  

	Genogram p = new PersonElem;
	p->name = n;
	p->gender = g;
	p->b = emptyData;
	p->d = emptyData;
    Relation* r = new Relation;
	p->adjList = r;
	r->mother = emptyGm;
    r->father = emptyGm;
    r->couple = emptyGm;
    r->list = emptySons;
	

	if (isEmpty(gm)) {
    	gm = p;
    	p->next = emptyGm;
  	} else {
    	p->next = gm;
    	gm = p;
  	  }
  return true;
}

bool genogram::AddRelMother(Name mother, Name son, Genogram& gm){
	
	if(isEmpty(gm)) return false;

	if(mother == son) return false;

	if (!isPersonInGenogram(mother, gm) || !isPersonInGenogram(son, gm))
    	return false;
  

 	if (isRelationPInGenogram(mother,son,gm) || isRelationSInGenogram(son,mother,gm))
    	return false;
	

 	addRelationMother(mother, son, gm);
    addRelationSon(son, mother, gm);
    return true;

}

bool genogram::AddRelFather(Name father, Name son, Genogram& gm){
	

	if(isEmpty(gm)) return false;

	if(father == son) return false;

	
	if (!isPersonInGenogram(father, gm) || !isPersonInGenogram(son, gm))
    	return false;
  

 	if (isRelationPInGenogram(father,son,gm) || isRelationSInGenogram(son,father,gm))
    	return false;
	

 	addRelationFather(father, son, gm);
    addRelationSon(son, father, gm);
    return true;

}

bool genogram::AddRelCouple(Name man, Name woman, Genogram& gm){
	

	if(isEmpty(gm)) return false;

	if(man == woman) return false;
	
	if (!isPersonInGenogram(man, gm) || !isPersonInGenogram(woman, gm))
    	return false;
  
	
 	if (isRelationCInGenogram(man, gm) || isRelationCInGenogram(woman,gm))
    	return false; 

 	addRelationCouple(man, woman, gm);
    return true;

}

bool genogram::AddRelChildToCouple(Name father, Name mother, Name son, Genogram& gm){

	if(!isRelationCouple(father, mother, gm))
		return false;
	
	if (isRelationSInGenogram(son,mother,gm) || isRelationSInGenogram(son,father,gm))
		return false;
	
	
	addRelationMother(mother,son,gm);
	addRelationFather(father,son,gm);
	addRelationSon(son,mother,gm);
	addRelationSon(son,father,gm);
	return true;
}

bool genogram::SetBorn(Name person, day giorno, month mese, year anno, Genogram& gm){

	if(isEmpty(gm)) return false;
	
	if (!isPersonInGenogram(person, gm) )
		return false; 
	
	PersonElem* p = getPerson(person, gm);
	if( isDataBorn(p) ) return false;

	Date* data = new Date;
	p->b = data;
	data->gg = giorno;
	data->mm = mese;
	data->aa = anno;
	return true;
}

bool genogram::SetDeath(Name person, day giorno, month mese, year anno, Genogram& gm){
	
	if(isEmpty(gm)) return false;
	
	if (!isPersonInGenogram(person, gm) )
		return false; 
	
	PersonElem* p = getPerson(person, gm);
	if( !isDataBorn(p) || isDataDeath(p) ) return false;

	Date* data = new Date;
	p->d = data;
	data->gg = giorno;
	data->mm = mese;
	data->aa = anno;
	return true;
}

bool genogram::IsValid(const Genogram& gm){
	
	if(isEmpty(gm)){
		 cout<<endl<<"Genogramma vuoto"<<endl;
		 return false; 
	}
	
	if (!checkGenderMother(gm) ){
		cout<<endl<<"Errore genere della madre di qualche persona"<<endl;
		return false;
	}

	if (!checkGenderFather(gm) ){
		cout<<endl<<"Errore genere del padre di qualche persona"<<endl;
		return false;
	}	
	
	if(!checkDates(gm) ){
		cout<<endl<<"Errore esiste una persona che ha data di nascita posteriore alla data di morte"<<endl;
		return false;
	}
	
	if(!checkDatesDescent(gm) ){
		cout<<endl<<"Errore esiste una persona che ha data di nascita dei discendenti posteriore alla propria"<<endl;
		return false;
	}
	
	if(!checkConnection(gm) ){
		cout<<endl<<"Errore il genogramma è disconnesso"<<endl;
		return false;
	}

	return true;
}
	
bool genogram::DeletePerson(Name person, Genogram& gm){
	
	if(isEmpty(gm)) return false;
	
	if (!isPersonInGenogram(person, gm) )
		return false; 

	PersonElem *p = getPerson(person, gm);
	
	if(p->adjList->mother != emptyGm){
		
		PersonElem *m = p->adjList->mother;
		Relation *r = m->adjList;

		CancellaRelazioni(p,r,gm);
	
	}
	
	if(p->adjList->father != emptyGm){
		
		PersonElem *f = p->adjList->father;
		Relation *r = f->adjList;

		CancellaRelazioni(p,r,gm);
	
	}
	
	if(p->adjList->couple != emptyGm){
	
		PersonElem *c = p->adjList->couple;
		Relation *r = c->adjList;
		
		r->couple = emptyGm;
	}
	
	if(p->adjList->list != emptySons){
	
		Relation *r = p->adjList;
		Sons *s = r->list;
		
		while(s != emptySons){

			Sons *aux = s;
			s = s->next;
			delete aux;

		}
	
		delete s;
		
		for (PersonElem *q = gm; q != emptyGm; q = q->next) {
	
			
			if(q->adjList->mother == p){
				PersonElem *aux = q;
				q = q->next;
				CancellaPersona(aux,gm);
			} 
			
			if(q->adjList->father == p){
				PersonElem *aux = q;
				q = q->next;
				CancellaPersona(aux,gm);
			} 

			if(q->adjList->couple == p){
				q->adjList->couple = emptyGm;
			}  
		
			if(q->adjList->list->son == p){
				q->adjList->list->son = q->adjList->list->son->next;
			}
		}
	}
	
	CancellaPersona(p,gm);		
			
 return true;

}

/*******************************************************************************************************/
// Stampa il genogramma


void printGenogram(const genogram::Genogram& gm) {
  cout<<endl;

  if(isEmpty(gm)){
	cout<<"Genogramma vuoto"<<endl;
	return;
	}
	
  for (genogram::Genogram p = gm; p != emptyGm; p = p->next) {
    cout << p->name <<" "<< p->gender ;
	if(isDataBorn(p) ){
		cout<<" "<< p->b->gg <<"/"<< p->b->mm <<"/"<< p->b->aa<<" " ;

		if(isDataDeath(p) )
			cout<<p->d->gg <<"/"<< p->b->mm <<"/"<< p->b->aa <<endl;
		else
			cout<<nodata<<endl;
	}
	else 
		cout<<endl;
	printAdjList(p->name, gm);
  }
}
