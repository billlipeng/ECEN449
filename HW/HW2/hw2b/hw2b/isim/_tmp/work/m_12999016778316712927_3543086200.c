/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                         */
/*  \   \        Copyright (c) 2003-2007 Xilinx, Inc.                 */
/*  /   /        All Right Reserved.                                  */
/* /---/   /\                                                         */
/* \   \  /  \                                                        */
/*  \___\/\___\                                                       */
/**********************************************************************/

/* This file is designed for use with ISim build 0xabfbedd0 */

#include "xsi.h"
#include <memory.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
static const char *ng0 = "/homes/ugrad/billlipeng/ECEN449/HW/HW2/hw2b/hw2b/zero_checker.v";
static int ng1[] = {0, 0};
static int ng2[] = {11, 0};
static int ng3[] = {1, 0};
static int ng4[] = {6, 0};



static void C29_0(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    char *t8;
    char *t9;
    char *t10;
    unsigned int t11;
    unsigned int t12;
    char *t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    char *t20;

LAB0:    t1 = (t0 + 2872U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    t2 = (t0 + 1712);
    t3 = (t2 + 48U);
    t4 = *((char **)t3);
    t5 = (t0 + 3472);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    t10 = (t9 + 4LL);
    t11 = 1U;
    t12 = t11;
    t13 = (t4 + 4LL);
    t14 = *((unsigned int *)t4);
    t11 = (t11 & t14);
    t15 = *((unsigned int *)t13);
    t12 = (t12 & t15);
    t16 = *((unsigned int *)t9);
    *((unsigned int *)t9) = (t16 & 4294967294U);
    t17 = *((unsigned int *)t9);
    *((unsigned int *)t9) = (t17 | t11);
    t18 = *((unsigned int *)t10);
    *((unsigned int *)t10) = (t18 & 4294967294U);
    t19 = *((unsigned int *)t10);
    *((unsigned int *)t10) = (t19 | t12);
    xsi_driver_vfirst_trans(t5, 0, 0);
    t20 = (t0 + 3376);
    *((int *)t20) = 1;

LAB1:    return;
}

static void A31_1(char *t0)
{
    char t13[8];
    char t15[8];
    char t31[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    unsigned int t6;
    unsigned int t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    char *t11;
    char *t12;
    char *t14;
    char *t16;
    char *t17;
    char *t18;
    char *t19;
    char *t20;
    char *t21;
    unsigned int t22;
    unsigned int t23;
    unsigned int t24;
    unsigned int t25;
    unsigned int t26;
    char *t27;
    char *t28;
    char *t29;
    char *t30;
    char *t32;

LAB0:    t1 = (t0 + 3088U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(31, ng0);
    t2 = (t0 + 3392);
    *((int *)t2) = 1;
    t3 = (t0 + 3120);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(32, ng0);

LAB5:    xsi_set_current_line(33, ng0);
    t4 = (t0 + 1160U);
    t5 = *((char **)t4);
    t4 = (t5 + 4LL);
    t6 = *((unsigned int *)t4);
    t7 = (~(t6));
    t8 = *((unsigned int *)t5);
    t9 = (t8 & t7);
    t10 = (t9 != 0);
    if (t10 > 0)
        goto LAB6;

LAB7:    xsi_set_current_line(45, ng0);
    t2 = ((char*)((ng1)));
    t3 = (t0 + 1712);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);

LAB8:    goto LAB2;

LAB6:    xsi_set_current_line(34, ng0);

LAB9:    xsi_set_current_line(35, ng0);
    xsi_set_current_line(35, ng0);
    t11 = ((char*)((ng1)));
    t12 = (t0 + 2032);
    xsi_vlogvar_assign_value(t12, t11, 0, 0, 32);

LAB10:    t2 = (t0 + 2032);
    t3 = (t2 + 48U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng2)));
    memset(t13, 0, 8);
    xsi_vlog_signed_less(t13, 32, t4, 32, t5, 32);
    t11 = (t13 + 4LL);
    t6 = *((unsigned int *)t11);
    t7 = (~(t6));
    t8 = *((unsigned int *)t13);
    t9 = (t8 & t7);
    t10 = (t9 != 0);
    if (t10 > 0)
        goto LAB11;

LAB12:    xsi_set_current_line(40, ng0);
    t2 = (t0 + 1872);
    t3 = (t2 + 48U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng4)));
    memset(t13, 0, 8);
    xsi_vlog_signed_greater(t13, 32, t4, 32, t5, 32);
    t11 = (t13 + 4LL);
    t6 = *((unsigned int *)t11);
    t7 = (~(t6));
    t8 = *((unsigned int *)t13);
    t9 = (t8 & t7);
    t10 = (t9 != 0);
    if (t10 > 0)
        goto LAB17;

LAB18:
LAB19:    goto LAB8;

LAB11:    xsi_set_current_line(36, ng0);

LAB13:    xsi_set_current_line(37, ng0);
    t12 = (t0 + 1000U);
    t14 = *((char **)t12);
    t12 = (t0 + 960U);
    t16 = (t12 + 72U);
    t17 = *((char **)t16);
    t18 = (t0 + 2032);
    t19 = (t18 + 48U);
    t20 = *((char **)t19);
    xsi_vlog_generic_get_index_select_value(t15, 1, t14, t17, 2, t20, 32, 1);
    t21 = (t15 + 4LL);
    t22 = *((unsigned int *)t21);
    t23 = (~(t22));
    t24 = *((unsigned int *)t15);
    t25 = (t24 & t23);
    t26 = (t25 != 0);
    if (t26 > 0)
        goto LAB14;

LAB15:
LAB16:    xsi_set_current_line(35, ng0);
    t2 = (t0 + 2032);
    t3 = (t2 + 48U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng3)));
    memset(t13, 0, 8);
    xsi_vlog_signed_add(t13, 32, t4, 32, t5, 32);
    t11 = (t0 + 2032);
    xsi_vlogvar_assign_value(t11, t13, 0, 0, 32);
    goto LAB10;

LAB14:    xsi_set_current_line(38, ng0);
    t27 = (t0 + 1872);
    t28 = (t27 + 48U);
    t29 = *((char **)t28);
    t30 = ((char*)((ng3)));
    memset(t31, 0, 8);
    xsi_vlog_signed_add(t31, 32, t29, 32, t30, 32);
    t32 = (t0 + 1872);
    xsi_vlogvar_assign_value(t32, t31, 0, 0, 32);
    goto LAB16;

LAB17:    xsi_set_current_line(41, ng0);
    t12 = ((char*)((ng3)));
    t14 = (t0 + 1712);
    xsi_vlogvar_assign_value(t14, t12, 0, 0, 1);
    goto LAB19;

}


extern void work_m_12999016778316712927_3543086200_init()
{
	static char *pe[] = {(void *)C29_0,(void *)A31_1};
	xsi_register_didat("work_m_12999016778316712927_3543086200", "isim/_tmp/work/m_12999016778316712927_3543086200.didat");
	xsi_register_executes(pe);
}
