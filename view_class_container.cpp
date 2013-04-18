#include "view_class_container.h"

View_class_container::View_class_container()
{
    Number_of_defined_views = 0;
    isActive = false;
}
void View_class_container::Add(View_class new_view){

    new_view.set_ID(Number_of_defined_views);
    view_vector.push_back(new_view);
    Number_of_defined_views = Number_of_defined_views + 1;
}

void View_class_container::Remove(){
    view_vector.pop_back();
    Number_of_defined_views = Number_of_defined_views - 1;
}

/** \brief Add some basic view to the view container
*
*
*/
void View_class_container::Define_Some_Basic_Views(){
    //view used for pair and odd frames
    View_class base_7bit_view = View_class("base 7 bit","view the 7 bit as is buffered from enervis\nThreshold and gain are not used in this view");
    base_7bit_view.set_ProcessType( BASE_7BIT );
    base_7bit_view.threshold=0;
    base_7bit_view.gain=0;
    Add(base_7bit_view);
    View_class notzero_8bit_view =View_class("not zero 8 bit","if one of the bit is not zero set pixel white\nThreshold and gain are not used in this view");
    notzero_8bit_view.set_ProcessType( NOTZERO_8BIT );
    notzero_8bit_view.threshold = 0;
    notzero_8bit_view.gain=0;
    Add(notzero_8bit_view);
    View_class overthreshold_8bit_view = View_class("over threshold bin","if the value of the pixel exceed the threeshold set pixel white\nGain is not used in this view");
    overthreshold_8bit_view.set_ProcessType( OVERTHRESHOLD_8BIT );
    overthreshold_8bit_view.threshold = 5;
    overthreshold_8bit_view.gain=0;
    Add(overthreshold_8bit_view);
}
/** \brief Add some view to process the odd frames to the view container
*
*
*/
void View_class_container::Define_Some_Basic_Views_ODD(){

    //view used for odd frames
    View_class base_7bit_view_OF = View_class("base 7 bit OF","(!ODD FRAMES ONLY) view the 7 bit as is buffered from enervis\nThreshold and gain are not used in this view");
    base_7bit_view_OF.set_ProcessType( BASE_7BIT_OF );
    base_7bit_view_OF.threshold=0;
    base_7bit_view_OF.gain=0;
    Add(base_7bit_view_OF);
    View_class notzero_8bit_view_OF =View_class("not zero 8 bit OF","(!ODD FRAMES ONLY) if one of the bit is not zero set pixel white\nThreshold and gain are not used in this view");
    notzero_8bit_view_OF.set_ProcessType( NOTZERO_8BIT_OF );
    notzero_8bit_view_OF.threshold = 0;
    notzero_8bit_view_OF.gain=0;
    Add(notzero_8bit_view_OF);
    View_class overthreshold_8bit_view_OF = View_class("over threshold bin OF","(!ODD FRAMES ONLY) if the value of the pixel exceed the threeshold set pixel white\nGain is not used in this view");
    overthreshold_8bit_view_OF.set_ProcessType( OVERTHRESHOLD_8BIT_OF );
    overthreshold_8bit_view_OF.threshold = 5;
    overthreshold_8bit_view_OF.gain=0;
    Add(overthreshold_8bit_view_OF);
    View_class threshold_to_zero_8bit_view_OF = View_class("threshold to zero OF","(!ODD FRAMES ONLY) if the value of the pixel exceed the threeshold set pixel to src value\nGain is not used in this view");
    threshold_to_zero_8bit_view_OF.set_ProcessType( THRESHOLD_TO_ZERO_OF );
    threshold_to_zero_8bit_view_OF.threshold = 5;
    threshold_to_zero_8bit_view_OF.gain=0;
    Add(threshold_to_zero_8bit_view_OF);
    View_class threshold_to_zero_eq_8bit_view_OF = View_class("threshold to zero equalize OF","(!ODD FRAMES ONLY) if the value of the pixel exceed the threeshold set pixel to src value and equalize the result\nGain is not used in this view");
    threshold_to_zero_eq_8bit_view_OF.set_ProcessType( THRESHOLD_TO_ZERO_EQ_OF );
    threshold_to_zero_eq_8bit_view_OF.threshold = 5;
    threshold_to_zero_eq_8bit_view_OF.gain=0;
    Add(threshold_to_zero_eq_8bit_view_OF);
}
/** \brief Add some view to process the pair frames to the view container
*
*
*/
void View_class_container::Define_Some_Basic_Views_PAIR(){
    //view used for pair frames:
    View_class base_7bit_view_PF = View_class("base 7 bit PF","(!PAIR FRAMES ONLY) view the 7 bit as is buffered from enervis\nThreshold and gain are not used in this view");
    base_7bit_view_PF.set_ProcessType( BASE_7BIT_PF );
    base_7bit_view_PF.threshold=0;
    base_7bit_view_PF.gain=0;
    Add(base_7bit_view_PF);
    View_class notzero_8bit_view_PF =View_class("not zero 8 bit PF","(!PAIR FRAMES ONLY) if one of the bit is not zero set pixel white\nThreshold and gain are not used in this view");
    notzero_8bit_view_PF.set_ProcessType( NOTZERO_8BIT_PF );
    notzero_8bit_view_PF.threshold = 0;
    notzero_8bit_view_PF.gain=0;
    Add(notzero_8bit_view_PF);
    View_class overthreshold_8bit_view_PF = View_class("over threshold bin PF","(!PAIR FRAMES ONLY) if the value of the pixel exceed the threeshold set pixel white\nGain is not used in this view");
    overthreshold_8bit_view_PF.set_ProcessType( OVERTHRESHOLD_8BIT_PF );
    overthreshold_8bit_view_PF.threshold = 5;
    overthreshold_8bit_view_PF.gain=0;
    Add(overthreshold_8bit_view_PF);
    View_class threshold_to_zero_8bit_view_PF = View_class("threshold to zero PF","(!PAIR FRAMES ONLY) if the value of the pixel exceed the threeshold set pixel to src value\nGain is not used in this view");
    threshold_to_zero_8bit_view_PF.set_ProcessType( THRESHOLD_TO_ZERO_PF );
    threshold_to_zero_8bit_view_PF.threshold = 5;
    threshold_to_zero_8bit_view_PF.gain=0;
    Add(threshold_to_zero_8bit_view_PF);
    View_class threshold_to_zero_eq_8bit_view_PF = View_class("threshold to zero equalize PF","(!PAIR FRAMES ONLY) if the value of the pixel exceed the threeshold set pixel to src value and equalize the result\nGain is not used in this view");
    threshold_to_zero_eq_8bit_view_PF.set_ProcessType( THRESHOLD_TO_ZERO_EQ_PF );
    threshold_to_zero_eq_8bit_view_PF.threshold = 5;
    threshold_to_zero_eq_8bit_view_PF.gain=0;
    Add(threshold_to_zero_eq_8bit_view_PF);
}

