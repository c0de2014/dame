/*----------------------------------------------#---#------------
  ----- C H A R - S C H L E I F E ---------------#-#-------------
  ------------------------------------------------#--------------
*/
int cs(int az, char vkt[], char kt[], char nkt[])                               //"Char-Schleife", automatisiertes ausgeben von diversen Zeichenfolgen
{                                                                               // kt -> Zeichen/Zeichenkette die wiederholt werden soll
 int i;                                                                         // vkt -> Text was vor der Wiederolung steht
 printf("%s", vkt);                                                             // nkt -> Text was nach der Wiederholung steht
 for (i=1; i<=az; i++)                                                          // az -> Wie oft kt wiederholt(hintereinander geschrieben) werden soll
 {                                                                              // Bsp: cs(3, "Hallo ", "ich ", "brauche Hilfe");
  printf("%s", kt);                                                             //    >> Hallo ich ich ich brauche Hilfe
 }
 printf("%s", nkt);
 return 1;
}
/*----------------------------------------------#---#------------
  ----- C O L O R - C H A R - S C H L E I F E ---#-#-------------
  ------------------------------------------------#--------------
*/
int ccs(int az, char vkt[], char kt[], char nkt[], int col)                     //"Color Char-Schleife", automatisiertes ausgeben von diversen Zeichenfolgen
{                                                                               // wie cs(), nur noch mit Farbausgabe -> col (4. Attribut)
 int i;                                                                         // Farben 1-16
 textcolor(col);                                                                // --> Nachteil: beachtet Anweisungen wie \n oder \t nicht !!!
 cprintf("%s", vkt);
 for (i=1; i<=az; i++)
 {
  textcolor(col);
  cprintf("%s", kt);
 }
 textcolor(col);
 cprintf("%s", nkt);
 return 1;
}
/*----------------------------------------------#---#------------
  ----- E X I T - K N O P P ---------------------#-#-------------
  ------------------------------------------------#--------------
*/
int exit_button()                                                               //Exit Knopf, zum schließen des Spiels
{
 int i, j, x=65, y=3;
 for (j=0; j<=2; j++)
 {
  for (i=0; i<=10; i++)
  {
   textcolor(4); gotoxy(x+i,y); cprintf("\xdb");
  }
  y++;
 }
 gotoxy(66,4); textcolor(12); textbackground(4); cprintf("e x i t \xaf"); textbackground(0);
 return 1;
}
/*----------------------------------------------#---#------------
  ----- E X I T - A U S -------------------------#-#-------------
  ------------------------------------------------#--------------
*/
int exit_timer()                                                                //Countdown-Timer, bis zu schließen des Fensters
{
 int i;
 for (i=5; i>=1; i--)
 {
  gotoxy(50,16); printf("Fenster schlie\xe1 \bt in: %is", i);
  gotoxy(80,25);
  _sleep(1);
 }
 return 1;
}
/*----------------------------------------------#---#------------
  ----- W A R T E N - 1 -------------------------#-#-------------
  ------------------------------------------------#--------------
*/
int warten1()
{
 int x=30, y=25, i;                                                             //Koordinaten für Animation
 bool run=true;
 while (run)
 {
  for (i=0; i<=3; i++)
  {
   if (kbhit()) run=false;
   else
   {
    gotoxy(x+i,y);
    printf(".");
    gotoxy(80,25);
    _sleep(1);
   }
  }
  gotoxy(x,y);
  printf("      ");
  gotoxy(80,25);
 }
 return 1;
}
/*----------------------------------------------#---#------------
  ----- W A R T E N - 2 -------------------------#-#-------------
  ------------------------------------------------#--------------
*/
int warten2()
{
 int x=31, y=25, i, o, a=179, b=47, c=196, d=92;                                //Koordinaten für Animation
 bool run=true;
 while (run)
 {
    for (i=0; i<=3; i++)
    {
     if (kbhit()) run=false;
     else
     {
      switch(i)
      {
       case 0: o=a; break;
       case 1: o=b; break;
       case 2: o=c; break;
       case 3: o=d; break;
      }
      gotoxy(x,y);
      printf("%c", o);
      gotoxy(80,25);
      _sleep(1);
     }
    }
 }
 return 1;
}
/*----------------------------------------------#---#------------
  ----- W A R T E N - 3 -------------------------#-#-------------
  ------------------------------------------------#--------------
*/
int warten3()
{
 int i, x=30, y=25, col=8, col2=7;  //col2=col+8                                //Koordinaten + Farbe für Animation
 bool run=true;
 while (run)
 {
  textcolor(col);
  for (i=0; i<=3; i++)
  {
   gotoxy(x+i,y); cprintf("\xfe");  gotoxy(80,25);
  }
  for (i=0; i<=3; i++)
  {
   if (kbhit()) run=false;
   else
   {
    textcolor(col2); gotoxy(x+i,y); cprintf("\xfe");  gotoxy(80,25); _sleep(1);
    textcolor(col); gotoxy(x+i,y); cprintf("\xfe");
   }
  }
 }
 clrscr();
 return 1;
}
/*----------------------------------------------#---#------------
  ----- S P I E L A N L E I T u N G -------------#-#-------------
  ------------------------------------------------#--------------
*/
int spielanleitung()                                                            //Einleitung des Spiels
{
 int a;
 cs(63, "\xc9", "\xcd", "\xbb\n");                                              //DAME-Schriftzug
 printf("\xba  oooooooooo.         .o.       ooo        ooooo oooooooooooo  \xba\n");
 printf("\xba  `888'   `Y8b       .888.      `88.       .888' `888'     `8  \xba\n");
 printf("\xba   888      888     .8\x22 \b888.      888b     d'888   888          \xba\n");
 printf("\xba   888      888    .8' `888.     8 Y88. .P  888   888oooo8     \xba\n");
 printf("\xba   888      888   .88ooo8888.    8  `888'   888   888    \x22     \xba\n");
 printf("\xba   888     d88'  .8'     `888.   8    Y     888   888       o  \xba\n");
 printf("\xba  o888bood8P'   o88o     o8888o o8o        o888o o888ooooood8  \xba\n");
 cs(63, "\xba", " ", "\xba\n");
 cs(32, "\xba version 0.913 / (c) 2006 by dm", " ", "\xba\n");                        //copyright ;)
 cs(63, "\xc8", "\xcd", "\xbc\n\n");
 cs(9, "   Spieler \xb3 Stein \xb3 Dame\n  ", "\xc4", "\xc5");                  //Farberklärung
 cs(7, "", "\xc4", "\xc5");
 cs(6, "", "\xc4", "");
 ccs(1, "", "", "", 12);
 printf("\n      1.   \xb3   ");
 ccs(1, "", "\xb1\xb1", "", 12);
 printf("  \xb3");
 ccs(1, "  ", "\xdb\xdb", "", 12);
 printf("\n           \xb3       \xb3");
 printf("\n      2.   \xb3   ");
 ccs(1, "", "\xb1\xb1", "", 13);
 printf("  \xb3");
 ccs(1, "  ", "\xdb\xdb", "", 13);
 printf("\n\n\n \xaf ESC         - jetzt beenden");
 printf("\n \xaf Linksklick  - markiert 'Startfeld'\n \xaf Rechtsklick - markiert 'Zielfeld'");
 cs(3, " ", "\n", " \xaf Press any key to continue");
 warten3();
 gotoxy(80,25);
 a=getch(); clrscr();
 if (a==27) exit(1);                                                            //Bricht ab und schließt Fenster, wenn ESC gedrückt wird
 return 1;
}
/*----------------------------------------------#---#------------
  ----- S I E G E R -----------------------------#-#-------------
  ------------------------------------------------#--------------
*/
int sieger(int wer)
{
 int x=55, x2=38, y=14;
 if ((wer==1) || (wer==2))
 {
  switch(wer)
  {
  case 1: textcolor(12); break;
  case 2: textcolor(13); break;
  default: break;
  }
  gotoxy(x,y++); cprintf("\n          \|||/");                   printf("\n");
  gotoxy(x,y++); cprintf("\n          (o o)");                   printf("\n");
  gotoxy(x,y++); cprintf("\n |~~~~ooO~~(_)~~~~~~~|");            printf("\n");
  gotoxy(x,y++); cprintf("\n | Spieler  %i  hat   |", wer);            printf("\n");
  gotoxy(x,y++); cprintf("\n |     GEWONNEN      |");            printf("\n");
  gotoxy(x,y++); cprintf("\n |   a p p l a u s   |");            printf("\n");
  gotoxy(x,y++); cprintf("\n '~~~~~~~~~~~~~~Ooo~~'");            printf("\n");
  gotoxy(x,y++); cprintf("\n         |__|__|");                  printf("\n");
  gotoxy(x,y++); cprintf("\n          || ||");                   printf("\n");
  gotoxy(x,y++); cprintf("\n         ooO Ooo");                  printf("\n");
 }
 else
 {
  textcolor(12);
  textbackground(12);
  gotoxy(x2,y++); ccs(40, "", " ", "", 12);
  gotoxy(x2,y++); cprintf("  ACHTUNG! Es is ein K\x84 \bfer aufgetreten  ");
  gotoxy(x2,y++); cprintf("  Bitte sofort dem Programmier melden!  ");
  gotoxy(x2,y++); ccs(40, "", " ", "", 12);
  textbackground(0);
 }
 return 1;
}
/*----------------------------------------------#---#------------
  ----- F I G U R - S E T Z E N -----------------#-#-------------
  ------------------------------------------------#--------------
*/
int figursetzen()                                                               //Setzten der Figuren auf das Feld
{
 int i,j,x=1,y=1;
 for (j=2; j<=25; j=j+3)                                                        //Zeilenmitte 2,5,8,11 14,17,20,23 und dazugehörige
 {
  for (i=4; i<=32; i=i+4)                                                       //Spaltenmitte 4,8,12,16 20,24,28,32 wird mit Figur besetzt
  {
   if (j%2==1)                                                                  //Für ungerade Zeilen
   {
    gotoxy(i,j);                                                                //An Position i,j den Wert aus brett[x][y] schreiben
    if (i%8==0)                                                                 //Für gerade Spalten in ungeraden Zeilen -> 1. Farbe
    {
     textbackground(7);                                                         //Hintergrundfarbe anpassen
     switch(brett[x][y])
     {
      case 0: ccs(1, "", "  ", "", 0); break;                                   //Feld mit 0 belegt? = "leer" -> leer zeichnen
      case 1: ccs(1, "", "\xb1\xb1", "", 12); break;                                  //Feld mit 1 belegt? = Spieler1 -> Spielfigur1 zeichnen
      case 2: ccs(1, "", "\xb1\xb1", "", 13); break;                                  //Feld mit 2 belegt? = Spieler2 -> Spielfigur2 zeichnen
      case 3: ccs(1, "", "\xdb\xdb", "", 12); break;                                  //Feld mit 3 belegt? = Spieler1(Dame) -> Spielfigur1(Dame) zeichnen
      case 4: ccs(1, "", "\xdb\xdb", "", 13); break;                                  //Feld mit 4 belegt? = Spieler2(Dame) -> Spielfigur2(Dame) zeichnen
      default: break;
     }
     textbackground(0);                                                         //Hintergrundfarbe zurücksetzen, sonst ganzer Screen in Farbe
    }
    if (i%8!=0)                                                                 //Für ungerade Spalten in ungeraden Zeilen -> 2. Farbe
    {
     switch(brett[x][y])
     {
      case 0: ccs(1, "", "  ", "", 0); break;
      case 1: ccs(1, "", "\xb1\xb1", "", 12); break;
      case 2: ccs(1, "", "\xb1\xb1", "", 13); break;
      case 3: ccs(1, "", "\xdb\xdb", "", 12); break;
      case 4: ccs(1, "", "\xdb\xdb", "", 13); break;
      default: break;
     }
    }
   }
   if (j%2==0)                                                                  //Für gerade Zeilen
   {
    gotoxy(i,j);
    if (i%8==0)                                                                 //Für gerade Spalten in geraden Zeilen -> 2. Farbe
    {
     switch(brett[x][y])
     {
      case 0: ccs(1, "", "  ", "", 0); break;
      case 1: ccs(1, "", "\xb1\xb1", "", 12); break;
      case 2: ccs(1, "", "\xb1\xb1", "", 13); break;
      case 3: ccs(1, "", "\xdb\xdb", "", 12); break;
      case 4: ccs(1, "", "\xdb\xdb", "", 13); break;
      default: break;
     }

    }
    if (i%8!=0)                                                                 //Für ungerade Spalten in geraden Zeilen -> 1. Farbe
    {
     textbackground(7);
     switch(brett[x][y])
     {
      case 0: ccs(1, "", "  ", "", 0); break;
      case 1: ccs(1, "", "\xb1\xb1", "", 12); break;
      case 2: ccs(1, "", "\xb1\xb1", "", 13); break;
      case 3: ccs(1, "", "\xdb\xdb", "", 12); break;
      case 4: ccs(1, "", "\xdb\xdb", "", 13); break;
      default: break;
     }
     textbackground(0);
    }
   }
   x=x+1;                                                                       //Spaltenzahl erhöhen
  }
  x=1;                                                                          //Spaltenzahl zurücksetzen für neue Zeile
  y=y+1;                                                                        //Zeilenzahl erhöhen
  printf("\n");
 }
 gotoxy(38,25);                                                                 //Damit Cursor nicht im Feld blinkt
 return 1;
}
/*----------------------------------------------#---#------------
  ----- S P I E L F E L D -----------------------#-#-------------
  ------------------------------------------------#--------------
*/
int spielfeld()                                                                 //Zeichnet das reine Spielfeld, ohne Figuren
{
 int i,j,k, n=0;
 for (i=1; i<=8; i++)                                                           //Zeichnet 8 Zeilen
 {
  for (j=1; j<=8; j++)                                                          //Zeichnet 8 Spalten
  {
   if (i%2==0)                                                                  //Für gerade Felder:
   {
    for (k=1;k<=3;k++)                                                          //Zeichnet 1 Feld à 4*3 Buchstabenfelder
    {
     gotoxy((4*j)-1,k+n);                                                       //Springt dorthin, wo die linke, obere Ecke anfangen soll
     if (j%2==1)
     {
      ccs(4, "", "\xdb", "", 0);                                                    //Zeichnet 1 Zeile à 4 Buchstabenfelder
     }
     else
     {
      cs(4, "", "\xdb", "");                                                //Zeichnet 1 Zeile à 4 Buchstabenfelder in Farbe
     }
    }
   }
   if (i%2==1)                                                                  //Für ungerade Felder:
   {
    for (k=1;k<=3;k++)
    {
     gotoxy((4*j)-1,k+n);
     if ((j%2==1))
     {
      cs(4, "", "\xdb", "");
     }
     else
     {
      ccs(4, "", "\xdb", "", 0);
     }
    }
   }
  }
  n=n+3;                                                                        //Zeilenabstand (von einem 4*3er Feld): da k<=3 und n=n+3 -> direkt untereinander
 }
 printf("\n");
 exit_button();
// infos();
 return 1;
}
/*----------------------------------------------#---#------------
  ----- B R E T T A U S G A B E -----------------#-#-------------
  ------------------------------------------------#--------------
*/
int brettausgeben()
{
 spielfeld();
// koordanzeige();
 figursetzen();
// infos();
 return 1;
}
/*----------------------------------------------#---#------------
  ----- M A R K I E R E - F E L D ---------------#-#-------------
  ------------------------------------------------#--------------
*/
int spieler;
int markiere_feld(int x, int y)
{
 if (spieler==1)//(x%2)==(y%2)) // if ((x%2==y%2) && (x%1==y%1))
 {
  if (x%2==y%2) textbackground(7);
  else { if (x%2!=y%2) textbackground(0);  }
  x=x*4;
  y=y*3;
  textcolor(12);
  gotoxy(x-1,y);
  cprintf("\xc0\xc4\xc4\xd9");
  gotoxy(x-1,y-1);
  cprintf("\xb3");
  gotoxy(x-1,y-2);
  cprintf("\xda\xc4\xc4\xbf");
  gotoxy(x+2,y-1);
  cprintf("\xb3");
  textbackground(0);
 }
 else
 {
  if (x%2==y%2) textbackground(7);
  else { if (x%2!=y%2) textbackground(0);  }
  x=x*4;
  y=y*3;
  textcolor(13);
  gotoxy(x-1,y);
  cprintf("\xc0\xc4\xc4\xd9");
  gotoxy(x-1,y-1);
  cprintf("\xb3");
  gotoxy(x-1,y-2);
  cprintf("\xda\xc4\xc4\xbf");
  gotoxy(x+2,y-1);
  cprintf("\xb3");
  textbackground(0);
 }
 gotoxy(80,25);
 return 1;
}
