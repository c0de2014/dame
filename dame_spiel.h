#include <math.h>
#include <windows.h>

int brett[9][9];                                                                //Spielfeld anlegen
int mousex=0;                                                                   //globale Variable fuer X-Mauskoordinate
int mousey=0;                                                                   //globale Variable fuer Y-Mauskoordinate

/*brettausgeben()                                                                 //alte original brettausgabe - reicht zum Testen
{
 int i,j;
 printf("--------------------------------------------\n");
 for (j=1;j<=8;j++)
 {
  for (i=1;i<=8;i++)
  {
   printf(" %i",brett[i][j]);
  }
  printf("\n");
 }
}*/

DWORD mouseInit ()                                                              // Initialisiert die Maus und gibt die Anzahl der Maustasten zurück
{
 DWORD mode;
 GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE),&mode);
 SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE),mode|ENABLE_MOUSE_INPUT);
 DWORD buttons;
 GetNumberOfConsoleMouseButtons(&buttons);
 return buttons;
}

void showCursor (bool show = true)                                              // Zeigt oder versteckt den Mauscursor
{
 ShowCursor(show);
}

int im_feld(int x, int y)
{
 int status=0;
 if ((x>=1)&&(x<=8)&&(y>=1)&&(y<=8)) status=1;
 return status;
}

int can_movehoch(int x, int y)                                                  // prüft ob von x.y links/rechts drüber im feld und frei ist
{
 int status=0;
 if (im_feld(x,y)==1)                                                           // x.y  im feld ??
 {
  if (((im_feld(x-1,y-1)==1)||(im_feld(x+1,y-1)==1))                            // mögliches zielfeld im feld ??
      &&((brett[x-1][y-1]==0)||(brett[x+1][y-1]==0)))                             // zielfeld frei ??
     status=1;

 }
 return status;
}

int can_moverunter(int x, int y)                                                // prüft ob von x.y links/rechts drüber im feld und frei ist
{
 int status=0;
 if (im_feld(x,y)==1)                                                           // x.y  im feld ??
 {
  if (((im_feld(x-1,y+1)==1)||(im_feld(x+1,y+1)==1))                            // mögliches zielfeld im feld ??
      &&((brett[x-1][y+1]==0)||(brett[x+1][y+1]==0)))                             // zielfeld frei ??
   status=1;
 }
 return status;
}


int weiterschlagenrunter(int x,int y, int spieler)
{
 int success=0;
 if ((x+2<=8)&&(y+2<=8))                                                        //Zielfeld auf dem Brett ??
 {
  if ((brett[x+2][y+2]==0)
      && ((brett[x+1][y+1]==spieler)||(brett[x+1][y+1]==spieler+2)))
  {
   success=1;                                                                   //kann rechtsunten weiterschlagen
  }
 }
 if ((x-2>=1)&&(y+2<=8))                                                        //Zielfeld auf dem Brett ??
 {
  if ((brett[x-2][y+2]==0)
      && ((brett[x-1][y+1]==spieler)||(brett[x-1][y+1]==(spieler+2))))
  {
   success=1;                                                                   //kann linkssunten weiterschlagen
  }
 }
 return success;
}

int weiterschlagenhoch(int x,int y, int spieler)
{
 int success=0;
 if ((x+2<=8)&&(y-2>=1))                                                        //Zielfeld auf dem Brett ??
 {
  if ((brett[x+2][y-2]==0) && ((brett[x+1][y-1]==spieler)||(brett[x+1][y-1]==(spieler+2))))
  {
   success=1;                                                                   //kann rechtsoben weiterschlagen
  }
 }
 if ((x-2>=1)&&(y-2>=1))                                                        //Zielfeld auf dem Brett ??
 {
  if ((brett[x-2][y-2]==0) && ((brett[x-1][y-1]==spieler)||(brett[x-1][y-1]==(spieler+2))))
  {
   success=1;                                                                   //kann linksoben weiterschlagen
  }
 }
 return success;
}

int gewonnen(int spieler)                                                       //prüft ob gewonnen und spieler #spieler noch ziehn/schlagen kann
{                                                                               //und gibt 0 oder Spielernummer oder 3 für "patt" zurück
 int sieg=0,spieler1_status=0,spieler2_status=0;
 int schwarz_spieler1=0, schwarz_spieler2=0,weiss_spieler1=0, weiss_spieler2=0;
 int i, j;

 for (j=1;j<=8;j++)
 {
  for (i=1;i<=8;i++)
  {
   if (brett[i][j]==1)
   {
    if ((i%2)==(j%2))
       schwarz_spieler1=schwarz_spieler1+1;
    else
       weiss_spieler1=weiss_spieler1+1;
    if ((can_moverunter(i,j)==1)||(weiterschlagenrunter(i,j,1)==1))
       spieler1_status=1;
   }
   if (brett[i][j]==2)
   {
    if ((i%2)==(j%2))
       schwarz_spieler2=schwarz_spieler2+1;
    else
       weiss_spieler2=weiss_spieler2+1;
    if ((can_movehoch(i,j)==1)||(weiterschlagenhoch(i,j,2)==1))
       spieler2_status=1;
   }
   if (brett[i][j]==3)
   {
    if ((i%2)==(j%2))
       schwarz_spieler1=schwarz_spieler1+1;
    else
       weiss_spieler1=weiss_spieler1+1;
    if ((can_moverunter(i,j)==1)||(weiterschlagenrunter(i,j,1)==1)
        ||(can_movehoch(i,j)==1)||(weiterschlagenhoch(i,j,1)==1))
       spieler1_status=1;
   }
   if (brett[i][j]==4)
   {
    if ((i%2)==(j%2))
       schwarz_spieler2=schwarz_spieler2+1;
    else
       weiss_spieler2=weiss_spieler2+1;
    if ((can_moverunter(i,j)==1)||(weiterschlagenrunter(i,j,2)==1)
        ||(can_movehoch(i,j)==1)||(weiterschlagenhoch(i,j,2)==1))
       spieler2_status=1;
   }
  }
 }
 if (((schwarz_spieler1==0)&&(weiss_spieler2==0))                               // nur noch steine auf verschiedenfarbigen feldern? --> unentschieden
      ||((schwarz_spieler2==0)&&(weiss_spieler1==0)))
    sieg=3;
 if (((schwarz_spieler1+weiss_spieler1)==0)||((spieler1_status==0)&&(spieler==2)))
    sieg=2;
 if (((schwarz_spieler2+weiss_spieler2)==0)||((spieler2_status==0)&&(spieler==1)))
    sieg=1;
 return sieg;
}

startbrettbelegen()                                                             //Funktion um Brett vorzubereiten
{
 int i, j;                                                                      //Schleifenvariablen anlegen
 for (j=1;j<=8;j++)
 {
  switch (j)
  {
   case 1:
   case 2:  for (i=1;i<=8;i++)                                                  //obere 2 zeilen mit Spieler1-Steinen fuellen
            {
             brett[i][j]=1;
            }
            break;
   case 3:
   case 4:
   case 5:
   case 6:  for (i=1;i<=8;i++)                                                  //mittlere Zeilen mit "leer" fuellen
            {
             brett[i][j]=0;
            }
            break;
   case 7:
   case 8:  for (i=1;i<=8;i++)                                                  //untere Zeilen mit Spieler2-Steinen fuellen
            {
             brett[i][j]=2;
            }
            break;
   default: break;
  }
 }
 return 0;
}

startbrettbelegen2()                                                             //Funktion um Brett vorzubereiten
{
 int i, j;                                                                      //Schleifenvariablen anlegen
 for (j=1;j<=8;j++)
 {
  switch (j)
  {
   case 1:
   case 3:  for (i=2;i<=8;(i=i+2))                                                  //obere 2 zeilen mit Spieler1-Steinen fuellen
            {
             brett[i][j]=1;
            }
            break;
   case 2: for (i=1;i<=8;(i=i+2))                                                  //obere 2 zeilen mit Spieler1-Steinen fuellen
            {
             brett[i][j]=1;
            }
            break;
   case 4:
   case 5:  for (i=1;i<=8;i++)                                                  //mittlere Zeilen mit "leer" fuellen
            {
             brett[i][j]=0;
            }
            break;
   case 6:
   case 8:  for (i=1;i<=8;(i=i+2))                                                  //untere Zeilen mit Spieler2-Steinen fuellen
            {
             brett[i][j]=2;
            }
            break;
   case 7:  for (i=2;i<=8;(i=i+2))                                                  //untere Zeilen mit Spieler2-Steinen fuellen
            {
             brett[i][j]=2;
            }
            break;
   default: break;
  }
 }
 return 0;
}

int move1(int vx,int vy,int nx,int ny)                                          //Spieler1-Stein "runter" bewegen
{
 int success=0;                                                                 //success auf "Fehler" setzen

 if ((vx>=1)&&(vx<=8)&&(vy>=1)&&(vy<=8)&&(nx>=1)&&(nx<=8)&&(ny>=1)&&(ny<=8))    //Start- UND Zielkoordinaten auf dem Brett ??
 {
  if (brett[vx][vy]==1)                                                         //Spieler1-Stein auf Startfeld (vx,vy) ??
  {
   if (ny==vy+1)                                                                //Spieler1-Stein nach eine Reihe nach unten ??
   {
    if ((nx==vx+1)||(nx==vx-1))                                                 //Spieler1-Stein ein Feld nach links oder rechts ??
    {
     if (brett[nx][ny]==0)                                                      //Zielfeld leer ??
     {
      if (ny==8)                                                                //Spielfeld ueberquert ?? -> Stein wird zu Dame
      {
       brett[vx][vy]=0;
       brett[nx][ny]=3;
      }
      else
      {
       brett[vx][vy]=0;
       brett[nx][ny]=1;
      }
      success=1;                                                                //success auf "erfolgreich" setzen
     }
     else success=14;
    }
    else success=13;
   }
   else success=12;
  }
  else success=11;
 }
 else success=10;
 return success;                                                                //Fehlercode zurückgeben ( Fehler-1 - Erfolgreich )
}

int move2(int vx,int vy,int nx,int ny)                                          //Spieler2-Stein "hoch" bewegen
{
 int success=0;                                                                 //success auf "Fehler" setzen
 if ((vx>=1)&&(vx<=8)&&(vy>=1)&&(vy<=8)&&(nx>=1)&&(nx<=8)&&(ny>=1)&&(ny<=8))    //Start- UND Zielkoordinaten auf dem Brett ??
 {
  if (brett[vx][vy]==2)                                                         //Spieler2-Stein auf Startfeld (vx,vy) ??
  {
   if (ny==vy-1)                                                                //Spieler2-Stein nach eine Reihe nach unten ??
   {
    if ((nx==vx+1)||(nx==vx-1))                                                 //Spieler2-Stein ein Feld nach links oder rechts ??
    {
     if (brett[nx][ny]==0)                                                      //Zielfeld leer ??
     {
      if (ny==1)                                                                //Spielfeld ueberquert ?? -> Stein wird zu Dame
      {
       brett[vx][vy]=0;
       brett[nx][ny]=4;
      }
      else
      {
       brett[vx][vy]=0;
       brett[nx][ny]=2;
      }
      success=1;                                                                //success auf "erfolgreich" setzen
     }
     else success=14;
    }
    else success=13;
   }
   else success=12;
  }
  else success=11;
 }
 else success=10;
 return success;                                                                //Fehlercode zurückgeben ( Fehler-1 - Erfolgreich )
}

int damemove1(int vx,int vy,int nx,int ny)                                      //Spieler1-Dame bewegen
{
 int success=0;                                                                 //success auf "Fehler" setzen
 if ((vx>=1)&&(vx<=8)&&(vy>=1)&&(vy<=8)&&(nx>=1)&&(nx<=8)&&(ny>=1)&&(ny<=8))    //Start- UND Zielkoordinaten auf dem Brett ??
 {
  if (brett[vx][vy]==3)                                                         //Spieler1-Dame auf Startfeld (vx,vy) ??
  {
   if (  ((abs(vx-nx))==1)&&((abs(vy-ny))==1))                                  //Richtung prüfen ((deltaX == deltaY == 1) ??
   {
    if (brett[nx][ny]==0)                                                       //Zielfeld frei?
    {
     brett[vx][vy]=0;
     brett[nx][ny]=3;
     success=1;                                                                 //success auf "erfolgreich" setzen
    }
    else success=24;
   }
   else success=22;
  }
  else success=21;
 }
 else success=20;
 return success;                                                                //Fehlercode zurückgeben ( Fehler-1 - Erfolgreich )
}

int damemove2(int vx,int vy,int nx,int ny)                                      //Spieler2-Dame bewegen
{
 int success=0;                                                                 //success auf "Fehler" setzen
 if ((vx>=1)&&(vx<=8)&&(vy>=1)&&(vy<=8)&&(nx>=1)&&(nx<=8)&&(ny>=1)&&(ny<=8))    //Start- UND Zielkoordinaten auf dem Brett ??
 {
  if (brett[vx][vy]==4)                                                         //Spieler2-Dame auf Startfeld (vx,vy) ??
  {
   if (  ((abs(vx-nx))==1)&&((abs(vy-ny))==1))                                  //Richtung prüfen ((deltaX == deltaY == 1) ??
   {
    if (brett[nx][ny]==0)                                                       //Zielfeld frei?
    {
     brett[vx][vy]=0;
     brett[nx][ny]=4;
     success=1;                                                                 //success auf "erfolgreich" setzen
    }
    else success=24;
   }
   else success=22;
  }
  else success=21;
 }
 else success=20;
 return success;                                                                //Fehlercode zurückgeben ( Fehler-1 - Erfolgreich )
}


int beat1(int vx, int vy, int nx, int ny)
{
 int success=0;                                                                 //success auf "Fehler" setzen
 if ((vx>=1)&&(vx<=8)&&(vy>=1)&&(vy<=8)&&(nx>=1)&&(nx<=8)&&(ny>=1)&&(ny<=8))    //Start- UND Zielkoordinaten auf dem Brett ??
 {
  if (brett[vx][vy]==1)                                                         //Spieler1-Stein auf Startfeld (vx,vy) ??
  {
   if (((ny-vy)==2)&&(abs(nx-vx)==2))
   {
    if ((brett[vx+((nx-vx)/2)][vy+1]==2)||(brett[vx+((nx-vx)/2)][vy+1]==4))
    {
     if (brett[nx][ny]==0)
     {
      if (ny==8)
      {
       brett[vx][vy]=0;
       brett[vx+((nx-vx)/2)][vy+1]=0;                                            //Gegner löschen
       brett[nx][ny]=3;
      }
      else
      {
       brett[vx][vy]=0;
       brett[vx+((nx-vx)/2)][vy+1]=0;                                            //Gegner löschen
       brett[nx][ny]=1;
      }
      if (weiterschlagenrunter(nx,ny, 2)==1)
         success=99;                                 //wenn weiternach unten geschlagen werden kann success auf 99
      else
         success=1;
     }
     else success=34;
    }
    else success=33;
   }
   else success=32;
  }
  else success=31;
 }
 else success=30;
 return success;                                                                //Fehlercode zurückgeben ( Fehler-1 - Erfolgreich )
}

int beat2(int vx, int vy, int nx, int ny)
{
 int success=0;                                                                 //success auf "Fehler" setzen
 if ((vx>=1)&&(vx<=8)&&(vy>=1)&&(vy<=8)&&(nx>=1)&&(nx<=8)&&(ny>=1)&&(ny<=8))    //Start- UND Zielkoordinaten auf dem Brett ??
 {
  if (brett[vx][vy]==2)                                                         //Spieler2-Stein auf Startfeld (vx,vy) ??
  {
   if (((ny-vy)==-2)&&(abs(nx-vx)==2))
   {
    if ((brett[vx+((nx-vx)/2)][vy-1]==1)||(brett[vx+((nx-vx)/2)][vy-1]==3))
    {
     if (brett[nx][ny]==0)
     {
      if (ny==1)
      {
       brett[vx][vy]=0;
       brett[vx+((nx-vx)/2)][vy-1]=0;                                            //Gegner löschen
       brett[nx][ny]=4;
      }
      else
      {
       brett[vx][vy]=0;
       brett[vx+((nx-vx)/2)][vy-1]=0;                                            //Gegner löschen
       brett[nx][ny]=2;
      }
      if (weiterschlagenhoch(nx,ny, 1)==1)
         success=99;                                                             //wenn weiternach oben geschlagen werden kann -> success auf 99
      else
         success=1;
     }
     else success=34;
    }
    else success=33;
   }
   else success=32;
  }
  else success=31;
 }
 else success=30;
 return success;                                                                //Fehlercode zurückgeben ( Fehler-1 - Erfolgreich )
}

int damebeat1(int vx, int vy, int nx, int ny)                                   //als Spieler1-Dame schlage ausführen
{
 int success=0;
 if ((vx>=1)&&(vx<=8)&&(vy>=1)&&(vy<=8)&&(nx>=1)&&(nx<=8)&&(ny>=1)&&(ny<=8))
 {
  if (brett[vx][vy]==3)
  {
   if ((brett[vx+((nx-vx)/2)][vy+((ny-vy)/2)]==2)
       ||(brett[vx+((nx-vx)/2)][vy+((ny-vy)/2)]==4))
   {
    if (brett[nx][ny]==0)
    {
     brett[vx][vy]=0;
     brett[vx+((nx-vx)/2)][vy+((ny-vy)/2)]=0;
     brett[nx][ny]=3;
     if ((weiterschlagenrunter(nx,ny, 2)==1)||(weiterschlagenhoch(nx,ny, 2)==1))
     {
      success=99;
     }
     else success=1;
    }
    else success=43;
   }
   else success=42;
  }
  else success=41;
 }
 else success=40;
 return success;
}

int damebeat2(int vx, int vy, int nx, int ny)                                   //als Spieler2-Dame schlage ausführen
{
 int success=0;
 if ((vx>=1)&&(vx<=8)&&(vy>=1)&&(vy<=8)&&(nx>=1)&&(nx<=8)&&(ny>=1)&&(ny<=8))
 {
  if (brett[vx][vy]==4)
  {
   if ((brett[vx+((nx-vx)/2)][vy+((ny-vy)/2)]==1)
        ||(brett[vx+((nx-vx)/2)][vy+((ny-vy)/2)]==3))
   {
    if (brett[nx][ny]==0)
    {
     brett[vx][vy]=0;
     brett[vx+((nx-vx)/2)][vy+((ny-vy)/2)]=0;
     brett[nx][ny]=4;
     if ((weiterschlagenrunter(nx,ny, 1)==1)||(weiterschlagenhoch(nx,ny, 1)==1))
     {
      success=99;
     }
     else success=1;
    }
    else success=43;
   }
   else success=42;
  }
  else success=41;
 }
 else success=40;
 return success;
}

int move_all(int vx, int vy, int nx, int ny, int spieler)                       //diese funtion wird aus main aufgerufen, ruft dann die intern nötige
{                                                                               //move- oder beat-Funktionen auf
 int returncode=0, zugart=0;
 if ((abs(vx-nx)==1)&&(abs(vy-ny)==1))
    zugart=brett[vx][vy];
 else
 if ((abs(vx-nx)==2)&&(abs(vy-ny)==2))
    zugart=(brett[vx][vy]+4);
 if (spieler==2)
 {
  switch (zugart)
  {
  case 1:  returncode=0;
           break;
  case 2:  returncode=move2(vx,vy,nx,ny);
           break;
  case 3:  returncode=0;
           break;
  case 4:  returncode=damemove2(vx,vy,nx,ny);
           break;
  case 5:  returncode=0;
           break;
  case 6:  returncode=beat2(vx,vy,nx,ny);
           break;
  case 7:  returncode=0;
           break;
  case 8:  returncode=damebeat2(vx,vy,nx,ny);
           break;
  default: break;
  }
 }
 else
 {
  switch (zugart)
  {
  case 1:  returncode=move1(vx,vy,nx,ny);
           break;
  case 2:  returncode=0;
           break;
  case 3:  returncode=damemove1(vx,vy,nx,ny);
           break;
  case 4:  returncode=0;
           break;
  case 5:  returncode=beat1(vx,vy,nx,ny);
           break;
  case 6:  returncode=0;
           break;
  case 7:  returncode=damebeat1(vx,vy,nx,ny);
           break;
  case 8:  returncode=0;
           break;
  default: break;
  }
 }
 return returncode;
}

int getmouselxy()                                                               // schreibt Maus-Koordinaten bei Linksklick nach mousex und mousey
{
 mouseInit();
 showCursor();
 bool running = true;
 do
 {
  DWORD count;
  INPUT_RECORD ir;
  ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE),&ir,1,&count);
  switch(ir.EventType)
  {
   case MOUSE_EVENT:
        if(ir.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
        {
         mousex=ir.Event.MouseEvent.dwMousePosition.X;
         mousey=ir.Event.MouseEvent.dwMousePosition.Y;
         running = false;
        }
        break;
  }
 }
 while(running);
 return 1;
}

int getmouserxy()                                                               // schreibt Maus-Koordinaten bei Rechtsklick nach mousex und mousey
{
 mouseInit();
 showCursor();
 bool running = true;
 do
 {
  DWORD count;
  INPUT_RECORD ir;
  ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE),&ir,1,&count);
  switch(ir.EventType)
  {
   case MOUSE_EVENT:
        if(ir.Event.MouseEvent.dwButtonState & RIGHTMOST_BUTTON_PRESSED)
        {
         mousex=ir.Event.MouseEvent.dwMousePosition.X;
         mousey=ir.Event.MouseEvent.dwMousePosition.Y;
         running = false;
        }
        break;
  }
 }
 while(running);
 return 1;
}

bool exit_klick()
{
 char jein='?';
 bool status=false;
 int button_x1=64;
 int button_x2=74;
 int button_y1=2;
 int button_y2=4;
 if ((mousex>=button_x1)&&(mousex<=button_x2)
    &&(mousey>=button_y1)&&(mousey<=button_y2))
    {
     gotoxy(50,20);
     printf("Wirklich Beenden (j): ");
     jein=getche();
     switch(jein)
     {
      case 'j':
      case 'J': gotoxy(50,20);
                printf ("                          ");
                status=true;
                gotoxy(80,25);
                break;
      default:  gotoxy(50,20);
                printf ("                          ");
                gotoxy(80,25);
                break;
     }
    }
 return status;
}

bool muss_schlagen(int spieler)
{
 int x,y;
 bool status=false;
 int figur;



 for (y=1;y<=8;y++)
 {
  for (x=1;x<=8;x++)
  {
   figur=brett[x][y];
   if (spieler==1)
   {
    switch (figur)
    {
     case 1: if (weiterschlagenrunter(x,y,2)==1)
                status=true;
             break;
     case 3: if ((weiterschlagenhoch(x,y,2)==1)||(weiterschlagenrunter(x,y,2)==1))
                status=true;
             break;
     default: break;
    }
   }
   if (spieler==2)
   {
    switch (figur)
    {
     case 2: if (weiterschlagenhoch(x,y,1)==1)
                status=true;
             break;
     case 4: if ((weiterschlagenhoch(x,y,1)==1)||(weiterschlagenrunter(x,y,1)==1))
                status=true;
             break;
     default: break;
    }
   }
  }
 }
 return status;
}