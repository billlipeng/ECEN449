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
static const char *ng0 = "/homes/ugrad/billlipeng/ECEN449/HW/HW2/hw2a/hw2aa/ALU_3_bit.v";
static int ng1[] = {1, 0};
static int ng2[] = {0, 0};
static int ng3[] = {3, 0};
static int ng4[] = {2, 0};



static void C19_0(char *t0)
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

LAB0:    t1 = (t0 + 3352U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    t2 = (t0 + 2512);
    t3 = (t2 + 48U);
    t4 = *((char **)t3);
    t5 = (t0 + 4184);
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
    t20 = (t0 + 4072);
    *((int *)t20) = 1;

LAB1:    return;
}

static void C20_1(char *t0)
{
    char t3[8];
    char *t1;
    char *t2;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    unsigned int t12;
    unsigned int t13;
    char *t14;
    char *t15;
    char *t16;
    char *t17;
    char *t18;
    char *t19;
    unsigned int t20;
    unsigned int t21;
    char *t22;
    unsigned int t23;
    unsigned int t24;
    unsigned int t25;
    unsigned int t26;
    unsigned int t27;
    unsigned int t28;
    char *t29;

LAB0:    t1 = (t0 + 3568U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    t2 = (t0 + 2192);
    t4 = (t2 + 48U);
    t5 = *((char **)t4);
    memset(t3, 0, 8);
    t6 = (t3 + 4LL);
    t7 = (t5 + 4LL);
    t8 = *((unsigned int *)t5);
    t9 = (t8 >> 0);
    *((unsigned int *)t3) = t9;
    t10 = *((unsigned int *)t7);
    t11 = (t10 >> 0);
    *((unsigned int *)t6) = t11;
    t12 = *((unsigned int *)t3);
    *((unsigned int *)t3) = (t12 & 7U);
    t13 = *((unsigned int *)t6);
    *((unsigned int *)t6) = (t13 & 7U);
    t14 = (t0 + 4248);
    t15 = (t14 + 56U);
    t16 = *((char **)t15);
    t17 = (t16 + 56U);
    t18 = *((char **)t17);
    t19 = (t18 + 4LL);
    t20 = 7U;
    t21 = t20;
    t22 = (t3 + 4LL);
    t23 = *((unsigned int *)t3);
    t20 = (t20 & t23);
    t24 = *((unsigned int *)t22);
    t21 = (t21 & t24);
    t25 = *((unsigned int *)t18);
    *((unsigned int *)t18) = (t25 & 4294967288U);
    t26 = *((unsigned int *)t18);
    *((unsigned int *)t18) = (t26 | t20);
    t27 = *((unsigned int *)t19);
    *((unsigned int *)t19) = (t27 & 4294967288U);
    t28 = *((unsigned int *)t19);
    *((unsigned int *)t19) = (t28 | t21);
    xsi_driver_vfirst_trans(t14, 0, 2);
    t29 = (t0 + 4088);
    *((int *)t29) = 1;

LAB1:    return;
}

static void A23_2(char *t0)
{
    char t4[8];
    char t25[8];
    char t26[8];
    char t42[8];
    char t48[8];
    char t64[8];
    char t72[8];
    char t104[8];
    char t120[8];
    char t126[8];
    char t142[8];
    char t157[8];
    char t163[8];
    char t179[8];
    char t187[8];
    char t219[8];
    char t227[8];
    char *t1;
    char *t2;
    char *t3;
    char *t5;
    char *t6;
    char *t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    unsigned int t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    char *t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    unsigned int t21;
    char *t22;
    char *t23;
    char *t24;
    char *t27;
    char *t28;
    char *t29;
    char *t30;
    unsigned int t31;
    unsigned int t32;
    unsigned int t33;
    unsigned int t34;
    char *t35;
    unsigned int t36;
    unsigned int t37;
    unsigned int t38;
    char *t39;
    char *t40;
    char *t41;
    char *t43;
    char *t44;
    char *t45;
    char *t46;
    char *t47;
    char *t49;
    char *t50;
    char *t51;
    unsigned int t52;
    unsigned int t53;
    unsigned int t54;
    unsigned int t55;
    unsigned int t56;
    unsigned int t57;
    unsigned int t58;
    unsigned int t59;
    unsigned int t60;
    unsigned int t61;
    unsigned int t62;
    unsigned int t63;
    char *t65;
    char *t66;
    unsigned int t67;
    unsigned int t68;
    unsigned int t69;
    unsigned int t70;
    unsigned int t71;
    unsigned int t73;
    unsigned int t74;
    unsigned int t75;
    char *t76;
    char *t77;
    char *t78;
    unsigned int t79;
    unsigned int t80;
    unsigned int t81;
    unsigned int t82;
    unsigned int t83;
    unsigned int t84;
    unsigned int t85;
    char *t86;
    char *t87;
    unsigned int t88;
    unsigned int t89;
    unsigned int t90;
    unsigned int t91;
    unsigned int t92;
    unsigned int t93;
    unsigned int t94;
    unsigned int t95;
    int t96;
    int t97;
    unsigned int t98;
    unsigned int t99;
    unsigned int t100;
    unsigned int t101;
    unsigned int t102;
    unsigned int t103;
    char *t105;
    char *t106;
    unsigned int t107;
    unsigned int t108;
    unsigned int t109;
    unsigned int t110;
    unsigned int t111;
    char *t112;
    unsigned int t113;
    unsigned int t114;
    unsigned int t115;
    unsigned int t116;
    char *t117;
    char *t118;
    char *t119;
    char *t121;
    char *t122;
    char *t123;
    char *t124;
    char *t125;
    char *t127;
    char *t128;
    char *t129;
    unsigned int t130;
    unsigned int t131;
    unsigned int t132;
    unsigned int t133;
    unsigned int t134;
    unsigned int t135;
    unsigned int t136;
    unsigned int t137;
    unsigned int t138;
    unsigned int t139;
    unsigned int t140;
    unsigned int t141;
    char *t143;
    char *t144;
    unsigned int t145;
    unsigned int t146;
    unsigned int t147;
    unsigned int t148;
    unsigned int t149;
    char *t150;
    unsigned int t151;
    unsigned int t152;
    unsigned int t153;
    char *t154;
    char *t155;
    char *t156;
    char *t158;
    char *t159;
    char *t160;
    char *t161;
    char *t162;
    char *t164;
    char *t165;
    char *t166;
    unsigned int t167;
    unsigned int t168;
    unsigned int t169;
    unsigned int t170;
    unsigned int t171;
    unsigned int t172;
    unsigned int t173;
    unsigned int t174;
    unsigned int t175;
    unsigned int t176;
    unsigned int t177;
    unsigned int t178;
    char *t180;
    char *t181;
    unsigned int t182;
    unsigned int t183;
    unsigned int t184;
    unsigned int t185;
    unsigned int t186;
    unsigned int t188;
    unsigned int t189;
    unsigned int t190;
    char *t191;
    char *t192;
    char *t193;
    unsigned int t194;
    unsigned int t195;
    unsigned int t196;
    unsigned int t197;
    unsigned int t198;
    unsigned int t199;
    unsigned int t200;
    char *t201;
    char *t202;
    unsigned int t203;
    unsigned int t204;
    unsigned int t205;
    unsigned int t206;
    unsigned int t207;
    unsigned int t208;
    unsigned int t209;
    unsigned int t210;
    int t211;
    int t212;
    unsigned int t213;
    unsigned int t214;
    unsigned int t215;
    unsigned int t216;
    unsigned int t217;
    unsigned int t218;
    char *t220;
    char *t221;
    unsigned int t222;
    unsigned int t223;
    unsigned int t224;
    unsigned int t225;
    unsigned int t226;
    unsigned int t228;
    unsigned int t229;
    unsigned int t230;
    char *t231;
    char *t232;
    char *t233;
    unsigned int t234;
    unsigned int t235;
    unsigned int t236;
    unsigned int t237;
    unsigned int t238;
    unsigned int t239;
    unsigned int t240;
    char *t241;
    char *t242;
    unsigned int t243;
    unsigned int t244;
    unsigned int t245;
    int t246;
    unsigned int t247;
    unsigned int t248;
    unsigned int t249;
    int t250;
    unsigned int t251;
    unsigned int t252;
    unsigned int t253;
    unsigned int t254;
    char *t255;
    unsigned int t256;
    unsigned int t257;
    unsigned int t258;
    unsigned int t259;
    unsigned int t260;
    char *t261;
    char *t262;

LAB0:    t1 = (t0 + 3784U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(23, ng0);
    t2 = (t0 + 4104);
    *((int *)t2) = 1;
    t3 = (t0 + 3816);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(24, ng0);

LAB5:    xsi_set_current_line(26, ng0);
    t5 = (t0 + 1480U);
    t6 = *((char **)t5);
    memset(t4, 0, 8);
    t5 = (t4 + 4LL);
    t7 = (t6 + 4LL);
    t8 = *((unsigned int *)t6);
    t9 = (~(t8));
    *((unsigned int *)t4) = t9;
    *((unsigned int *)t5) = 0;
    if (*((unsigned int *)t7) != 0)
        goto LAB7;

LAB6:    t14 = *((unsigned int *)t4);
    *((unsigned int *)t4) = (t14 & 1U);
    t15 = *((unsigned int *)t5);
    *((unsigned int *)t5) = (t15 & 1U);
    t16 = (t4 + 4LL);
    t17 = *((unsigned int *)t16);
    t18 = (~(t17));
    t19 = *((unsigned int *)t4);
    t20 = (t19 & t18);
    t21 = (t20 != 0);
    if (t21 > 0)
        goto LAB8;

LAB9:    xsi_set_current_line(36, ng0);

LAB15:    xsi_set_current_line(37, ng0);
    t2 = (t0 + 1160U);
    t3 = *((char **)t2);
    t2 = (t0 + 1320U);
    t5 = *((char **)t2);
    memset(t4, 0, 8);
    xsi_vlog_unsigned_add(t4, 4, t3, 3, t5, 3);
    t2 = (t0 + 2192);
    xsi_vlogvar_assign_value(t2, t4, 0, 0, 4);
    xsi_set_current_line(38, ng0);
    t2 = (t0 + 1160U);
    t3 = *((char **)t2);
    memset(t4, 0, 8);
    t2 = (t4 + 4LL);
    t5 = (t3 + 4LL);
    t8 = *((unsigned int *)t3);
    t9 = (t8 >> 0);
    *((unsigned int *)t4) = t9;
    t10 = *((unsigned int *)t5);
    t11 = (t10 >> 0);
    *((unsigned int *)t2) = t11;
    t12 = *((unsigned int *)t4);
    *((unsigned int *)t4) = (t12 & 3U);
    t13 = *((unsigned int *)t2);
    *((unsigned int *)t2) = (t13 & 3U);
    t6 = (t0 + 1320U);
    t7 = *((char **)t6);
    memset(t25, 0, 8);
    t6 = (t25 + 4LL);
    t16 = (t7 + 4LL);
    t14 = *((unsigned int *)t7);
    t15 = (t14 >> 0);
    *((unsigned int *)t25) = t15;
    t17 = *((unsigned int *)t16);
    t18 = (t17 >> 0);
    *((unsigned int *)t6) = t18;
    t19 = *((unsigned int *)t25);
    *((unsigned int *)t25) = (t19 & 3U);
    t20 = *((unsigned int *)t6);
    *((unsigned int *)t6) = (t20 & 3U);
    memset(t26, 0, 8);
    xsi_vlog_unsigned_add(t26, 3, t4, 3, t25, 3);
    t22 = (t0 + 2352);
    xsi_vlogvar_assign_value(t22, t26, 0, 0, 3);
    xsi_set_current_line(40, ng0);
    t2 = (t0 + 2192);
    t3 = (t2 + 48U);
    t5 = *((char **)t3);
    t6 = (t0 + 2192);
    t7 = (t6 + 64U);
    t16 = *((char **)t7);
    t22 = ((char*)((ng3)));
    xsi_vlog_generic_get_index_select_value(t4, 32, t5, t16, 2, t22, 32, 1);
    t23 = ((char*)((ng2)));
    memset(t25, 0, 8);
    t24 = (t25 + 4LL);
    t27 = (t4 + 4LL);
    t28 = (t23 + 4LL);
    t8 = *((unsigned int *)t4);
    t9 = *((unsigned int *)t23);
    t10 = (t8 ^ t9);
    t11 = *((unsigned int *)t27);
    t12 = *((unsigned int *)t28);
    t13 = (t11 ^ t12);
    t14 = (t10 | t13);
    t15 = *((unsigned int *)t27);
    t17 = *((unsigned int *)t28);
    t18 = (t15 | t17);
    t19 = (~(t18));
    t20 = (t14 & t19);
    if (t20 != 0)
        goto LAB19;

LAB16:    if (t18 != 0)
        goto LAB18;

LAB17:    *((unsigned int *)t25) = 1;

LAB19:    memset(t26, 0, 8);
    t29 = (t26 + 4LL);
    t30 = (t25 + 4LL);
    t21 = *((unsigned int *)t30);
    t31 = (~(t21));
    t32 = *((unsigned int *)t25);
    t33 = (t32 & t31);
    t34 = (t33 & 1U);
    if (t34 != 0)
        goto LAB20;

LAB21:    if (*((unsigned int *)t30) != 0)
        goto LAB22;

LAB23:    t35 = (t26 + 4LL);
    t36 = *((unsigned int *)t26);
    t37 = *((unsigned int *)t35);
    t38 = (t36 || t37);
    if (t38 > 0)
        goto LAB24;

LAB25:    memcpy(t72, t26, 8);

LAB26:    memset(t104, 0, 8);
    t105 = (t104 + 4LL);
    t106 = (t72 + 4LL);
    t107 = *((unsigned int *)t106);
    t108 = (~(t107));
    t109 = *((unsigned int *)t72);
    t110 = (t109 & t108);
    t111 = (t110 & 1U);
    if (t111 != 0)
        goto LAB38;

LAB39:    if (*((unsigned int *)t106) != 0)
        goto LAB40;

LAB41:    t112 = (t104 + 4LL);
    t113 = *((unsigned int *)t104);
    t114 = (!(t113));
    t115 = *((unsigned int *)t112);
    t116 = (t114 || t115);
    if (t116 > 0)
        goto LAB42;

LAB43:    memcpy(t227, t104, 8);

LAB44:    t255 = (t227 + 4LL);
    t256 = *((unsigned int *)t255);
    t257 = (~(t256));
    t258 = *((unsigned int *)t227);
    t259 = (t258 & t257);
    t260 = (t259 != 0);
    if (t260 > 0)
        goto LAB74;

LAB75:    xsi_set_current_line(43, ng0);
    t2 = ((char*)((ng2)));
    t3 = (t0 + 2512);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);

LAB76:
LAB10:    goto LAB2;

LAB7:    t10 = *((unsigned int *)t4);
    t11 = *((unsigned int *)t7);
    *((unsigned int *)t4) = (t10 | t11);
    t12 = *((unsigned int *)t5);
    t13 = *((unsigned int *)t7);
    *((unsigned int *)t5) = (t12 | t13);
    goto LAB6;

LAB8:    xsi_set_current_line(27, ng0);

LAB11:    xsi_set_current_line(28, ng0);
    t22 = (t0 + 1160U);
    t23 = *((char **)t22);
    t22 = (t0 + 1320U);
    t24 = *((char **)t22);
    memset(t25, 0, 8);
    xsi_vlog_unsigned_add(t25, 4, t23, 3, t24, 3);
    t22 = (t0 + 2192);
    xsi_vlogvar_assign_value(t22, t25, 0, 0, 4);
    xsi_set_current_line(29, ng0);
    t2 = (t0 + 2192);
    t3 = (t2 + 48U);
    t5 = *((char **)t3);
    memset(t4, 0, 8);
    t6 = (t4 + 4LL);
    t7 = (t5 + 4LL);
    t8 = *((unsigned int *)t5);
    t9 = (t8 >> 3);
    t10 = (t9 & 1);
    *((unsigned int *)t4) = t10;
    t11 = *((unsigned int *)t7);
    t12 = (t11 >> 3);
    t13 = (t12 & 1);
    *((unsigned int *)t6) = t13;
    t16 = (t4 + 4LL);
    t14 = *((unsigned int *)t16);
    t15 = (~(t14));
    t17 = *((unsigned int *)t4);
    t18 = (t17 & t15);
    t19 = (t18 != 0);
    if (t19 > 0)
        goto LAB12;

LAB13:    xsi_set_current_line(32, ng0);
    t2 = ((char*)((ng2)));
    t3 = (t0 + 2512);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);

LAB14:    goto LAB10;

LAB12:    xsi_set_current_line(30, ng0);
    t22 = ((char*)((ng1)));
    t23 = (t0 + 2512);
    xsi_vlogvar_assign_value(t23, t22, 0, 0, 1);
    goto LAB14;

LAB18:    *((unsigned int *)t25) = 1;
    *((unsigned int *)t24) = 1;
    goto LAB19;

LAB20:    *((unsigned int *)t26) = 1;
    goto LAB23;

LAB22:    *((unsigned int *)t26) = 1;
    *((unsigned int *)t29) = 1;
    goto LAB23;

LAB24:    t39 = (t0 + 2352);
    t40 = (t39 + 48U);
    t41 = *((char **)t40);
    t43 = (t0 + 2352);
    t44 = (t43 + 64U);
    t45 = *((char **)t44);
    t46 = ((char*)((ng4)));
    xsi_vlog_generic_get_index_select_value(t42, 32, t41, t45, 2, t46, 32, 1);
    t47 = ((char*)((ng1)));
    memset(t48, 0, 8);
    t49 = (t48 + 4LL);
    t50 = (t42 + 4LL);
    t51 = (t47 + 4LL);
    t52 = *((unsigned int *)t42);
    t53 = *((unsigned int *)t47);
    t54 = (t52 ^ t53);
    t55 = *((unsigned int *)t50);
    t56 = *((unsigned int *)t51);
    t57 = (t55 ^ t56);
    t58 = (t54 | t57);
    t59 = *((unsigned int *)t50);
    t60 = *((unsigned int *)t51);
    t61 = (t59 | t60);
    t62 = (~(t61));
    t63 = (t58 & t62);
    if (t63 != 0)
        goto LAB30;

LAB27:    if (t61 != 0)
        goto LAB29;

LAB28:    *((unsigned int *)t48) = 1;

LAB30:    memset(t64, 0, 8);
    t65 = (t64 + 4LL);
    t66 = (t48 + 4LL);
    t67 = *((unsigned int *)t66);
    t68 = (~(t67));
    t69 = *((unsigned int *)t48);
    t70 = (t69 & t68);
    t71 = (t70 & 1U);
    if (t71 != 0)
        goto LAB31;

LAB32:    if (*((unsigned int *)t66) != 0)
        goto LAB33;

LAB34:    t73 = *((unsigned int *)t26);
    t74 = *((unsigned int *)t64);
    t75 = (t73 & t74);
    *((unsigned int *)t72) = t75;
    t76 = (t26 + 4LL);
    t77 = (t64 + 4LL);
    t78 = (t72 + 4LL);
    t79 = *((unsigned int *)t76);
    t80 = *((unsigned int *)t77);
    t81 = (t79 | t80);
    *((unsigned int *)t78) = t81;
    t82 = *((unsigned int *)t78);
    t83 = (t82 != 0);
    if (t83 == 1)
        goto LAB35;

LAB36:
LAB37:    goto LAB26;

LAB29:    *((unsigned int *)t48) = 1;
    *((unsigned int *)t49) = 1;
    goto LAB30;

LAB31:    *((unsigned int *)t64) = 1;
    goto LAB34;

LAB33:    *((unsigned int *)t64) = 1;
    *((unsigned int *)t65) = 1;
    goto LAB34;

LAB35:    t84 = *((unsigned int *)t72);
    t85 = *((unsigned int *)t78);
    *((unsigned int *)t72) = (t84 | t85);
    t86 = (t26 + 4LL);
    t87 = (t64 + 4LL);
    t88 = *((unsigned int *)t26);
    t89 = (~(t88));
    t90 = *((unsigned int *)t86);
    t91 = (~(t90));
    t92 = *((unsigned int *)t64);
    t93 = (~(t92));
    t94 = *((unsigned int *)t87);
    t95 = (~(t94));
    t96 = (t89 & t91);
    t97 = (t93 & t95);
    t98 = (~(t96));
    t99 = (~(t97));
    t100 = *((unsigned int *)t78);
    *((unsigned int *)t78) = (t100 & t98);
    t101 = *((unsigned int *)t78);
    *((unsigned int *)t78) = (t101 & t99);
    t102 = *((unsigned int *)t72);
    *((unsigned int *)t72) = (t102 & t98);
    t103 = *((unsigned int *)t72);
    *((unsigned int *)t72) = (t103 & t99);
    goto LAB37;

LAB38:    *((unsigned int *)t104) = 1;
    goto LAB41;

LAB40:    *((unsigned int *)t104) = 1;
    *((unsigned int *)t105) = 1;
    goto LAB41;

LAB42:    t117 = (t0 + 2192);
    t118 = (t117 + 48U);
    t119 = *((char **)t118);
    t121 = (t0 + 2192);
    t122 = (t121 + 64U);
    t123 = *((char **)t122);
    t124 = ((char*)((ng3)));
    xsi_vlog_generic_get_index_select_value(t120, 32, t119, t123, 2, t124, 32, 1);
    t125 = ((char*)((ng1)));
    memset(t126, 0, 8);
    t127 = (t126 + 4LL);
    t128 = (t120 + 4LL);
    t129 = (t125 + 4LL);
    t130 = *((unsigned int *)t120);
    t131 = *((unsigned int *)t125);
    t132 = (t130 ^ t131);
    t133 = *((unsigned int *)t128);
    t134 = *((unsigned int *)t129);
    t135 = (t133 ^ t134);
    t136 = (t132 | t135);
    t137 = *((unsigned int *)t128);
    t138 = *((unsigned int *)t129);
    t139 = (t137 | t138);
    t140 = (~(t139));
    t141 = (t136 & t140);
    if (t141 != 0)
        goto LAB48;

LAB45:    if (t139 != 0)
        goto LAB47;

LAB46:    *((unsigned int *)t126) = 1;

LAB48:    memset(t142, 0, 8);
    t143 = (t142 + 4LL);
    t144 = (t126 + 4LL);
    t145 = *((unsigned int *)t144);
    t146 = (~(t145));
    t147 = *((unsigned int *)t126);
    t148 = (t147 & t146);
    t149 = (t148 & 1U);
    if (t149 != 0)
        goto LAB49;

LAB50:    if (*((unsigned int *)t144) != 0)
        goto LAB51;

LAB52:    t150 = (t142 + 4LL);
    t151 = *((unsigned int *)t142);
    t152 = *((unsigned int *)t150);
    t153 = (t151 || t152);
    if (t153 > 0)
        goto LAB53;

LAB54:    memcpy(t187, t142, 8);

LAB55:    memset(t219, 0, 8);
    t220 = (t219 + 4LL);
    t221 = (t187 + 4LL);
    t222 = *((unsigned int *)t221);
    t223 = (~(t222));
    t224 = *((unsigned int *)t187);
    t225 = (t224 & t223);
    t226 = (t225 & 1U);
    if (t226 != 0)
        goto LAB67;

LAB68:    if (*((unsigned int *)t221) != 0)
        goto LAB69;

LAB70:    t228 = *((unsigned int *)t104);
    t229 = *((unsigned int *)t219);
    t230 = (t228 | t229);
    *((unsigned int *)t227) = t230;
    t231 = (t104 + 4LL);
    t232 = (t219 + 4LL);
    t233 = (t227 + 4LL);
    t234 = *((unsigned int *)t231);
    t235 = *((unsigned int *)t232);
    t236 = (t234 | t235);
    *((unsigned int *)t233) = t236;
    t237 = *((unsigned int *)t233);
    t238 = (t237 != 0);
    if (t238 == 1)
        goto LAB71;

LAB72:
LAB73:    goto LAB44;

LAB47:    *((unsigned int *)t126) = 1;
    *((unsigned int *)t127) = 1;
    goto LAB48;

LAB49:    *((unsigned int *)t142) = 1;
    goto LAB52;

LAB51:    *((unsigned int *)t142) = 1;
    *((unsigned int *)t143) = 1;
    goto LAB52;

LAB53:    t154 = (t0 + 2352);
    t155 = (t154 + 48U);
    t156 = *((char **)t155);
    t158 = (t0 + 2352);
    t159 = (t158 + 64U);
    t160 = *((char **)t159);
    t161 = ((char*)((ng4)));
    xsi_vlog_generic_get_index_select_value(t157, 32, t156, t160, 2, t161, 32, 1);
    t162 = ((char*)((ng2)));
    memset(t163, 0, 8);
    t164 = (t163 + 4LL);
    t165 = (t157 + 4LL);
    t166 = (t162 + 4LL);
    t167 = *((unsigned int *)t157);
    t168 = *((unsigned int *)t162);
    t169 = (t167 ^ t168);
    t170 = *((unsigned int *)t165);
    t171 = *((unsigned int *)t166);
    t172 = (t170 ^ t171);
    t173 = (t169 | t172);
    t174 = *((unsigned int *)t165);
    t175 = *((unsigned int *)t166);
    t176 = (t174 | t175);
    t177 = (~(t176));
    t178 = (t173 & t177);
    if (t178 != 0)
        goto LAB59;

LAB56:    if (t176 != 0)
        goto LAB58;

LAB57:    *((unsigned int *)t163) = 1;

LAB59:    memset(t179, 0, 8);
    t180 = (t179 + 4LL);
    t181 = (t163 + 4LL);
    t182 = *((unsigned int *)t181);
    t183 = (~(t182));
    t184 = *((unsigned int *)t163);
    t185 = (t184 & t183);
    t186 = (t185 & 1U);
    if (t186 != 0)
        goto LAB60;

LAB61:    if (*((unsigned int *)t181) != 0)
        goto LAB62;

LAB63:    t188 = *((unsigned int *)t142);
    t189 = *((unsigned int *)t179);
    t190 = (t188 & t189);
    *((unsigned int *)t187) = t190;
    t191 = (t142 + 4LL);
    t192 = (t179 + 4LL);
    t193 = (t187 + 4LL);
    t194 = *((unsigned int *)t191);
    t195 = *((unsigned int *)t192);
    t196 = (t194 | t195);
    *((unsigned int *)t193) = t196;
    t197 = *((unsigned int *)t193);
    t198 = (t197 != 0);
    if (t198 == 1)
        goto LAB64;

LAB65:
LAB66:    goto LAB55;

LAB58:    *((unsigned int *)t163) = 1;
    *((unsigned int *)t164) = 1;
    goto LAB59;

LAB60:    *((unsigned int *)t179) = 1;
    goto LAB63;

LAB62:    *((unsigned int *)t179) = 1;
    *((unsigned int *)t180) = 1;
    goto LAB63;

LAB64:    t199 = *((unsigned int *)t187);
    t200 = *((unsigned int *)t193);
    *((unsigned int *)t187) = (t199 | t200);
    t201 = (t142 + 4LL);
    t202 = (t179 + 4LL);
    t203 = *((unsigned int *)t142);
    t204 = (~(t203));
    t205 = *((unsigned int *)t201);
    t206 = (~(t205));
    t207 = *((unsigned int *)t179);
    t208 = (~(t207));
    t209 = *((unsigned int *)t202);
    t210 = (~(t209));
    t211 = (t204 & t206);
    t212 = (t208 & t210);
    t213 = (~(t211));
    t214 = (~(t212));
    t215 = *((unsigned int *)t193);
    *((unsigned int *)t193) = (t215 & t213);
    t216 = *((unsigned int *)t193);
    *((unsigned int *)t193) = (t216 & t214);
    t217 = *((unsigned int *)t187);
    *((unsigned int *)t187) = (t217 & t213);
    t218 = *((unsigned int *)t187);
    *((unsigned int *)t187) = (t218 & t214);
    goto LAB66;

LAB67:    *((unsigned int *)t219) = 1;
    goto LAB70;

LAB69:    *((unsigned int *)t219) = 1;
    *((unsigned int *)t220) = 1;
    goto LAB70;

LAB71:    t239 = *((unsigned int *)t227);
    t240 = *((unsigned int *)t233);
    *((unsigned int *)t227) = (t239 | t240);
    t241 = (t104 + 4LL);
    t242 = (t219 + 4LL);
    t243 = *((unsigned int *)t241);
    t244 = (~(t243));
    t245 = *((unsigned int *)t104);
    t246 = (t245 & t244);
    t247 = *((unsigned int *)t242);
    t248 = (~(t247));
    t249 = *((unsigned int *)t219);
    t250 = (t249 & t248);
    t251 = (~(t246));
    t252 = (~(t250));
    t253 = *((unsigned int *)t233);
    *((unsigned int *)t233) = (t253 & t251);
    t254 = *((unsigned int *)t233);
    *((unsigned int *)t233) = (t254 & t252);
    goto LAB73;

LAB74:    xsi_set_current_line(41, ng0);
    t261 = ((char*)((ng1)));
    t262 = (t0 + 2512);
    xsi_vlogvar_assign_value(t262, t261, 0, 0, 1);
    goto LAB76;

}


extern void work_m_14881990391713354488_1252437416_init()
{
	static char *pe[] = {(void *)C19_0,(void *)C20_1,(void *)A23_2};
	xsi_register_didat("work_m_14881990391713354488_1252437416", "isim/_tmp/work/m_14881990391713354488_1252437416.didat");
	xsi_register_executes(pe);
}
