void main(void){
//Primer fem les inicialitzacions bàsiques del LCD
 baseInit();
 LCD_Init();
 initAccel();
//Netejem el display
 LCD_ClearDisplay();
 LCD_Config(1,0,0);
 int n=10;
 int pos=16;
 //Inicialitzem els vectors on guardarem els valors de x i y
 int32_t vector_media_x[n];
 int32_t vector_media_y[n];
 int32_t dist_x[pos];
 int32_t dist_y[pos];

//Inicialitzem els valors limit de x e y, que hem calculat experimentalment
 int32_t minY=-40;//Acceleració quan inclinem -45º en y
 int32_t maxY=45 ;//Acceleració quan inclinem 45º en y
 int32_t minX=-42;//Acceleració quan inclinem -45º en x
 int32_t maxX=48 ;//Acceleració quan inclinem 45º en x
 int32_t media_x=0;
 int32_t media_y=0;

//Imprimim al centre de la pantalla del LCD (aquest té 16 posicions) els asteriscs inicials
 SLEEP_MS(10);
 LCD_GotoXY(8,0);
 SLEEP_MS(10);
 LCD_SendChar('*');
 SLEEP_MS(10);
 LCD_GotoXY(8,1);
 SLEEP_MS(10);
 LCD_SendChar('*');
 int i;
 //Llegim els valors inicials de y i de x, per tal de usarlos com a referència
  int32_t x_inicial = readAccel(0x29,1);
  int32_t y_inicial = readAccel(0x2B,1);

  //Per inicialitzar els vectors de mitjana, fem un for assignant-lis el valor inicial
 for(i=0;i<n; i++){
 vector_media_x[i]=x_inicial;
 vector_media_y[i]=y_inicial;
 }

  //En el següent bucle, el que fem és distribuir uniformement els valors d'accelarció
 //a l'esquerra es troba el valor de minima acceleració i a la dreta el de màxima
  for(i=0; i<8; i++){
	  dist_x[i]= ((x_inicial - minX) / 8) * i + minX;
	  dist_x[pos - i-1]= maxX - (maxX-x_inicial) / 8 * i;
	  dist_y[i]= (y_inicial - minY) / 8 * i + minY;
	  dist_y[pos- i-1]= maxY - (maxY-y_inicial) / 8 * i;
  }
  dist_x[8]=x_inicial;
  dist_y[8]=y_inicial;
//Fem una espera perquè doni temps al ull humà a veure-ho
  SLEEP_MS(500);
  LCD_ClearDisplay();

  while(1) {

  SLEEP_MS(100);
  LCD_ClearDisplay();
//Ara tornem a llegir dades de l'accelerometre (en aquest cas del eix X)
  int32_t x = readAccel(0x29,1);
  SLEEP_MS(10);
  media_x=0;
//Introduim aquest nou valor llegit en el vector de mitjanes
  for(i=0; i<= n-2; i++){
  vector_media_x[i]=vector_media_x[i+1];
  media_x=media_x+vector_media_x[i];
  }
  vector_media_x[n-1]=x;
  media_x=(media_x+x) /n;
	  //Busquem la posició en la qual hauriem de col#locar-lo
  int k=0;
  while (((k+1)<= pos) && media_x>dist_x[k+1] ){
  k++;
  }
 //Posem el asterisc a la posició que pertoca
  LCD_Config(1,0,0); //Desconnectem el cursor
  LCD_GotoXY(k,0);
  SLEEP_MS(10);
  LCD_SendChar('*'); 
 //Fem el mateix procediment però aquest cop per la Y
  int32_t y = readAccel(0x2B,1);
  SLEEP_MS(10);
  media_y=0;
  for(i=0; i<= n-2; i++){
  vector_media_y[i]=vector_media_y[i+1];
  media_y=media_y+vector_media_y[i];
  }
  vector_media_y[n-1]=y;
  media_y=(media_y+y) /n;

   int j=0;
   while ((j+1)<= pos && media_y>dist_y[j+1] ){
   j++;
   }
   LCD_Config(1,0,0);
   LCD_GotoXY(j+1,1);
   SLEEP_MS(10);
   LCD_SendChar('*');
   }
  }





