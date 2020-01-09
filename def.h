#define _V 6
#define _B 163
typedef unsigned int u_int;


//************************************************************************//
//------------------------------------------------------------------------//
//                                                                        //
//                         Binary Field Arithmetic &                      //
//																		  //
//					  Elliptic Curve Arithmetic over That				  // 
//																		  //
//========================================================================//
//************************************************************************//


void MReduce_163(u_int *c);
void Substitute(u_int *a, u_int *b);
void Gfm_163(u_int *a, u_int *b, u_int *c);
void re_Gfm_163(u_int *a, u_int *b);

void sTable(void);

void Sqr_163(u_int *a, u_int *c);
void re_Sqr_163(u_int *a);
void n_Sqr_163(u_int *a, u_int *c, int n);
void re_n_Sqr_163(u_int *a, int n);
void Inv_163(u_int *a, u_int *b);
void re_Inv_163(u_int *a);
void Add_163(u_int *a, u_int *b, u_int *c); 
void Madd(u_int  *x1, u_int  *z1, u_int  *x2, 
		  u_int  *z2,  u_int  *x);
void Mdouble(u_int  *x, u_int  *z, u_int  *c);
void Mxy(u_int *x, u_int *y, u_int *x1, u_int *z1,
		 u_int *x2, u_int *z2, u_int *xx, u_int *yy);
void Montgomery_EC_Point_Multi(u_int *x, u_int *y,	
							   u_int *xx, u_int *yy, u_int *k);
void Test_curve_equa(u_int *xx, u_int *yy, u_int *C);
void declare();
void tablefixed();
void GDouble_Proj(u_int  *x1, u_int  *y1, u_int  *z1,
				  u_int  *x2, u_int  *y2, u_int  *z2);
void GAdd(u_int  *x1, u_int  *y1, u_int  *z1,
		  u_int  *x2, u_int  *y2, 
		  u_int  *x3, u_int  *y3, u_int  *z3);
void Proj_to_Affine(u_int  *x1, u_int  *y1, u_int  *z1,
					u_int  *x, u_int  *y);
void GDouble_Affine(u_int  *x1, u_int  *y1,
					u_int  *x2, u_int  *y2);
void GDouble_n(u_int *x, u_int *y, u_int *PP, u_int *QQ, int n);
void Fixed_EC_Point_Multi(u_int *k, u_int *xx, u_int *yy);
