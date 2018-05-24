

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

// tabviewoffset

#define Tabview_Offset 130

// Gauge

#define RANGE_GAUGE 9000
#define RED_LINE 7800
#define gaugeKPH 1

/**********************
 *      EXTERN
 **********************/

//extern lv_indev_t * indev_list;

/**********************
 *  STATIC PROTOTYPES
 **********************/
static lv_res_t position_label (lv_obj_t * child);
static lv_style_t style_txt;
static lv_res_t click_Parametres(lv_obj_t * child);
static lv_res_t click_Parametres_DEL(lv_obj_t * child);
static lv_res_t click_home(lv_obj_t * child);
static lv_res_t action_switch_LED (lv_obj_t * child);
static lv_res_t actionSlider(lv_obj_t * slider);
static lv_res_t sw_master_slave(lv_obj_t * sw);
void Parametres(void);
void switch_tab(lv_obj_t * obj,int tab);
void click_Parametres_DEBUG(lv_obj_t * child);
static lv_res_t click_gauge(lv_obj_t * child);
static lv_res_t click_menu_PARAM(lv_obj_t * child);
static lv_res_t tab_load_action(lv_obj_t * child);

void Principale (void);


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
int active_tab = -1;

extern bool led_flag;
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
lv_obj_t * gauge;

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
lv_obj_t * tab_princ_del;
lv_obj_t * tab_princ_debug;
lv_obj_t * tab_princ_chiffre;
lv_obj_t * tab_princ_gauge;
lv_obj_t * tab_princ_stat;
lv_obj_t * tab_princ_stat2;
lv_obj_t * tab_princ_stat3;
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

lv_obj_t * list_gauge;
lv_obj_t * btn_list_gauge;
lv_obj_t * btn_slide_gauge;

// btn des parametres

lv_obj_t * btncanbus;
lv_obj_t * btnhome;
lv_obj_t * btnwifi;


// tab cadran divis� 1

lv_obj_t * ligne_hor;
lv_obj_t * ligne_ver;

lv_obj_t * label_Cadran1_titre;
lv_obj_t * label_Cadran1_unit;
lv_obj_t * label_Cadran1_Valeur;

lv_obj_t * label_Cadran2_titre;
lv_obj_t * label_Cadran2_unit;
lv_obj_t * label_Cadran2_Valeur;

lv_obj_t * label_Cadran3_titre;
lv_obj_t * label_Cadran3_unit;
lv_obj_t * label_Cadran3_Valeur;

lv_obj_t * label_Cadran4_titre;
lv_obj_t * label_Cadran4_unit;
lv_obj_t * label_Cadran4_Valeur;

// tab cadran divis� 2

lv_obj_t * ligne_hor2;
lv_obj_t * ligne_ver2;

lv_obj_t * label_Cadran1_titre2;
lv_obj_t * label_Cadran1_unit2;
lv_obj_t * label_Cadran1_Valeur2;

lv_obj_t * label_Cadran2_titre2;
lv_obj_t * label_Cadran2_unit2;
lv_obj_t * label_Cadran2_Valeur2;

// tab cadran divis� 3

lv_obj_t * ligne_hor3;
lv_obj_t * ligne_ver3;

lv_obj_t * label_Cadran1_titre3;
lv_obj_t * label_Cadran1_unit3;
lv_obj_t * label_Cadran1_Valeur3;

lv_obj_t * label_Cadran2_titre3;
lv_obj_t * label_Cadran2_unit3;
lv_obj_t * label_Cadran2_Valeur3;

lv_obj_t * label_Cadran3_titre3;
lv_obj_t * label_Cadran3_unit3;
lv_obj_t * label_Cadran3_Valeur3;

//---------------------------------

lv_obj_t * tableau_objet_valeur[] = { &label_Cadran1_Valeur, &label_Cadran2_Valeur, &label_Cadran3_Valeur, &label_Cadran4_Valeur };

lv_obj_t * label_pos_test;
lv_obj_t * label_valeur_pos;


//lv_obj_t * ctnUnlock;
#if LV_DEMO_WALLPAPER

/*----------DECLARATION DES IMAGES------*/

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
	/*Create the first image without re-color*/
	//set_cadran(1,100);
}


void Principale ()
{
	int nb_slider = 4;
	int slider_gap = 65;
	int sliderRGB_Height = 160;
	int sliderRGB_Width = 45;
	int sliderLabel_Gap = 100; // gap entre les slider et le label activ�/d�sactiv�
	int OFFSET_X_SLIDER = 80;
	int OFFSET_Y_SLIDER = 120;
	int slider_Y_pos = LV_VER_RES - sliderRGB_Height - OFFSET_Y_SLIDER;
	int Pos_Slider_1 = ((LV_HOR_RES-(nb_slider*(slider_gap+sliderRGB_Width)))/2) + OFFSET_X_SLIDER;
	int actual_slider_pos = Pos_Slider_1;

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
	static lv_style_t style_cadran_titre;
	static lv_style_t style_cadran_unit;
	static lv_style_t style_cadran_value;

	static lv_point_t line_points_hor[] = {{0, 200}, {400, 200}};
	static lv_point_t line_points_ver[] = {{185, 0}, {185, 400}};

	static lv_point_t line_points_hor2[] = {{0, 200}, {400, 200}};

	static lv_point_t line_points_hor3[] = {{0, 200}, {400, 200}};
	static lv_point_t line_points_ver3[] = {{185, 0}, {185, 200}};

	static lv_style_t style_invisible;

	//
	// instanciation des �l�ments de la page principale
	//

	tv_Princ = lv_tabview_create(lv_scr_act(),NULL);
		lv_obj_set_hidden(tv_Princ,true);
		lv_obj_set_size(tv_Princ,LV_HOR_RES,525); /// 130 car la longueur des boutons est de 130
		lv_obj_set_pos(tv_Princ,0,-135);
		lv_page_set_sb_mode(tv_Princ,LV_SB_MODE_OFF);
//		lv_obj_set_style(tv_Princ,&style_invisible);

		tab_princ = lv_tabview_add_tab(tv_Princ,"PRINC"); // TAB POUR LA CONFIGURATION
			lv_page_set_scrl_fit(tab_princ,false,false);
			lv_page_set_scrl_height(tab_princ, lv_obj_get_height(tab_princ));
			lv_page_set_scrl_width(tab_princ, lv_obj_get_width(tab_princ));
			lv_page_set_sb_mode(tab_princ,LV_SB_MODE_OFF);

		tab_princ_del = lv_tabview_add_tab(tv_Princ,"DEL"); // TAB DE SETTING DES DELS
			lv_page_set_scrl_fit(tab_princ_del,false,false);
			lv_page_set_scrl_height(tab_princ_del, lv_obj_get_height(tab_princ_del));
			lv_page_set_scrl_width(tab_princ_del, lv_obj_get_width(tab_princ_del));
			lv_page_set_sb_mode(tab_princ_del,LV_SB_MODE_OFF);
		tab_princ_debug = lv_tabview_add_tab(tv_Princ,"DEBUG"); // TAB DEBUG
			lv_page_set_scrl_fit(tab_princ_debug,false,false);
			lv_page_set_scrl_height(tab_princ_debug, lv_obj_get_height(tab_princ_debug));
			lv_page_set_scrl_width(tab_princ_debug, lv_obj_get_width(tab_princ_debug));
			lv_page_set_sb_mode(tab_princ_debug,LV_SB_MODE_OFF);
		tab_princ_chiffre = lv_tabview_add_tab(tv_Princ,"COMPTEUR"); // TAB COMPTEUR
			lv_page_set_scrl_fit(tab_princ_chiffre,false,false);
			lv_page_set_scrl_height(tab_princ_chiffre, lv_obj_get_height(tab_princ_chiffre));
			lv_page_set_scrl_width(tab_princ_chiffre, lv_obj_get_width(tab_princ_chiffre));
			lv_page_set_sb_mode(tab_princ_chiffre,LV_SB_MODE_OFF);
		tab_princ_gauge = lv_tabview_add_tab(tv_Princ,"INDICATEUR");
			lv_page_set_scrl_fit(tab_princ_gauge,false,false);
			lv_page_set_scrl_height(tab_princ_gauge, lv_obj_get_height(tab_princ_gauge));
			lv_page_set_scrl_width(tab_princ_gauge, lv_obj_get_width(tab_princ_gauge));
			lv_page_set_sb_mode(tab_princ_gauge,LV_SB_MODE_OFF);
		tab_princ_stat = lv_tabview_add_tab(tv_Princ,"Stats");
			lv_page_set_scrl_fit(tab_princ_stat,false,false);
			lv_page_set_scrl_height(tab_princ_stat, lv_obj_get_height(tab_princ_stat));
			lv_page_set_scrl_width(tab_princ_stat, lv_obj_get_width(tab_princ_stat));
			lv_page_set_sb_mode(tab_princ_stat,LV_SB_MODE_OFF);
		tab_princ_stat2 = lv_tabview_add_tab(tv_Princ,"Stats");
			lv_page_set_scrl_fit(tab_princ_stat2,false,false);
			lv_page_set_scrl_height(tab_princ_stat2, lv_obj_get_height(tab_princ_stat2));
			lv_page_set_scrl_width(tab_princ_stat2, lv_obj_get_width(tab_princ_stat2));
			lv_page_set_sb_mode(tab_princ_stat2,LV_SB_MODE_OFF);
		tab_princ_stat3 = lv_tabview_add_tab(tv_Princ,"Stats");
			lv_page_set_scrl_fit(tab_princ_stat3,false,false);
			lv_page_set_scrl_height(tab_princ_stat3, lv_obj_get_height(tab_princ_stat3));
			lv_page_set_scrl_width(tab_princ_stat3, lv_obj_get_width(tab_princ_stat3));
			lv_page_set_sb_mode(tab_princ_stat3,LV_SB_MODE_OFF);
		tab_princ_graph = lv_tabview_add_tab(tv_Princ, "GRAPH");
			lv_page_set_scrl_fit(tab_princ_graph,false,false);
			lv_page_set_scrl_height(tab_princ_graph, lv_obj_get_height(tab_princ_graph));
			lv_page_set_scrl_width(tab_princ_graph, lv_obj_get_width(tab_princ_graph));

		lv_tabview_set_sliding(tv_Princ,true);
//		lv_tabview_set_style(tv_Princ,LV_TABVIEW_STYLE_BG,&style_invisible);



		Image_config = lv_img_create(tab_princ,NULL);
			lv_img_set_src(Image_config,&config);
			lv_obj_align(Image_config,tab_princ,LV_ALIGN_CENTER,0,0);
			lv_obj_set_click(Image_config,true);
			lv_obj_set_signal_func(Image_config,click_Parametres);

	switch_tab(tv_Princ,1);
	HAL_Delay(100);
	lv_obj_set_hidden(tv_Princ,false);

//
//		section LED
//

// ***************************
//
// Config du slider Rouge
//
// ***************************

	sliderR = lv_slider_create(tab_princ_del,NULL);

		lv_obj_set_size(sliderR,sliderRGB_Width,sliderRGB_Height);
		lv_slider_set_range(sliderR,0,255);

		lv_obj_set_pos(sliderR,Pos_Slider_1,slider_Y_pos +25);

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
		style_indic_R.body.shadow.width = 8;
		style_indic_R.body.shadow.color = LV_COLOR_RED;
		style_indic_R.body.padding.hor = 2;
		style_indic_R.body.padding.ver = 2;

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
		lv_obj_align(sliderG,sliderR,LV_ALIGN_IN_RIGHT_MID,slider_gap,0);
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
		style_indic_G.body.shadow.width = 8;
		style_indic_G.body.shadow.color = LV_COLOR_GREEN;
		style_indic_G.body.padding.hor = 2;
		style_indic_G.body.padding.ver = 2;

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
		lv_obj_align(sliderB,sliderG,LV_ALIGN_IN_RIGHT_MID,slider_gap,0);
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
		style_indic_B.body.shadow.width = 8;
		style_indic_B.body.shadow.color = LV_COLOR_BLUE;
		style_indic_B.body.padding.hor = 2;
		style_indic_B.body.padding.ver = 2;

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
		lv_obj_align(sliderI,sliderB,LV_ALIGN_IN_RIGHT_MID,slider_gap,0);
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
		style_indic_I.body.shadow.width = 8;
		style_indic_I.body.shadow.color = LV_COLOR_WHITE;
		style_indic_I.body.padding.hor = 2;
		style_indic_I.body.padding.ver = 2;

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
		knob_off_style_sw.body.shadow.width = 2;
		knob_off_style_sw.body.shadow.type = LV_SHADOW_BOTTOM;

	lv_style_copy(&knob_on_style_sw, &lv_style_pretty_color);
		knob_on_style_sw.body.radius = LV_RADIUS_CIRCLE;
		knob_on_style_sw.body.shadow.width = 2;
		knob_on_style_sw.body.shadow.type = LV_SHADOW_BOTTOM;

	toggleOnOff = lv_sw_create(tab_princ_del, NULL);
		int size_width_toggle = 95;
		int size_height_toggle = 60;
		int toggle_Y_align = lv_obj_get_y(sliderR) - sliderLabel_Gap; // Param�tre d'alignement vertical de la switch

		lv_obj_set_size(toggleOnOff,size_width_toggle,size_height_toggle);
		label_toggle = lv_label_create(tab_princ_del,NULL);

		lv_label_set_text(label_toggle,"Deactivated");
		lv_sw_set_action(toggleOnOff,action_switch_LED);


		lv_sw_set_style(toggleOnOff, LV_SW_STYLE_BG, &bg_style_sw);
		lv_sw_set_style(toggleOnOff, LV_SW_STYLE_INDIC, &indic_style_sw);
		lv_sw_set_style(toggleOnOff, LV_SW_STYLE_KNOB_ON, &knob_on_style_sw);
		lv_sw_set_style(toggleOnOff, LV_SW_STYLE_KNOB_OFF, &knob_off_style_sw);

		lv_obj_set_pos(toggleOnOff,lv_obj_get_x(sliderR),toggle_Y_align+10);
		lv_obj_align(label_toggle,toggleOnOff,LV_ALIGN_OUT_RIGHT_MID,50,0);



	toggleCan_Master_Slave = lv_sw_create(tab_princ_debug,NULL);
		lv_obj_set_size(toggleCan_Master_Slave,80,50);
		lv_obj_set_pos(toggleCan_Master_Slave,70,60);
		lv_sw_set_action(toggleCan_Master_Slave,sw_master_slave);
//		lv_obj_align(toggleCan_Master_Slave,tab_princ_debug,LV_ALIGN_OUT_TOP_LEFT,DEBUG_TB->coords.x1,100);


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
		lv_label_set_align(txt, LV_LABEL_ALIGN_LEFT);       /*Center aligned lines*/

		lv_label_set_text(txt, "10");
		lv_obj_set_width(txt, 300);                           /*Set a width*/

	lv_obj_align(txt,tab_princ_chiffre,LV_ALIGN_CENTER,50,0);


//**************************
//		GAUGE
//**************************

	static lv_style_t style_gauge;
	lv_style_copy(&style_gauge, &lv_style_pretty_color);
		style_gauge.body.main_color = LV_COLOR_HEX3(0x666);     /*Line color at the beginning*/
		style_gauge.body.grad_color =  LV_COLOR_HEX3(0x666);    /*Line color at the end*/
		style_gauge.body.padding.hor = 10;                      /*Scale line length*/
		style_gauge.body.padding.inner = 8 ;                    /*Scale label padding*/
		style_gauge.body.border.color = LV_COLOR_HEX3(0x333);   /*Needle middle circle color*/
		style_gauge.line.width = 4;
		style_gauge.text.color = LV_COLOR_HEX3(0x333);
		style_gauge.line.color = LV_COLOR_RED;                  /*Line color after the critical value*/

	gauge = lv_gauge_create(tab_princ_gauge,NULL);
		lv_obj_set_size(gauge,325,360);
		lv_gauge_set_style(gauge, &style_gauge);
		lv_gauge_set_range(gauge,0,RANGE_GAUGE);
		lv_gauge_set_critical_value(gauge, RED_LINE);
		lv_gauge_set_scale(gauge,240,(RANGE_GAUGE/200),(RANGE_GAUGE/1000)+1);
		lv_obj_align(gauge,tab_princ_gauge,LV_ALIGN_CENTER,0,0);
		gauge->click = 1;

		lv_obj_get_drag_parent(gauge);

//**************************
//		Stats
//**************************

/*---------------LIGNES DE L'�CRAN---------------------*/


	static lv_style_t style_line;
		lv_style_copy(&style_line, &lv_style_plain);
		style_line.line.color = LV_COLOR_MAKE(0x00, 0x3b, 0x75);
		style_line.line.width = 8;


		ligne_hor = lv_line_create(tab_princ_stat,NULL);
			lv_line_set_points(ligne_hor,line_points_hor,2);
			lv_line_set_style(ligne_hor, &style_line);

		ligne_ver = lv_line_create(tab_princ_stat,NULL);
			lv_line_set_points(ligne_ver,line_points_ver,2);
			lv_line_set_style(ligne_ver, &style_line);


		ligne_hor2 = lv_line_create(tab_princ_stat2,NULL);
			lv_line_set_points(ligne_hor2,line_points_hor2,2);
			lv_line_set_style(ligne_hor2, &style_line);


		ligne_hor3 = lv_line_create(tab_princ_stat3,NULL);
			lv_line_set_points(ligne_hor3,line_points_hor3,2);
			lv_line_set_style(ligne_hor3, &style_line);

		ligne_ver3 = lv_line_create(tab_princ_stat3,NULL);
			lv_line_set_points(ligne_ver3,line_points_ver3,2);
			lv_line_set_style(ligne_ver3, &style_line);


/*-----------------STYLE DU TEXTE POUR LA POLICE----------*/

	lv_style_copy(&style_cadran_titre, &lv_style_plain);
		style_cadran_titre.text.font = &lv_font_dejavu_60_8bpp;
		style_cadran_titre.text.letter_space = 2;
		style_cadran_titre.text.line_space = 1;
		style_cadran_titre.text.color = LV_COLOR_HEX(0x606060);

	lv_style_copy(&style_cadran_unit, &lv_style_plain);
		style_cadran_unit.text.font = &lv_font_dejavu_20;
		style_cadran_unit.text.letter_space = 2;
		style_cadran_unit.text.line_space = 1;
		style_cadran_unit.text.color = LV_COLOR_HEX(0x606060);

	lv_style_copy(&style_cadran_value, &lv_style_plain);
		style_cadran_value.text.font = &lv_font_dejavu_60_8bpp;
		style_cadran_value.text.letter_space = 2;
		style_cadran_value.text.line_space = 1;
		style_cadran_value.text.color = LV_COLOR_HEX(0x606060);

/*----------------------LABELS DU CADRANS tab1-----------------------*/

/*
		label_pos_test = lv_label_create(tab_princ_stat,NULL);
			lv_obj_set_style(label_pos_test,&style_cadran_titre);
			lv_obj_set_pos(label_pos_test,150,50);
			lv_label_set_text(label_pos_test,"AFR�");
			label_pos_test->click = 1;
			lv_obj_set_drag(label_pos_test,true);

		lv_obj_t * btn_valeur_pos = lv_btn_create(tab_princ_stat,NULL);
			lv_obj_set_size(btn_valeur_pos,60,60);
			lv_obj_set_pos(btn_valeur_pos,125,300);
			lv_btn_set_action(btn_valeur_pos,LV_BTN_ACTION_CLICK,position_label);
*/

	label_Cadran1_titre = lv_label_create(tab_princ_stat,NULL);
		lv_obj_set_style(label_Cadran1_titre,&style_cadran_titre);
		lv_obj_set_pos(label_Cadran1_titre,55,42);
		lv_label_set_text(label_Cadran1_titre,"AFR");


	label_Cadran2_titre = lv_label_create(tab_princ_stat,NULL);
		lv_obj_set_style(label_Cadran2_titre,&style_cadran_titre);
		lv_obj_set_pos(label_Cadran2_titre,200,42);
		lv_label_set_text(label_Cadran2_titre,"AFRT");

	label_Cadran3_titre = lv_label_create(tab_princ_stat,NULL);
		lv_obj_set_style(label_Cadran3_titre,&style_cadran_titre);
		lv_obj_set_pos(label_Cadran3_titre,55,205);
		lv_label_set_text(label_Cadran3_titre,"VSS");

	label_Cadran4_titre = lv_label_create(tab_princ_stat,NULL);
		lv_obj_set_style(label_Cadran4_titre,&style_cadran_titre);
		lv_obj_set_pos(label_Cadran4_titre,215,205);
		lv_label_set_text(label_Cadran4_titre,"MPG");


	label_Cadran1_unit = lv_label_create(tab_princ_stat,NULL);
		lv_obj_set_style(label_Cadran1_unit,&style_cadran_unit);
		lv_label_set_text(label_Cadran1_unit,"AFR");
		lv_obj_align(label_Cadran1_unit,label_Cadran1_titre,LV_ALIGN_CENTER,0,40);

	label_Cadran2_unit = lv_label_create(tab_princ_stat,NULL);
		lv_obj_set_style(label_Cadran2_unit,&style_cadran_unit);
		lv_label_set_text(label_Cadran2_unit,"AFR");
		lv_obj_align(label_Cadran2_unit,label_Cadran2_titre,LV_ALIGN_CENTER,0,40);

	label_Cadran3_unit = lv_label_create(tab_princ_stat,NULL);
		lv_obj_set_style(label_Cadran3_unit,&style_cadran_unit);
#ifdef gaugeKPH
		lv_label_set_text(label_Cadran3_unit,"KPH");
#endif
#ifdef gaugeMPH
		lv_label_set_text(label_Cadran3_unit,"MPH");
#endif
		lv_obj_align(label_Cadran3_unit,label_Cadran3_titre,LV_ALIGN_CENTER,0,40);


	label_Cadran4_unit = lv_label_create(tab_princ_stat,NULL);
		lv_obj_set_style(label_Cadran4_unit,&style_cadran_unit);
		lv_obj_align(label_Cadran4_unit,label_Cadran4_titre,LV_ALIGN_CENTER,0,40);
		lv_label_set_text(label_Cadran4_unit,"");

	label_Cadran1_Valeur = lv_label_create(tab_princ_stat,NULL);
		lv_obj_set_style(label_Cadran1_Valeur,&style_cadran_value);
		lv_label_set_text(label_Cadran1_Valeur,"0");
		lv_obj_align(label_Cadran1_Valeur,label_Cadran1_unit,LV_ALIGN_CENTER,0,40);

	label_Cadran2_Valeur = lv_label_create(tab_princ_stat,NULL);
		lv_obj_set_style(label_Cadran2_Valeur,&style_cadran_value);
		lv_label_set_text(label_Cadran2_Valeur,"0");
		lv_obj_align(label_Cadran2_Valeur,label_Cadran2_unit,LV_ALIGN_CENTER,0,40);

	label_Cadran3_Valeur = lv_label_create(tab_princ_stat,NULL);
		lv_obj_set_style(label_Cadran3_Valeur,&style_cadran_value);
		lv_label_set_text(label_Cadran3_Valeur,"0");
		lv_obj_align(label_Cadran3_Valeur,label_Cadran3_unit,LV_ALIGN_CENTER,0,40);

	label_Cadran4_Valeur = lv_label_create(tab_princ_stat,NULL);
		lv_obj_set_style(label_Cadran4_Valeur,&style_cadran_value);
		lv_label_set_text(label_Cadran4_Valeur,"0");
		lv_obj_align(label_Cadran4_Valeur,label_Cadran4_titre,LV_ALIGN_CENTER,0,80);

	lv_label_set_align(label_Cadran1_Valeur,LV_LABEL_ALIGN_CENTER);
	lv_label_set_align(label_Cadran2_Valeur,LV_LABEL_ALIGN_CENTER);
	lv_label_set_align(label_Cadran3_Valeur,LV_LABEL_ALIGN_CENTER);
	lv_label_set_align(label_Cadran4_Valeur,LV_LABEL_ALIGN_CENTER);

/*----------------------LABELS DU CADRANS tab2-----------------------*/
		label_Cadran1_titre2 = lv_label_create(tab_princ_stat2,NULL);
			lv_obj_set_style(label_Cadran1_titre2,&style_cadran_titre);
			lv_label_set_text(label_Cadran1_titre2,"AFR");
			lv_obj_align(label_Cadran1_titre2,tab_princ_stat2,LV_ALIGN_IN_TOP_MID,0,50);

		label_Cadran2_titre2 = lv_label_create(tab_princ_stat2,NULL);
			lv_obj_set_style(label_Cadran2_titre2,&style_cadran_titre);
			lv_label_set_text(label_Cadran2_titre2,"Turbo");
			lv_obj_align(label_Cadran2_titre2,tab_princ_stat2,LV_ALIGN_CENTER,0,50);

		label_Cadran1_unit2 = lv_label_create(tab_princ_stat2,NULL);
			lv_obj_set_style(label_Cadran1_unit2,&style_cadran_unit);
			lv_label_set_text(label_Cadran1_unit2,"AFR");
			lv_obj_align(label_Cadran1_unit2,label_Cadran1_titre2,LV_ALIGN_CENTER,0,40);

		label_Cadran2_unit2 = lv_label_create(tab_princ_stat2,NULL);
			lv_obj_set_style(label_Cadran2_unit2,&style_cadran_unit);
			lv_label_set_text(label_Cadran2_unit2,"PSI");
			lv_obj_align(label_Cadran2_unit2,label_Cadran2_titre2,LV_ALIGN_CENTER,0,40);

		label_Cadran1_Valeur2 = lv_label_create(tab_princ_stat2,NULL);
			lv_obj_set_style(label_Cadran1_Valeur2,&style_cadran_value);
			lv_label_set_text(label_Cadran1_Valeur2,"0");
			lv_obj_align(label_Cadran1_Valeur2,label_Cadran1_unit2,LV_ALIGN_CENTER,0,40);

		label_Cadran2_Valeur2 = lv_label_create(tab_princ_stat2,NULL);
			lv_obj_set_style(label_Cadran2_Valeur2,&style_cadran_value);
			lv_label_set_text(label_Cadran2_Valeur2,"0");
			lv_obj_align(label_Cadran2_Valeur2,label_Cadran2_unit2,LV_ALIGN_CENTER,0,40);

		lv_label_set_align(label_Cadran1_Valeur2,LV_LABEL_ALIGN_CENTER);
		lv_label_set_align(label_Cadran2_Valeur2,LV_LABEL_ALIGN_CENTER);

/*----------------------LABELS DU CADRANS tab3-----------------------*/

		label_Cadran1_titre3 = lv_label_create(tab_princ_stat3,NULL);
			lv_obj_set_style(label_Cadran1_titre3,&style_cadran_titre);
			lv_obj_set_pos(label_Cadran1_titre3,55,42);
			lv_label_set_text(label_Cadran1_titre3,"AFR");

		label_Cadran2_titre3 = lv_label_create(tab_princ_stat3,NULL);
			lv_obj_set_style(label_Cadran2_titre3,&style_cadran_titre);
			lv_obj_set_pos(label_Cadran2_titre3,200,42);
			lv_label_set_text(label_Cadran2_titre3,"AFRT");

		label_Cadran3_titre3 = lv_label_create(tab_princ_stat3,NULL);
			lv_obj_set_style(label_Cadran3_titre3,&style_cadran_titre);
			lv_label_set_text(label_Cadran3_titre3,"VSS");
			lv_obj_align(label_Cadran3_titre3,tab_princ_stat3,LV_ALIGN_CENTER,0,50);

		label_Cadran1_unit3 = lv_label_create(tab_princ_stat3,NULL);
			lv_obj_set_style(label_Cadran1_unit3,&style_cadran_unit);
			lv_label_set_text(label_Cadran1_unit3,"AFR");
			lv_obj_align(label_Cadran1_unit3,label_Cadran1_titre3,LV_ALIGN_CENTER,0,40);

		label_Cadran2_unit3 = lv_label_create(tab_princ_stat3,NULL);
			lv_obj_set_style(label_Cadran2_unit3,&style_cadran_unit);
			lv_label_set_text(label_Cadran2_unit3,"AFR");
			lv_obj_align(label_Cadran2_unit3,label_Cadran2_titre3,LV_ALIGN_CENTER,0,40);

		label_Cadran3_unit3 = lv_label_create(tab_princ_stat3,NULL);
			lv_obj_set_style(label_Cadran3_unit3,&style_cadran_unit);

		#ifdef gaugeKPH
			lv_label_set_text(label_Cadran3_unit3,"KPH");
		#endif

		#ifdef gaugeMPH
			lv_label_set_text(label_Cadran3_unit3,"MPH");
		#endif
			lv_obj_align(label_Cadran3_unit3,label_Cadran3_titre3,LV_ALIGN_CENTER,0,40);


		label_Cadran1_Valeur3 = lv_label_create(tab_princ_stat3,NULL);
			lv_obj_set_style(label_Cadran1_Valeur3,&style_cadran_value);
			lv_label_set_text(label_Cadran1_Valeur3,"0");
			lv_obj_align(label_Cadran1_Valeur3,label_Cadran1_unit3,LV_ALIGN_CENTER,0,40);

		label_Cadran2_Valeur3 = lv_label_create(tab_princ_stat3,NULL);
			lv_obj_set_style(label_Cadran2_Valeur3,&style_cadran_value);
			lv_label_set_text(label_Cadran2_Valeur3,"0");
			lv_obj_align(label_Cadran2_Valeur3,label_Cadran2_unit3,LV_ALIGN_CENTER,0,40);

		label_Cadran3_Valeur3 = lv_label_create(tab_princ_stat3,NULL);
			lv_obj_set_style(label_Cadran3_Valeur3,&style_cadran_value);
			lv_label_set_text(label_Cadran3_Valeur3,"0");
			lv_obj_align(label_Cadran3_Valeur3,label_Cadran3_unit3,LV_ALIGN_CENTER,0,40);

		lv_label_set_align(label_Cadran1_Valeur3,LV_LABEL_ALIGN_CENTER);
		lv_label_set_align(label_Cadran2_Valeur3,LV_LABEL_ALIGN_CENTER);
		lv_label_set_align(label_Cadran3_Valeur3,LV_LABEL_ALIGN_CENTER);

/*------------------- Tab Graphique -------------------*/

		static lv_style_t dataGraph_Style;
		lv_style_copy(&dataGraph_Style, &lv_style_pretty);
		dataGraph_Style.body.shadow.width = 6;
		dataGraph_Style.body.shadow.color = LV_COLOR_GRAY;
		dataGraph_Style.line.color = LV_COLOR_GRAY;

		dataGraph = lv_chart_create(tab_princ_graph, NULL);
		lv_obj_set_size(dataGraph, 320, 350);
		lv_obj_set_style(dataGraph, &dataGraph_Style);
		lv_obj_align(dataGraph, NULL, LV_ALIGN_CENTER, 0, 0);
		lv_chart_set_type(dataGraph, LV_CHART_TYPE_LINE);  //LV_CHART_TYPE_POINT | LV_CHART_TYPE_LINE);   /*Show lines and points too*/
		lv_chart_set_series_opa(dataGraph, LV_OPA_70);                            /*Opacity of the data series*/
		lv_chart_set_series_width(dataGraph, 10);
		lv_page_set_sb_mode(tab_princ_graph, LV_SB_MODE_OFF);

		lv_chart_set_range(dataGraph, 0, 4095);
		lv_chart_set_point_count(dataGraph,30);

		ser1 = lv_chart_add_series(dataGraph, LV_COLOR_RED);

}




void Parametres() // on place la variable initPosition dans
{

	static lv_style_t style_btn;
	lv_style_copy(&style_btn, &lv_style_transp);


	tv_Param = lv_tabview_create(lv_scr_act(),NULL);
		lv_obj_set_size(tv_Param,LV_HOR_RES,525); /// 130 car la longueur des boutons est de 130
		lv_obj_set_pos(tv_Param,0,-135);
		lv_page_set_scrl_fit(tv_Param,false,false);
		lv_page_set_scrl_height(tv_Param, lv_obj_get_height(tv_Param));
		lv_page_set_scrl_width(tv_Param, lv_obj_get_width(tv_Param));
		lv_obj_set_hidden(tv_Param,true);


		tab_param_home = lv_tabview_add_tab(tv_Param,"HOME");
			lv_page_set_scrl_fit(tab_param_home,false,false);
			lv_page_set_scrl_height(tab_param_home, lv_obj_get_height(tab_param_home));
			lv_page_set_scrl_width(tab_param_home, lv_obj_get_width(tab_param_home));
			lv_page_set_sb_mode(tab_param_home,false);


		tab_param_wifi = lv_tabview_add_tab(tv_Param,"WIFI");
			lv_page_set_scrl_fit(tab_param_wifi,false,false);
			lv_page_set_scrl_height(tab_param_wifi, lv_obj_get_height(tab_param_wifi));
			lv_page_set_scrl_width(tab_param_wifi, lv_obj_get_width(tab_param_wifi));
			lv_page_set_sb_mode(tab_param_wifi,false);

		tab_param_canbus = lv_tabview_add_tab(tv_Param,"CANBUS");
			lv_page_set_scrl_fit(tab_param_canbus,false,false);
			lv_page_set_scrl_height(tab_param_canbus, lv_obj_get_height(tab_param_canbus));
			lv_page_set_scrl_width(tab_param_canbus, lv_obj_get_width(tab_param_canbus));
			lv_page_set_sb_mode(tab_param_canbus,false);

		lv_tabview_set_sliding(tv_Param,true);

		switch_tab(tv_Param,1);


		// cr�ation des objet images

	image_home = lv_img_create(tab_param_home,NULL);
		lv_img_set_src(image_home,&home);
		lv_obj_align(image_home,tab_param_home,LV_ALIGN_CENTER,0,0);
		lv_obj_set_drag_parent(image_home,true);
		lv_obj_set_signal_func(image_home,click_home);

	image_wifi = lv_img_create(tab_param_wifi,NULL);
		lv_img_set_src(image_wifi,&wifi);
		lv_obj_align(image_wifi,tab_param_wifi,LV_ALIGN_CENTER,0,0);

	image_canbus = lv_img_create(tab_param_canbus,NULL);
		lv_img_set_src(image_canbus,&canbus_ico);
		lv_obj_align(image_canbus,tab_param_canbus,LV_ALIGN_CENTER,0,0);
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
	switch_tab(tv_Param,1);
	HAL_Delay(50);
	lv_obj_set_hidden(tv_Princ,true);
	lv_obj_set_hidden(tv_Param,false);
	switch_tab(tv_Princ,1);
	HAL_Delay(50);
}

static lv_res_t position_label (lv_obj_t * child)
{
	int test;
	int test2;
	test = lv_obj_get_x(label_pos_test);
	test2 = lv_obj_get_y(label_pos_test);

	return LV_RES_OK;
}

static lv_res_t click_gauge(lv_obj_t * child)
{
	/*
	HAL_Delay(100);
	if (!lv_indev_is_dragging(indev_list))
	{
		lv_ta_add_text(DEBUG_TB,"CLICK !");
	}
	else
	{
		lv_ta_add_text(DEBUG_TB,"DRAGGING !");
	}
*/
	return LV_RES_OK;
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
	switch_tab(tv_Param,1);

/*
	level++;
	//	switch_window(lv_obj_get_parent(child),ctnParametre);
*/
	return LV_RES_OK;
}

static lv_res_t click_menu_PARAM(lv_obj_t * child)
{

	lv_obj_set_hidden(tv_Param,true);
	lv_obj_set_hidden(tv_Princ,false);

/*
	level++;
	//	switch_window(lv_obj_get_parent(child),ctnParametre);
*/
	return LV_RES_OK;
}

static lv_res_t tab_load_action(lv_obj_t * child)
{
	active_tab = lv_tabview_get_tab_act(tv_Princ);
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
	last_tab = lv_tabview_get_tab_act(tv_Princ);
	switch_tab(tv_Princ,3);
}

void click_Back(lv_obj_t * child)
{
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

void set_cadran (uint16_t no_cadran,uint16_t valeur) // on passe le numero du cadran et ola valeur en param�tre, et on l'affiche dans le cadran en question
{

	char buffer[50];
	itoa(valeur,buffer,2);
	lv_label_set_text(tableau_objet_valeur[no_cadran],buffer);

}
