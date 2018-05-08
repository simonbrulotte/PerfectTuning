

/**
 * @file demo.c
 * @Author Simon Brulotte
 * @Brief  Ce fichier contient l'interface graphique pour le projet
 */

/*********************
 *      INCLUDES
 *********************/
#include "demo.h"
#include <stm32f769i_discovery_ts.h>
#include "ledDriver.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lv_conf.h"
#include <math.h>
/*********************
 *      DEFINES
 *********************/


#define ctnPrincipal_init_ver_gap (LV_VER_RES-(ctnPrincipal_nbBtn*(ctnPrinc_btnGap+ctnPrinc_btnHeight)))/2
#define ctnPrincipal_nbBtn 3
#define ctnPrinc_btnGap 20

#define ctnPrinc_btnHeight 60
#define ctnPrinc_btnWitdh 200
#define ctnPrinc_btnTotalDst (ctnPrinc_btnHeight+ctnPrinc_btnGap)

#define ctnNORTH LV_VER_RES
#define ctnSUD -(LV_VER_RES)
#define ctnOUEST -(LV_HOR_RES)
#define ctnEST LV_HOR_RES

#define delay_anim_nop 150

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

void Parametres(void);
void slide_container(lv_obj_t * actual_ctn,lv_obj_t * next_ctn);
void switch_window(lv_obj_t * actual,lv_obj_t * next);
static lv_res_t click_Parametres(lv_obj_t * child);
static lv_res_t click_Parametres_DEL(lv_obj_t * child);
void click_Parametres_GAUGE(lv_obj_t * child);
void click_Back(lv_obj_t * child);
static lv_res_t action_switch_LED (lv_obj_t * child);
static lv_res_t actionSlider(lv_obj_t * slider);

/**********************
 *  STATIC VARIABLES
 **********************/


/**********************
 *  Global VARIABLES
 **********************/

uint8_t val_SliderR=0;
uint8_t val_SliderG=0;
uint8_t val_SliderB=0;
uint8_t val_SliderI=0;
int delay_anim = 0;
int level = 0;

bool led_flag=false;

lv_obj_t * Actual_ctn;
lv_obj_t * label;
//containers

lv_obj_t * ctnParametre;
lv_obj_t * ctnPrincipal;
lv_obj_t * ctnGauge;
lv_obj_t * ctnParamLED;
lv_obj_t * ctnParamGAUGE;


//composant de la page d'acceuil
lv_obj_t * btnParametre;
lv_obj_t * btnGauges;
lv_obj_t * btnVehicule;
lv_obj_t * btnLock;
lv_obj_t * btnUnlock;

//composants de la page param�tres DEL
lv_obj_t * sliderR;
lv_obj_t * sliderG;
lv_obj_t * sliderB;
lv_obj_t * sliderI;
lv_obj_t * toggleOnOff;
lv_obj_t * label_toggle;

//composants de la page param�tres TUNING

lv_obj_t * param_tuning_gauge;
lv_obj_t * btn_tuning_Retour;
lv_obj_t * btn_tuning_Apply;


//composant de la page V�hicule

lv_obj_t * btn_ctnvehicule_Start;

//lv_obj_t * ctnUnlock;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void demo2_create()
{
	Principale();
	Parametres();
}



void Principale ()
{
	//
	// instanciation des �l�ments de la page principale
	//
	int actual_btn_pos=ctnPrincipal_init_ver_gap;
	ctnPrincipal = lv_cont_create(lv_scr_act(),NULL);
		lv_obj_set_size(ctnPrincipal,LV_HOR_RES,LV_VER_RES);


	btnParametre = lv_btn_create(ctnPrincipal,NULL);
		lv_obj_set_size(btnParametre,ctnPrinc_btnWitdh,ctnPrinc_btnHeight);
		label = lv_label_create(btnParametre, NULL);
		lv_label_set_text(label, "Parametres");
		lv_obj_set_pos(btnParametre,(LV_HOR_RES-ctnPrinc_btnWitdh)/2,actual_btn_pos);
		actual_btn_pos += ctnPrinc_btnTotalDst ;
		lv_btn_set_action(btnParametre,LV_BTN_ACTION_CLICK,click_Parametres);


	btnVehicule = lv_btn_create(ctnPrincipal,NULL);
		lv_obj_set_size(btnVehicule,ctnPrinc_btnWitdh,ctnPrinc_btnHeight);
		label = lv_label_create(btnVehicule, NULL);
		lv_label_set_text(label, "Vehicule");
		lv_obj_set_pos(btnVehicule,(LV_HOR_RES-ctnPrinc_btnWitdh)/2,actual_btn_pos); // regle le gap et la hauteur du bouton
		actual_btn_pos += ctnPrinc_btnTotalDst ;

	btnGauges = lv_btn_create(ctnPrincipal,NULL);
		lv_obj_set_size(btnGauges,ctnPrinc_btnWitdh,ctnPrinc_btnHeight);
		label = lv_label_create(btnGauges, NULL);
		lv_label_set_text(label, "Gauges / Stats");
		lv_obj_set_pos(btnGauges,(LV_HOR_RES-ctnPrinc_btnWitdh)/2,actual_btn_pos);

}




void Parametres() // on place la variable initPosition dans
{
	int nb_Button=2;
	int nb_slider = 4;
	int slider_gap = 15;

	int sliderRGB_Height = 140;
	int sliderRGB_Width = 60;
	int sliderLabel_Gap = 110;
	int slider_Y_pos = LV_VER_RES - sliderRGB_Height - 100;
	int current_X = (LV_HOR_RES-(nb_slider*(slider_gap+sliderRGB_Width)))/2;
	int actual_slider_pos = current_X;

	int size_W_retour = 50;
	int size_H_retour = 50;

	int pos_X_retour = (LV_HOR_RES/2)-(size_W_retour/2);
	int pos_Y_retour = 15;

	static lv_style_t style_bg_R;
	static lv_style_t style_indic_R;
	static lv_style_t style_knob_R;
	static lv_style_t style_bg_G;
	static lv_style_t style_indic_G;
	static lv_style_t style_knob_G;
	static lv_style_t style_bg_B;
	static lv_style_t style_indic_B;
	static lv_style_t style_knob_B;
	static lv_style_t style_bg_I;
	static lv_style_t style_indic_I;
	static lv_style_t style_knob_I;
	static lv_style_t bg_style_sw;
	static lv_style_t indic_style_sw;
	static lv_style_t knob_on_style_sw;
	static lv_style_t knob_off_style_sw;

	//acceuil du container parametre

	int actual_btn_pos = (LV_VER_RES-(nb_Button*(ctnPrinc_btnGap+ctnPrinc_btnHeight)))/2;

	ctnParametre = lv_cont_create(lv_scr_act(),NULL);

		lv_obj_set_size(ctnParametre,LV_HOR_RES,LV_VER_RES);
		lv_obj_set_hidden(ctnParametre,true);

		lv_obj_t * btnBack_Param = lv_btn_create(ctnParametre,NULL);
			lv_obj_set_size(btnBack_Param,size_W_retour,size_H_retour);
			lv_obj_set_pos(btnBack_Param,pos_X_retour,pos_Y_retour);
			label = lv_label_create(btnBack_Param, NULL);
			lv_label_set_text(label, "<-");
			lv_btn_set_action(btnBack_Param,LV_BTN_ACTION_CLICK,click_Back);

		lv_obj_t * btn_Param_LED = lv_btn_create(ctnParametre,NULL);
			lv_obj_set_size(btn_Param_LED,ctnPrinc_btnWitdh,ctnPrinc_btnHeight);
			label = lv_label_create(btn_Param_LED, NULL);
			lv_label_set_text(label, "DEL");
			lv_obj_set_pos(btn_Param_LED,(LV_HOR_RES-ctnPrinc_btnWitdh)/2,actual_btn_pos);
			actual_btn_pos += ctnPrinc_btnTotalDst ;
			lv_btn_set_action(btn_Param_LED,LV_BTN_ACTION_CLICK,click_Parametres_DEL);

		lv_obj_t * btn_Param_GAUGE = lv_btn_create(ctnParametre,NULL);
			lv_obj_set_size(btn_Param_GAUGE,ctnPrinc_btnWitdh,ctnPrinc_btnHeight);
			label = lv_label_create(btn_Param_GAUGE, NULL);
			lv_label_set_text(label, "Gauge");
			lv_obj_set_pos(btn_Param_GAUGE,(LV_HOR_RES-ctnPrinc_btnWitdh)/2,actual_btn_pos);
			actual_btn_pos += ctnPrinc_btnTotalDst ;
			lv_btn_set_action(btn_Param_GAUGE,LV_BTN_ACTION_CLICK,click_Parametres_GAUGE);


// ***************************
//
// panneau du controle des led
//
// ***************************

	ctnParamLED = lv_cont_create(lv_scr_act(),NULL);
		lv_obj_set_size(ctnParamLED,LV_HOR_RES,LV_VER_RES);
		lv_obj_set_hidden(ctnParamLED,true);
		//lv_obj_set_pos(ctnParamLED,0,ctnNORTH);

		lv_obj_t * btnBack_Param_LED = lv_btn_create(ctnParamLED,NULL);
			lv_obj_set_size(btnBack_Param_LED,size_W_retour,size_H_retour);
			lv_obj_set_pos(btnBack_Param_LED,pos_X_retour,pos_Y_retour);
			label = lv_label_create(btnBack_Param_LED, NULL);
			lv_label_set_text(label, "<-");
			lv_btn_set_action(btnBack_Param_LED,LV_BTN_ACTION_CLICK,click_Back);

// ***************************
//
// Config du slider Rouge
//
// ***************************

		sliderR = lv_slider_create(ctnParamLED,NULL);


			lv_obj_set_size(sliderR,sliderRGB_Width,sliderRGB_Height);
			lv_slider_set_range(sliderR,0,255);
			lv_obj_set_pos(sliderR,actual_slider_pos,slider_Y_pos);
			lv_slider_set_action(sliderR,actionSlider);
#ifdef rgb_label
			lv_obj_t * label_R = lv_label_create(ctnParamLED,NULL);
			lv_obj_align(label_R,sliderR,LV_ALIGN_OUT_BOTTOM_MID,0,0);
			lv_label_set_text(label_R,"R");
			lv_obj_align(label_R,sliderR,LV_ALIGN_CENTER,0,-(LV_VER_RES-(sliderLabel_Gap+sliderRGB_Height)));
#endif

			lv_style_copy(&style_bg_R, &lv_style_pretty);
			style_bg_R.body.main_color =  LV_COLOR_RED;
			style_bg_R.body.grad_color =  LV_COLOR_GRAY;
			style_bg_R.body.radius = LV_RADIUS_CIRCLE;
			style_bg_R.body.border.color = LV_COLOR_RED;

			lv_style_copy(&style_indic_R, &lv_style_pretty);
			style_indic_R.body.grad_color =  LV_COLOR_RED;
			style_indic_R.body.main_color =  LV_COLOR_RED;
			style_indic_R.body.radius = LV_RADIUS_CIRCLE;
			style_indic_R.body.shadow.width = 10;
			style_indic_R.body.shadow.color = LV_COLOR_RED;
			style_indic_R.body.padding.hor = 3;
			style_indic_R.body.padding.ver = 3;

			lv_style_copy(&style_knob_R, &lv_style_pretty);
			style_knob_R.body.radius = LV_RADIUS_CIRCLE;
			style_knob_R.body.opa = LV_OPA_70;
			style_knob_R.body.padding.ver = 5 ;

			lv_slider_set_style(sliderR, LV_SLIDER_STYLE_BG, &style_bg_R);
			lv_slider_set_style(sliderR, LV_SLIDER_STYLE_INDIC,&style_indic_R);
			lv_slider_set_style(sliderR, LV_SLIDER_STYLE_KNOB, &style_knob_R);

			actual_slider_pos += sliderRGB_Width + slider_gap;


		// ***************************
		//
		// Config du slider Vert
		//
		// ***************************

		sliderG = lv_slider_create(ctnParamLED,NULL);
			lv_obj_set_size(sliderG,sliderRGB_Width,sliderRGB_Height);
			lv_slider_set_range(sliderG,0,255);
			lv_obj_set_pos(sliderG,actual_slider_pos,slider_Y_pos);
			lv_slider_set_action(sliderG,actionSlider);
#ifdef rgb_label
			lv_obj_t * label_G = lv_label_create(ctnParamLED,NULL);
			lv_obj_align(label_G,sliderG,LV_ALIGN_OUT_BOTTOM_MID,0,0);
			lv_label_set_text(label_G,"G");
			lv_obj_align(label_G,sliderG,LV_ALIGN_CENTER,0,-(LV_VER_RES-(sliderLabel_Gap+sliderRGB_Height)));
#endif


			lv_style_copy(&style_bg_G, &lv_style_pretty);
			style_bg_G.body.main_color =  LV_COLOR_GREEN;
			style_bg_G.body.grad_color =  LV_COLOR_GRAY;
			style_bg_G.body.radius = LV_RADIUS_CIRCLE;
			style_bg_G.body.border.color = LV_COLOR_GREEN;

			lv_style_copy(&style_indic_G, &lv_style_pretty);
			style_indic_G.body.grad_color =  LV_COLOR_GREEN;
			style_indic_G.body.main_color =  LV_COLOR_GREEN;
			style_indic_G.body.radius = LV_RADIUS_CIRCLE;
			style_indic_G.body.shadow.width = 10;
			style_indic_G.body.shadow.color = LV_COLOR_GREEN;
			style_indic_G.body.padding.hor = 3;
			style_indic_G.body.padding.ver = 3;

			lv_style_copy(&style_knob_G, &lv_style_pretty);
			style_knob_G.body.radius = LV_RADIUS_CIRCLE;
			style_knob_G.body.opa = LV_OPA_70;
			style_knob_G.body.padding.ver = 5 ;

			lv_slider_set_style(sliderG, LV_SLIDER_STYLE_BG, &style_bg_G);
			lv_slider_set_style(sliderG, LV_SLIDER_STYLE_INDIC,&style_indic_G);
			lv_slider_set_style(sliderG, LV_SLIDER_STYLE_KNOB, &style_knob_G);

			actual_slider_pos += sliderRGB_Width + slider_gap;

// ***************************
//
// Config du slider Bleu
//
// ***************************

		sliderB = lv_slider_create(ctnParamLED,NULL);
			lv_obj_set_size(sliderB,sliderRGB_Width,sliderRGB_Height);
			lv_slider_set_range(sliderB,0,255);
			lv_obj_set_pos(sliderB,actual_slider_pos,slider_Y_pos);
			lv_slider_set_action(sliderB,actionSlider);
#ifdef rgb_label
			lv_obj_t * label_B= lv_label_create(ctnParamLED,NULL);
			lv_obj_align(label_B,sliderB,LV_ALIGN_OUT_BOTTOM_MID,0,0);
			lv_label_set_text(label_B,"B");
			lv_obj_align(label_B,sliderB,LV_ALIGN_CENTER,0,-(LV_VER_RES-(sliderLabel_Gap+sliderRGB_Height)));
#endif


			lv_style_copy(&style_bg_B, &lv_style_pretty);
			style_bg_B.body.main_color =  LV_COLOR_BLUE;
			style_bg_B.body.grad_color =  LV_COLOR_GRAY;
			style_bg_B.body.radius = LV_RADIUS_CIRCLE;
			style_bg_B.body.border.color = LV_COLOR_BLUE;

			lv_style_copy(&style_indic_B, &lv_style_pretty);
			style_indic_B.body.grad_color =  LV_COLOR_BLUE;
			style_indic_B.body.main_color =  LV_COLOR_BLUE;
			style_indic_B.body.radius = LV_RADIUS_CIRCLE;
			style_indic_B.body.shadow.width = 10;
			style_indic_B.body.shadow.color = LV_COLOR_BLUE;
			style_indic_B.body.padding.hor = 3;
			style_indic_B.body.padding.ver = 3;

			lv_style_copy(&style_knob_B, &lv_style_pretty);
			style_knob_B.body.radius = LV_RADIUS_CIRCLE;
			style_knob_B.body.opa = LV_OPA_70;
			style_knob_B.body.padding.ver = 5 ;

			lv_slider_set_style(sliderB, LV_SLIDER_STYLE_BG, &style_bg_B);
			lv_slider_set_style(sliderB, LV_SLIDER_STYLE_INDIC,&style_indic_B);
			lv_slider_set_style(sliderB, LV_SLIDER_STYLE_KNOB, &style_knob_B);

			actual_slider_pos += sliderRGB_Width + slider_gap;

		// ***************************
		//
		// Config du slider INTENSITE
		//
		// ***************************


		sliderI = lv_slider_create(ctnParamLED,NULL);
			lv_obj_set_size(sliderI,sliderRGB_Width,sliderRGB_Height);
			lv_slider_set_range(sliderI,0,100);
			lv_slider_set_value(sliderI,50);
			lv_obj_set_pos(sliderI,actual_slider_pos,slider_Y_pos);
			lv_slider_set_action(sliderI,actionSlider);

#ifdef rgb_label
			lv_obj_t * label_I= lv_label_create(ctnParamLED,NULL);
			lv_obj_align(label_I,sliderI,LV_ALIGN_OUT_BOTTOM_MID,0,0);
			lv_label_set_text(label_I,"I");
			lv_obj_align(label_I,sliderI,LV_ALIGN_CENTER,0,-(LV_VER_RES-(sliderLabel_Gap+sliderRGB_Height)));
#endif



			lv_style_copy(&style_bg_I, &lv_style_pretty);
			style_bg_I.body.main_color =  LV_COLOR_WHITE;
			style_bg_I.body.grad_color =  LV_COLOR_GRAY;
			style_bg_I.body.radius = LV_RADIUS_CIRCLE;
			style_bg_I.body.border.color = LV_COLOR_WHITE;

			lv_style_copy(&style_indic_I, &lv_style_pretty);
			style_indic_I.body.grad_color =  LV_COLOR_WHITE;
			style_indic_I.body.main_color =  LV_COLOR_WHITE;
			style_indic_I.body.radius = LV_RADIUS_CIRCLE;
			style_indic_I.body.shadow.width = 10;
			style_indic_I.body.shadow.color = LV_COLOR_WHITE;
			style_indic_I.body.padding.hor = 3;
			style_indic_I.body.padding.ver = 3;

			lv_style_copy(&style_knob_I, &lv_style_pretty);
			style_knob_I.body.radius = LV_RADIUS_CIRCLE;
			style_knob_I.body.opa = LV_OPA_70;
			style_knob_I.body.padding.ver = 5 ;

			lv_slider_set_style(sliderI, LV_SLIDER_STYLE_BG, &style_bg_I);
			lv_slider_set_style(sliderI, LV_SLIDER_STYLE_INDIC,&style_indic_I);
			lv_slider_set_style(sliderI, LV_SLIDER_STYLE_KNOB, &style_knob_I);
			actual_slider_pos += sliderRGB_Width + slider_gap; // pour positionner de facon �gale les sliders

		//
		// creation et style de la switch
		//
		lv_style_copy(&bg_style_sw, &lv_style_pretty);
		bg_style_sw.body.radius = LV_RADIUS_CIRCLE;

		lv_style_copy(&indic_style_sw, &lv_style_pretty_color);
		indic_style_sw.body.radius = LV_RADIUS_CIRCLE;
		indic_style_sw.body.main_color = LV_COLOR_HEX(0x9fc8ef);
		indic_style_sw.body.grad_color = LV_COLOR_HEX(0x9fc8ef);
		indic_style_sw.body.padding.hor = 0;
		indic_style_sw.body.padding.ver = 0;

		lv_style_copy(&knob_off_style_sw, &lv_style_pretty);
		knob_off_style_sw.body.radius = LV_RADIUS_CIRCLE;
		knob_off_style_sw.body.shadow.width = 4;
		knob_off_style_sw.body.shadow.type = LV_SHADOW_BOTTOM;

		lv_style_copy(&knob_on_style_sw, &lv_style_pretty_color);
		knob_on_style_sw.body.radius = LV_RADIUS_CIRCLE;
		knob_on_style_sw.body.shadow.width = 4;
		knob_on_style_sw.body.shadow.type = LV_SHADOW_BOTTOM;

		toggleOnOff = lv_sw_create(ctnParamLED, NULL);
			int size_width_toggle = 105;
			int size_height_toggle = 60;

			int toggle_Y_align = lv_obj_get_y(sliderR) - sliderLabel_Gap; // Param�tre d'alignement vertical de la switch

			lv_obj_set_size(toggleOnOff,size_width_toggle,size_height_toggle);
			label_toggle = lv_label_create(ctnParamLED,NULL);

			lv_label_set_text(label_toggle,"Deactivated");
			lv_sw_set_action(toggleOnOff,action_switch_LED);

/*			lv_obj_set_pos(label_toggle,
							lv_obj_get_x(toggleOnOff)+size_width_toggle+sliderLabel_Gap,
							toggle_Y_align + ((size_height_toggle)/2)-20);
*/


			lv_sw_set_style(toggleOnOff, LV_SW_STYLE_BG, &bg_style_sw);
			lv_sw_set_style(toggleOnOff, LV_SW_STYLE_INDIC, &indic_style_sw);
			lv_sw_set_style(toggleOnOff, LV_SW_STYLE_KNOB_ON, &knob_on_style_sw);
			lv_sw_set_style(toggleOnOff, LV_SW_STYLE_KNOB_OFF, &knob_off_style_sw);

			lv_obj_set_pos(toggleOnOff,lv_obj_get_x(sliderR),toggle_Y_align+10);
			lv_obj_align(label_toggle,toggleOnOff,LV_ALIGN_OUT_RIGHT_MID,50,0);








	// panneau du controle des Gauges



	ctnParamGAUGE = lv_cont_create(lv_scr_act(),NULL);
	lv_obj_set_size(ctnParamGAUGE,LV_HOR_RES,LV_VER_RES);
	lv_obj_set_hidden(ctnParamGAUGE,true);
	//lv_obj_set_pos(ctnParamGAUGE,0,ctnSUD);

	lv_obj_t * btnBack_Param_GAUGE = lv_btn_create(ctnParamGAUGE,NULL);
	lv_obj_set_size(btnBack_Param_GAUGE,size_W_retour,size_H_retour);
	lv_obj_set_pos(btnBack_Param_GAUGE,pos_X_retour,pos_Y_retour);
	label = lv_label_create(btnBack_Param_GAUGE, NULL);
	lv_label_set_text(label, "<-");
	lv_btn_set_action(btnBack_Param_GAUGE,LV_BTN_ACTION_CLICK,click_Back);


}


//
//
//faire une fonction pour tout le reste
//

static lv_res_t click_Parametres(lv_obj_t * child)
{

	level++;
	switch_window(lv_obj_get_parent(child),ctnParametre);

}

static lv_res_t click_Parametres_DEL(lv_obj_t * child)
{

	level++;
	Actual_ctn = lv_obj_get_parent(child);
	lv_obj_set_hidden(Actual_ctn,true);
	lv_obj_set_hidden(ctnParamLED,false);

//	switch_window(Actual_ctn,ctnParamLED);

}

void click_Parametres_GAUGE(lv_obj_t * child)
{

	level++;
	Actual_ctn = lv_obj_get_parent(child);
	switch_window(Actual_ctn,ctnParamGAUGE);


}

void click_Back(lv_obj_t * child)
{
	level--;
	switch (level)
	{
		case 0:
			switch_window(lv_obj_get_parent(child),ctnPrincipal);
			break;

		case 1:
			switch_window(lv_obj_get_parent(child),Actual_ctn);
			break;
	}
	if (level < 0)
	{
		level = 0;
	}
}



void slide_container(lv_obj_t * actual_ctn,lv_obj_t * next_ctn)
{

/*
	delay_anim = delay_anim_nop;

	if (lv_obj_get_x(next_ctn) != 0) // Le d�placement se ferait horizontalement
	{
		if (lv_obj_get_x(next_ctn) == -(LV_HOR_RES)) // Lorsque le container voulu est � gauche
		{
			for (int x = 0;x>=LV_HOR_RES;x++)
			{
				lv_obj_set_pos(actual_ctn,lv_obj_get_x(actual_ctn)+1,0);
				lv_obj_set_pos(next_ctn,lv_obj_get_x(next_ctn)+1,0);
				while(delay_anim >= 0)
				{
					delay_anim--;
					asm("NOP");
				}
				delay_anim = delay_anim_nop;
			}
			//lv_obj_set_pos(actual_ctn,LV_HOR_RES,0);
		//	lv_obj_set_pos(next_ctn,0,0);

		}
		else // Lorsque le container voulu est � droite
		{
			for (int x = 0;x>=LV_HOR_RES;x++)
			{
				lv_obj_set_pos(actual_ctn,lv_obj_get_x(actual_ctn)-1,0);
				lv_obj_set_pos(next_ctn,lv_obj_get_x(next_ctn)-1,0);
				while(delay_anim >= 0)
				{
					delay_anim--;
					asm("NOP");
				}
				delay_anim = delay_anim_nop;
			}
			lv_obj_set_pos(actual_ctn,-(LV_HOR_RES),0);
			lv_obj_set_pos(next_ctn,0,0);

		}
	}


	if (lv_obj_get_y(next_ctn) != 0)// Le d�placement se ferait horizontalement
	{

		if (lv_obj_get_y(next_ctn) == -(LV_VER_RES)) // Lorsque le container voulu est en Bas
		{
			for (int x = 0;x>=LV_VER_RES;x++)
			{
				lv_obj_set_pos(actual_ctn,lv_obj_get_y(actual_ctn)+1,0);
				lv_obj_set_pos(next_ctn,lv_obj_get_y(next_ctn)+1,0);
				while(delay_anim >= 0)
				{
					delay_anim--;
					asm("NOP");
				}
				delay_anim = delay_anim_nop;
			}
			lv_obj_set_pos(actual_ctn,0,LV_VER_RES);
			lv_obj_set_pos(next_ctn,0,0);

		}

		else // Lorsque le container voulu est en Haut
		{
			for (int x = 0;x>=LV_VER_RES;x++)
			{
				lv_obj_set_pos(actual_ctn,lv_obj_get_y(actual_ctn)-1,0);
				lv_obj_set_pos(next_ctn,lv_obj_get_y(next_ctn)-1,0);
				while(delay_anim >= 0)
				{
					delay_anim--;
					asm("NOP");
				}
				delay_anim = delay_anim_nop;
			}
			lv_obj_set_pos(actual_ctn,0,-(LV_VER_RES));
			lv_obj_set_pos(next_ctn,0,0);
		}

	}
*/



}

void switch_window(lv_obj_t * actual,lv_obj_t * next)
{
	lv_obj_set_hidden(actual,true);
	lv_obj_set_hidden(next,false);
}

static lv_res_t action_switch_LED(lv_obj_t * child)
{

	if (lv_sw_get_state(toggleOnOff))
	{
		lv_label_set_text(label_toggle,"Activated");
		set_leds();
	}
	else
	{
		lv_label_set_text(label_toggle,"Deactivated");
		turnOffBar();
	}
}

static lv_res_t actionSlider(lv_obj_t * slider)
{
	/*
		int a=lv_slider_get_value(slider);
		char buffer[50];
		itoa(a,buffer,10);
		lv_ta_set_text(textbox_I,buffer);
		//
		// AJOUTER CODE POUR CONTROLER DELs
		//
		//
	 */

	set_leds();

}

void set_leds()
{
	val_SliderI = lv_slider_get_value(sliderI);
	val_SliderR = (int)round((lv_slider_get_value(sliderR)*(val_SliderI))/lv_slider_get_max_value(sliderI));
	val_SliderG = (int)round((lv_slider_get_value(sliderG)*(val_SliderI))/lv_slider_get_max_value(sliderI));
	val_SliderB = (int)round((lv_slider_get_value(sliderB)*(val_SliderI))/lv_slider_get_max_value(sliderI));

	if (lv_sw_get_state(toggleOnOff))
	{

		led_flag = true;
	}

}


