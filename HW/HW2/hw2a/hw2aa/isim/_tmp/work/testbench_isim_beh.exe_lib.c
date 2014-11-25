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
    work_m_14881990391713354488_1252437416_init();
    work_m_02599616674169276613_1949178628_init();


    xsi_register_tops("work_m_02599616674169276613_1949178628");
    xsi_register_tops("work_m_13203454983236357486_2073120511");


    return xsi_run_simulation(argc, argv);

}
