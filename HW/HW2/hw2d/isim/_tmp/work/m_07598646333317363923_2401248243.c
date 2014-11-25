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
static const char *ng0 = "/homes/ugrad/billlipeng/ECEN449/HW/HW2/hw2d/stat_machine.v";
static unsigned int ng1[] = {0U, 0U};
static int ng2[] = {1, 0};
static unsigned int ng3[] = {1U, 0U};
static int ng4[] = {0, 0};
static unsigned int ng5[] = {2U, 0U};



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

LAB0:    t1 = (t0 + 2712U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    t2 = (t0 + 1712);
    t3 = (t2 + 48U);
    t4 = *((char **)t3);
    t5 = (t0 + 3312);
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
    t20 = (t0 + 3216);
    *((int *)t20) = 1;

LAB1:    return;
}

static void A30_1(char *t0)
{
    char t16[8];
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
    int t13;
    char *t14;
    char *t15;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    unsigned int t21;
    unsigned int t22;
    unsigned int t23;
    unsigned int t24;

LAB0:    t1 = (t0 + 2928U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(30, ng0);
    t2 = (t0 + 3232);
    *((int *)t2) = 1;
    t3 = (t0 + 2960);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(31, ng0);

LAB5:    xsi_set_current_line(32, ng0);
    t4 = (t0 + 1000U);
    t5 = *((char **)t4);
    t4 = (t5 + 4LL);
    t6 = *((unsigned int *)t4);
    t7 = (~(t6));
    t8 = *((unsigned int *)t5);
    t9 = (t8 & t7);
    t10 = (t9 != 0);
    if (t10 > 0)
        goto LAB6;

LAB7:    xsi_set_current_line(37, ng0);

LAB10:    xsi_set_current_line(38, ng0);
    t2 = (t0 + 1872);
    t3 = (t2 + 48U);
    t4 = *((char **)t3);

LAB11:    t5 = ((char*)((ng1)));
    t13 = xsi_vlog_unsigned_case_compare(t4, 2, t5, 2);
    if (t13 == 1)
        goto LAB12;

LAB13:    t2 = ((char*)((ng3)));
    t13 = xsi_vlog_unsigned_case_compare(t4, 2, t2, 2);
    if (t13 == 1)
        goto LAB14;

LAB15:    t2 = ((char*)((ng5)));
    t13 = xsi_vlog_unsigned_case_compare(t4, 2, t2, 2);
    if (t13 == 1)
        goto LAB16;

LAB17:
LAB18:
LAB8:    goto LAB2;

LAB6:    xsi_set_current_line(33, ng0);

LAB9:    xsi_set_current_line(34, ng0);
    t11 = ((char*)((ng1)));
    t12 = (t0 + 1872);
    xsi_vlogvar_assign_value(t12, t11, 0, 0, 2);
    goto LAB8;

LAB12:    xsi_set_current_line(40, ng0);

LAB19:    xsi_set_current_line(41, ng0);
    t11 = (t0 + 1160U);
    t12 = *((char **)t11);
    t11 = (t12 + 4LL);
    t6 = *((unsigned int *)t11);
    t7 = (~(t6));
    t8 = *((unsigned int *)t12);
    t9 = (t8 & t7);
    t10 = (t9 != 0);
    if (t10 > 0)
        goto LAB20;

LAB21:    xsi_set_current_line(47, ng0);

LAB24:    xsi_set_current_line(48, ng0);
    t2 = ((char*)((ng4)));
    t3 = (t0 + 1712);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);
    xsi_set_current_line(49, ng0);
    t2 = ((char*)((ng1)));
    t3 = (t0 + 1872);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 2);

LAB22:    goto LAB18;

LAB14:    xsi_set_current_line(54, ng0);

LAB25:    xsi_set_current_line(55, ng0);
    t3 = (t0 + 1160U);
    t5 = *((char **)t3);
    t3 = (t5 + 4LL);
    t6 = *((unsigned int *)t3);
    t7 = (~(t6));
    t8 = *((unsigned int *)t5);
    t9 = (t8 & t7);
    t10 = (t9 != 0);
    if (t10 > 0)
        goto LAB26;

LAB27:    xsi_set_current_line(61, ng0);

LAB30:    xsi_set_current_line(62, ng0);
    t2 = ((char*)((ng2)));
    t3 = (t0 + 1712);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);
    xsi_set_current_line(63, ng0);
    t2 = ((char*)((ng3)));
    t3 = (t0 + 1872);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 2);

LAB28:    goto LAB18;

LAB16:    xsi_set_current_line(68, ng0);

LAB31:    xsi_set_current_line(69, ng0);
    t3 = (t0 + 1160U);
    t5 = *((char **)t3);
    memset(t16, 0, 8);
    t3 = (t16 + 4LL);
    t11 = (t5 + 4LL);
    t6 = *((unsigned int *)t5);
    t7 = (~(t6));
    *((unsigned int *)t16) = t7;
    *((unsigned int *)t3) = 0;
    if (*((unsigned int *)t11) != 0)
        goto LAB33;

LAB32:    t18 = *((unsigned int *)t16);
    *((unsigned int *)t16) = (t18 & 1U);
    t19 = *((unsigned int *)t3);
    *((unsigned int *)t3) = (t19 & 1U);
    t12 = (t16 + 4LL);
    t20 = *((unsigned int *)t12);
    t21 = (~(t20));
    t22 = *((unsigned int *)t16);
    t23 = (t22 & t21);
    t24 = (t23 != 0);
    if (t24 > 0)
        goto LAB34;

LAB35:
LAB36:    goto LAB18;

LAB20:    xsi_set_current_line(42, ng0);

LAB23:    xsi_set_current_line(43, ng0);
    t14 = ((char*)((ng2)));
    t15 = (t0 + 1712);
    xsi_vlogvar_assign_value(t15, t14, 0, 0, 1);
    xsi_set_current_line(44, ng0);
    t2 = ((char*)((ng3)));
    t3 = (t0 + 1872);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 2);
    goto LAB22;

LAB26:    xsi_set_current_line(56, ng0);

LAB29:    xsi_set_current_line(57, ng0);
    t11 = ((char*)((ng4)));
    t12 = (t0 + 1712);
    xsi_vlogvar_assign_value(t12, t11, 0, 0, 1);
    xsi_set_current_line(58, ng0);
    t2 = ((char*)((ng5)));
    t3 = (t0 + 1872);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 2);
    goto LAB28;

LAB33:    t8 = *((unsigned int *)t16);
    t9 = *((unsigned int *)t11);
    *((unsigned int *)t16) = (t8 | t9);
    t10 = *((unsigned int *)t3);
    t17 = *((unsigned int *)t11);
    *((unsigned int *)t3) = (t10 | t17);
    goto LAB32;

LAB34:    xsi_set_current_line(70, ng0);

LAB37:    xsi_set_current_line(71, ng0);
    t14 = ((char*)((ng4)));
    t15 = (t0 + 1712);
    xsi_vlogvar_assign_value(t15, t14, 0, 0, 1);
    xsi_set_current_line(72, ng0);
    t2 = ((char*)((ng1)));
    t3 = (t0 + 1872);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 2);
    goto LAB36;

}


extern void work_m_07598646333317363923_2401248243_init()
{
	static char *pe[] = {(void *)C29_0,(void *)A30_1};
	xsi_register_didat("work_m_07598646333317363923_2401248243", "isim/_tmp/work/m_07598646333317363923_2401248243.didat");
	xsi_register_executes(pe);
}
