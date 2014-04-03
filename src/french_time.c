#include "french_time.h"

static char* const STR_HEURE = "heure";
static const char* STR_H = " h.";
static const char* STR_MOINS = "moins";

static char* HEURES[] = {
	"minuit","une","deux","trois","quatre","cinq","six","sept","huit","neuf","dix","onze","midi"};

static char* SEIZEMINS[] = {
	"pile",
  "un",
  "deux",
  "trois",
  "quatre",
  "cinq",
  "six",
  "sept",
  "huit",
  "neuf",
  "dix",
  "onze",
  "douze",
  "treize",
  "quatorze",
  "et quart",
  "seize"};

static char* DIZAINE[] = {
	"",
  "dix",
  "vingt",
  "trente",
  "quarante",
  "cinquante"};

static char* DIZAINEMINS[] = {
	"",
  "et un",
  "deux",
  "trois",
  "quatre",
  "cinq",
  "six",
  "sept",
  "huit",
  "neuf"};

static char* MOINSMINUTES[] = {
	"vingt",
  "le quart",
  "dix",
  "cinq"};

static const char* JOURS[] = {
	"Dimanche","Lundi","Mardi","Mercredi","Jeudi","Vendredi","Samedi"};

static const char* MOIS[] = {
	"Jan.","Fév.","Mars","Avril","Mai","Juin","Juil.","Août","Sep.","Oct.","Nov.","Déc."};

int textwatch_time(char* line1, char* line2, char* line3, char* line4, struct tm * t) {

	int hours = t->tm_hour;
	int minutes = t->tm_min;
  
	int nbLine = 3;
	strncpy(line1, "",LINE_BUFFER_SIZE -1);
	strncpy(line2, "",LINE_BUFFER_SIZE -1);
	strncpy(line3, "",LINE_BUFFER_SIZE -1);
	strncpy(line4, "",LINE_BUFFER_SIZE -1);	
	
  //ne dépasse jamais 23 (retourne à 0)
  if (hours >= 24) hours = 0;
  //pour transforer le 24h en 15h
	if (hours > 12) hours -= 12;
  
  
  //////////
  //HEURE
  //////////
  
  //si moins vingt, moins le quart, moins dix, moins cinq, passer à l'heure d'après
  if (minutes == 40 || minutes == 45 || minutes == 50 || minutes == 55)
  {
    hours++;
  }
  
  //////////
  //MINUTES
  //////////
  
  //nombre de lignes pour afficher les minutes
  int lignesminutes;
  
  //carmina burana
  //https://www.youtube.com/watch?v=GXFSK0ogeg4
  char* mina = "";
  
  //...
  char* minb = "";
  
  //Jusqu'a 16
  if (minutes <= 16)
  {
    //affiche les 16 premières minutes
    mina = SEIZEMINS[minutes];
      
    int lignesminutes = 1;
  }
  //Au dessus de 16 jusqu'a 59
  else if (minutes > 16  && minutes <= 59) 
  {
    int lignesminutes = 2;
    
        //si moins vingt, moins le quart, moins dix, moins cinq, passer à l'heure d'après
        if (minutes == 40 || minutes == 45 || minutes == 50 || minutes == 55)
        {
          mina = "moins";

          switch (minutes)
          {
              //vingt
              case 40 :
                minb = MOINSMINUTES[0];
              
                break;
              
              //le quart
              case 45 :
                minb = MOINSMINUTES[1];
              
                break;
              
              //dix
              case 50 :
                minb = MOINSMINUTES[2];
              
                break;
              
              //cinq
              case 55 :
                minb = MOINSMINUTES[3];
              
                break;           
            }
        }
        //si pas moins vingt, moins le quart, moins dix, moins cinq
        else
        { 
          mina = DIZAINE[minutes / 10];
          minb = DIZAINEMINS[minutes % 10];
        }
  }
  
  //////////
  //AFFICHAGE
  //////////
  
  strcat(line1, HEURES[hours]); //on affiche l'heure (toujours en première ligne)
  
  //si minuit on affiche pas heure
  if (hours == 0)
  {
    strcat(line2, mina);
    strcat(line3, minb);
  }
  //si au dessus on affiche heure
  else
  {
    strcat(line2, STR_HEURE);
    strcat(line3, mina);
    strcat(line4, minb);
    
    if (hours > 1) strcat(line2, "s"); //rajoute un "s" à heure
  }
  
  //Retourne le nombre de lignes
  //return nbLine;
  return 4;
}

void info_lines(char* line1,struct tm * t) {
	
	char wday[LINE_BUFFER_SIZE];
	char mday[LINE_BUFFER_SIZE];
	char mon[LINE_BUFFER_SIZE];
	strncpy(line1, "",LINE_BUFFER_SIZE -1);
	snprintf(wday, LINE_BUFFER_SIZE, "%s", JOURS[t->tm_wday]);
	snprintf(mday, LINE_BUFFER_SIZE, "%d", t->tm_mday);
	snprintf(mon, LINE_BUFFER_SIZE, "%s", MOIS[t->tm_mon]);
	strcat(line1, wday);
	strcat(line1, " ");
	strcat(line1, mday);
	strcat(line1, " ");
	strcat(line1, mon);


}

void majMinute(char * str, struct tm * t){
	//str[0] = 'a';
	//strcpy(str, "a");
	snprintf(str, 3, "%d", t->tm_min);
}
