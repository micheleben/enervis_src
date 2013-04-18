#ifndef __ENERVIS_CLASS_H__
#define __ENERVIS_CLASS_H__

#include <math.h>
#include <fstream>


/*!
 \brief

*/
enum FrameType {
    PAIR_FRAME,
    ODD_FRAME
};


/*!
 \brief The enervis class is the c++ interface with the enervis sensor


*/


class enervis_class
{
public:
     	
    unsigned char frame_processed_8bit[10816]; /*! this is the frame in 8bit format as result from the union of the buffers*/
    unsigned char frame1_S8[10816];
    unsigned char frame2_S8[10816]; /*!< TODO */ /*!< TODO */
    unsigned char frame1_sim[10816]; /*!< TODO */ /*!< TODO */
    unsigned char frame2_sim[10816]; /*!< TODO */ /*!< TODO */
    unsigned char frame_s8b_sim[10816]; /*!< TODO */ /*!< TODO */
    unsigned short int threeshold; /*!< TODO */ /*!< TODO */
    
    unsigned short int PWM_DOWN_COST_duty; /*!< TODO */ /*!< TODO */
    unsigned short int PWM_DOWN_COST_length; /*!< TODO */ /*!< TODO */
    unsigned short int PWM_DOWN_end; /*!< TODO */ /*!< TODO */
    unsigned short int PWM_DOWN_length; /*!< TODO */ /*!< TODO */
    unsigned short int PWM_DOWN_increment; /*!< TODO */ /*!< TODO */
    //-----------------------------
    unsigned short int PWM_UP_COST_duty; /*!< TODO */ /*!< TODO */
    unsigned short int PWM_UP_COST_length; /*!< TODO */ /*!< TODO */
    //unsigned short int PWM_UP_end;
    unsigned short int PWM_UP_start; /*!< TODO */ /*!< TODO */
    unsigned short int PWM_UP_stop; /*!< TODO */ /*!< TODO */
    unsigned short int PWM_UP_length; /*!< TODO */ /*!< TODO */
    unsigned short int PWM_UP_increment; /*!< TODO */ /*!< TODO */
    //-----------------------------
    unsigned short int WAIT_prepare_readout; /*!< TODO */ /*!< TODO */
    unsigned short int WAIT_finish_readout; /*!< TODO */ /*!< TODO */
    unsigned short int WAIT_prepare_integration; /*!< TODO */ /*!< TODO */
    unsigned short int WAIT_finish_integration; /*!< TODO */ /*!< TODO */
    unsigned short int WAIT_update_row; /*!< TODO */ /*!< TODO */
    unsigned short int WAIT_next_row_eof; /*!< TODO */ /*!< TODO */
    //-----------------------------
    unsigned short int time_conversion_max_11bit; /*!< TODO */ /*!< TODO */
    unsigned short int time_point_A_11bit; /*!< TODO */ /*!< TODO */
    unsigned short int time_point_B_11bit; /*!< TODO */ /*!< TODO */
    unsigned short int conv_div_A_5bit; /*!< TODO */ /*!< TODO */
    unsigned short int conv_div_B_5bit; /*!< TODO */ /*!< TODO */
    unsigned short int conv_div_C_5bit; /*!< TODO */ /*!< TODO */
    //-----------------------------
    unsigned short int rsnbl_start_value; /*!< TODO */ /*!< TODO */
    unsigned short int rsnbl_stop_value ; /*!< TODO */ /*!< TODO */
    //----------------- conf 
    unsigned short int S8B; /*!< TODO */ /*!< TODO */
    unsigned short int Mask; /*!< TODO */ /*!< TODO */
    unsigned short int MaxMin; /*!< TODO */ /*!< TODO */
    unsigned short int CNT; /*!< TODO */ /*!< TODO */
    unsigned short int S0; /*!< TODO */ /*!< TODO */
    unsigned short int S1; /*!< TODO */ /*!< TODO */
    unsigned short int fUPD; /*!< TODO */ /*!< TODO */
    unsigned short int Auto_MAXMIN; /*!< TODO */ /*!< TODO */
    
    unsigned short int software_downloading_data; /*!< TODO */ /*!< TODO */
    unsigned short int general_conf; /*!< TODO */ /*!< TODO */
    
    //----------------------------------------
    // The proposed value from the interface.
    // The following values are evaluated by the 
    // enervis_class::CheckProposedValues() and, if correct, copied
    // to the correspondent previous values
    //----------------------------------------
    unsigned short int flag_S8B; /*!< TODO */ /*!< TODO */
    unsigned short int flag_Mask; /*!< TODO */ /*!< TODO */
    unsigned short int flag_MaxMin; /*!< TODO */ /*!< TODO */
    unsigned short int flag_CNT; /*!< TODO */ /*!< TODO */
    unsigned short int flag_S0; /*!< TODO */ /*!< TODO */
    unsigned short int flag_S1; /*!< TODO */ /*!< TODO */
    unsigned short int flag_fUPD; /*!< TODO */ /*!< TODO */
    unsigned short int flag_software_downloading_data; /*!< TODO */ /*!< TODO */
    unsigned short int flag_Auto_MAXMIN; /*!< TODO */ /*!< TODO */
    
    unsigned short int proposed_PWM_DOWN_COST_duty; /*!< TODO */ /*!< TODO */
    //int proposed_PWM_DOWN_COST_length;
    unsigned short int proposed_PWM_DOWN_end; /*!< TODO */ /*!< TODO */
    unsigned short int proposed_PWM_DOWN_length; /*!< TODO */ /*!< TODO */
    unsigned short int proposed_PWM_DOWN_increment; /*!< TODO */ /*!< TODO */
    //-----------------------------
    unsigned short int proposed_PWM_UP_COST_duty; /*!< TODO */ /*!< TODO */
    //int proposed_PWM_UP_COST_length;
    //unsigned short int proposed_PWM_UP_end;
    unsigned short int proposed_PWM_UP_start; /*!< TODO */ /*!< TODO */
    unsigned short int proposed_PWM_UP_stop; /*!< TODO */ /*!< TODO */
    unsigned short int proposed_PWM_UP_length; /*!< TODO */ /*!< TODO */
    unsigned short int proposed_PWM_UP_increment; /*!< TODO */ /*!< TODO */
    //-----------------------------
    unsigned short int proposed_WAIT_prepare_readout; /*!< TODO */ /*!< TODO */
    unsigned short int proposed_WAIT_finish_readout; /*!< TODO */ /*!< TODO */
    unsigned short int proposed_WAIT_prepare_integration; /*!< TODO */ /*!< TODO */
    unsigned short int proposed_WAIT_finish_integration; /*!< TODO */ /*!< TODO */
    unsigned short int proposed_WAIT_update_row; /*!< TODO */ /*!< TODO */
    unsigned short int proposed_WAIT_next_row_eof; /*!< TODO */ /*!< TODO */
    //-----------------------------
    unsigned short int proposed_time_conversion_max_11bit; /*!< TODO */ /*!< TODO */
    unsigned short int proposed_time_point_A_11bit; /*!< TODO */ /*!< TODO */
    unsigned short int proposed_time_point_B_11bit; /*!< TODO */ /*!< TODO */
    unsigned short int proposed_conv_div_A_5bit; /*!< TODO */ /*!< TODO */
    unsigned short int proposed_conv_div_B_5bit; /*!< TODO */ /*!< TODO */
    unsigned short int proposed_conv_div_C_5bit; /*!< TODO */ /*!< TODO */
    //--------------------------------------
    unsigned short int proposed_rsnbl_start_value; /*!< TODO */ /*!< TODO */
    unsigned short int proposed_rsnbl_stop_value ; /*!< TODO */ /*!< TODO */
    //-------------------------------
    // opalkelly and spartan interface.
    // This values correspond to the 16 bit signals that are connected to xem3001   
    //the following quantities are expressed in 16 bit clock pulses 
    unsigned short int clk_wait_prepare_readout;  /*!< TODO */ /*!< TODO */
    unsigned short int clk_wait_finish_readout; /*!< TODO */ /*!< TODO */
    unsigned short int clk_wait_prepare_integration; /*!< TODO */ /*!< TODO */
    unsigned short int clk_wait_finish_integration; /*!< TODO */ /*!< TODO */
    unsigned short int clk_wait_update_row; /*!< TODO */ /*!< TODO */
    unsigned short int clk_wait_next_row_eof; /*!< TODO */ /*!< TODO */
    
    unsigned short int sig_pwm_down_cost_duty; /*!< TODO */ /*!< TODO */
    unsigned short int sig_pwm_down_cost_length; /*!< TODO */ /*!< TODO */
    unsigned short int sig_pwm_down_end; /*!< TODO */ /*!< TODO */
    unsigned short int sig_pwm_down_length; /*!< TODO */ /*!< TODO */
    unsigned short int sig_pwm_down_increment; /*!< TODO */ /*!< TODO */
    
    unsigned short int sig_pwm_up_cost_duty; /*!< TODO */ /*!< TODO */
    unsigned short int sig_pwm_up_cost_length; /*!< TODO */ /*!< TODO */
    
    //unsigned short int sig_pwm_up_end;
    unsigned short int sig_pwm_up_start; /*!< TODO */ /*!< TODO */
    unsigned short int sig_pwm_up_stop; /*!< TODO */ /*!< TODO */
    
    unsigned short int sig_pwm_up_length; /*!< TODO */ /*!< TODO */
    unsigned short int sig_pwm_up_increment; /*!< TODO */ /*!< TODO */
    
    unsigned short int sig_gSELECT_RAM_BLOCK_TO_READ; /*!< TODO */ /*!< TODO */
    
    unsigned short int sig_gACTUAL_RAM_ADDRESS; /*!< TODO */ /*!< TODO */
    unsigned short int sig_gACTUAL_RAM_BLOCK; /*!< TODO */ /*!< TODO */
    unsigned int sig_gPIPEO_COUNT; /*!< TODO */ /*!< TODO */
    //configurazione del clock
    unsigned short int sig_time_conversion_max_11bit; /*!< TODO */ /*!< TODO */
    unsigned short int sig_time_point_A_11bit; /*!< TODO */ /*!< TODO */
    unsigned short int sig_time_point_B_11bit; /*!< TODO */ /*!< TODO */
    unsigned short int sig_conv_div_A_5bit; /*!< TODO */ /*!< TODO */
    unsigned short int sig_conv_div_B_5bit; /*!< TODO */ /*!< TODO */
    unsigned short int sig_conv_div_C_5bit; /*!< TODO */ /*!< TODO */
    //-----------------------------
    unsigned short int sig_rsnbl_start_value; /*!< TODO */ /*!< TODO */
    unsigned short int sig_rsnbl_stop_value ;    /*!< TODO */ /*!< TODO */
    //--- general conf
    unsigned int sig_general_conf; /*!< TODO */ /*!< TODO */
    // data from ram memory (pipeOut 1024 x16 bit = 2048 char)
    unsigned char bufout[2048]; /*! first buffer of memory it contains the 8 bit value of pixels from pixel 0 to pixel   */
    unsigned char bufout_1[2048]; /*! second buffer it contains the 8 bit value of pixels from pixel 0 to pixel*/
    unsigned char bufout_2[2048]; /*! third buffer it contains the 8 bit value of pixels from pixel 0 to pixel*/
    unsigned char bufout_3[2048]; /*! fourth buffer it contains the 8 bit value of pixels from pixel 0 to pixel*/
    unsigned char bufout_4[2048]; /*! fifth buffer it contains the 8 bit value of pixels from pixel 0 to pixel*/
    unsigned char bufout_5[2048]; /*! sixth buffer it contains the 8 bit value of pixels from pixel 0 to pixel*/
    unsigned char bufout_6[2048]; /*! seventh buffer it contains the 8 bit value of pixels from pixel 0 to pixel */
    //--- end of spartan and xem interface

    //--------------------------------------
    int updatetime; /*!< TODO */ /*!< TODO */
    int flag_write_buffer; /*!< TODO */ /*!< TODO */

    /*!
     \brief /called at init to set the defaults

    */
    void SetDefaultValues();

    /*!
     \brief check the values proposed (writed into the class from some external interface

     \return bool
    */
    bool CheckProposedValues();
    /*!
     \brief Set the proposed values and sync correlated values run checkProposedValues routine previous

    */
    void SetProposedValues();

    void ProcessBuffer();
    void ProcessBuffer_bin();
    void ProcessBuffer_bis();

    void GetValueOn_XEMFPGA();
    bool SetValueOn_XEMFPGA();
    bool Configure_XEM(std::string fileName_stdstring);

    /*!
     \brief Get frame with opalkelly boards
     \return FrameType
    */
    FrameType GetFrameOn_XEMFPGA();
    /*!
     \brief Get frame with opalkelly boards without blocking the firmware in the general conf loop.
     \return FrameType
    */
    FrameType GetFrameOn_XEMFPGA_NB();
};

extern  enervis_class *gEnervis; /*! this is the pointer to a global available object of the enervis_class */

#endif    
