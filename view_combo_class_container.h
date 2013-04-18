#ifndef VIEW_COMBO_CLASS_CONTAINER_H
#define VIEW_COMBO_CLASS_CONTAINER_H

#include "view_combo_class.h"

class View_combo_class_container
{
public:

    bool isActive; /*! if this boolean is active the combo view selected in the container is activated*/
    int Number_of_defined_combo_views; /*! this is incremented when new combo views are added to the container*/
    int selection; /*! this is the address of the combo view in the combo view container */
    std::vector<View_combo_class> view_combo_vector; /*! the combo view container */
    /*!
     \brief Add a new_combo_view to the container

     \param new_view
    */
    void Add(View_combo_class new_view);
    /*!
     \brief Remove a combo view from the container

    */
    void Remove();
    /*!
     \brief add the default views to the container
    */

    void Define_Some_Basic_Combo_Views();

    View_combo_class_container();
};
extern View_combo_class_container *gDefinedComboViews; /*! a global pointer used to define the views available on on the combo interface*/
extern cv::Mat * gCV_MAT_FRAME_VIEW_COMBO; /*! the opencv rapresentions of the frame as are view on the combo interface */
#endif // VIEW_COMBO_CLASS_CONTAINER_H
