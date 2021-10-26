
int main(void){
 baseInit();
 LCD_Init();
 initAccel();
 LCD_ClearDisplay();

 int32_t x_inicial = readAccel(0x29, 1);
 int32_t y_inicial = readAccel(0x2b, 1);

 LCD_GotoXY(7,0);
 LCD_SendString("*");

 LCD_GotoXY(7,1);
 LCD_SendString("*");

 LCD_Config(1,0,0);

 int32_t val_max_x = 60;
 int32_t val_min_x = -55;
 int32_t val_max_y = 53;
 int32_t val_min_y = -56;
 int32_t x,y;

while(1){

	x = readAccel(0x29, 1);
	y = readAccel(0x2b, 1);

	x = x - x_inicial;
	y = y - y_inicial;

	SLEEP_MS(100);

	LCD_ClearDisplay();
	SLEEP_MS(100);

	if(x<=val_max_x || x>=val_min_x){

		LCD_GotoXY((x*7/val_max_x)+7,0);

	}else if(x>val_max_x){

		LCD_GotoXY(15,0);
	}else if(x<val_min_x){

		LCD_GotoXY(0,0);
	}
	LCD_SendString("*");

	if(y<=val_max_y || y>=val_min_y){

		LCD_GotoXY((y*7/val_max_y)+7,1);

	}else if(y>val_max_y){

		LCD_GotoXY(15,1);

	}else if(y<val_min_y){

		LCD_GotoXY(0,1);
	}
	LCD_SendString("*");
}
 }
