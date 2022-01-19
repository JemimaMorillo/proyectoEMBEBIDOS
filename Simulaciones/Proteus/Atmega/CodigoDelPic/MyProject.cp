#line 1 "C:/Users/PC/Desktop/proyectoArchivos/ArchivoMusica/MyProject.c"


int tempo=136 ;
int negra=440;
int redonda= 1760;
int blanca=880;
int corchea= 220;
int fusa=110;
int semifusa=55;

int si4=494;


int do5=523;
int dos5=554;
int re5= 587;
int res5=622;
int mi5=659;
int fa5=698;
int fas5= 740;
int sol5= 784;
int sols5=831;
int la5=880;
int las5=932;
int si5= 988;



int do6=1047;
int dos6=1109;
int re6= 1175;
int res6=1245;
int mi6=1319;
int fa6=1397;
int fas6= 1480;
int sol6= 1568;
int sols6=1661;
int la6=1760;
int las6=1865;
int si6= 1976;






void Alarma() {
 Sound_Play(res6,blanca); Sound_Play(mi6,blanca);

}

void main() {


 ANSEL = 0;
 ANSELH = 0;
 C1ON_bit = 0;
 C2ON_bit = 0;

 TRISB = 0xF8;

 Sound_Init(&PORTC, 3);


 while (1) {
 if (Button(&PORTB,3,1,1))

 Alarma();
 Delay_ms(100) ;




 if (Button(&PORTB,4,1,1))


 Delay_ms(100) ;


 }
}
