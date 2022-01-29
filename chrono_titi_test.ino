// bit_A = broche 2; 1
// bit_B = broche 3; 2
// bit_C = broche 4; 4
// bit_D = broche 5; 8
//latch_dizmin = 11;
//latch_min = 10;
//latch_dizsec = 9;
//latch_sec = 8;
//latch_cent = 7;
//latch_mil = 6;

//Indice = digit, sous indice = n° du bit
//Premier digit (indice 0) = droite(milliemes (indice 5) = dizaine minute

//Premier bit (sous-indice 0) = poids FAIBLE
byte digit[]={2,3,4,5}; //4 bits des décodeurs BCD 0=1 1=2 2=4 3=8
byte latch[] = {6,7,8,9,10,11}; // 6 pins des latch des décodeurs

int chiffre[] = {0,0,0,0,0,0}; //nombres à afficher en façade (ms cs s ds m dm)
int atemps1[3] = {0,0,0}; //liste contenant le temps modifiee pour l'affichage 0=m 1=s 2=c

const int startstop = 12; // bouton poussoir start/stop connecté àa la masse si appuyer
const int bpreset = 13; //bouton poussoir reset connecté àa la masse si appuyer
boolean etatss; // variable booleenne pour l'état du bp start/stop
boolean etatr; // variable booleenne pour l'état du bp reset

volatile unsigned long t0; 
long tecoul; 

void setup()
{
   // Les broches sont toutes des sorties
    pinMode(digit[0], OUTPUT);
    pinMode(digit[1], OUTPUT);
    pinMode(digit[2], OUTPUT);
    pinMode(digit[3], OUTPUT);
    pinMode(latch[0], OUTPUT);
    pinMode(latch[1], OUTPUT);
    pinMode(latch[2], OUTPUT);
    pinMode(latch[3], OUTPUT);
    pinMode(latch[4], OUTPUT);
    pinMode(latch[5], OUTPUT);
    // sauf les deux BP
    pinMode(startstop, INPUT_PULLUP);
    pinMode(bpreset, INPUT_PULLUP);
    
    // Les broches sont toutes mises à l'état haut
    digitalWrite(digit[0], LOW);
    digitalWrite(digit[1], LOW);
    digitalWrite(digit[2], LOW);
    digitalWrite(digit[3], LOW);
    digitalWrite(latch[0], LOW);
    digitalWrite(latch[1], LOW);
    digitalWrite(latch[2], LOW);
    digitalWrite(latch[3], LOW);
    digitalWrite(latch[4], LOW);
    digitalWrite(latch[5], LOW);

}

void loop ()
{
  calc_tps();
  affiche_digits();
}  

void affiche_digits()
{
    for(byte i=0; i<6; i++)
    {
        for(byte n=0; n<4; n++)
        digitalWrite(digit[n], bitRead(chiffre[i],n));
        //Latch
        digitalWrite(latch[i],1);
        digitalWrite(latch[i],0);
    }
}
 
void calc_tps()
{
    t0 = millis(); 

    tecoul = millis() - t0;       //decoupage puis soustraction des minutes
    atemps1[0] = tecoul / 60000;
    tecoul %= 60000;
    
    atemps1[1] = tecoul / 1000;  //secondes
    tecoul %= 1000;
 
    atemps1[2] = tecoul / 10;    //centiemes

    chiffre[0] = atemps1[2] % 10;// recup les centieme
    chiffre[1] = atemps1[2] / 10;// recup les dizaines de centiemes
    chiffre[2] = atemps1[1] % 10;// recup les secondes
    chiffre[3] = atemps1[1] / 10;// recup les dizaines de secondes
    chiffre[4] = atemps1[0] % 10;// recup les minutes
    chiffre[5] = atemps1[0] / 10;// recup les dizaines de minutes
    return chiffre[0,1,2,3,4,5];
}
