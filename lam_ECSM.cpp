// lam_ECSM.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include "def.h"
#include "time.h"

u_int cbuff[11];
u_int S[256];

//======================================================================//
//                                                                      //
// *****************       Arithmetic of F(2^163)      *****************//
//                                                                      //
//======================================================================//

void sTable(void)// insert 0 between every bit of k={1,256}
{
	int i, ss;
	for(i = 0; i < 256; i++)
	{
		ss = i;

		S[i] = ss / 128;
		ss = ss % 128;

		S[i] = S[i] * 4 + ss / 64;
		ss = ss % 64;

		
		S[i] = S[i] * 4 + ss / 32;
		ss = ss % 32;

		
		S[i] = S[i] * 4 + ss / 16;
		ss = ss % 16;

		
		S[i] = S[i] * 4 + ss / 8;
		ss = ss % 8;

		
		S[i] = S[i] * 4 + ss / 4;
		ss = ss % 4;

		
		S[i] = S[i] * 4 + ss / 2;
		ss = ss % 2;

		S[i] = S[i] * 4 + ss;
		
		
	}
}

void MReduce_163(u_int *a)//mod f(x) = x163 + x8 + x2 + x + 1.
{

	a[5] ^= (a[10]<<5)^(a[10]>>1)^(a[10]>>2)^(a[10]>>3)^(a[9]>>27);
	a[4] ^= (a[10]<<31)^(a[10]<<30)^(a[10]<<29)^(a[9]<<5)^(a[9]>>1)^(a[9]>>2)^(a[9]>>3)^(a[8]>>27);
	a[3] ^= (a[9]<<31)^(a[9]<<30)^(a[9]<<29)^(a[8]<<5)^(a[8]>>1)^(a[8]>>2)^(a[8]>>3)^(a[7]>>27);
	a[2] ^= (a[8]<<31)^(a[8]<<30)^(a[8]<<29)^(a[7]<<5)^(a[7]>>1)^(a[7]>>2)^(a[7]>>3)^(a[6]>>27);
	a[1] ^= (a[7]<<31)^(a[7]<<30)^(a[7]<<29)^(a[6]<<5)^(a[6]>>1)^(a[6]>>2)^(a[6]>>3)^(a[5]>>27);
	a[10] = (a[5]&0xfffffff8);
	a[0] ^= (a[6]<<31)^(a[6]<<30)^(a[6]<<29)^(a[10]<<5)^(a[10]>>1)^(a[10]>>2)^(a[10]>>3);
	a[5] &= 0x7;

}

void Substitute(u_int *a, u_int *b)
{
	b[0] = a[0]; 
	b[1] = a[1]; 
	b[2] = a[2]; 
	b[3] = a[3]; 
	b[4] = a[4]; 
	b[5] = a[5]; 
}

void Gfm_163(u_int *a, u_int *b, u_int *c)
{
	int k, k1, k2, k3, k4, k5;
	u_int  P[96], ss, tt;

				a[5] &= 0x7; b[5] &=0x7;
				P[6*0+0] = 0;
				P[6*0+1] = 0;
				P[6*0+2] = 0;
				P[6*0+3] = 0;
				P[6*0+4] = 0;
				P[6*0+5] = 0;			
				P[6*1+0] = b[0];
				P[6*1+1] = b[1];
				P[6*1+2] = b[2];
				P[6*1+3] = b[3];
				P[6*1+4] = b[4];
				P[6*1+5] = b[5];
				P[6*2+0] = b[0]<<1;
				P[6*2+1] = (b[0]>>31)^(b[1]<<1);
				P[6*2+2] = (b[1]>>31)^(b[2]<<1);
				P[6*2+3] = (b[2]>>31)^(b[3]<<1);
				P[6*2+4] = (b[3]>>31)^(b[4]<<1);
				P[6*2+5] = (b[4]>>31)^(b[5]<<1);
				P[6*3+0] = P[6*1+0]^P[6*2+0];
				P[6*3+1] = P[6*1+1]^P[6*2+1];
				P[6*3+2] = P[6*1+2]^P[6*2+2];
				P[6*3+3] = P[6*1+3]^P[6*2+3];
				P[6*3+4] = P[6*1+4]^P[6*2+4];
				P[6*3+5] = P[6*1+5]^P[6*2+5];
				P[6*4+0] = b[0]<<2;
				P[6*4+1] = (b[0]>>30)^(b[1]<<2);
				P[6*4+2] = (b[1]>>30)^(b[2]<<2);
				P[6*4+3] = (b[2]>>30)^(b[3]<<2);
				P[6*4+4] = (b[3]>>30)^(b[4]<<2);
				P[6*4+5] = (b[4]>>30)^(b[5]<<2);
				P[6*5+0] = P[6*1+0]^P[6*4+0];
				P[6*5+1] = P[6*1+1]^P[6*4+1];
				P[6*5+2] = P[6*1+2]^P[6*4+2];
				P[6*5+3] = P[6*1+3]^P[6*4+3];
				P[6*5+4] = P[6*1+4]^P[6*4+4];
				P[6*5+5] = P[6*1+5]^P[6*4+5];
				P[6*6+0] = P[6*2+0]^P[6*4+0];
				P[6*6+1] = P[6*2+1]^P[6*4+1];
				P[6*6+2] = P[6*2+2]^P[6*4+2];
				P[6*6+3] = P[6*2+3]^P[6*4+3];
				P[6*6+4] = P[6*2+4]^P[6*4+4];
				P[6*6+5] = P[6*2+5]^P[6*4+5];
				P[6*7+0] = P[6*3+0]^P[6*4+0];
				P[6*7+1] = P[6*3+1]^P[6*4+1];
				P[6*7+2] = P[6*3+2]^P[6*4+2];
				P[6*7+3] = P[6*3+3]^P[6*4+3];
				P[6*7+4] = P[6*3+4]^P[6*4+4];
				P[6*7+5] = P[6*3+5]^P[6*4+5];
				P[6*8+0] = b[0]<<3;
				P[6*8+1] = (b[0]>>29)^(b[1]<<3);
				P[6*8+2] = (b[1]>>29)^(b[2]<<3);
				P[6*8+3] = (b[2]>>29)^(b[3]<<3);
				P[6*8+4] = (b[3]>>29)^(b[4]<<3);
				P[6*8+5] = (b[4]>>29)^(b[5]<<3);
				P[6*9+0] = P[6*8+0]^P[6*1+0];
				P[6*9+1] = P[6*8+1]^P[6*1+1];
				P[6*9+2] = P[6*8+2]^P[6*1+2];
				P[6*9+3] = P[6*8+3]^P[6*1+3];
				P[6*9+4] = P[6*8+4]^P[6*1+4];
				P[6*9+5] = P[6*8+5]^P[6*1+5];
				P[6*10+0] = P[6*2+0]^P[6*8+0];
				P[6*10+1] = P[6*2+1]^P[6*8+1];
				P[6*10+2] = P[6*2+2]^P[6*8+2];
				P[6*10+3] = P[6*2+3]^P[6*8+3];
				P[6*10+4] = P[6*2+4]^P[6*8+4];
				P[6*10+5] = P[6*2+5]^P[6*8+5];
				P[6*11+0] = P[6*3+0]^P[6*8+0];
				P[6*11+1] = P[6*3+1]^P[6*8+1];
				P[6*11+2] = P[6*3+2]^P[6*8+2];
				P[6*11+3] = P[6*3+3]^P[6*8+3];
				P[6*11+4] = P[6*3+4]^P[6*8+4];
				P[6*11+5] = P[6*3+5]^P[6*8+5];
				P[6*12+0] = P[6*4+0]^P[6*8+0];
				P[6*12+1] = P[6*4+1]^P[6*8+1];
				P[6*12+2] = P[6*4+2]^P[6*8+2];
				P[6*12+3] = P[6*4+3]^P[6*8+3];
				P[6*12+4] = P[6*4+4]^P[6*8+4];
				P[6*12+5] = P[6*4+5]^P[6*8+5];
				P[6*13+0] = P[6*5+0]^P[6*8+0];
				P[6*13+1] = P[6*5+1]^P[6*8+1];
				P[6*13+2] = P[6*5+2]^P[6*8+2];
				P[6*13+3] = P[6*5+3]^P[6*8+3];
				P[6*13+4] = P[6*5+4]^P[6*8+4];
				P[6*13+5] = P[6*5+5]^P[6*8+5];
				P[6*14+0] = P[6*6+0]^P[6*8+0];
				P[6*14+1] = P[6*6+1]^P[6*8+1];
				P[6*14+2] = P[6*6+2]^P[6*8+2];
				P[6*14+3] = P[6*6+3]^P[6*8+3];
				P[6*14+4] = P[6*6+4]^P[6*8+4];
				P[6*14+5] = P[6*6+5]^P[6*8+5];
				P[6*15+0] = P[6*7+0]^P[6*8+0];
				P[6*15+1] = P[6*7+1]^P[6*8+1];
				P[6*15+2] = P[6*7+2]^P[6*8+2];
				P[6*15+3] = P[6*7+3]^P[6*8+3];
				P[6*15+4] = P[6*7+4]^P[6*8+4];
				P[6*15+5] = P[6*7+5]^P[6*8+5];

 			k  = (a[0]>>28)*6;
			k1 = (a[1]>>28)*6;
			k2 = (a[2]>>28)*6;
			k3 = (a[3]>>28)*6;
			k4 = (a[4]>>28)*6;
			tt = P[k];
			cbuff[0] = tt<<4;
			ss = P[k+1]^P[k1];
			tt = tt >> 28;
			cbuff[1] = (ss<<4)^tt;
			tt = ss >> 28;
			ss = P[k+2]^P[k1+1]^P[k2];
			cbuff[2] = (ss<<4)^tt;
			tt = ss >> 28;			
			ss = P[k+3]^P[k1+2]^P[k2+1]^P[k3];
			cbuff[3] = (ss<<4)^tt;
			tt = ss >> 28;
			ss = P[k+4]^P[k1+3]^P[k2+2]^P[k3+1]^P[k4];
			cbuff[4] = (ss<<4)^tt;
			tt = ss >> 28;
			ss = P[k+5]^P[k1+4]^P[k2+3]^P[k3+2]^P[k4+1];
			cbuff[5] = (ss<<4)^tt;
			tt = ss >> 28;
			ss = P[k1+5]^P[k2+4]^P[k3+3]^P[k4+2];
			cbuff[6] = (ss<<4)^tt;
			tt = ss >> 28;			
			ss = P[k2+5]^P[k3+4]^P[k4+3];
			cbuff[7] = (ss<<4)^tt;
			tt = ss >> 28;	
			ss = P[k3+5]^P[k4+4];
			cbuff[8] = (ss<<4)^tt;
			tt = ss >> 28;	
			ss = P[k4+5];
			cbuff[9] = (ss<<4)^tt;
			cbuff[10] = ss >> 28;
			k = ((a[0]&0x0f000000)>>24)*6;
			k1 = ((a[1]&0x0f000000)>>24)*6;
			k2 = ((a[2]&0x0f000000)>>24)*6;
			k3 = ((a[3]&0x0f000000)>>24)*6;
			k4 = ((a[4]&0x0f000000)>>24)*6;
			tt = cbuff[0]^P[k];
			cbuff[0] = tt << 4;
			tt = tt >> 28;
			ss = cbuff[1]^P[k+1]^P[k1];
			cbuff[1] = (ss<<4)^tt;
			tt = ss >> 28;
			ss = cbuff[2]^P[k+2]^P[k1+1]^P[k2];
			cbuff[2] = (ss<<4)^tt;
			tt = ss >> 28;			
			ss = cbuff[3]^P[k+3]^P[k1+2]^P[k2+1]^P[k3];
			cbuff[3] = (ss<<4)^tt;
			tt = ss >> 28;
			ss = cbuff[4]^P[k+4]^P[k1+3]^P[k2+2]^P[k3+1]^P[k4];
			cbuff[4] = (ss<<4)^tt;
			tt = ss >> 28;
			ss = cbuff[5]^P[k+5]^P[k1+4]^P[k2+3]^P[k3+2]^P[k4+1];
			cbuff[5] = (ss<<4)^tt;
			tt = ss >> 28;
			ss = cbuff[6]^P[k1+5]^P[k2+4]^P[k3+3]^P[k4+2];
			cbuff[6] = (ss<<4)^tt;
			tt = ss >> 28;			
			ss = cbuff[7]^P[k2+5]^P[k3+4]^P[k4+3];
			cbuff[7] = (ss<<4)^tt;
			tt = ss >> 28;	
			ss = cbuff[8]^P[k3+5]^P[k4+4];
			cbuff[8] = (ss<<4)^tt;
			tt = ss >> 28;	
			ss = cbuff[9]^P[k4+5];
			cbuff[9] = (ss<<4)^tt;
			tt = ss >> 28;	
			ss = cbuff[10];
			cbuff[10] = (ss<<4)^tt;	
			k = ((a[0]&0x00f00000)>>20)*6;
			k1 = ((a[1]&0x00f00000)>>20)*6;
			k2 = ((a[2]&0x00f00000)>>20)*6;
			k3 = ((a[3]&0x00f00000)>>20)*6;
			k4 = ((a[4]&0x00f00000)>>20)*6;
			tt = cbuff[0]^P[k+0];
			cbuff[0] = tt << 4;
			tt = tt >> 28;
			ss = cbuff[1]^P[k+1]^P[k1];
			cbuff[1] = (ss<<4)^tt;
			tt = ss >> 28;
			ss = cbuff[2]^P[k+2]^P[k1+1]^P[k2];
			cbuff[2] = (ss<<4)^tt;
			tt = ss >> 28;			
			ss = cbuff[3]^P[k+3]^P[k1+2]^P[k2+1]^P[k3];
			cbuff[3] = (ss<<4)^tt;
			tt = ss >> 28;
			ss = cbuff[4]^P[k+4]^P[k1+3]^P[k2+2]^P[k3+1]^P[k4];
			cbuff[4] = (ss<<4)^tt;
			tt = ss >> 28;
			ss = cbuff[5]^P[k+5]^P[k1+4]^P[k2+3]^P[k3+2]^P[k4+1];
			cbuff[5] = (ss<<4)^tt;
			tt = ss >> 28;
			ss = cbuff[6]^P[k1+5]^P[k2+4]^P[k3+3]^P[k4+2];
			cbuff[6] = (ss<<4)^tt;
			tt = ss >> 28;			
			ss = cbuff[7]^P[k2+5]^P[k3+4]^P[k4+3];
			cbuff[7] = (ss<<4)^tt;
			tt = ss >> 28;	
			ss = cbuff[8]^P[k3+5]^P[k4+4];
			cbuff[8] = (ss<<4)^tt;
			tt = ss >> 28;	
			ss = cbuff[9]^P[k4+5];
			cbuff[9] = (ss<<4)^tt;
			tt = ss >> 28;	
			ss = cbuff[10];
			cbuff[10] = (ss<<4)^tt;
			k = ((a[0]&0x000f0000)>>16)*6;
			k1 = ((a[1]&0x000f0000)>>16)*6;
			k2 = ((a[2]&0x000f0000)>>16)*6;
			k3 = ((a[3]&0x000f0000)>>16)*6;
			k4 = ((a[4]&0x000f0000)>>16)*6;
			tt = cbuff[0]^P[k];
			cbuff[0] = tt << 4;
			tt = tt >> 28;
			ss = cbuff[1]^P[k+1]^P[k1];
			cbuff[1] = (ss<<4)^tt;
			tt = ss >> 28;
			ss = cbuff[2]^P[k+2]^P[k1+1]^P[k2];
			cbuff[2] = (ss<<4)^tt;
			tt = ss >> 28;			
			ss = cbuff[3]^P[k+3]^P[k1+2]^P[k2+1]^P[k3];
			cbuff[3] = (ss<<4)^tt;
			tt = ss >> 28;
			ss = cbuff[4]^P[k+4]^P[k1+3]^P[k2+2]^P[k3+1]^P[k4];
			cbuff[4] = (ss<<4)^tt;
			tt = ss >> 28;
			ss = cbuff[5]^P[k+5]^P[k1+4]^P[k2+3]^P[k3+2]^P[k4+1];
			cbuff[5] = (ss<<4)^tt;
			tt = ss >> 28;
			ss = cbuff[6]^P[k1+5]^P[k2+4]^P[k3+3]^P[k4+2];
			cbuff[6] = (ss<<4)^tt;
			tt = ss >> 28;			
			ss = cbuff[7]^P[k2+5]^P[k3+4]^P[k4+3];
			cbuff[7] = (ss<<4)^tt;
			tt = ss >> 28;	
			ss = cbuff[8]^P[k3+5]^P[k4+4];
			cbuff[8] = (ss<<4)^tt;
			tt = ss >> 28;	
			ss = cbuff[9]^P[k4+5];
			cbuff[9] = (ss<<4)^tt;
			tt = ss >> 28;	
			ss = cbuff[10];
			cbuff[10] = (ss<<4)^tt;
			k = ((a[0]&0x0000f000)>>12)*6;
			k1 = ((a[1]&0x0000f000)>>12)*6;
			k2 = ((a[2]&0x0000f000)>>12)*6;
			k3 = ((a[3]&0x0000f000)>>12)*6;
			k4 = ((a[4]&0x0000f000)>>12)*6;	
			tt = cbuff[0]^P[k];
			cbuff[0] = tt << 4;
			tt = tt >> 28;
			ss = cbuff[1]^P[k+1]^P[k1];
			cbuff[1] = (ss<<4)^tt;
			tt = ss >> 28;
			ss = cbuff[2]^P[k+2]^P[k1+1]^P[k2];
			cbuff[2] = (ss<<4)^tt;
			tt = ss >> 28;			
			ss = cbuff[3]^P[k+3]^P[k1+2]^P[k2+1]^P[k3];
			cbuff[3] = (ss<<4)^tt;
			tt = ss >> 28;
			ss = cbuff[4]^P[k+4]^P[k1+3]^P[k2+2]^P[k3+1]^P[k4];
			cbuff[4] = (ss<<4)^tt;
			tt = ss >> 28;
			ss = cbuff[5]^P[k+5]^P[k1+4]^P[k2+3]^P[k3+2]^P[k4+1];
			cbuff[5] = (ss<<4)^tt;
			tt = ss >> 28;
			ss = cbuff[6]^P[k1+5]^P[k2+4]^P[k3+3]^P[k4+2];
			cbuff[6] = (ss<<4)^tt;
			tt = ss >> 28;			
			ss = cbuff[7]^P[k2+5]^P[k3+4]^P[k4+3];
			cbuff[7] = (ss<<4)^tt;
			tt = ss >> 28;	
			ss = cbuff[8]^P[k3+5]^P[k4+4];
			cbuff[8] = (ss<<4)^tt;
			tt = ss >> 28;	
			ss = cbuff[9]^P[k4+5];
			cbuff[9] = (ss<<4)^tt;
			tt = ss >> 28;	
			ss = cbuff[10];
			cbuff[10] = (ss<<4)^tt;
			k = ((a[0]&0x00000f00)>>8)*6;
			k1 = ((a[1]&0x00000f00)>>8)*6;
			k2 = ((a[2]&0x00000f00)>>8)*6;
			k3 = ((a[3]&0x00000f00)>>8)*6;
			k4 = ((a[4]&0x00000f00)>>8)*6;
			tt = cbuff[0]^P[k];
			cbuff[0] = tt << 4;
			tt = tt >> 28;
			ss = cbuff[1]^P[k+1]^P[k1];
			cbuff[1] = (ss<<4)^tt;
			tt = ss >> 28;
			ss = cbuff[2]^P[k+2]^P[k1+1]^P[k2];
			cbuff[2] = (ss<<4)^tt;
			tt = ss >> 28;			
			ss = cbuff[3]^P[k+3]^P[k1+2]^P[k2+1]^P[k3];
			cbuff[3] = (ss<<4)^tt;
			tt = ss >> 28;
			ss = cbuff[4]^P[k+4]^P[k1+3]^P[k2+2]^P[k3+1]^P[k4];
			cbuff[4] = (ss<<4)^tt;
			tt = ss >> 28;
			ss = cbuff[5]^P[k+5]^P[k1+4]^P[k2+3]^P[k3+2]^P[k4+1];
			cbuff[5] = (ss<<4)^tt;
			tt = ss >> 28;
			ss = cbuff[6]^P[k1+5]^P[k2+4]^P[k3+3]^P[k4+2];
			cbuff[6] = (ss<<4)^tt;
			tt = ss >> 28;			
			ss = cbuff[7]^P[k2+5]^P[k3+4]^P[k4+3];
			cbuff[7] = (ss<<4)^tt;
			tt = ss >> 28;	
			ss = cbuff[8]^P[k3+5]^P[k4+4];
			cbuff[8] = (ss<<4)^tt;
			tt = ss >> 28;	
			ss = cbuff[9]^P[k4+5];
			cbuff[9] = (ss<<4)^tt;
			tt = ss >> 28;	
			ss = cbuff[10];
			cbuff[10] = (ss<<4)^tt;
			k = ((a[0]&0x000000f0)>>4)*6;
			k1 = ((a[1]&0x000000f0)>>4)*6;
			k2 = ((a[2]&0x000000f0)>>4)*6;
			k3 = ((a[3]&0x000000f0)>>4)*6;
			k4 = ((a[4]&0x000000f0)>>4)*6;	
			tt = cbuff[0]^P[k];
			cbuff[0] = tt << 4;
			tt = tt >> 28;
			ss = cbuff[1]^P[k+1]^P[k1];
			cbuff[1] = (ss<<4)^tt;
			tt = ss >> 28;
			ss = cbuff[2]^P[k+2]^P[k1+1]^P[k2];
			cbuff[2] = (ss<<4)^tt;
			tt = ss >> 28;			
			ss = cbuff[3]^P[k+3]^P[k1+2]^P[k2+1]^P[k3];
			cbuff[3] = (ss<<4)^tt;
			tt = ss >> 28;
			ss = cbuff[4]^P[k+4]^P[k1+3]^P[k2+2]^P[k3+1]^P[k4];
			cbuff[4] = (ss<<4)^tt;
			tt = ss >> 28;
			ss = cbuff[5]^P[k+5]^P[k1+4]^P[k2+3]^P[k3+2]^P[k4+1];
			cbuff[5] = (ss<<4)^tt;
			tt = ss >> 28;
			ss = cbuff[6]^P[k1+5]^P[k2+4]^P[k3+3]^P[k4+2];
			cbuff[6] = (ss<<4)^tt;
			tt = ss >> 28;			
			ss = cbuff[7]^P[k2+5]^P[k3+4]^P[k4+3];
			cbuff[7] = (ss<<4)^tt;
			tt = ss >> 28;	
			ss = cbuff[8]^P[k3+5]^P[k4+4];
			cbuff[8] = (ss<<4)^tt;
			tt = ss >> 28;	
			ss = cbuff[9]^P[k4+5];
			cbuff[9] = (ss<<4)^tt;
			tt = ss >> 28;	
			ss = cbuff[10];
			cbuff[10] = (ss<<4)^tt;
			k  = (a[0]&0x0000000f)*6;
			k1 = (a[1]&0x0000000f)*6;
			k2 = (a[2]&0x0000000f)*6;
			k3 = (a[3]&0x0000000f)*6;
			k4 = (a[4]&0x0000000f)*6;
			k5 = (a[5]&0x0000000f)*6;
			cbuff[0] ^= P[k];
			cbuff[1] ^= P[k+1]^P[k1];
			cbuff[2] ^= P[k+2]^P[k1+1]^P[k2];
			cbuff[3] ^= P[k+3]^P[k1+2]^P[k2+1]^P[k3];
			cbuff[4] ^= P[k+4]^P[k1+3]^P[k2+2]^P[k3+1]^P[k4];
			cbuff[5] ^= P[k+5]^P[k1+4]^P[k2+3]^P[k3+2]^P[k4+1]^P[k5];
			cbuff[6] ^= P[k1+5]^P[k2+4]^P[k3+3]^P[k4+2]^P[k5+1];	
			cbuff[7] ^= P[k2+5]^P[k3+4]^P[k4+3]^P[k5+2];
			cbuff[8] ^= P[k3+5]^P[k4+4]^P[k5+3];
			cbuff[9] ^= P[k4+5]^P[k5+4];
			cbuff[10] ^= P[k5+5];

	MReduce_163(cbuff);
	Substitute(cbuff,c);

}

void re_Gfm_163(u_int *a, u_int *b)
{
		Gfm_163(a,b,cbuff);
		Substitute(cbuff,b);
}

void Sqr_163(u_int *a, u_int *c)
{
		cbuff[0] = S[a[0]&0xff];
		cbuff[0] ^= S[(a[0]&0xff00)>>8]<<16;
		cbuff[1] = S[(a[0]&0xff0000)>>16];
		cbuff[1] ^= S[(a[0]&0xff000000)>>24]<<16;
		cbuff[2] = S[a[1]&0xff];
		cbuff[2] ^= S[(a[1]&0xff00)>>8]<<16;
		cbuff[3] = S[(a[1]&0xff0000)>>16];
		cbuff[3] ^= S[(a[1]&0xff000000)>>24]<<16;
		cbuff[4] = S[a[2]&0xff];
		cbuff[4] ^= S[(a[2]&0xff00)>>8]<<16;
		cbuff[5] = S[(a[2]&0xff0000)>>16];
		cbuff[5] ^= S[(a[2]&0xff000000)>>24]<<16;
		cbuff[6] = S[a[3]&0xff];
		cbuff[6] ^= S[(a[3]&0xff00)>>8]<<16;
		cbuff[7] = S[(a[3]&0xff0000)>>16];
		cbuff[7] ^= S[(a[3]&0xff000000)>>24]<<16;
		cbuff[8] = S[a[4]&0xff];
		cbuff[8] ^= S[(a[4]&0xff00)>>8]<<16;
		cbuff[9] = S[(a[4]&0xff0000)>>16];
		cbuff[9] ^= S[(a[4]&0xff000000)>>24]<<16;
		cbuff[10] = S[a[5]&0xff];

		MReduce_163(cbuff);
		Substitute(cbuff,c);

}

void re_Sqr_163(u_int *a)
{
		Sqr_163(a,cbuff);
		Substitute(cbuff,a);
}

void n_Sqr_163(u_int *a, u_int *c, int n)
{
	int i;
	u_int cc[_V];

	Sqr_163(a,c);

	for( i = 1; i < n; i++)
	{
		Substitute(c,cc);
		Sqr_163(cc,c);
	}
}

void re_n_Sqr_163(u_int *a, int n)
{
		n_Sqr_163(a,cbuff,n);
		Substitute(cbuff,a);
}

void Inv_163(u_int *a, u_int *b)
{
	u_int  y2[_V], y3[_V], y5[_V];

	Sqr_163(a,y2);
	re_Gfm_163(a,y2);
	Sqr_163(y2,y3);
	re_Gfm_163(a,y3);
	n_Sqr_163(y3,y5,2);
	re_Gfm_163(y2,y5);
	n_Sqr_163(y5,y3,5);
	re_Gfm_163(y5,y3);
	n_Sqr_163(y3,b,10);
	re_Gfm_163(y3,b);
	n_Sqr_163(b,y5,20);
	re_Gfm_163(b,y5);
	n_Sqr_163(y5,y3,40);
	re_Gfm_163(y5,y3);
	n_Sqr_163(y3,y5,80);
	re_Gfm_163(y5,y3);
	n_Sqr_163(y3,y5,2);
	re_Gfm_163(y5,y2);
	Sqr_163(y2,b);
}

void re_Inv_163(u_int *a)
{
	u_int cc[_V];
	Inv_163(a, cc);
	Substitute(cc,a);
}

void Add_163(u_int *a, u_int *b, u_int *c)
{
	c[0] = a[0] ^ b[0];
	c[1] = a[1] ^ b[1];
	c[2] = a[2] ^ b[2];
	c[3] = a[3] ^ b[3];
	c[4] = a[4] ^ b[4];
	c[5] = a[5] ^ b[5];
}

//////////////////////////////////////////////////////////////////////////

//************************************************************************//
//------------------------------------------------------------------------//
//                                                                        //
//                    Selection of Elliptic Curve                         //
//                                                                        //
//========================================================================//
//************************************************************************//

u_int precomput_PP[_V *_B], precomput_QQ[_V *_B], Lam_precomput_PP[_V *_B], Lam_precomput_QQ[_V *_B], 
curv_a[_V], curv_b[_V], curv_c[_V], co[_V], one[_V], base_x[_V], base_y[_V];

//Curve equation: y^2 + xy = x^3 + ax^2 + b;
// c^2 = b;
//G=(base_x, base_y) is a base point on the curve, order of which is order_n.

void declare()
{	
	curv_a[5] = 0x7; curv_a[4] = 0x2546B543; 
	curv_a[3] = 0x5234A422; curv_a[2] = 0xE0789675;
	curv_a[1] = 0xF432C894; curv_a[0] = 0x35DE5242;
    
	curv_b[5] = 0x0; curv_b[4] = 0xC9517D06; 
	curv_b[3] = 0xD5240D3C; curv_b[2] = 0xFF38C74B;
	curv_b[1] = 0x20B6CD4D; curv_b[0] = 0x6F9DD4D9;

	one[5] = 0; one[4] = 0; one[3] = 0; one[2] = 0; one[1] = 0; one[0] = 1;
	// #(E) = 8 00000000 00000000 0003CC1F 9104398E 9B5D5F82. 
	
	n_Sqr_163(curv_b,curv_c,162); // c=b^(1/2)
	Add_163(curv_a, curv_b, co);
	Add_163(co, one, co);
	n_Sqr_163(co,co,162);
	
	base_x[5] = 0x7; base_x[4] = 0xAF699895;
	base_x[3] = 0x46103D79; base_x[2] = 0x329FCC3D;
	base_x[1] = 0x74880F33; base_x[0] = 0xBBE803CB;
	
	base_y[5] = 0x1; base_y[4] = 0xEC23211B;
	base_y[3] = 0x5966ADEA; base_y[2] = 0x1D3F87F7;
	base_y[1] = 0xEA5848AE; base_y[0] = 0xF0B7CA9F;
	//ord(base point) = 4 00000000 00000000 0001e60f c8821cc7 4daeafc1


}

void Test_curve_equa(u_int *xx, u_int *yy, u_int *C)
{
	int i;
	u_int x[_V], y[_V], D[_V], E[_V];
	
    Sqr_163(xx,x);
    Sqr_163(yy,y);
    Gfm_163(xx,yy,D);
    Gfm_163(curv_a,x,E);
    Gfm_163(xx,x,x);
	
    for( i = 0; i < _V; i++)C[i] = y[i] ^ x[i] ^ D[i] ^ E[i] ^ curv_b[i];
}

///////////////////////////////////////////////////////////////////////////////////////////
//                                                                                       //
//      Elliptic Curve Point Multiplication(Montgomery point multiplication)             // 
//                                                                                       //
//                                                                                       //
//                                                                                       //
///////////////////////////////////////////////////////////////////////////////////////////

void Madd(u_int  *x1, u_int  *z1,
		  u_int  *x2, u_int  *z2, 
		  u_int  *x)
{
	u_int  T1[_V], T2[_V], T3[_V];

    Gfm_163(x1,z2,T1);
    Gfm_163(z1,x2,T2);
	Add_163(T1,T2,T3);
	Sqr_163(T3,z1);
	Gfm_163(T1,T2,T3);	
	Gfm_163(z1,x,T1);
    Add_163(T1,T3,x1);
}

void Mdouble(u_int  *x, u_int  *z)		 
{
	u_int  T1[_V],T2[_V],T3[_V];

	Sqr_163(x,T1);
    Sqr_163(z,T2);
	Gfm_163(T1,T2,z);	
    Gfm_163(curv_c,T2,T3);
	Add_163(T1,T3,T1);
    Sqr_163(T1,x);
}

void Mxy(u_int *x, u_int *y,
		 u_int *x1, u_int *z1,
		 u_int *x2, u_int *z2,
		 u_int *xx, u_int *yy)
{ 
	u_int A[_V], B[_V], C[_V], D[_V], E[_V], F[_V];
 
    Gfm_163(x,z1,A);
    Gfm_163(z1,z2,B);
    Gfm_163(x,z2,C);
    Gfm_163(A,B,D);
	Inv_163(D,E);  
	Add_163(A,x1,A);
    Add_163(x2,C,C);
    Gfm_163(y,D,D);
    Gfm_163(A,C,C);
    Sqr_163(x,F);
    Add_163(F,y,F);
    Gfm_163(F,B,F);
    Add_163(F,C,F);
    Gfm_163(F,A,F);
    Add_163(F,D,F);
    Gfm_163(F,E,yy);
    Gfm_163(x,x1,A);
    Gfm_163(A,B,A);
    Gfm_163(A,E,xx);
}

void Montgomery_EC_Point_Multi(u_int *x, u_int *y, u_int *xx, u_int *yy, u_int *k)
{
	int i, nonzero_bit =0, flag_x = 0, flag_y = 0, flag_k = 0;
	u_int  x1[_V], z1[_V], x2[_V], z2[_V];

	for( i = 0; i < _V; i++) 
	{
		if(x[i]) flag_x = 1;
		if(y[i]) flag_y = 1;
	}

	
	for( i = _B - 1; i >= 0; i--)
	{
		if(k[i]) 
		{ 
			flag_k = 1; nonzero_bit = i; break; 
		}
	}

	if((flag_k == 0)||((flag_x == 0)&&(flag_y == 0)))
	{
		for( i = 0; i < _V; i++){xx[i] = 0; yy[i] = 0;}
	}

	else
	{	

		for( i = 0; i < _V; i++){x1[i] = x[i]; z1[i] = 0;}
		z1[0] = 1;

		Sqr_163(x,z2);	Sqr_163(z2,x2);	Add_163(x2,curv_b,x2);

			for( i = nonzero_bit - 1; i >= 0; i--)
				{
					if(k[i]) { Madd(x1,z1,x2,z2,x);	Mdouble(x2,z2);	}
					else { Madd(x2,z2,x1,z1,x);	Mdouble(x1,z1);	}
				}
		Mxy(x,y,x1,z1,x2,z2,xx,yy);
	}
}



/////////////////////////////////////////////////////////////////////////////////
//                                                                             //
//      Elliptic Curve Point Multiplication(Fixed point multiplication)	       // 
//                                                                             //
//                                                                             //
//                                                                             //
/////////////////////////////////////////////////////////////////////////////////
 
void GDouble_Proj(u_int  *x1, u_int  *y1, u_int  *z1,
		  u_int  *x2, u_int  *y2, u_int  *z2)
{
	u_int A[_V], B[_V], C[_V], D[_V];

		Sqr_163(x1, A);
		Sqr_163(z1, B);
		Gfm_163(A, B, z2);
		Gfm_163(curv_c, B, B);
		Add_163(A,B,C);
		Sqr_163(C, x2);
		Add_163(y1,B,C);
		Sqr_163(C, C);
		Gfm_163(curv_a, z2, D);
		Add_163(D,C,D);
		Gfm_163(D, x2, D);
		Sqr_163(B, B);
		Gfm_163(B, z2, B);
		Add_163(B,D,y2);
	
}

void GAdd(u_int  *x1, u_int  *y1, u_int  *z1,
		  u_int  *x2, u_int  *y2,
		  u_int  *x3, u_int  *y3, u_int  *z3)
{
	u_int A[_V], B[_V], C[_V], D[_V], E[_V], F[_V], G[_V];

				Sqr_163(z1, A);
				Gfm_163(curv_a, A, D);
				Gfm_163(A, y2, A);
				Add_163(A,y1,A);
				Gfm_163(x2, z1, B);
				Add_163(B,x1,B);
				Gfm_163(B, z1, C);
				Sqr_163(C, z3);
				Add_163(D,C,D);
				Gfm_163(A, C, E);
				Sqr_163(B, B);
				Gfm_163(D, B, D);
				Add_163(D,E,D);
				Sqr_163(A, A);
				Add_163(A,D,x3);
				Gfm_163(x2, z3, F);
				Add_163(F,x3,F);
				Add_163(x2,y2,G);
				Sqr_163(z3, A);
				Gfm_163(A, G, G);
				Add_163(E,z3,E);
				Gfm_163(E, F, F);
				Add_163(F,G,y3);
}


void Proj_to_Affine(u_int  *x1, u_int  *y1, u_int  *z1,
					u_int  *x, u_int  *y)
{
	int j, flag = 0;
	u_int A[_V];

	for( j = 0; j < _V; j++) if(z1[j]){flag = 1; break;}
	
	if(flag)
		{
			Inv_163(z1, A);
			Gfm_163(A, x1, x);
			Sqr_163(A, A);
			Gfm_163(A, y1, y);
		}

	else  for( j = 0; j < _V; j++){x[j] = 0; y[j] = 0;}
}

void GDouble_Affine(u_int  *x1, u_int  *y1,
		  u_int  *x2, u_int  *y2)
{
    u_int A[_V], B[_V], C[_V], D[_V];

		Inv_163(x1, A);
	    Gfm_163(A, y1, A);   
		Add_163(A,x1,A);
		Sqr_163(A, B);
		Add_163(A,B,B);    
		Add_163(B,curv_a,x2);	
		Add_163(x1,x2,C);
		Add_163(y1,x2,D);
		Gfm_163(A, C, C);
		Add_163(C,D,y2);
}


void GDouble_n(u_int *x, u_int *y, u_int *PP0, u_int *QQ0, int n)
{
	int i, j;
    u_int xbuff[_V], ybuff[_V];

    for( i = 0; i < _V; i++){ xbuff[i] = x[i]; ybuff[i] = y[i]; }
	

	if(n)
		{
			for( i = 0; i < n; i++) 
				{
					GDouble_Affine(xbuff, ybuff, PP0, QQ0);
					for( j = 0; j < _V; j++){xbuff[j] = PP0[j]; ybuff[j] = QQ0[j];}
				}			
		}

	else for( i = 0; i < _V; i++){ PP0[i] = xbuff[i]; QQ0[i] = ybuff[i]; }	
	
}

void tablefixed()
{
	int i, j; 	
	u_int A[_V], B[_V];	
     
        for (i = 0; i < _B; i++)
			{
				GDouble_n(base_x, base_y, A, B, i);
				for( j = 0; j < _V; j++) { precomput_PP[_V*i+j] = A[j];
										   precomput_QQ[_V*i+j] = B[j];	}
			}

}

void Fixed_EC_Point_Multi(u_int *k, u_int *xx, u_int *yy)
{
	int i, j;
	u_int A[_V], B[_V], C[_V], zz[_V], BuffPP[_V], BuffQQ[_V];

	int  flag_k = 0, nonzero_bit = 0;


	for( i = 0; i < _B; i++)
	{
		if(k[i]) {flag_k = 1; nonzero_bit = i; break;}
	}

	if(flag_k == 0)
	{
		for( i = 0; i < _V; i++){xx[i] = 0; yy[i] = 0;}
	}


	else
	{
		 for( j = 0; j < _V; j++)
		 {
			 A[j] = precomput_PP[nonzero_bit*_V+j]; 
			 B[j] = precomput_QQ[nonzero_bit*_V+j];
			 C[j] = 0;
		 }
		 C[0] = 1;

		for( i = nonzero_bit + 1; i < _B; i++)
		{	
			if(k[i])
			{

				 for( j = 0; j < _V; j++)
				 { 
					 BuffPP[j] = precomput_PP[i*_V+j]; 
					 BuffQQ[j] = precomput_QQ[i*_V+j];
				 }

	  			 GAdd(A, B, C, BuffPP, BuffQQ, xx, yy, zz);

				 for( j = 0; j < _V; j++)
				 {
					 A[j] = xx[j]; 
					 B[j] = yy[j]; 
					 C[j] = zz[j];
				 }

			}
					  
		}

		Proj_to_Affine(A, B, C, xx, yy);
	}

}


////////////////////////////////////////////////////////////////////////////////
//============================================================================//
//                                                                            //
//                     ECSM on the Lambda Coordinates                         //
//                                                                            //
//============================================================================//
////////////////////////////////////////////////////////////////////////////////

void Lam_DBL(u_int *X, u_int *L, u_int *Z)
{
	u_int A[_V], B[_V];

	Gfm_163(L, Z, A);
	Sqr_163(L, L);
	Sqr_163(Z, Z);
	Gfm_163(curv_a, Z, B);
	Add_163(L, B, B);
	Add_163(A, B, L);
	Sqr_163(X, X);
	Add_163(X, B, B);
	Add_163(Z, B, B);
	Add_163(X, A, A);
	Add_163(L, Z, X);
	Gfm_163(X, B, B);
	Gfm_163(co, Z, X);
	Gfm_163(L, Z, Z);
	Add_163(X, A, A);
	Sqr_163(A, A);
	Sqr_163(L, X);
	Add_163(A, B, L);
}

void Lam_ADD(u_int *T1, u_int *T2, u_int *T3,
			 u_int *T4, u_int *T5, u_int *T6)
{
	u_int T7[_V], T8[_V];

	Gfm_163(T2, T6, T7);
	Gfm_163(curv_a, T3, T8);
	Add_163(T2, T8, T2);
	Add_163(T5, T6, T8);
	Gfm_163(T2, T8, T8);
	Add_163(T7, T8, T8);
	Gfm_163(T3, T5, T2);
	Gfm_163(curv_a, T2, T5);
	Add_163(T5, T8, T8);
	Add_163(T2, T7, T5);
	Add_163(T7, T8, T7);
	Add_163(T2, T8, T8);
	Sqr_163(T5, T2);
	Gfm_163(T3, T4, T3);
	Sqr_163(T3, T3);
	Gfm_163(T1, T6, T6);
	Sqr_163(T6, T6);
	Gfm_163(T1, T4, T1);
	Gfm_163(T1, T2, T1);
	Add_163(T3, T6, T4);
	Gfm_163(T3, T7, T3);
	Gfm_163(T6, T8, T6);
	Add_163(T3, T6, T2);
	Gfm_163(T4, T5, T3);
}

void Lam_Mix_ADD(u_int *T1, u_int *T2, u_int *T3,
				 u_int *T4, u_int *T5)
{
	u_int T6[_V], T7[_V];

	Add_163(T5, one, T6);
	Gfm_163(curv_a, T3, T7);
	Add_163(T2, T7, T7);
	Gfm_163(T6, T7, T7);
	Add_163(T2, T7, T7);
	Gfm_163(T3, T5, T6);
	Gfm_163(curv_a, T6, T5); 
	Add_163(T5, T7, T7);
	Add_163(T2, T6, T5);
	Add_163(T6, T7, T6);
	Add_163(T2, T7, T7);
	Gfm_163(T1, T4, T2);
	Gfm_163(T3, T4, T4);
	Sqr_163(T4, T4);
	Sqr_163(T5, T3);
	Sqr_163(T1, T1);
	Gfm_163(T1, T6, T6);
	Gfm_163(T4, T7, T7);
	Add_163(T1, T4, T4);
	Gfm_163(T2, T3, T1);
	Gfm_163(T4, T5, T3);
	Add_163(T6, T7, T2);
}


void Affine_to_Lambda(u_int *x, u_int *y, u_int *lamda)
{
	u_int buf[_V];

	Inv_163(x, buf);
	Gfm_163(buf, y, buf);
	Add_163(x, buf, lamda);
}

void Lambda_to_Affine(u_int *x, u_int *lamda, u_int *y)
{
	u_int buf[_V];
	Add_163(lamda, x, buf);
	Gfm_163(buf, x, y);
}

void LamProj_to_LamAffine(u_int *X, u_int *L, u_int *Z,
						  u_int *x, u_int *lamda)
{
	int j, flag = 0;
	u_int A[_V];
	
	for( j = 0; j < _V; j++) if(Z[j]){flag = 1; break;}
	
	if(flag)
	{
		Inv_163(Z, A);
		Gfm_163(A, X, x);
		Gfm_163(A, L, lamda);
	}
	
	else  for( j = 0; j < _V; j++) {x[j] = 0; lamda[j] = 0;}
}

//--------------------------------------------
void LamDBL_Affine(u_int *x1, u_int *lam1,
				   u_int *x2, u_int *lam2)
{
    u_int A[_V], B[_V], C[_V], D[_V];
	
	Sqr_163(lam1, A);
	Add_163(A, curv_a, B);
	Add_163(B, lam1, x2);
	Sqr_163(x1, A);
	Inv_163(x2, C);
	Gfm_163(A, C, D);
	Add_163(D, B, D);
	Add_163(D, one, lam2);
}


void LamDBL_Affine_n(u_int *x, u_int *lam, u_int *PP0, u_int *QQ0, int n)
{
	int i, j;
    u_int xbuff[_V], lbuff[_V];
	
    for( i = 0; i < _V; i++){ xbuff[i] = x[i]; lbuff[i] = lam[i]; }
	
	
	if(n)
	{
		for( i = 0; i < n; i++) 
		{
			LamDBL_Affine(xbuff, lbuff, PP0, QQ0);
			for( j = 0; j < _V; j++){xbuff[j] = PP0[j]; lbuff[j] = QQ0[j];}
		}			
	}
	
	else for( i = 0; i < _V; i++){ PP0[i] = xbuff[i]; QQ0[i] = lbuff[i]; }	
	
}

void LamDBL_Precomutation()
{
	int i, j; 	
	u_int lam[_V], A[_V], B[_V];	

	Affine_to_Lambda(base_x, base_y, lam);
	
	for (i = 0; i < _B; i++)
	{
		LamDBL_Affine_n(base_x, lam, A, B, i);
		for( j = 0; j < _V; j++) 
		{ 
			Lam_precomput_PP[_V*i+j] = A[j];
			Lam_precomput_QQ[_V*i+j] = B[j];	
		}
	}
	
}
//--------------------------------------------

void ECSM_using_Lambda_coordinate(u_int *k, u_int *xx, u_int *yy)
{
	int i, j;
	u_int A[_V], B[_V], C[_V], BuffPP[_V], BuffQQ[_V];
	
	int  flag_k = 0, nonzero_bit = 0;
	
	
	for( i = 0; i < _B; i++)
	{
		if(k[i]) {flag_k = 1; nonzero_bit = i; break;}
	}
	
	if(flag_k == 0)
	{
		for( i = 0; i < _V; i++) {xx[i] = 0; yy[i] = 0;}
	}
	
	
	else
	{
		for( j = 0; j < _V; j++)
		{
			A[j] = Lam_precomput_PP[nonzero_bit*_V+j]; 
			B[j] = Lam_precomput_QQ[nonzero_bit*_V+j];
			C[j] = 0;
		}
		C[0] = 1;

		
		for( i = nonzero_bit + 1; i < _B; i++)
		{	
			if(k[i])
			{
				
				for( j = 0; j < _V; j++)
				{ 
					BuffPP[j] = Lam_precomput_PP[i*_V+j]; 
					BuffQQ[j] = Lam_precomput_QQ[i*_V+j];
				}
				
				Lam_Mix_ADD(A, B, C, BuffPP, BuffQQ);
				
			}
			
		}
		
		LamProj_to_LamAffine(A, B, C, xx, yy);
		Lambda_to_Affine(xx, yy, yy);
	}

}



///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

void main()
{
	sTable();
	declare();

	u_int pass[_V];

	Test_curve_equa(base_x, base_y, pass);
	if (pass[0] || pass[1] || pass[2] || pass[3] || pass[4] || pass[5])
	{
		printf("The Base point is Invalid !\n");
		return;
	}

	u_int k[_B];
	int i;
	
	//------------------------------------------------//
	srand( (unsigned)time( NULL ) );                  //
	k[_B - 1] = 1;                                    //  Chose scalar k at random.
	for(i = 0; i < _B - 1 ; i++)  k[i] = rand() % 2;  //
	//------------------------------------------------//
	

	u_int x[_V], y[_V];

	printf("base_x = %x %x %x %x %x %x\n", base_x[5],base_x[4],base_x[3],base_x[2],base_x[1],base_x[0]);
	printf("base_y = %x %x %x %x %x %x\n", base_y[5],base_y[4],base_y[3],base_y[2],base_y[1],base_y[0]);
	
	printf("k = ");
	for (i = _B-1; i >= 0; i--) printf("%u", k[i]);
	printf("\n\n\n");

	
	clock_t start, finish;
	int h;
	double Times;

	printf("\n********  Mongomery ECSM  **********\n");

	start = clock();
	for(h = 0; h < 100; h++)
	{
		Montgomery_EC_Point_Multi(base_x, base_y, x, y, k);
	}
	finish = clock();
	Times = (double)((finish-start)/(double)(CLOCKS_PER_SEC));

	printf("x = %x %x %x %x %x %x\n", x[5],x[4],x[3],x[2],x[1],x[0]);
	printf("y = %x %x %x %x %x %x\n", y[5],y[4],y[3],y[2],y[1],y[0]);
	printf("TIME : %f  second\n", Times);

	printf("\n********  General ECSM (Fixed point ECSM) **********\n");

	tablefixed();
	LamDBL_Precomutation();

	start = clock();
	for(h = 0; h < 100; h++)
	{
		Fixed_EC_Point_Multi(k, x, y);
	}
	finish = clock();
	Times = (double)((finish-start)/(double)(CLOCKS_PER_SEC));
	
	printf("x = %x %x %x %x %x %x\n", x[5],x[4],x[3],x[2],x[1],x[0]);
	printf("y = %x %x %x %x %x %x\n", y[5],y[4],y[3],y[2],y[1],y[0]);
	printf("TIME : %f  second\n", Times);

	
	printf("\n********  ECSM using Lambda coordinates **********\n");

	start = clock();
	for(h = 0; h < 100; h++)
	{
		ECSM_using_Lambda_coordinate(k, x, y);
	}
	finish = clock();
	Times = (double)((finish-start)/(double)(CLOCKS_PER_SEC));
	
	printf("x = %x %x %x %x %x %x\n", x[5],x[4],x[3],x[2],x[1],x[0]);
	printf("y = %x %x %x %x %x %x\n", y[5],y[4],y[3],y[2],y[1],y[0]);
	printf("TIME : %f  second\n", Times);

	
}
