#ifndef VIEW_CLASS_CONTAINER_H
#define VIEW_CLASS_CONTAINER_H

#include <iostream>
#include <vector>
#include "view_class.h"
/*!
 \brief
*/
class View_class_container
{
public:
    /*! if this boolean is active the view selected in the container is activated*/
    bool isActive;
    /*! this is incremented when new views are added to the container*/
    int Number_of_defined_views;
    /*! this is the address of the view in the view container */
    int selection;
    /*! the view container */
    std::vector<View_class> view_vector;
    /*!
     \brief Add a new_view to the container

     \param new_view
    */
    void Add(View_class new_view);
    /*!
     \brief Remove a view from the container

    */
    void Remove();
    /*!
     \brief add the default views to the container
    */
    void Define_Some_Basic_Views();
    void Define_Some_Basic_Views_ODD();
    void Define_Some_Basic_Views_PAIR();

/*!
 \brief

*/
    View_class_container();

};
/*! a global pointer used to define the views available on the left label*/
extern View_class_container *gDefinedViews_left;
/*! a global pointer used to define the views available on the left label*/
extern View_class_container *gDefinedViews_right;

//These are the opencv rapresentions of the frame as are view on the interface:
//the gCV_MAT_FRAME_VIEW is processed (eg applying threshold and gain) to produce these
//two new rapresentation)
//extern CvMat* gCV_MAT_FRAME_VIEW_left; /*! the opencv rapresentions of the frame as are view on the interface in the left label */
/*! the opencv rapresentions of the frame as are view on the interface in the left label */
extern cv::Mat * gCV_MAT_FRAME_VIEW_left;
//extern CvMat* gCV_MAT_FRAME_VIEW_right; /*! the opencv rapresentions of the frame as are view on the interface in the right label */
/*! the opencv rapresentions of the frame as are view on the interface in the right label */
extern cv::Mat * gCV_MAT_FRAME_VIEW_right;
#endif // VIEW_CLASS_CONTAINER_H
