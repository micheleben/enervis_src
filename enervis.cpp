#include "enervis.h"
#include "global_variables.h"
#include "okFrontPanelDLL_ben.h"


void enervis_class::SetDefaultValues() {
    updatetime = 30;
    flag_write_buffer = 0;
    S8B = 0x0001; // 0x01 if 8bit mode, 0x00 if binary mode
    flag_S8B = 1;
    Mask = 0x0002 ; // 0x00 if non active, 0x02 if active;
    flag_Mask = 1;
    MaxMin = 0x0004; // 0x00 if Min, 0x04 if Max;
    flag_MaxMin = 1;
    S0 = 0x0008;
    flag_S0 = 1;
    S1 = 0x0010;
    flag_S1 = 1;
    CNT = 0x0020;
    flag_CNT = 1;
    fUPD = 0x0000;
    flag_fUPD = 0;
    software_downloading_data = 0x0000;
    flag_software_downloading_data = 0;
    Auto_MAXMIN = 0x0000;
    flag_Auto_MAXMIN = 0;

    PWM_DOWN_COST_duty = 45;
    PWM_DOWN_COST_length = 64; //max 255 8 bit
    PWM_DOWN_length = 35;
    PWM_DOWN_end = 45;//int(PWM_DOWN_length/PWM_DOWN_COST_length * PWM_DOWN_COST_duty);
    PWM_DOWN_increment = 1;
    //-------------------------------
    PWM_UP_COST_duty = 120;
    PWM_UP_COST_length = 255; //max 255 8 bit
    PWM_UP_length = 1500; //max 1023 10 bit
    PWM_UP_start = 124;//int(PWM_UP_length/PWM_UP_COST_length * PWM_UP_COST_duty);
    PWM_UP_stop = 1500;
    PWM_UP_increment = 1;
    //--------------------------------
    WAIT_prepare_readout = 500; //max 4095 12 bit
    WAIT_finish_readout= 500; //max 4095 12 bit
    WAIT_prepare_integration = 250; //max 4095 12 bit
    WAIT_finish_integration = 250; //max 4095 12 bit
    WAIT_update_row = 250; //max 4095 12 bit
    WAIT_next_row_eof = 250; //max 4095 12 bit
    //------------------------------
    time_conversion_max_11bit = 500;
    time_point_A_11bit = 300;
    time_point_B_11bit = 200;
    conv_div_A_5bit = 4;
    conv_div_B_5bit = 10;
    conv_div_C_5bit = 31;
    //-------------------------------
    rsnbl_start_value= 1;
    rsnbl_stop_value = 3072;
    //--- spartan and xem interface
    sig_gSELECT_RAM_BLOCK_TO_READ = 0x01;

    clk_wait_prepare_readout =  WAIT_prepare_readout;
    clk_wait_finish_readout =  WAIT_finish_readout;
    clk_wait_prepare_integration =  WAIT_prepare_integration;
    clk_wait_finish_integration =  WAIT_finish_integration;
    clk_wait_update_row =   WAIT_update_row;
    clk_wait_next_row_eof =  WAIT_next_row_eof;

    sig_time_conversion_max_11bit = time_conversion_max_11bit  ;
    sig_time_point_A_11bit = time_point_A_11bit;
    sig_time_point_B_11bit = time_point_B_11bit;
    sig_conv_div_A_5bit = conv_div_A_5bit;
    sig_conv_div_B_5bit = conv_div_B_5bit;
    sig_conv_div_C_5bit = conv_div_C_5bit;
    //-------------------------------
    sig_rsnbl_start_value = rsnbl_start_value;
    sig_rsnbl_stop_value = rsnbl_stop_value;


}

bool enervis_class::CheckProposedValues() {
    if (proposed_PWM_DOWN_COST_duty > PWM_DOWN_COST_length) return false;
    if (proposed_PWM_DOWN_length > 255) return false; // 8bit
    if (proposed_PWM_UP_COST_duty > PWM_UP_COST_length) return false;
    if (proposed_PWM_UP_length > 4095) return false; // 12bit
    //if (proposed_PWM_UP_stop > 4095) return false; // 12bit
    if (proposed_WAIT_prepare_readout > 4095) return false; //max 4095 12 bit
    if (proposed_WAIT_finish_readout > 4095) return false; //max 4095 12 bit
    if (proposed_WAIT_prepare_integration > 4095) return false; //max 4095 12 bit
    if (proposed_WAIT_finish_integration > 4095) return false; //max 4095 12 bit
    if (proposed_WAIT_update_row > 4095) return false; //max 4095 12 bit
    if (proposed_WAIT_next_row_eof > 4095) return false; //max 4095 12 bit
    //-------------------------------
    if (proposed_rsnbl_start_value > 65535) return false; //max 65535 16 bit
    if (proposed_rsnbl_stop_value > 65535) return false; //max 65535 16 bit
    if (proposed_rsnbl_start_value > proposed_rsnbl_stop_value) return false;
    //-------------------------------
    if (proposed_time_conversion_max_11bit > 2047) return false; //max 2047 11 bit
    if (proposed_time_point_A_11bit > 2047) return false; //max 2047 11 bit
    if (proposed_time_point_B_11bit > 2047) return false; //max 2047 11 bit
    if (proposed_conv_div_A_5bit > 31) return false; //max 31 5 bit
    if (proposed_conv_div_B_5bit> 31) return false; //max 31 5 bit
    if (proposed_conv_div_C_5bit> 31) return false; //max 31 5 bit
    if ((proposed_time_point_A_11bit + proposed_time_point_B_11bit) > proposed_time_conversion_max_11bit) return false;
    return true;
}

void enervis_class::SetProposedValues() {
    double evaluate,f1,f2,f3;
    PWM_DOWN_COST_duty = proposed_PWM_DOWN_COST_duty;
    //PWM_DOWN_COST_length = PWM_DOWN_COST_length;
    PWM_DOWN_length = proposed_PWM_DOWN_length;
    f1 = static_cast<double>(proposed_PWM_DOWN_length);
    f2 = static_cast<double>(PWM_DOWN_COST_length);
    f3 = static_cast<double>(proposed_PWM_DOWN_COST_duty);
    evaluate = f1/f2*f3;
    proposed_PWM_DOWN_end = static_cast<unsigned int> (evaluate);
    PWM_DOWN_end = proposed_PWM_DOWN_end;
    PWM_DOWN_increment = proposed_PWM_DOWN_increment;
    //-------------------------------
    PWM_UP_COST_duty = proposed_PWM_UP_COST_duty;
    //PWM_UP_COST_length = PWM_UP_COST_length;
    PWM_UP_length = proposed_PWM_UP_length;
    f1 = static_cast<double>(proposed_PWM_UP_length);
    f2 = static_cast<double>(PWM_UP_COST_length);
    f3 = static_cast<double>(proposed_PWM_UP_COST_duty);
    evaluate = f1/f2*f3;
    proposed_PWM_UP_start = static_cast<unsigned int> (evaluate);
    PWM_UP_start = proposed_PWM_UP_start;
    PWM_UP_increment = proposed_PWM_UP_increment;
    //--------------------------------
    WAIT_prepare_readout = proposed_WAIT_prepare_readout;
    WAIT_finish_readout= proposed_WAIT_finish_readout;
    WAIT_prepare_integration = proposed_WAIT_prepare_integration;
    WAIT_finish_integration = proposed_WAIT_finish_integration;
    WAIT_update_row = proposed_WAIT_update_row;
    WAIT_next_row_eof = proposed_WAIT_next_row_eof;
    //---------------------------------
    time_conversion_max_11bit = proposed_time_conversion_max_11bit;
    time_point_A_11bit = proposed_time_point_A_11bit ;
    time_point_B_11bit = proposed_time_point_B_11bit ;
    conv_div_A_5bit = proposed_conv_div_A_5bit ;
    conv_div_B_5bit = proposed_conv_div_B_5bit ;
    conv_div_C_5bit = proposed_conv_div_C_5bit;
    //---------------------------------
    rsnbl_start_value = proposed_rsnbl_start_value;
    rsnbl_stop_value = proposed_rsnbl_stop_value;
    // general conf:
    if (flag_S8B == 1) S8B = 0x0001; // 0x01 if 8bit mode, 0x00 if binary mode
    else S8B = 0x0000;
    if (flag_Mask == 1) Mask = 0x0002; // 0x00 if non active, 0x02 if active;
    else Mask = 0x0000 ;
    if (flag_MaxMin == 1) MaxMin = 0x0004; // 0x00 if Min, 0x04 if Max;
    else MaxMin = 0x0000;
    if (flag_S0 == 1) S0 = 0x0008; // 0x00 if S0 = 0, 0x08 if S0 = 1;
    else S0 = 0x0000;
    if (flag_S1 == 1) S1 = 0x0010; // 0x00 if S1 = 0, 0x10 if S1 = 1;
    else S1 = 0x0000;
    if (flag_CNT == 1) CNT = 0x0020; // 0x00 if S1 = 0, 0x10 if S1 = 1;
    else CNT = 0x0000;
    if (flag_fUPD == 1) fUPD = 0x0040; // 0x00 if S1 = 0, 0x10 if S1 = 1;
    else fUPD = 0x0000;
    if (flag_software_downloading_data == 1) software_downloading_data = 0x0080; // 0x00 if not downloading, 0x80 if downloading;
    else software_downloading_data = 0x0000;
    if (flag_Auto_MAXMIN == 1) Auto_MAXMIN = 0x0100; // 0x100 if not downloading, 0x80 if downloading;
    else Auto_MAXMIN = 0x0000;
    general_conf = S8B | Mask | MaxMin | S0 | S1 | CNT | fUPD|  software_downloading_data| Auto_MAXMIN;
    //--- set the signals of the spartan and xem interface..
    //--- all this stuff are here to easily adapt the rest of the code when the
    //--- interface will be changed.
    sig_general_conf = general_conf;
    clk_wait_prepare_readout =  WAIT_prepare_readout;
    clk_wait_finish_readout =  WAIT_finish_readout;
    clk_wait_prepare_integration =  WAIT_prepare_integration;
    clk_wait_finish_integration =  WAIT_finish_integration;
    clk_wait_update_row =   WAIT_update_row;
    clk_wait_next_row_eof =  WAIT_next_row_eof;

    sig_pwm_down_cost_duty = PWM_DOWN_COST_duty;
    sig_pwm_down_cost_length = PWM_DOWN_COST_length;

    sig_pwm_down_end = PWM_DOWN_end;
    sig_pwm_down_length = PWM_DOWN_length;
    sig_pwm_down_increment =  PWM_DOWN_increment;

    sig_pwm_up_cost_duty = PWM_UP_COST_duty;
    sig_pwm_up_cost_length = PWM_UP_COST_length;

    sig_pwm_up_start = PWM_UP_start;
    sig_pwm_up_length = PWM_UP_length;
    sig_pwm_up_increment =  PWM_UP_increment;

    sig_time_conversion_max_11bit = time_conversion_max_11bit  ;
    sig_time_point_A_11bit = time_point_A_11bit;
    sig_time_point_B_11bit = time_point_B_11bit;
    sig_conv_div_A_5bit = conv_div_A_5bit;
    sig_conv_div_B_5bit = conv_div_B_5bit;
    sig_conv_div_C_5bit = conv_div_C_5bit;

    sig_rsnbl_start_value = rsnbl_start_value;
    sig_rsnbl_stop_value = rsnbl_stop_value;

}


void enervis_class::ProcessBuffer(){
    //save the buffer content in the appropriate frame stucture
    //opalkelly and spartan3:
    const char *buffer_file_name;
    unsigned short int conv;
    int offset;
    int frame_sel;
    int end_frame;
    //note : the mask for semplified version is an or on the eight bit (11111111)
    //while in the S8B should be an and with 0xFE (11111110)
    unsigned char mask_S8B = 0xFE;
    unsigned char mask_bit1 = 0x01;
    unsigned char mask_bit2 = 0x02;
    unsigned char mask_bit3 = 0x04;
    unsigned char mask_bit4 = 0x08;
    unsigned char mask_bit5 = 0x10;
    unsigned char mask_bit6 = 0x20;
    unsigned char mask_bit7 = 0x40;
    unsigned char mask_bit8 = 0x80;
    int i,flag;
    switch (sig_gSELECT_RAM_BLOCK_TO_READ){
        case 1:
            offset = 0;
            frame_sel = 1;
            end_frame = 1024;
            buffer_file_name = "bin_buffer_1_1.dat";
        break;
        case 64:
            offset = 0;
            frame_sel = 2;
            end_frame = 1024;
            buffer_file_name = "bin_buffer_2_1.dat";
        break;
        case 2:
            offset = 2048;
            frame_sel = 1;
            end_frame = 1024;
            buffer_file_name = "bin_buffer_1_2.dat";
        break;
        case 128:
            offset = 2048;
            frame_sel = 2;
            end_frame = 1024;
            buffer_file_name = "bin_buffer_2_2.dat";
        break;
        //---
        case 4:
            offset = 4096;
            frame_sel = 1;
            end_frame = 1024;
            buffer_file_name = "bin_buffer_1_3.dat";
        break;
        case 256:
            offset = 4096;
            frame_sel = 2;
            end_frame = 1024;
            buffer_file_name = "bin_buffer_2_3.dat";
        break;
        //---
        case 8:
            offset = 6144;
            frame_sel = 1;
            end_frame = 1024;
            buffer_file_name = "bin_buffer_1_4.dat";
        break;
        case 512:
            offset = 6144;
            frame_sel = 2;
            end_frame = 1024;
            buffer_file_name = "bin_buffer_2_4.dat";
        break;
        //---
        case 16:
            offset = 8192;
            frame_sel = 1;
            end_frame = 1024;
            buffer_file_name = "bin_buffer_1_5.dat";
        break;
        case 1024:
            offset = 8192;
            frame_sel = 2;
            end_frame = 1024;
            buffer_file_name = "bin_buffer_2_5.dat";
        break;
        //---
        case 32:
            offset = 10240;
            frame_sel = 1;
            end_frame = 288;
            buffer_file_name = "bin_buffer_1_6.dat";
        break;
        case 2048:
            offset = 10240;
            frame_sel = 2;
            end_frame = 288;
            buffer_file_name = "bin_buffer_2_6.dat";
        break;
        }
    //bufout[i] = bufout[i] & 0xFE; // erase the hot pixel
    if (frame_sel == 1){
        for (i=0;i<end_frame;i++){

            frame1_S8[i*2 + offset] = bufout[i*2] >>1 ;
            frame1_S8[i*2 + offset] = frame1_S8[i*2 + offset] & 0x7F; // put the MSB to 0 after shifting
            frame1_S8[i*2 + offset + 1 ] = bufout[i*2 + 1]  >> 1;
            frame1_S8[i*2 + offset + 1 ] = frame1_S8[i*2 + offset + 1 ] & 0x7F;  // put the MSB to 0 after shifting
            conv = static_cast<unsigned short int>(bufout[i*2]);
            //if (bufout[i*2] != 0x00) frame1_sim[i*2 + offset] = 0xFF;
            if ( conv > threeshold ) frame1_sim[i*2 + offset] = 0xFF;
            else frame1_sim[i*2 + offset] = 0x00;
            conv = static_cast<unsigned short int>(bufout[i*2 +1]);
            //if (bufout[i*2 + 1] != 0x00) frame1_sim[i*2 + offset +1] = 0xFF;
            if ( conv > threeshold ) frame1_sim[i*2 + offset +1] = 0xFF;
            else frame1_sim[i*2 + offset +1] = 0x00;
            /*
            //reverse frame1_S8
            //frame1_S8[i*2 + offset] =((frame1_S8[i*2 + offset] * 0x80200802ULL) & 0x0884422110ULL) * 0x0101010101ULL >> 32;
            //frame1_S8[i*2 + offset] = frame1_S8[i*2 + offset] >> 1;
            if (frame1_S8[i*2 + offset] == 0x40) {
                frame1_S8[i*2 + offset] = 0x00;
            }
            if (frame1_S8[i*2 + offset] == 0x41) {
                frame1_S8[i*2 + offset] = 0x00;
            }
            */
            /*reverse frame1_S8
            //frame1_S8[i*2 + offset + 1 ] = ((frame1_S8[i*2 + offset + 1] * 0x80200802ULL) & 0x0884422110ULL) * 0x0101010101ULL >> 32;
            //frame1_S8[i*2 + offset + 1 ] = frame1_S8[i*2 + offset + 1 ] >> 1;
            if (frame1_S8[i*2 + offset + 1] == 0x40){
                frame1_S8[i*2 + offset + 1 ] = 0x00;
            }
            if (frame1_S8[i*2 + offset + 1] == 0x41){
                frame1_S8[i*2 + offset + 1 ] = 0x00;
            } */
        }
    } else {
        for (i=0;i<end_frame;i++){
            frame2_S8[i*2 + offset] = bufout[i*2] >> 1;
            frame2_S8[i*2 + offset] = frame2_S8[i*2 + offset] & 0x7F; // put the MSB to 0 after shifting
            frame2_S8[i*2 + offset + 1 ] = frame2_S8[i*2 + offset + 1 ] >> 1;
            frame2_S8[i*2 + offset + 1 ] = frame2_S8[i*2 + offset + 1 ] & 0x7F;  // put the MSB to 0 after shifting
            conv = static_cast<unsigned short int>(bufout[i*2]);
            //if (bufout[i*2] != 0x00) frame2_sim[i*2 + offset] = 0xFF;
            if ( conv > threeshold ) frame2_sim[i*2 + offset] = 0xFF;
            else frame2_sim[i*2 + offset] = 0x00;
            conv = static_cast<unsigned short int>(bufout[i*2 +1]);
            //if (bufout[i*2 + 1] != 0x00) frame2_sim[i*2 + offset +1] = 0xFF;
            if ( conv > threeshold ) frame2_sim[i*2 + offset +1] = 0xFF;
            else frame2_sim[i*2 + offset +1] = 0x00;
            /*reverse frame1_S8
            frame2_S8[i*2 + offset] =((frame2_S8[i*2 + offset] * 0x80200802ULL) & 0x0884422110ULL) * 0x0101010101ULL >> 32;
            frame2_S8[i*2 + offset] = frame2_S8[i*2 + offset] >> 1;
            frame2_S8[i*2 + offset + 1 ] = bufout[i*2 + 1] >> 1;
            frame2_S8[i*2 + offset + 1 ] = ((frame2_S8[i*2 + offset + 1] * 0x80200802ULL) & 0x0884422110ULL) * 0x0101010101ULL >> 32;
            flag = bufout[i*2] & mask_bit1;
            flag = flag | ((bufout[i*2] & mask_bit2) >> 1);
            flag = flag | ((bufout[i*2] & mask_bit3) >> 2);
            flag = flag | ((bufout[i*2] & mask_bit4) >> 3);
            flag = flag | ((bufout[i*2] & mask_bit5) >> 4);
            flag = flag | ((bufout[i*2] & mask_bit6) >> 5);
            flag = flag | ((bufout[i*2] & mask_bit7) >> 6);
            flag = flag | ((bufout[i*2] & mask_bit8) >> 7);
            if (flag == 1) frame2_sim[i*2 + offset] = 0xFF;
            else frame2_sim[i*2 + offset] = 0x00;
            flag = bufout[i*2 + 1] & mask_bit1;
            flag = flag | ((bufout[i*2 + 1] & mask_bit2) >> 1);
            flag = flag | ((bufout[i*2 + 1] & mask_bit3) >> 2);
            flag = flag | ((bufout[i*2 + 1] & mask_bit4) >> 3);
            flag = flag | ((bufout[i*2 + 1] & mask_bit5) >> 4);
            flag = flag | ((bufout[i*2 + 1] & mask_bit6) >> 5);
            flag = flag | ((bufout[i*2 + 1] & mask_bit7) >> 6);
            flag = flag | ((bufout[i*2 + 1] & mask_bit8) >> 7);
            if (flag == 1) frame2_sim[i*2 + offset + 1] = 0xFF;
            else frame2_sim[i*2 + offset + 1] = 0x00;
            */
            }
    }
    if (flag_write_buffer == 1) {
        //save buffer in a binary file
        std::ofstream bin_buffer(buffer_file_name,std::ios::out|std::ios::binary);
        bin_buffer.write(reinterpret_cast<const char*>(bufout),2048);
        bin_buffer.close();
    }
}

void enervis_class::ProcessBuffer_bin(){
    //save the buffer content in the appropriate frame stucture
    //opalkelly and spartan3:
    const char *buffer_file_name;
    int end_frame = 1456;
    buffer_file_name = "bin_buffer_s8b_0.dat";
    //note : the mask for semplified version is an or on the eight bit (11111111)
    //while in the S8B should be an and with 0xFE (11111110)
    unsigned char mask_bit1 = 0x01;
    unsigned char mask_bit2 = 0x02;
    unsigned char mask_bit3 = 0x04;
    unsigned char mask_bit4 = 0x08;
    unsigned char mask_bit5 = 0x10;
    unsigned char mask_bit6 = 0x20;
    unsigned char mask_bit7 = 0x40;
    unsigned char mask_bit8 = 0x80;
    int i,j,c;
    j = 0;
    c = 0;
    for (i=1;i<end_frame;i++){
        c++;
        if (c != 14) {
            if ((bufout[i] & mask_bit1) == mask_bit1) frame_s8b_sim[j*8 + 7] = 0xCC;
            else frame_s8b_sim[j*8 + 7] = 0x00;
            if ((bufout[i] & mask_bit2) == mask_bit2) frame_s8b_sim[j*8 + 6] = 0xCC;
            else frame_s8b_sim[j*8 + 6] = 0x00;
            if ((bufout[i] & mask_bit3) == mask_bit3) frame_s8b_sim[j*8 + 5] = 0xCC;
            else frame_s8b_sim[j*8 + 5] = 0x00;
            if ((bufout[i] & mask_bit4) == mask_bit4) frame_s8b_sim[j*8 + 4] = 0xCC;
            else frame_s8b_sim[j*8 + 4] = 0x00;
            if ((bufout[i] & mask_bit5) == mask_bit5) frame_s8b_sim[j*8 + 3] = 0xCC;
            else frame_s8b_sim[j*8 + 3] = 0x00;
            if ((bufout[i] & mask_bit6) == mask_bit6) frame_s8b_sim[j*8 + 2] = 0xCC;
            else frame_s8b_sim[j*8 + 2] = 0x00;
            if ((bufout[i] & mask_bit7) == mask_bit7) frame_s8b_sim[j*8 + 1] = 0xCC;
            else frame_s8b_sim[j*8 + 1] = 0x00;
            if ((bufout[i] & mask_bit8) == mask_bit8) frame_s8b_sim[j*8 + 0] = 0xCC;
            else frame_s8b_sim[j*8 + 0] = 0x00;
            j++;
        } else {
            c = 0;
        }
    }
    if (flag_write_buffer == 1) {
        //save buffer in a binary file
        std::ofstream bin_buffer(buffer_file_name,std::ios::out|std::ios::binary);
        bin_buffer.write(reinterpret_cast<const char*>(bufout),2048);
        bin_buffer.close();
    }
};

void enervis_class::ProcessBuffer_bis(){
    //save the buffer content in the appropriate frame stucture
    //opalkelly and spartan3:
    const char *buffer_file_name_1;
    const char *buffer_file_name_2;
    const char *buffer_file_name_3;
    const char *buffer_file_name_4;
    const char *buffer_file_name_5;
    const char *buffer_file_name_6;
    //note : the mask for semplified version is an or on the eight bit (11111111)
    //while in the S8B should be an and with 0xFE (11111110)
    unsigned char mask_S8B = 0xFE;
    int frame_sel;
    int i,flag;
    switch (sig_gSELECT_RAM_BLOCK_TO_READ){
        case 1:
            frame_sel = 1;
            buffer_file_name_1 = "bin_buffer_1_1.dat";
            buffer_file_name_2 = "bin_buffer_1_2.dat";
            buffer_file_name_3 = "bin_buffer_1_3.dat";
            buffer_file_name_4 = "bin_buffer_1_4.dat";
            buffer_file_name_5 = "bin_buffer_1_5.dat";
            buffer_file_name_6 = "bin_buffer_1_6.dat";
        break;
        case 2:
            frame_sel = 2;
            buffer_file_name_1 = "bin_buffer_2_1.dat";
            buffer_file_name_2 = "bin_buffer_2_2.dat";
            buffer_file_name_3 = "bin_buffer_2_3.dat";
            buffer_file_name_4 = "bin_buffer_2_4.dat";
            buffer_file_name_5 = "bin_buffer_2_5.dat";
            buffer_file_name_6 = "bin_buffer_2_6.dat";
        break;
        }
    if (frame_sel == 1){
        for (i=0;i<2048;i++){
            frame1_S8[i*2] = bufout_1[i] >>1 ;
            frame1_S8[i*2+ 2048] = bufout_2[i] >>1 ;
            frame1_S8[i*2+ 4096] = bufout_3[i] >>1 ;
            frame1_S8[i*2+ 6144] = bufout_4[i] >>1 ;
            frame1_S8[i*2+ 8192] = bufout_5[i] >>1 ;
            /*
            if (bufout[i*2] != 0x00) frame1_sim[i*2 + offset] = 0xCC;
            else frame1_sim[i*2 + offset] = 0x00;
            if (bufout[i*2 + 1] != 0x00) frame1_sim[i*2 + offset +1] = 0xCC;
            else frame1_sim[i*2 + offset +1] = 0x00;
            /*
            flag = bufout[i*2] & mask_bit1;
            flag = flag | ((bufout[i*2] & mask_bit2) >> 1);
            flag = flag | ((bufout[i*2] & mask_bit3) >> 2);
            flag = flag | ((bufout[i*2] & mask_bit4) >> 3);
            flag = flag | ((bufout[i*2] & mask_bit5) >> 4);
            flag = flag | ((bufout[i*2] & mask_bit6) >> 5);
            flag = flag | ((bufout[i*2] & mask_bit7) >> 6);
            flag = flag | ((bufout[i*2] & mask_bit8) >> 7);
            if (flag == 1) frame1_sim[i*2 + offset] = 0xFF;
            else frame1_sim[i*2 + offset] = 0;
            flag = bufout[i*2 + 1] & mask_bit1;
            flag = flag | ((bufout[i*2 + 1] & mask_bit2) >> 1);
            flag = flag | ((bufout[i*2 + 1] & mask_bit3) >> 2);
            flag = flag | ((bufout[i*2 + 1] & mask_bit4) >> 3);
            flag = flag | ((bufout[i*2 + 1] & mask_bit5) >> 4);
            flag = flag | ((bufout[i*2 + 1] & mask_bit6) >> 5);
            flag = flag | ((bufout[i*2 + 1] & mask_bit7) >> 6);
            flag = flag | ((bufout[i*2 + 1] & mask_bit8) >> 7);
            if (flag == 1) frame1_sim[i*2 + offset + 1] = 0xFF;
            else frame1_sim[i*2 + offset + 1] = 0;
            */
        }
    } else {
        for (i=0;i<2048;i++){
            frame2_S8[i*2] = bufout_1[i] >>1 ;
            frame2_S8[i*2+ 2048] = bufout_2[i] >>1 ;
            frame2_S8[i*2+ 4096] = bufout_3[i] >>1 ;
            frame2_S8[i*2+ 6144] = bufout_4[i] >>1 ;
            frame2_S8[i*2+ 8192] = bufout_5[i] >>1 ;
            /*
            flag = bufout[i*2] & mask_bit1;
            flag = flag | ((bufout[i*2] & mask_bit2) >> 1);
            flag = flag | ((bufout[i*2] & mask_bit3) >> 2);
            flag = flag | ((bufout[i*2] & mask_bit4) >> 3);
            flag = flag | ((bufout[i*2] & mask_bit5) >> 4);
            flag = flag | ((bufout[i*2] & mask_bit6) >> 5);
            flag = flag | ((bufout[i*2] & mask_bit7) >> 6);
            flag = flag | ((bufout[i*2] & mask_bit8) >> 7);
            if (flag == 1) frame2_sim[i*2 + offset] = 0xFF;
            else frame2_sim[i*2 + offset] = 0x00;
            flag = bufout[i*2 + 1] & mask_bit1;
            flag = flag | ((bufout[i*2 + 1] & mask_bit2) >> 1);
            flag = flag | ((bufout[i*2 + 1] & mask_bit3) >> 2);
            flag = flag | ((bufout[i*2 + 1] & mask_bit4) >> 3);
            flag = flag | ((bufout[i*2 + 1] & mask_bit5) >> 4);
            flag = flag | ((bufout[i*2 + 1] & mask_bit6) >> 5);
            flag = flag | ((bufout[i*2 + 1] & mask_bit7) >> 6);
            flag = flag | ((bufout[i*2 + 1] & mask_bit8) >> 7);
            if (flag == 1) frame2_sim[i*2 + offset + 1] = 0xFF;
            else frame2_sim[i*2 + offset + 1] = 0x00;
            */
            }
    }
    if (flag_write_buffer == 1) {
        //save buffer in a binary file
        std::ofstream bin_buffer;
        bin_buffer.open(buffer_file_name_1,std::ios::out|std::ios::binary);
        bin_buffer.write(reinterpret_cast<const char*>(bufout_1),2048);
        bin_buffer.close();
        bin_buffer.open(buffer_file_name_2,std::ios::out|std::ios::binary);
        bin_buffer.write(reinterpret_cast<const char*>(bufout_2),2048);
        bin_buffer.close();
        bin_buffer.open(buffer_file_name_3,std::ios::out|std::ios::binary);
        bin_buffer.write(reinterpret_cast<const char*>(bufout_3),2048);
        bin_buffer.close();
        bin_buffer.open(buffer_file_name_4,std::ios::out|std::ios::binary);
        bin_buffer.write(reinterpret_cast<const char*>(bufout_4),2048);
        bin_buffer.close();
        bin_buffer.open(buffer_file_name_5,std::ios::out|std::ios::binary);
        bin_buffer.write(reinterpret_cast<const char*>(bufout_5),2048);
        bin_buffer.close();
        bin_buffer.open(buffer_file_name_6,std::ios::out|std::ios::binary);
        bin_buffer.write(reinterpret_cast<const char*>(bufout_6),2048);
        bin_buffer.close();


    }
}
bool enervis_class::SetValueOn_XEMFPGA(){
    /**
     * Set value on FPGA spartan of xem
    VHDL SIDE (INPUT):
    --the signals attached to the wait
    ep00 : okWireIn    port map (ok1=>ok1, ep_addr=> x"00",ep_dataout => clk_wait_prepare_readout);
    ep01 : okWireIn    port map (ok1=>ok1, ep_addr=> x"01",ep_dataout => clk_wait_finish_readout);
    ep02 : okWireIn    port map (ok1=>ok1, ep_addr=> x"02",ep_dataout => clk_wait_prepare_integration);
    ep03 : okWireIn    port map (ok1=>ok1, ep_addr=> x"03",ep_dataout => clk_wait_finish_integration);
    ep04 : okWireIn    port map (ok1=>ok1, ep_addr=> x"04",ep_dataout => clk_wait_update_row);
    ep05 : okWireIn    port map (ok1=>ok1, ep_addr=> x"05",ep_dataout => clk_wait_next_row_eof);
    --pwm control
    ep06 : okWireIn    port map (ok1=>ok1, ep_addr=> x"06",ep_dataout => sig_pwm_down_cost_duty);
    ep07 : okWireIn    port map (ok1=>ok1, ep_addr=> x"07",ep_dataout => sig_pwm_down_cost_length);
    ep08 : okWireIn    port map (ok1=>ok1, ep_addr=> x"08",ep_dataout => sig_pwm_down_end);
    ep09 : okWireIn    port map (ok1=>ok1, ep_addr=> x"09",ep_dataout => sig_pwm_down_length);
    ep0a : okWireIn    port map (ok1=>ok1, ep_addr=> x"0a",ep_dataout => sig_pwm_down_increment);
    ep0b : okWireIn    port map (ok1=>ok1, ep_addr=> x"0b",ep_dataout => sig_pwm_up_cost_duty);
    ep0c : okWireIn    port map (ok1=>ok1, ep_addr=> x"0c",ep_dataout => sig_pwm_up_cost_length);
    ep0d : okWireIn    port map (ok1=>ok1, ep_addr=> x"0d",ep_dataout => sig_pwm_up_end);
    ep0e : okWireIn    port map (ok1=>ok1, ep_addr=> x"0e",ep_dataout => sig_pwm_up_length);
    ep0f : okWireIn    port map (ok1=>ok1, ep_addr=> x"0f",ep_dataout => sig_pwm_up_increment);
    --general conf (S8B, MaxMin, ...)
    ep10 : okWireIn    port map (ok1=>ok1, ep_addr=> x"10",ep_dataout => sig_general_conf);
    ep11 : okWireIn    port map (ok1=>ok1, ep_addr=> x"11",ep_dataout => sig_gSELECT_RAM_BLOCK_TO_READ);

    ep12 : okWireIn    port map (ok1=>ok1, ep_addr=> x"12",ep_dataout => sig_time_conversion_max_11bit);
    ep13 : okWireIn    port map (ok1=>ok1, ep_addr=> x"13",ep_dataout => sig_time_point_A_11bit);
    ep14 : okWireIn    port map (ok1=>ok1, ep_addr=> x"14",ep_dataout => sig_time_point_B_11bit);
    ep15 : okWireIn    port map (ok1=>ok1, ep_addr=> x"15",ep_dataout => sig_conv_div_A_5bit);
    ep16 : okWireIn    port map (ok1=>ok1, ep_addr=> x"16",ep_dataout => sig_conv_div_B_5bit);
    ep17 : okWireIn    port map (ok1=>ok1, ep_addr=> x"17",ep_dataout => sig_conv_div_C_5bit);
    -- rsNBL
    ep18 : okWireIn    port map (ok1=>ok1, ep_addr=> x"18",ep_dataout => sig_rsnbl_start_value);
    ep19 : okWireIn    port map (ok1=>ok1, ep_addr=> x"19",ep_dataout => sig_rsnbl_stop_value);
*/
    if (gFlag_xem_configured) {
        /* update values in input */
        gDev->SetWireInValue(0x00, clk_wait_prepare_readout);
        gDev->SetWireInValue(0x01, clk_wait_finish_readout);
        gDev->SetWireInValue(0x02, clk_wait_prepare_integration);
        gDev->SetWireInValue(0x03, clk_wait_finish_integration);
        gDev->SetWireInValue(0x04, clk_wait_update_row);
        gDev->SetWireInValue(0x05, clk_wait_next_row_eof);
        gDev->SetWireInValue(0x06, sig_pwm_down_cost_duty);
        gDev->SetWireInValue(0x07, sig_pwm_down_cost_length);
        gDev->SetWireInValue(0x08, sig_pwm_down_end);
        gDev->SetWireInValue(0x09, sig_pwm_down_length);
        gDev->SetWireInValue(0x0a, sig_pwm_down_increment);
        gDev->SetWireInValue(0x0b, sig_pwm_up_cost_duty);
        gDev->SetWireInValue(0x0c, sig_pwm_up_cost_length);
        //gDev->SetWireInValue(0x0d, enervis->sig_pwm_up_end);
        gDev->SetWireInValue(0x0e, sig_pwm_up_length);
        gDev->SetWireInValue(0x0f, sig_pwm_up_increment);
        gDev->SetWireInValue(0x10, sig_general_conf);

        gDev->SetWireInValue(0x12, sig_time_conversion_max_11bit);
        gDev->SetWireInValue(0x13, sig_time_point_A_11bit);
        gDev->SetWireInValue(0x14, sig_time_point_B_11bit);
        gDev->SetWireInValue(0x15, sig_conv_div_A_5bit);
        gDev->SetWireInValue(0x16, sig_conv_div_B_5bit);
        gDev->SetWireInValue(0x17, sig_conv_div_C_5bit);

        gDev->SetWireInValue(0x18, sig_rsnbl_start_value);
        gDev->SetWireInValue(0x19, sig_rsnbl_stop_value);

        gDev->SetWireInValue(0x11, sig_gSELECT_RAM_BLOCK_TO_READ);
        gDev->UpdateWireIns();
    }
    return true;
}

void enervis_class::GetValueOn_XEMFPGA(){
    if (gFlag_xem_configured) {
        gDev->UpdateWireOuts();
        gDev->UpdateTriggerOuts();
        sig_gPIPEO_COUNT = gDev->GetWireOutValue(0x2c) | gDev->GetWireOutValue(0x2d) << 16;
        sig_gACTUAL_RAM_ADDRESS = gDev->GetWireOutValue(0x2a);
        sig_gACTUAL_RAM_BLOCK  = gDev->GetWireOutValue(0x2b);
        gDev->ActivateTriggerIn(0x40, 0);
        gDev->ReadFromPipeOut(0xa1, 2048, bufout);
     }
}

/** \brief Get frame with opalkelly boards
*
*   This function download the contents of ram blocks that corrensponds to the frame
*   where the fpga is not writing. It returns the type of frame that has been read,
*   ODD if is the first frame or PAIR if is the second frame.
*   If the sensor is working in 8bit mode (flag_8Bit set to 1), it stores the data on
*   bufout_1, bufout_2, bufout_3, bufout_4, bufout_5, bufout_6 constant char vectors,
*   otherwise in bufout char vector
*/
FrameType enervis_class::GetFrameOn_XEMFPGA(){
    FrameType select_frame = ODD_FRAME;
    if (flag_S8B == 1) {
        //8bit format , we have to download 6 blocks of rams
        //say to firmware we want to download data
        flag_software_downloading_data = 1;
        software_downloading_data = 0x0080;
        general_conf = S8B | Mask | MaxMin | S0 | S1 | CNT | fUPD|  software_downloading_data| Auto_MAXMIN;
        sig_general_conf = general_conf;
        gDev->SetWireInValue(0x10, sig_general_conf);
        gDev->UpdateWireIns(); //syscall 1
        gDev->UpdateWireOuts(); //syscall 2
        sig_gACTUAL_RAM_BLOCK  = gDev->GetWireOutValue(0x2b);
        switch (sig_gACTUAL_RAM_BLOCK){
        case 1:
        case 2:
        case 4:
        case 8:
        case 16:
        case 32:
            select_frame = PAIR_FRAME;
            sig_gSELECT_RAM_BLOCK_TO_READ = 64;
        break;
        case 64:
        case 128:
        case 256:
        case 512:
        case 1024:
        case 2048:
            select_frame = ODD_FRAME;
            sig_gSELECT_RAM_BLOCK_TO_READ = 1;
        break;
        }
        //Now we know which frame we want to download
        gDev->SetWireInValue(0x11, sig_gSELECT_RAM_BLOCK_TO_READ);
        gDev->UpdateWireIns(); //syscall 3
        gDev->ReadFromPipeOut(0xa1, 2048, bufout_1); //syscall 4
        if (select_frame == PAIR_FRAME){
            //download the rest of the second (PAIR) frame
            sig_gSELECT_RAM_BLOCK_TO_READ = 128;
            gDev->SetWireInValue(0x11, sig_gSELECT_RAM_BLOCK_TO_READ);
            gDev->UpdateWireIns(); //syscall 5
            gDev->ReadFromPipeOut(0xa1, 2048, bufout_2); //syscall 6

            sig_gSELECT_RAM_BLOCK_TO_READ = 256;
            gDev->SetWireInValue(0x11, sig_gSELECT_RAM_BLOCK_TO_READ);
            gDev->UpdateWireIns(); //syscall 7
            gDev->ReadFromPipeOut(0xa1, 2048, bufout_3); //syscall 8

            sig_gSELECT_RAM_BLOCK_TO_READ = 512;
            gDev->SetWireInValue(0x11, sig_gSELECT_RAM_BLOCK_TO_READ);
            gDev->UpdateWireIns(); //syscall 9
            gDev->ReadFromPipeOut(0xa1, 2048, bufout_4); //syscall 10

            sig_gSELECT_RAM_BLOCK_TO_READ = 1024;
            gDev->SetWireInValue(0x11, sig_gSELECT_RAM_BLOCK_TO_READ);
            gDev->UpdateWireIns(); //syscall 10
            gDev->ReadFromPipeOut(0xa1, 2048, bufout_5); //syscall 11

            sig_gSELECT_RAM_BLOCK_TO_READ = 2048;
            gDev->SetWireInValue(0x11, sig_gSELECT_RAM_BLOCK_TO_READ);
            gDev->UpdateWireIns(); //syscall 12
            gDev->ReadFromPipeOut(0xa1, 2048, bufout_6); //syscall 13

        } else {
            //download the rest of the first (ODD) frame
            sig_gSELECT_RAM_BLOCK_TO_READ = 2;
            gDev->SetWireInValue(0x11, sig_gSELECT_RAM_BLOCK_TO_READ);
            gDev->UpdateWireIns(); //syscall 5
            gDev->ReadFromPipeOut(0xa1, 2048, bufout_2); //syscall 6

            sig_gSELECT_RAM_BLOCK_TO_READ = 4;
            gDev->SetWireInValue(0x11, sig_gSELECT_RAM_BLOCK_TO_READ);
            gDev->UpdateWireIns(); //syscall 7
            gDev->ReadFromPipeOut(0xa1, 2048, bufout_3); //syscall 8

            sig_gSELECT_RAM_BLOCK_TO_READ = 8;
            gDev->SetWireInValue(0x11, sig_gSELECT_RAM_BLOCK_TO_READ);
            gDev->UpdateWireIns(); //syscall 9
            gDev->ReadFromPipeOut(0xa1, 2048, bufout_4); //syscall 10

            sig_gSELECT_RAM_BLOCK_TO_READ = 16;
            gDev->SetWireInValue(0x11, sig_gSELECT_RAM_BLOCK_TO_READ);
            gDev->UpdateWireIns(); //syscall 10
            gDev->ReadFromPipeOut(0xa1, 2048, bufout_5); //syscall 11

            sig_gSELECT_RAM_BLOCK_TO_READ = 32;
            gDev->SetWireInValue(0x11, sig_gSELECT_RAM_BLOCK_TO_READ);
            gDev->UpdateWireIns(); //syscall 12
            gDev->ReadFromPipeOut(0xa1, 2048, bufout_6); //syscall 13
        }
        //say to the firmware that we have finish
        flag_software_downloading_data = 1;
        software_downloading_data = 0x0000;
        general_conf = S8B | Mask | MaxMin | S0 | S1 | CNT | fUPD|  software_downloading_data| Auto_MAXMIN;
        sig_general_conf = general_conf;
        gDev->SetWireInValue(0x10, sig_general_conf);
        gDev->UpdateWireIns(); //syscall 14
    } else {
        gDev->UpdateWireOuts(); //syscall 1
        sig_gACTUAL_RAM_BLOCK  = gDev->GetWireOutValue(0x2b);
        if (sig_gACTUAL_RAM_BLOCK == 1){
            select_frame = PAIR_FRAME;
            sig_gSELECT_RAM_BLOCK_TO_READ = 64;
        }else {
            select_frame = ODD_FRAME;
            sig_gSELECT_RAM_BLOCK_TO_READ = 1;
        }
        gDev->SetWireInValue(0x11, sig_gSELECT_RAM_BLOCK_TO_READ);
        gDev->UpdateWireIns(); //syscall 2
        gDev->ReadFromPipeOut(0xa1, 2048, bufout); //syscall 3
    }
    return select_frame;
}

bool enervis_class::Configure_XEM(std::string fileName_stdstring ){
        if (gFlag_dev_instantiated == true) {
            // Create and open the XEM (check for supported versions).

            if (okCFrontPanel::NoError != gDev->OpenBySerial()) {
                return false;
            }
            // Setup the PLL from the stored configuration.
            gDev->LoadDefaultPLLConfiguration();
            // Download the configuration file. Note the conversion between the
            // std string and a *char
            gDev->ConfigureFPGA(fileName_stdstring.c_str());
            return true;
        }
        return false;
}

/** \brief Get frame with opalkelly boards (not blocking)
*
*   This function download the contents of ram blocks that corrensponds to the frame
*   where the fpga is not writing. It returns the type of frame that has been read,
*   ODD if is the first frame or PAIR if is the second frame.
*   If the sensor is working in 8bit mode (flag_8Bit set to 1), it stores the data on
*   bufout_1, bufout_2, bufout_3, bufout_4, bufout_5, bufout_6 constant char vectors,
*   otherwise in bufout char vector
*/
FrameType enervis_class::GetFrameOn_XEMFPGA_NB(){
    FrameType select_frame = ODD_FRAME;
    if (flag_S8B == 1) {
        //8bit format , we have to download 6 blocks of rams
        //say to firmware we want to download data
        //flag_software_downloading_data = 1;
        //software_downloading_data = 0x0000;
        //general_conf = S8B | Mask | MaxMin | S0 | S1 | CNT | fUPD|  software_downloading_data| Auto_MAXMIN;
        //sig_general_conf = general_conf;
        //gDev->SetWireInValue(0x10, sig_general_conf);
        //gDev->UpdateWireIns(); //syscall 1
        gDev->UpdateWireOuts(); //syscall 2
        sig_gACTUAL_RAM_BLOCK  = gDev->GetWireOutValue(0x2b);
        switch (sig_gACTUAL_RAM_BLOCK){
        case 1:
        case 2:
        case 4:
        case 8:
        case 16:
        case 32:
            select_frame = PAIR_FRAME;
            sig_gSELECT_RAM_BLOCK_TO_READ = 64;
        break;
        case 64:
        case 128:
        case 256:
        case 512:
        case 1024:
        case 2048:
            select_frame = ODD_FRAME;
            sig_gSELECT_RAM_BLOCK_TO_READ = 1;
        break;
        }
        //Now we know which frame we want to download
        gDev->SetWireInValue(0x11, sig_gSELECT_RAM_BLOCK_TO_READ);
        gDev->UpdateWireIns(); //syscall 3
        gDev->ReadFromPipeOut(0xa1, 2048, bufout_1); //syscall 4
        if (select_frame == PAIR_FRAME){
            //download the rest of the second (PAIR) frame
            sig_gSELECT_RAM_BLOCK_TO_READ = 128;
            gDev->SetWireInValue(0x11, sig_gSELECT_RAM_BLOCK_TO_READ);
            gDev->UpdateWireIns(); //syscall 5
            gDev->ReadFromPipeOut(0xa1, 2048, bufout_2); //syscall 6

            sig_gSELECT_RAM_BLOCK_TO_READ = 256;
            gDev->SetWireInValue(0x11, sig_gSELECT_RAM_BLOCK_TO_READ);
            gDev->UpdateWireIns(); //syscall 7
            gDev->ReadFromPipeOut(0xa1, 2048, bufout_3); //syscall 8

            sig_gSELECT_RAM_BLOCK_TO_READ = 512;
            gDev->SetWireInValue(0x11, sig_gSELECT_RAM_BLOCK_TO_READ);
            gDev->UpdateWireIns(); //syscall 9
            gDev->ReadFromPipeOut(0xa1, 2048, bufout_4); //syscall 10

            sig_gSELECT_RAM_BLOCK_TO_READ = 1024;
            gDev->SetWireInValue(0x11, sig_gSELECT_RAM_BLOCK_TO_READ);
            gDev->UpdateWireIns(); //syscall 10
            gDev->ReadFromPipeOut(0xa1, 2048, bufout_5); //syscall 11

            sig_gSELECT_RAM_BLOCK_TO_READ = 2048;
            gDev->SetWireInValue(0x11, sig_gSELECT_RAM_BLOCK_TO_READ);
            gDev->UpdateWireIns(); //syscall 12
            gDev->ReadFromPipeOut(0xa1, 2048, bufout_6); //syscall 13

        } else {
            //download the rest of the first (ODD) frame
            sig_gSELECT_RAM_BLOCK_TO_READ = 2;
            gDev->SetWireInValue(0x11, sig_gSELECT_RAM_BLOCK_TO_READ);
            gDev->UpdateWireIns(); //syscall 5
            gDev->ReadFromPipeOut(0xa1, 2048, bufout_2); //syscall 6

            sig_gSELECT_RAM_BLOCK_TO_READ = 4;
            gDev->SetWireInValue(0x11, sig_gSELECT_RAM_BLOCK_TO_READ);
            gDev->UpdateWireIns(); //syscall 7
            gDev->ReadFromPipeOut(0xa1, 2048, bufout_3); //syscall 8

            sig_gSELECT_RAM_BLOCK_TO_READ = 8;
            gDev->SetWireInValue(0x11, sig_gSELECT_RAM_BLOCK_TO_READ);
            gDev->UpdateWireIns(); //syscall 9
            gDev->ReadFromPipeOut(0xa1, 2048, bufout_4); //syscall 10

            sig_gSELECT_RAM_BLOCK_TO_READ = 16;
            gDev->SetWireInValue(0x11, sig_gSELECT_RAM_BLOCK_TO_READ);
            gDev->UpdateWireIns(); //syscall 10
            gDev->ReadFromPipeOut(0xa1, 2048, bufout_5); //syscall 11

            sig_gSELECT_RAM_BLOCK_TO_READ = 32;
            gDev->SetWireInValue(0x11, sig_gSELECT_RAM_BLOCK_TO_READ);
            gDev->UpdateWireIns(); //syscall 12
            gDev->ReadFromPipeOut(0xa1, 2048, bufout_6); //syscall 13
        }
        //say to the firmware that we have finish
        //flag_software_downloading_data = 1;
        //software_downloading_data = 0x0000;
        //general_conf = S8B | Mask | MaxMin | S0 | S1 | CNT | fUPD|  software_downloading_data| Auto_MAXMIN;
        //sig_general_conf = general_conf;
        //gDev->SetWireInValue(0x10, sig_general_conf);
        //gDev->UpdateWireIns(); //syscall 14
    } else {
        gDev->UpdateWireOuts(); //syscall 1
        sig_gACTUAL_RAM_BLOCK  = gDev->GetWireOutValue(0x2b);
        if (sig_gACTUAL_RAM_BLOCK == 1){
            select_frame = PAIR_FRAME;
            sig_gSELECT_RAM_BLOCK_TO_READ = 64;
        }else {
            select_frame = ODD_FRAME;
            sig_gSELECT_RAM_BLOCK_TO_READ = 1;
        }
        gDev->SetWireInValue(0x11, sig_gSELECT_RAM_BLOCK_TO_READ);
        gDev->UpdateWireIns(); //syscall 2
        gDev->ReadFromPipeOut(0xa1, 2048, bufout); //syscall 3
    }
    return select_frame;
}


