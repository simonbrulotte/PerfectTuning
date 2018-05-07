/**
 * @file demo.c
 * @Author Simon Brulotte
 * @Brief  Ce fichier contient l'interface graphique pour le projet
 */

/*********************
 *      INCLUDES
 *********************/
#include "demo.h"
#include "ledDriver.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if USE_LV_DEMO


/*********************
 *      DEFINES
 *********************/
#define OFFSET_SLIDER_1 35 // décalage du premier slider car les autres sont alignés dessus
#define OFFSET_ENTRE_SLIDERS 90 // décalage entre les Sliders
#define OFFSET_TEXTBOX_1 30
#define OFFSET_ENTRE_TEXTBOX 90
#define OFFSET_LABEL_1 60
#define OFFSET_ENTRE_LABEL_RGBI 90
#define RANGE_GAUGE 6000
#define RED_LINE 4500

#define POSITION_Y_TEXTBOX_RGBI 155
#define POSITION_Y_SLIDERS_RGBI 220
#define POSITION_Y_LABELS_RGBI 170


#define TAILLE_X_TEXTBOX 70
#define TAILLE_Y_TEXTBOX 50


/**********************
 *      TYPEDEFS
 **********************/



/**********************
 *  STATIC PROTOTYPES
 **********************/
void set_leds(void);
static lv_res_t actionCheckBox(lv_obj_t * checkbox);
static lv_res_t actionSlider_R(lv_obj_t * slider);
static lv_res_t actionSlider_G(lv_obj_t * slider);
static lv_res_t actionSlider_B(lv_obj_t * slider);
static lv_res_t actionSlider_I(lv_obj_t * slider);
static lv_res_t actionSlider_gauge(lv_obj_t * slider);

/**********************
 *  STATIC VARIABLES
 **********************/

lv_obj_t * textbox_R;
lv_obj_t * textbox_G;
lv_obj_t * textbox_B;
lv_obj_t * textbox_I;

lv_obj_t * slider_R;
lv_obj_t * slider_G;
lv_obj_t * slider_B;
lv_obj_t * slider_I;
lv_obj_t * label_Param;
lv_obj_t * cbox_DELs;

lv_obj_t * gauge;
lv_obj_t * slider_gauge;

lv_obj_t * tabview;


/**********************
 *      MACROS
 **********************/




/**********************
 *   GLOBAL FUNCTIONS
 **********************/


lv_obj_t * DEBUG;
#define offset_ecran -135 // pour ajuster le offset pour cacher les tabviews

void demo_create(void)
{
	turnOffBar();
	/**********************
	*
	* CONFIGURATION TABVIEW
	*
	***********************/

	static lv_style_t style_tabview;
	lv_style_copy(&style_tabview, &lv_style_plain);
	style_tabview.body.main_color = LV_COLOR_SILVER;
	style_tabview.body.border.color = LV_COLOR_GRAY;
	style_tabview.body.border.width = 1;
	style_tabview.body.border.opa = LV_OPA_50;
	style_tabview.body.padding.hor = 10;            /*Horizontal padding, used by the bar indicator below*/
	style_tabview.body.padding.ver = 10;            /*Vertical padding, used by the bar indicator below*/
	style_tabview.body.padding.inner = 10;


	tabview = lv_tabview_create(lv_scr_act(), NULL);


	lv_tabview_set_style(tabview,LV_TABVIEW_STYLE_BG,&style_tabview);


	lv_tabview_set_sliding(tabview,false);

	lv_obj_t *tab1 = lv_tabview_add_tab(tabview, "Config");
	lv_obj_t *tab2 = lv_tabview_add_tab(tabview, "Gauge");
	lv_obj_t *tab3 = lv_tabview_add_tab(tabview, "Debug");
	lv_obj_t *tab4 = lv_tabview_add_tab(tabview, "Led Setup");

	//lv_obj_set_pos(tabview,0,offset_ecran);  // Puisque qu'on ne peut pas désactiver le tabview ,  on fait un offset à l'écran en déplacant la position de l'objet

	DEBUG = lv_ta_create(tab3, NULL);
	lv_obj_set_size(DEBUG,360,360);
	lv_ta_set_text(DEBUG,"DEBUG \n");

	/***********************
	*
	* CONFIGURATION Gauge
	*
	************************/

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

	gauge = lv_gauge_create(tab2,NULL);
	lv_obj_set_size(gauge,440,480);
	lv_gauge_set_style(gauge, &style_gauge);
	lv_gauge_set_range(gauge,0,RANGE_GAUGE);
	lv_gauge_set_critical_value(gauge, RED_LINE);
	lv_gauge_set_scale(gauge,240,(RANGE_GAUGE/200),(RANGE_GAUGE/1000)+1);

	slider_gauge = lv_slider_create(tab2,NULL);
	lv_obj_set_size(slider_gauge,400,60);
	lv_obj_align(slider_gauge,gauge,LV_ALIGN_IN_BOTTOM_MID,0,0);
	lv_slider_set_action(slider_gauge,actionSlider_gauge);
	lv_slider_set_range(slider_gauge,0,RANGE_GAUGE);




	/***********************
	*
	* CONFIGURATION Checkbox
	*
	************************/
	static lv_style_t style_border;
	lv_style_copy(&style_border, &lv_style_pretty_color);
	style_border.glass = 1;
	style_border.body.empty = 1;

	cbox_DELs = lv_cb_create(tab1,NULL);
	lv_obj_set_size(cbox_DELs,100,10);
	lv_cb_set_text(cbox_DELs,"Activer les DELs");

	lv_obj_align(cbox_DELs,tabview,LV_ALIGN_CENTER,0,0);

	lv_cb_set_action(cbox_DELs,actionCheckBox);


	/*********************
	*
	* CONFIGURATION LABELS
	*
	**********************/

	lv_obj_t * label_R = lv_label_create(tab1,NULL);
	lv_obj_t * label_G = lv_label_create(tab1,NULL);
	lv_obj_t * label_B = lv_label_create(tab1,NULL);
	lv_obj_t * label_I = lv_label_create(tab1,NULL);

	lv_label_set_text(label_R,"R");
	lv_label_set_text(label_G,"G");
	lv_label_set_text(label_B,"B");
	lv_label_set_text(label_I,"I");

	lv_obj_align(label_R,tab1,LV_ALIGN_IN_TOP_LEFT,OFFSET_LABEL_1,POSITION_Y_LABELS_RGBI);
	lv_obj_align(label_G,label_R,LV_ALIGN_IN_TOP_LEFT,OFFSET_ENTRE_LABEL_RGBI,0);
	lv_obj_align(label_B,label_G,LV_ALIGN_IN_TOP_LEFT,OFFSET_ENTRE_LABEL_RGBI,0);
	lv_obj_align(label_I,label_B,LV_ALIGN_IN_TOP_LEFT,OFFSET_ENTRE_LABEL_RGBI,0);



	/***************************
	*
	* CONFIGURATION DES TEXTBOXS
	*
	****************************/

	textbox_R = lv_ta_create(tab1,NULL);
	lv_obj_set_size(textbox_R,TAILLE_X_TEXTBOX,TAILLE_Y_TEXTBOX);
	lv_obj_align(textbox_R,tab1,LV_ALIGN_IN_TOP_LEFT,OFFSET_TEXTBOX_1,POSITION_Y_TEXTBOX_RGBI);
	lv_ta_set_text(textbox_R,"0");

	textbox_G = lv_ta_create(tab1,NULL);
	lv_obj_set_size(textbox_G,TAILLE_X_TEXTBOX,TAILLE_Y_TEXTBOX);
	lv_obj_align(textbox_G,textbox_R,LV_ALIGN_IN_TOP_RIGHT,OFFSET_ENTRE_TEXTBOX,0);
	lv_ta_set_text(textbox_G,"0");

	textbox_B = lv_ta_create(tab1,NULL);
	lv_obj_set_size(textbox_B,TAILLE_X_TEXTBOX,TAILLE_Y_TEXTBOX);
	lv_obj_align(textbox_B,textbox_G,LV_ALIGN_IN_TOP_RIGHT,OFFSET_ENTRE_TEXTBOX,0);
	lv_ta_set_text(textbox_B,"0");

	//intensité des leds
	textbox_I = lv_ta_create(tab1,NULL);
	lv_obj_set_size(textbox_I,TAILLE_X_TEXTBOX,TAILLE_Y_TEXTBOX);
	lv_obj_align(textbox_I,textbox_B,LV_ALIGN_IN_TOP_RIGHT,OFFSET_ENTRE_TEXTBOX,0);
	lv_ta_set_text(textbox_I,"0");



	lv_ta_set_cursor_type(textbox_R,LV_CURSOR_HIDDEN);
	lv_ta_set_cursor_type(textbox_G,LV_CURSOR_HIDDEN);
	lv_ta_set_cursor_type(textbox_B,LV_CURSOR_HIDDEN);
	lv_ta_set_cursor_type(textbox_I,LV_CURSOR_HIDDEN);


	/**************************
	*
	* CONFIGURATION DES SLIDERS
	*
	***************************/

	slider_R = lv_slider_create(tab1,NULL);
	lv_obj_set_size(slider_R,60,200);
	lv_obj_align(slider_R,tab1,LV_ALIGN_IN_TOP_LEFT,OFFSET_SLIDER_1,POSITION_Y_SLIDERS_RGBI);
	lv_slider_set_action(slider_R,actionSlider_R);
	lv_slider_set_range(slider_R,0,255);

	slider_G = lv_slider_create(tab1,NULL);
	lv_obj_set_size(slider_G,60,200);
	lv_obj_align(slider_G,slider_R,LV_ALIGN_IN_TOP_LEFT,OFFSET_ENTRE_SLIDERS,0);
	lv_slider_set_action(slider_G,actionSlider_G);
	lv_slider_set_range(slider_G,0,255);

	slider_B = lv_slider_create(tab1,NULL);
	lv_obj_set_size(slider_B,60,200);
	lv_obj_align(slider_B,slider_G,LV_ALIGN_IN_TOP_LEFT,OFFSET_ENTRE_SLIDERS,0);
	lv_slider_set_action(slider_B,actionSlider_B);
	lv_slider_set_range(slider_B,0,255);

	slider_I = lv_slider_create(tab1,NULL);
	lv_obj_set_size(slider_I,60,200);
	lv_obj_align(slider_I,slider_B,LV_ALIGN_IN_TOP_LEFT,OFFSET_ENTRE_SLIDERS,0);
	lv_slider_set_action(slider_I,actionSlider_I);
	lv_slider_set_range(slider_I,0,100);

}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static lv_res_t actionSlider_R(lv_obj_t * slider)
{
	int a=lv_slider_get_value(slider);
	char buffer[50];
	itoa(a,buffer,10);
	lv_ta_set_text(textbox_R,buffer);
	//
	// AJOUTER CODE POUR CONTROLER DELs
	//
	set_leds();
}

static lv_res_t actionSlider_G(lv_obj_t * slider)
{
	int a=lv_slider_get_value(slider);
	char buffer[50];
	itoa(a,buffer,10);
	lv_ta_set_text(textbox_G,buffer);
	//
	// AJOUTER CODE POUR CONTROLER DELs
	//
	set_leds();

}

static lv_res_t actionSlider_B(lv_obj_t * slider)
{
	int a=lv_slider_get_value(slider);
	char buffer[50];
	itoa(a,buffer,10);
	lv_ta_set_text(textbox_B,buffer);
	//
	// AJOUTER CODE POUR CONTROLER DELs
	//
	set_leds();
}

static lv_res_t actionSlider_I(lv_obj_t * slider)
{
	int a=lv_slider_get_value(slider);
	char buffer[50];
	itoa(a,buffer,10);
	lv_ta_set_text(textbox_I,buffer);
	//
	// AJOUTER CODE POUR CONTROLER DELs
	//
	//set_leds();
}

static lv_res_t actionSlider_gauge(lv_obj_t * slider)
{
	int a=(lv_slider_get_value(slider));
	lv_gauge_set_value(gauge,NULL,a);
	//
	// AJOUTER CODE POUR CONTROLER DELs
	//

}

/*
static lv_res_t actionCheckBox(lv_obj_t * checkbox)
{
	if (cbox_Ledon)
	{
		cbox_Ledon = false;
		turnOffBar();
	}
	else
	{
		cbox_Ledon = true;
		set_leds();

	}
}

void set_leds()
{
	if (cbox_Ledon)
	{
		int i=0;
		for (i=0;i<N_LEDS;i++)
		{
			ws2812_set_color(i,(uint8_t)lv_slider_get_value(slider_R),(uint8_t)lv_slider_get_value(slider_G),(uint8_t)lv_slider_get_value(slider_B));
		}
		led_flag = true;
	}
}
*/

#endif  /*USE_LV_DEMO*/
