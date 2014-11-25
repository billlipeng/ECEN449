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

#include "xsi.h"

struct XSI_INFO xsi_info;


int isim_run(int argc, char **argv)
{
    xsi_init_design(argc, argv);
    xsi_register_info(&xsi_info);

    work_m_13203454983236357486_2073120511_init();
    work_m_12999016778316712927_3543086200_init();
    work_m_03966753657235039494_1949178628_init();


    xsi_register_tops("work_m_03966753657235039494_1949178628");
    xsi_register_tops("work_m_13203454983236357486_2073120511");


    return xsi_run_simulation(argc, argv);

}
