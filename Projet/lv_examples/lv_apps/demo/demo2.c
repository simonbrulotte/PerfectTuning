

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
#include "lvgl/lv_misc/lv_font.h"
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

#define OFFSET_X_SLIDER 5 // plus on augmente la valeur, plus les sliders sont � gauche
#define OFFSET_Y_SLIDER 80 // plus on descend la valeur, plus on descend les slider

#define delay_anim_nop 150


// tabviewoffset

#define Tabview_Offset 130


/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static lv_style_t style_txt;
static lv_res_t click_Parametres(lv_obj_t * child);
static lv_res_t click_Parametres_DEL(lv_obj_t * child);
static lv_res_t click_home(lv_obj_t * child);
static lv_res_t action_switch_LED (lv_obj_t * child);
static lv_res_t actionSlider(lv_obj_t * slider);
static lv_res_t sw_master_slave(lv_obj_t * sw);
void Parametres(void);
void switch_window(lv_obj_t * actual,lv_obj_t * next);
void switch_tab(lv_obj_t * obj,int tab);
void click_Parametres_DEBUG(lv_obj_t * child);
static lv_res_t click_menu_PARAM(lv_obj_t * child);

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
int last_tab = 0;

bool led_flag=false;
bool can_mode_master = true;

lv_obj_t * Actual_ctn;
lv_obj_t * label;
//containers

lv_obj_t * ctnParametre;
lv_obj_t * ctnPrincipal;
lv_obj_t * ctnGauge;
lv_obj_t * ctnParamLED;
lv_obj_t * ctnParamDEBUG;


//composant de la page d'accueil
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

lv_obj_t *DEBUG_TB;
lv_obj_t * txt;

//composants de la page param�tres TUNING

lv_obj_t * param_tuning_gauge;
lv_obj_t * btn_tuning_Retour;
lv_obj_t * btn_tuning_Apply;


//composant de la page V�hicule

lv_obj_t * btn_ctnvehicule_Start;

//Composants du tab Graph
lv_obj_t * dataGraph;
lv_chart_series_t * ser1;


/// TABVIEW Principal

lv_obj_t * tv_Princ;
lv_obj_t * tab_princ;
lv_obj_t * tab__princ_param;
lv_obj_t * tab_princ_del;
lv_obj_t * tab_princ_debug;
lv_obj_t * tab_princ_chiffre;
lv_obj_t * tab_princ_graph;


// Tabview Param�tres
lv_obj_t * tv_Param;
lv_obj_t * tab_param_wifi; // param�tre du wifi
lv_obj_t * tab_param_home; // param�tre du wifi
lv_obj_t * tab_param_canbus; // param�tre du canbus
lv_obj_t * tab_param_DEL; // param�tre des del
lv_obj_t * tab_param_general; // param�tre des del

lv_obj_t * toggleCan_Master_Slave;
lv_obj_t * Image_config;

lv_obj_t * image_home;
lv_obj_t * image_wifi;
lv_obj_t * image_canbus;



//lv_obj_t * ctnUnlock;
#if LV_DEMO_WALLPAPER
LV_IMG_DECLARE(config);
LV_IMG_DECLARE(home);
LV_IMG_DECLARE(wifi);
LV_IMG_DECLARE(canbus_ico);
#endif




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

	tv_Princ = lv_tabview_create(lv_scr_act(),NULL);
		lv_obj_set_size(tv_Princ,LV_HOR_RES,600); /// 130 car la longueur des boutons est de 130
		lv_obj_set_pos(tv_Princ,0,-120);
		tab_princ = lv_tabview_add_tab(tv_Princ,"PRINC");
		tab_princ_del = lv_tabview_add_tab(tv_Princ,"DEL");
		tab_princ_debug = lv_tabview_add_tab(tv_Princ,"DEBUG");
		tab_princ_chiffre = lv_tabview_add_tab(tv_Princ,"INDICATEUR");
		tab_princ_graph = lv_tabview_add_tab(tv_Princ, "GRAPH");
		lv_tabview_set_sliding(tv_Princ,true);
	Image_config = lv_img_create(tab_princ,NULL);
		lv_img_set_src(Image_config,&config);
		lv_obj_set_pos(Image_config,(LV_HOR_RES/2)-(lv_obj_get_width(Image_config)/2),200);


	static lv_style_t style_btnParam;
	lv_style_copy(&style_btnParam, &lv_style_transp);

	btnParametre = lv_btn_create(tab_princ,NULL);
		lv_obj_set_size(btnParametre,200,200);
		lv_btn_set_action(btnParametre,LV_BTN_ACTION_CLICK,click_Parametres);
		lv_btn_set_style(btnParametre,LV_BTNM_STYLE_BG,&style_btnParam);
		lv_btn_set_style(btnParametre,LV_BTNM_STYLE_BTN_PR,&style_btnParam);
		lv_btn_set_style(btnParametre,LV_BTNM_STYLE_BTN_REL,&style_btnParam);
		lv_obj_align(btnParametre,tab_princ,LV_ALIGN_CENTER,0,0);

	//
	//	section LED
	//

	int nb_slider = 4;
	int slider_gap = 15;

	int sliderRGB_Height = 175;
	int sliderRGB_Width = 50;
	int sliderLabel_Gap = 75; // gap entre les slider et le label activ�/d�sactiv�

	int slider_Y_pos = LV_VER_RES - sliderRGB_Height - OFFSET_Y_SLIDER;
	int current_X_SLIDER = ((LV_HOR_RES-(nb_slider*(slider_gap+sliderRGB_Width)))/2) + OFFSET_X_SLIDER;
	int actual_slider_pos = current_X_SLIDER;



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



		// ***************************
		//
		// Config du slider Rouge
		//
		// ***************************

		sliderR = lv_slider_create(tab_princ_del,NULL);

			lv_obj_set_size(sliderR,sliderRGB_Width,sliderRGB_Height);
			lv_slider_set_range(sliderR,0,255);
			lv_obj_set_pos(sliderR,actual_slider_pos,slider_Y_pos);
			lv_slider_set_action(sliderR,actionSlider);

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

		sliderG = lv_slider_create(tab_princ_del,NULL);
			lv_obj_set_size(sliderG,sliderRGB_Width,sliderRGB_Height);
			lv_slider_set_range(sliderG,0,255);
			lv_obj_align(sliderG,sliderR,LV_ALIGN_IN_RIGHT_MID,sliderLabel_Gap,0);
			//lv_obj_set_pos(sliderG,actual_slider_pos,slider_Y_pos);
			lv_slider_set_action(sliderG,actionSlider);

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

		sliderB = lv_slider_create(tab_princ_del,NULL);
			lv_obj_set_size(sliderB,sliderRGB_Width,sliderRGB_Height);
			lv_slider_set_range(sliderB,0,255);
			lv_obj_align(sliderB,sliderG,LV_ALIGN_IN_RIGHT_MID,sliderLabel_Gap,0);
//			lv_obj_set_pos(sliderB,actual_slider_pos,slider_Y_pos);
			lv_slider_set_action(sliderB,actionSlider);

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

		sliderI = lv_slider_create(tab_princ_del,NULL);
			lv_obj_set_size(sliderI,sliderRGB_Width,sliderRGB_Height);
			lv_slider_set_range(sliderI,0,100);
			lv_slider_set_value(sliderI,50);
			lv_obj_align(sliderI,sliderB,LV_ALIGN_IN_RIGHT_MID,sliderLabel_Gap,0);

//			lv_obj_set_pos(sliderI,actual_slider_pos,slider_Y_pos);
			lv_slider_set_action(sliderI,actionSlider);

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

		//*********************************
		// 								  *
		// creation et style de la switch *
		//								  *
		//*********************************

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

		toggleOnOff = lv_sw_create(tab_princ_del, NULL);
			int size_width_toggle = 105;
			int size_height_toggle = 60;

			int toggle_Y_align = lv_obj_get_y(sliderR) - sliderLabel_Gap; // Param�tre d'alignement vertical de la switch

			lv_obj_set_size(toggleOnOff,size_width_toggle,size_height_toggle);
			label_toggle = lv_label_create(tab_princ_del,NULL);

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



	//ctnParamDEBUG = lv_cont_create(tab_debug,NULL);

		//lv_obj_set_size(ctnParamDEBUG,LV_HOR_RES,LV_VER_RES);
//		lv_obj_set_hidden(ctnParamDEBUG,true);

		toggleCan_Master_Slave = lv_sw_create(tab_princ_debug,NULL);
		lv_obj_set_size(toggleCan_Master_Slave,80,50);
		lv_obj_set_pos(toggleCan_Master_Slave,120,260);
		lv_sw_set_action(toggleCan_Master_Slave,sw_master_slave);



		DEBUG_TB = lv_ta_create(tab_princ_debug,NULL);
		lv_obj_set_size(DEBUG_TB,250,175);
		lv_obj_set_pos(DEBUG_TB,70,120);
		lv_ta_set_text(DEBUG_TB,"CanBus mode Master\n");
		lv_ta_set_cursor_type(DEBUG_TB,LV_CURSOR_NONE);


		lv_style_copy(&style_txt, &lv_style_plain);
		style_txt.text.font = &lv_font_dejavu_240;
		style_txt.text.letter_space = 2;
		style_txt.text.line_space = 1;
		style_txt.text.color = LV_COLOR_HEX(0x606060);

		txt = lv_label_create(tab_princ_chiffre, NULL);
		lv_obj_set_style(txt, &style_txt);                    /*Set the created style*/
		lv_label_set_long_mode(txt, LV_LABEL_LONG_BREAK);     /*Break the long lines*/
		lv_label_set_recolor(txt, true);                      /*Enable re-coloring by commands in the text*/
		lv_label_set_align(tab_princ_chiffre, LV_LABEL_ALIGN_CENTER);       /*Center aligned lines*/
		lv_label_set_text(txt, "10");
		lv_obj_set_width(txt, 300);                           /*Set a width*/
		lv_obj_set_pos(txt,100,400);

		/*------------------- Tab Graphique -------------------*/
		static lv_style_t dataGraph_Style;
		lv_style_copy(&dataGraph_Style, &lv_style_pretty);
		dataGraph_Style.body.shadow.width = 6;
		dataGraph_Style.body.shadow.color = LV_COLOR_GRAY;
		dataGraph_Style.line.color = LV_COLOR_GRAY;

		dataGraph = lv_chart_create(tab_princ_graph, NULL);
		lv_obj_set_size(dataGraph, 350, 350);
		lv_obj_set_style(dataGraph, &dataGraph_Style);
		lv_obj_align(dataGraph, NULL, LV_ALIGN_CENTER, 0, 0);
		lv_chart_set_type(dataGraph, LV_CHART_TYPE_POINT | LV_CHART_TYPE_LINE);   /*Show lines and points too*/
		lv_chart_set_series_opa(dataGraph, LV_OPA_70);                            /*Opacity of the data series*/
		lv_chart_set_series_width(dataGraph, 10);

		lv_chart_set_range(dataGraph, 0, 255);

		ser1 = lv_chart_add_series(dataGraph, LV_COLOR_RED);
}




void Parametres() // on place la variable initPosition dans
{


	lv_obj_t * btncanbus;
	lv_obj_t * btnhome;
	lv_obj_t * btnwifi;

	static lv_style_t style_btn;
	lv_style_copy(&style_btn, &lv_style_transp);


	tv_Param = lv_tabview_create(lv_scr_act(),NULL);
		lv_obj_set_size(tv_Param,LV_HOR_RES,600); /// 130 car la longueur des boutons est de 130
		lv_obj_set_pos(tv_Param,0,-120);
		lv_obj_set_hidden(tv_Param,true);

		tab_param_home = lv_tabview_add_tab(tv_Param,"HOME");
		tab_param_wifi = lv_tabview_add_tab(tv_Param,"WIFI");
		tab_param_canbus = lv_tabview_add_tab(tv_Param,"CANBUS");
		tab_param_DEL = lv_tabview_add_tab(tv_Param,"DEL");

		lv_tabview_set_sliding(tv_Param,true);

	// cr�ation des objet images


	btnhome = lv_btn_create(tab_param_home,NULL);
		lv_obj_set_size(btnhome,200,200);
		lv_btn_set_action(btnhome,LV_BTN_ACTION_CLICK,click_home);
		lv_btn_set_style(btnhome,LV_BTNM_STYLE_BG,&style_btn);
		lv_btn_set_style(btnhome,LV_BTNM_STYLE_BTN_PR,&style_btn);
		lv_btn_set_style(btnhome,LV_BTNM_STYLE_BTN_REL,&style_btn);
		lv_obj_align(btnhome,tv_Param,LV_ALIGN_CENTER,0,0);

	image_home = lv_img_create(tab_param_home,NULL);
		lv_img_set_src(image_home,&home);
//		lv_obj_set_pos(image_home,(LV_HOR_RES/2)-(lv_obj_get_width(image_home)/2),200);

	btnwifi = lv_btn_create(tab_param_wifi,NULL);
		lv_obj_set_size(btnwifi,200,200);
		lv_btn_set_action(btnwifi,LV_BTN_ACTION_CLICK,click_menu_PARAM);
		lv_btn_set_style(btnwifi,LV_BTNM_STYLE_BG,&style_btn);
		lv_btn_set_style(btnwifi,LV_BTNM_STYLE_BTN_PR,&style_btn);
		lv_btn_set_style(btnwifi,LV_BTNM_STYLE_BTN_REL,&style_btn);
		lv_obj_align(btnwifi,tv_Param,LV_ALIGN_CENTER,0,0);


	image_wifi = lv_img_create(tab_param_wifi,NULL);
		lv_img_set_src(image_wifi,&wifi);
//		lv_obj_set_pos(image_wifi,(LV_HOR_RES/2)-(lv_obj_get_width(image_wifi)/2),200);


	btncanbus = lv_btn_create(tab_param_canbus,NULL);
		lv_obj_set_size(btncanbus,200,200);
		lv_btn_set_action(btncanbus,LV_BTN_ACTION_CLICK,click_menu_PARAM);
		lv_btn_set_style(btncanbus,LV_BTNM_STYLE_BG,&style_btn);
		lv_btn_set_style(btncanbus,LV_BTNM_STYLE_BTN_PR,&style_btn);
		lv_btn_set_style(btncanbus,LV_BTNM_STYLE_BTN_REL,&style_btn);
		lv_obj_align(btncanbus,tv_Param,LV_ALIGN_CENTER,0,0);

	image_canbus = lv_img_create(tab_param_canbus,NULL);
		lv_img_set_src(image_canbus,&canbus_ico);
//		lv_obj_set_pos(image_canbus,(LV_HOR_RES/2)-(lv_obj_get_width(image_canbus)/2),200);

}

static lv_res_t sw_master_slave(lv_obj_t * sw)
{
	if (can_mode_master == true)
	{
		can_mode_master = false;
		lv_ta_add_text(DEBUG_TB,"CanBus mode Slave\n");
	}
	else
	{
		can_mode_master = true;
		lv_ta_add_text(DEBUG_TB,"CanBus mode Master\n");

	}
}

static lv_res_t click_Parametres(lv_obj_t * child)
{

	lv_obj_set_hidden(tv_Princ,true);
	switch_tab(tv_Param,1);
	lv_obj_set_hidden(tv_Param,false);
}

void afficheCanBus_Data(uint8_t *data, uint8_t dataLenght)
{
	int i;
	uint8_t tempBuf[10];
	uint8_t canbusString[50];

	for(i=0; i<(dataLenght-1); i++)
	{
		sprintf(tempBuf, "[%d],", data[i]);
		strcat(canbusString, tempBuf);
	}
	i++;
	sprintf(tempBuf, "[%d]\n", data[i]);
	strcat(canbusString, tempBuf);

	lv_ta_add_text(DEBUG_TB,"CanBus mode Slave\n");
}

void afficheGraphData_CanBus(uint32_t graphPointY){
	lv_chart_set_next(dataGraph, ser1, graphPointY);
	lv_chart_refresh(dataGraph);
}

static lv_res_t click_home(lv_obj_t * child)
{

	lv_obj_set_hidden(tv_Param,true);
	lv_obj_set_hidden(tv_Princ,false);

/*
	level++;
	//	switch_window(lv_obj_get_parent(child),ctnParametre);
*/

}
static lv_res_t click_menu_PARAM(lv_obj_t * child)
{

	lv_obj_set_hidden(tv_Param,true);
	lv_obj_set_hidden(tv_Princ,false);

/*
	level++;
	//	switch_window(lv_obj_get_parent(child),ctnParametre);
*/

}


static lv_res_t click_Parametres_DEL(lv_obj_t * child)
{

/*
	level++;
	Actual_ctn = lv_obj_get_parent(child);
	lv_obj_set_hidden(Actual_ctn,true);
	lv_obj_set_hidden(ctnParamLED,false);
*/
	return LV_RES_OK;
}

void click_Parametres_DEBUG(lv_obj_t * child)
{
/*
	level++;
	Actual_ctn = lv_obj_get_parent(child);
	switch_window(Actual_ctn,ctnParamDEBUG);
*/
	last_tab = lv_tabview_get_tab_act(tv_Princ);
	switch_tab(tv_Princ,3);
}

void click_Back(lv_obj_t * child)
{
	/*
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
	}*/
	if (lv_tabview_get_tab_act(tv_Princ) == 1)
	{
		lv_tabview_set_tab_act(tv_Princ,0,true);
	}
	else
	{
		lv_tabview_set_tab_act(tv_Princ,last_tab,true);
	}
}

void switch_tab(lv_obj_t * obj,int tab)
{
	lv_tabview_set_tab_act(obj,tab,true);
}

void switch_window(lv_obj_t * actual,lv_obj_t * next)
{

	/*
	lv_obj_set_hidden(actual,true);
	lv_obj_set_hidden(next,false);
	*/

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
	return LV_RES_OK;
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
	return LV_RES_OK;
}

void set_leds()
{
	val_SliderI = lv_slider_get_value(sliderI);
	val_SliderR = (uint8_t)round((lv_slider_get_value(sliderR)*(val_SliderI))/lv_slider_get_max_value(sliderI));
	val_SliderG = (uint8_t)round((lv_slider_get_value(sliderG)*(val_SliderI))/lv_slider_get_max_value(sliderI));
	val_SliderB = (uint8_t)round((lv_slider_get_value(sliderB)*(val_SliderI))/lv_slider_get_max_value(sliderI));

	if (lv_sw_get_state(toggleOnOff))
	{
		led_flag = true;
	}
}
