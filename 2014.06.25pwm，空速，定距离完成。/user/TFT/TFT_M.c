#include "TFT_M.h"


u8 Menu_Sign=0,Menu_Step=0;

void TFT_Touch_Deal(u16 x,u16 y)
{
	 if(Menu_Step==0)
	 {
		 
		 if(But3_Deal(x,y,1)){ Menu_Step=1; Menu_Sign=0;}
		 else if(But3_Deal(x,y,2)){ Menu_Step=1; Menu_Sign=1;M1_S1_P();}
		 else if(But3_Deal(x,y,3)){ Menu_Step=1; Menu_Sign=2;M1_S2_P();}
		 else if(But3_Deal(x,y,4)){ Menu_Step=1; Menu_Sign=3;M1_S3_P();}
		 else if(But3_Deal(x,y,5)){ Menu_Step=1; Menu_Sign=4;M1_S4_P();}
		 else if(But3_Deal(x,y,6)){ Menu_Step=1; Menu_Sign=5;}
		 else if(But3_Deal(x,y,7)){ Menu_Step=1; Menu_Sign=6;}
		 else if(But3_Deal(x,y,8)){ Menu_Step=1; Menu_Sign=7;}
		 else if(But3_Deal(x,y,9)){ Menu_Step=1; Menu_Sign=8;}
   }
	 else if(Menu_Step==1)
	 {
			if(Menu_Sign==0){}
			else if(Menu_Sign==1){M1_S1(x,y);}
			else if(Menu_Sign==2){M1_S2(x,y);}
			else if(Menu_Sign==3){M1_S3(x,y);}
			else if(Menu_Sign==4){M1_S4(x,y);}
			else if(Menu_Sign==5){}
			else if(Menu_Sign==6){}
			else if(Menu_Sign==7){}
		  else if(Menu_Sign==8){}
			
		  if(But3_Deal(x,y,0)){Menu_Sign=0,Menu_Step=0; M_S0(); }
   }
	 
	 //M_S0(10);
	 TFT_Show_Num1(5,0,Menu_Step,1,0x0);
	 TFT_Show_Num1(15,0,Menu_Sign,1,0x0);
	 
	 TFT_Show_Num1(25,0,x,4,0x0);
	 TFT_Show_Num1(50,0,y,4,0x0);
	  
}

void Creat_All(void)
{
	  //界面
	    TFT_Show_Num(200,70 ,leng,4,0x0,0xffff);// 起始横坐标纵坐标，数字，长度，颜色1，颜色2
	    Creat_Buuton_3(0,300,60,20,0x3333,"Return",0x1111,"Return",0);// 返回用
//	
	    Creat_Buuton_3(0,0,240,30,0xf0f0,"  ",0xf45f,"  ",1);
			Creat_Buuton_3(10,40,105,130,0x1111,"Ce_Shi",0x4774,"In 1",2);
			Creat_Buuton_3(125,40,105,130,0x2222,"ANg_Q",0x3773,"In 2",3);
			Creat_Buuton_3(10,180,105,130,0x3333,"Inter3",0x2772,"In 3",4);
			Creat_Buuton_3(125,180,105,130,0x4444,"Inter4",0x1771,"In 4",5);

	  /*   第一层  */  
			Creat_Buuton_2(35,40,0xf45f,"M0 On",0x2345,"M0OFF",1,0);
			Creat_Buuton_2(140,40,0xf45f,"M1 On",0x2345,"M1OFF",1,1);
			Creat_Buuton_2(35,70,0x1111,"M2 On",0x5555,"M2OFF",1,2);
			Creat_Buuton_2(140,70,0x1111,"M3 On",0x5555,"M3OFF",1,3);
		
			Creat_Buuton_0(70,110,"M:",0,1500,MaxMM,10,0);  // 长100
			
			Creat_Sq(10,150,190,24,0,MaxMM,0,0);
			Creat_Sq(10,180,190,24,MinPWM,MinPWM+MaxMM,MinPWM,1);//调占空比
			Creat_Sq(10,210,190,24,MinPWM,MinPWM+MaxMM,MinPWM,2);
			Creat_Sq(10,240,190,24,MinPWM,MinPWM+MaxMM,MinPWM,3);
			Creat_Sq(10,270,190,24,MinPWM,MinPWM+MaxMM,MinPWM,4);
	
//	  /*   第二层  */
//	
			Creat_Buuton_2(20,90,0xf45f,"Ad_0",0x2345,"Wait",1,4);
			Creat_Buuton_2(20,115,0x3333,"MON",0x7777,"MOFF",0,5);
			Creat_Buuton_0(5,140,"PA:",0,300,A,1,1);  // 长100
			Creat_Buuton_0(5,180,"PB:",0,200,B,1,2);  // 长100
			Creat_Buuton_0(5,220,"PC:",0,100,C,1,3);  // 长100
			Creat_Buuton_0(5,260,"M0:",0,5,1,AdAng,4);  // 长100

//		/* 第三层 */

      Creat_Buuton_0(138,57,"B0:",7,70,10,2,5);
			Creat_Buuton_0(138,117,"B1:",7,70,10,2,6);
			Creat_Buuton_0(138,177,"B2:",7,70,10,2,7);
			Creat_Buuton_0(138,237,"B3:",7,70,10,2,8);
			
      Creat_Sq(5,60,100,24,0,50,0,5);
			Creat_Sq(5,120,100,24,0,50,0,6);
			Creat_Sq(5,180,100,24,0,50,0,7);
			Creat_Sq(5,240,100,24,0,50,0,8);

//	  Creat_Sq(10,270,190,24,0,1000,300,4);
	  //Creat_PWindow(10,15,120,120,"WinX:",0x9999,1,30,0x7777,0x0,800,0);
		//Creat_PWindow(10,160,120,120,"WinY:",0x3333,1,30,0x9999,0xf45f,800,1);
//		
//		/* 第四层 */
      Creat_PWindow(10,15,120,120,"WinX:",0x9999,1,30,0x7777,0x0,800,0);
		  Creat_PWindow(10,160,120,120,"WinY:",0x3333,1,30,0x9999,0xf45f,800,1);
//		Creat_Sq(5,200,200,20,1,10000,20,4);
//		Creat_Sq(5,250,200,20,1,10000,300,5);
//		Creat_Buuton_0(5,150,"B04:",1,10000,20,1,4);  // 长100 宽31
//		
		M_S0();
	  
}
void M_S0(void)
{
	My_TFT_Sq(0,30,240,290,0xffff);
	Dorw_But3(1);
	Dorw_But3(2);
	Dorw_But3(3);
	Dorw_But3(4);
	Dorw_But3(5);
}
void M1_S1_P(void)
{	  
	  
	  My_TFT_Sq(0,0,240,320,0xffff);
	  Dorw_But3(0);  // 返回用
	 // Dorw_But3(3);
	  
	  Dorw_But2(0);
		Dorw_But2(1);
		Dorw_But2(2);
		Dorw_But2(3);
	  Dorw_But0(0);
 	
	  Dorw_Slider(0);
	  Dorw_Slider(1);
	  Dorw_Slider(2);
	  Dorw_Slider(3);
	  Dorw_Slider(4);
}
void M1_S2_P(void)
{	  
	  My_TFT_Sq(0,0,240,320,0xffff);
	  Dorw_But3(0);  // 返回用
	  
	  Dorw_But0(1);
		Dorw_But0(2);
		Dorw_But0(3);
		Dorw_But0(4);
	  Dorw_But2(4);
	  Dorw_But2(5);
	
		TFT_Sq_Str(0,30,40,24,"Angx:",0x0,0x3333);
		TFT_Sq_Str(0,60,40,24,"AngY:",0x0,0x3333);
}
void M1_S3_P(void)
{	
	  My_TFT_Sq(0,0,240,320,0xffff);
	  Dorw_But3(0);  // 返回用
	 // Dorw_But3(3);
	
	  Dorw_But0(5);
		Dorw_But0(6);
		Dorw_But0(7);
		Dorw_But0(8);
	  Dorw_Slider(5);
	  Dorw_Slider(6);
	  Dorw_Slider(7);
	  Dorw_Slider(8);
}
void M1_S4_P(void)
{	
    My_TFT_Sq(0,0,240,320,0xffff);
	  Dorw_But3(0);  // 返回用
	  //Dorw_But3(3);
	  
	  Drow_PWindow(0);
	  Drow_PWindow(1);
}
void M1_S1(u16 x,u16 y)
{
		static u16 Lastpmm,Lastmaxpmm;
		static u8 m0,m1,m2,m3;

		m0=But2_Deal(x,y,0);
		m1=But2_Deal(x,y,1);
		m2=But2_Deal(x,y,2);
		m3=But2_Deal(x,y,3);
		Lastmaxpmm=But0_Deal(x,y,0);

		if(!m0){Slider_Updat(MinPWM,1);PM1=MinPWM;}
		if(!m1){Slider_Updat(MinPWM,2);PM2=MinPWM;}
		if(!m2){Slider_Updat(MinPWM,3);PM3=MinPWM;}
		if(!m3){Slider_Updat(MinPWM,4);PM4=MinPWM;}

		if(MaxMM!=Lastmaxpmm)
		{
				MaxMM=Lastmaxpmm;
			  //MaxPWM=MinPWM+MaxMM;
				Creat_Sq(10,150,190,24,0,MaxMM,0,0);
				Creat_Sq(10,180,190,24,MinPWM,MinPWM+MaxMM,MinPWM,1);
				Creat_Sq(10,210,190,24,MinPWM,MinPWM+MaxMM,MinPWM,2);
				Creat_Sq(10,240,190,24,MinPWM,MinPWM+MaxMM,MinPWM,3);
				Creat_Sq(10,270,190,24,MinPWM,MinPWM+MaxMM,MinPWM,4);
		}
		Lastpmm=Adjust_Slider(x,y,0);
		if(PMM!=Lastpmm)
		{
			  PMM=Lastpmm;
			  if(m0){PM1=MinPWM+PMM;Slider_Updat(PM1,1);}
				if(m1){PM2=MinPWM+PMM;Slider_Updat(PM2,2);}
				if(m2){PM3=MinPWM+PMM;Slider_Updat(PM3,3);}
				if(m3){PM4=MinPWM+PMM;Slider_Updat(PM4,4);}
		}

		if(m0)PM1=Adjust_Slider(x,y,1);
		if(m1)PM2=Adjust_Slider(x,y,2);
		if(m2)PM3=Adjust_Slider(x,y,3);
		if(m3)PM4=Adjust_Slider(x,y,4);


		//printf(" %d %d %d %d\r\n ",m0,m1,m2,m3);
		//printf(" %d %d %d %d\r\n ",PM1,PM2,PM3,PM4);
}

void M1_S2(u16 x,u16 y)
{
//	 u32 a0;
	 A=But0_Deal(x,y,1);
	 B=But0_Deal(x,y,2);
	 C=But0_Deal(x,y,3);
	 ShowMode=But0_Deal(x,y,4);
	 AdAng=But2_Deal(x,y,4);
	 MON=But2_Deal(x,y,5);

	 M1_S2_m00();
	//printf(" MON=%d\r\n ",MON);
}
void M1_S3(u16 x,u16 y)
{
	  But0_Deal(x,y,5);
		But0_Deal(x,y,6);
		But0_Deal(x,y,7);
		But0_Deal(x,y,8);
	  AngX=Adjust_Slider(x,y,5);
	  Adjust_Slider(x,y,6);
	  Adjust_Slider(x,y,7);
	  Adjust_Slider(x,y,8);
	// Adjust_Window(x,y,0);
}
void M1_S4(u16 x,u16 y)
{
	  //static u16 dat=300;
	
//	  Slider_Updat(PWM4,4);
//	  PWM4=Adjust_Slider(x,y,4);
//	  Slider_Updat(PWM4,5);
//	  PWM4=Adjust_Slider(x,y,5);
//	  But0_Updat(PWM4,4);
//	  PWM4=But0_Deal(x,y,4);
}
void M1_S2_m00(void) 
{
	  if(ShowMode==0 || ShowMode==2 )  // 选中 X
		{
			  TFT_Sq_Str(0,30,40,24,"Angx:",0xf100,0x3333);
			  TFT_Sq_Str(0,60,40,24,"AngY:",0x0,0x3333);
    }
		if(ShowMode==1 || ShowMode==3 )   // 选中 Y
		{
			  TFT_Sq_Str(0,30,40,24,"Angx:",0x0,0x3333);
			  TFT_Sq_Str(0,60,40,24,"AngY:",0xf100,0x3333);
    }
		if(ShowMode==4 )   // 选中 Y
		{
			  TFT_Sq_Str(0,30,40,24,"Angx:",0xf100,0x3333);
			  TFT_Sq_Str(0,60,40,24,"AngY:",0xf100,0x3333);
    }
}
void M1_S2_m0(void)
{
	   u16 t;

	   if(stic>60)
		 {
			 stic=0;
			
//			  printf(" %f %f \r\n",qx+1,qy+3);
//		   TFT_ShowString(100,50,"qx:",0x0,0xffff);
//			 My_TFT_Sq(120,50,30,20,0xffff);		
//			// TFT_Show_Num(120,50,q0,4,0x0,0xffff);
//			 
//			 TFT_ShowString(150,50,"qy:",0x0,0xffff);
//			 My_TFT_Sq(170,50,30,20,0xffff);
//			 TFT_Show_Float2(170,50,qy,1,8,0x0);
			 //TFT_Show_Num(170,50,q1,4,0x0,0xffff);
			
			 TFT_ShowString(120,50,"m1:",0x0,0xffff);
			 TFT_Show_Num(140,50,PM1,4,0x0,0xffff);			 
			 TFT_ShowString(170,50,"m3:",0x0,0xffff);
			 TFT_Show_Num(190,50,PM3,4,0x0,0xffff);
			 
			 TFT_ShowString(120,70,"m4:",0x0,0xffff);
			 TFT_Show_Num(140,70,PM4,4,0x0,0xffff);			 
			 TFT_ShowString(170,70,"m2:",0x0,0xffff);
			 TFT_Show_Num(190,70,PM2,4,0x0,0xffff);
			 
			 TFT_Sq_Float1(40,30,55,24,comx,2,7,0xf100,0x3333); 
			 TFT_Sq_Float1(40,60,55,24,comy,2,7,0xf100,0x3333);
	
		 }else stic++;
	 
		 
		 if(ShowMode==0)
		 {			  					 
				for(t=0;t<100;t++){TFT_DrawPoint(110+t,160-picda_0[t],0xffff);}	
				for(t=99;t>0;t--){picda_0[t]=picda_0[t-1];}								    
				picda_0[0]=(int)(comx*10);					        //
				for(t=0;t<100;t++){TFT_DrawPoint(110+t,160-picda_0[t],0xF810);}
		 }
		 else if(ShowMode==1)
		 {
				for(t=0;t<100;t++){TFT_DrawPoint(110+t,160-picda_0[t],0xffff);}	
				for(t=99;t>0;t--){picda_0[t]=picda_0[t-1];}								    
				picda_0[0]=(int)(qx/2);					        //
				for(t=0;t<100;t++){TFT_DrawPoint(110+t,160-picda_0[t],0xF810);}
		 }
		 else if(ShowMode==2)
		 {
				for(t=0;t<100;t++){TFT_DrawPoint(110+t,160-picda_0[t],0xffff);}	
				for(t=99;t>0;t--){picda_0[t]=picda_0[t-1];}								    
				picda_0[0]=(int)(angx*10);					        //
				for(t=0;t<100;t++){TFT_DrawPoint(110+t,160-picda_0[t],0xF810);}
				
				for(t=0;t<100;t++){TFT_DrawPoint(110+t,160-picda_1[t],0xffff);}	
				for(t=99;t>0;t--){picda_1[t]=picda_1[t-1];}								    
				picda_1[0]=(int)(comx*10);					        //
				for(t=0;t<100;t++){TFT_DrawPoint(110+t,160-picda_1[t],0x0);}
		 }
		 else if(ShowMode==3)
		 {
				for(t=0;t<100;t++){TFT_DrawPoint(110+t,160-picda_0[t],0xffff);}	
				for(t=99;t>0;t--){picda_0[t]=picda_0[t-1];}								    
				picda_0[0]=(int)(angy*10);					        //
				for(t=0;t<100;t++){TFT_DrawPoint(110+t,160-picda_0[t],0xF810);}
				
				for(t=0;t<100;t++){TFT_DrawPoint(110+t,160-picda_1[t],0xffff);}	
				for(t=99;t>0;t--){picda_1[t]=picda_1[t-1];}								    
				picda_1[0]=(int)(comy*10);					        //
				for(t=0;t<100;t++){TFT_DrawPoint(110+t,160-picda_1[t],0x0);}
		 }
		 else if(ShowMode==4)
		 {
				for(t=0;t<100;t++){TFT_DrawPoint(110+t,160-picda_0[t],0xffff);}	
				for(t=99;t>0;t--){picda_0[t]=picda_0[t-1];}								    
				picda_0[0]=(int)(comx*10);					        //
				for(t=0;t<100;t++){TFT_DrawPoint(110+t,160-picda_0[t],0xF810);}
				
				for(t=0;t<100;t++){TFT_DrawPoint(110+t,160-picda_1[t],0xffff);}	
				for(t=99;t>0;t--){picda_1[t]=picda_1[t-1];}								    
				picda_1[0]=(int)(comy*10);					        //
				for(t=0;t<100;t++){TFT_DrawPoint(110+t,160-picda_1[t],0x0);}
		 }
		 else if(ShowMode==5)
		 {
			  MON=0;Motor_PWM(MinPWM,MinPWM,MinPWM,MinPWM);
		 }

}
