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
 //
  for(i=0; i<8; i++){
	  dist_x[i]= ((x_inicial - minX) / 8) * i + minX;
	  dist_x[pos - i-1]= maxX - (maxX-x_inicial) / 8 * i;
	  dist_y[i]= (y_inicial - minY) / 8 * i + minY;
	  dist_y[pos- i-1]= maxY - (maxY-y_inicial) / 8 * i;
  }
  dist_x[8]=x_inicial;
  dist_y[8]=y_inicial;

  SLEEP_MS(500);
  LCD_ClearDisplay();

  while(1) {

  SLEEP_MS(100);
  LCD_ClearDisplay();

  int32_t x = readAccel(0x29,1);
  SLEEP_MS(10);
  media_x=0;
  for(i=0; i<= n-2; i++){
  vector_media_x[i]=vector_media_x[i+1];
  media_x=media_x+vector_media_x[i];
  }
  vector_media_x[n-1]=x;
  media_x=(media_x+x) /n;
  int k=0;
  while (((k+1)<= pos) && media_x>dist_x[k+1] ){
  k++;
  }
  LCD_Config(1,0,0);
  LCD_GotoXY(k+1,0);
  SLEEP_MS(10);
  LCD_SendChar('*');


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
  }*/




/*int main(void) {
	int32_t val, x, y;
    baseInit();
    LCD_Init();
    initAccel();
    val = writeAccel(0x20,6,1);
    LCD_ClearDisplay();
    LCD_Config(1,0,0);

//Fins aqui fem una inicialitzacio basica del LCD

    x = readAccel(0x29,1);
    y = readAccel(0x2B,1);

    LCD_GotoXY(3,0);
    LCD_SendString("*");
    LCD_GotoXY(7,1);
    LCD_SendString("*");
    while(1){
    	SLEEP_MS(500);
    	LCD_ClearDisplay();
    	x = readAccel(0x29,1);
    	y = readAccel(0x2B,1);
    	if(x>8){
    		x=8;
    	}
    	else if(x<-7){
    		x=-7;
    	}
    	if(y>8){
    		y=8;
    	}else if(y<-7){
    		y=-7;
    	}
    	x = x+7;
    	y = y+7;
    	LCD_GotoXY(x,0);
        LCD_SendString("*");
        DELAY_US(200);
        LCD_GotoXY(y,1);
        LCD_SendString("*");
    }
    return 0;
}*/

/*^
 const char smile[8] = {0b00000000,0b00001010,0b00001010,0b00001010,0b00000000,0b00010001,0b00001110,0b00000000,};
 */
/*
 baseInit(); // Basic initialization
	LCD_Init(); // Program the GPIO I/O lines

	LCD_Backlight(1);
	SLEEP_MS(1000);
	LCD_Backlight(0);

	SLEEP_MS(1000);
	LCD_ClearDisplay();
	SLEEP_MS(1000);

	LCD_SendString("David Fornos");
	SLEEP_MS(1000);
	LCD_GotoXY(0,1);
	LCD_SendString("Alex Melendez");
	LCD_Config(1,0,1);
	SLEEP_MS(1000);
	LCD_ClearDisplay();
	LCD_Config(1,0,0);

	while (1);
	return 0;
 