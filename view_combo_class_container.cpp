#include "view_combo_class_container.h"

View_combo_class_container::View_combo_class_container()
{

    Number_of_defined_combo_views = 0;
    isActive = false;
}
void View_combo_class_container::Add(View_combo_class new_view){

    new_view.set_ID(Number_of_defined_combo_views);
    view_combo_vector.push_back(new_view);
    Number_of_defined_combo_views = Number_of_defined_combo_views + 1;
}

void View_combo_class_container::Remove(){
    view_combo_vector.pop_back();
    Number_of_defined_combo_views = Number_of_defined_combo_views - 1;
}

/** \brief Add some basic combo views to the combo view container
*
*/
void View_combo_class_container::Define_Some_Basic_Combo_Views(){
    View_combo_class base_color = View_combo_class("combo color", "ccombine the left view and the right view in a naive rapresentation");
    base_color.set_ProcessTypeCombo( BASE_COLOR);
    Add(base_color);
    View_combo_class base_monochrome = View_combo_class("combo monochrome", "ccombine the left view and the right view in a monochrome rapresentation");
    base_monochrome.set_ProcessTypeCombo(BASE_MONOCHROME);
    Add(base_monochrome);
}
