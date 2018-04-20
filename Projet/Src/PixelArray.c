#include "PixelArray.h"

//Variables declarations

extern int *pbuf;
int pbufsize;

void __set_pixel_component(int index, int channel, int value);
void __set_pixel(int index, int value);


void initPixelArray(int size)
{
    pbufsize = size;
    pbuf[pbufsize];
    SetAll(0x0); // initialise memory to zeros
}


void SetAll(unsigned int value)
{
    // for each pixel
    for (int i=0 ; i < pbufsize; i++) {
        __set_pixel(i,value);
    }
}


void SetAllI(unsigned char value)
{
    // for each pixel
    for (int i=0 ; i < pbufsize; i++) {
        __set_pixel_component(i,3,value);
    }
}


void SetAllR(unsigned char value)
{
    // for each pixel
    for (int i=0 ; i < pbufsize; i++) {
        __set_pixel_component(i,2,value);
    }
}


void SetAllG(unsigned char value)
{
    // for each pixel
    for (int i=0 ; i < pbufsize; i++) {
        __set_pixel_component(i,1,value);
    }
}


void SetAllB(unsigned char value)
{
    // for each pixel
    for (int i=0 ; i < pbufsize; i++) {
        __set_pixel_component(i,0,value);
    }
}


void Set(int i, unsigned int value)
{
    if ((i >= 0) && (i < pbufsize)) {
        __set_pixel(i,value);
    }
}


void SetI(int i, unsigned char value)
{
    if ((i >= 0) && (i < pbufsize)) {
        __set_pixel_component(i,3,value);
    }
}


void SetR(int i, unsigned char value)
{
    if ((i >= 0) && (i < pbufsize)) {
        __set_pixel_component(i,2,value);
    }
}


void SetG(int i, unsigned char value)
{
    if ((i >= 0) && (i < pbufsize)) {
        __set_pixel_component(i,1,value);
    }
}


void SetB(int i, unsigned char value)
{
    if ((i >= 0) && (i < pbufsize)) {
        __set_pixel_component(i,0,value);
    }
}


int* getBuf()
{
    return (pbuf);
}

// set either the I,R,G,B value of specific pixel channel
void __set_pixel_component(int index, int channel, int value)
{

    // AND with 0x00 shifted to the right location to clear the bits
    pbuf[index] &= ~(0xFF << (8 * channel));

    // Set the bits with an OR
    pbuf[index] |= (value << (8 * channel));
}

// set either the I,R,G,B value of specific pixel channel
void __set_pixel(int index, int value)
{
    // AND with 0x00 shifted to the right location to clear the bits
    pbuf[index] = value;
}


