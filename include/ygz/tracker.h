#ifndef TRACKER_H_
#define TRACKER_H_

#include "ygz/frame.h"
#include "ygz/feature_detector.h"

namespace ygz {
    

class Tracker {
public:
    enum TrackerStatusType {
        TRACK_NOT_READY,
        TRACK_GOOD,
        TRACK_LOST
    };
    
    Tracker();
    ~Tracker(); 
    
    // set the reference to track 
    void SetReference( Frame::Ptr ref );
    
    // track the frame, call it after setting the reference
    void Track( Frame::Ptr curr );   
    
    // compute mean disparity, used in initilization 
    float MeanDisparity() const ;
    
    void GetTrackedPointsNormalPlane (
        vector<Vector2d>& pt1, 
        vector<Vector2d>& pt2 
    ) const ;
    
    void GetTrackedPixel (
        vector<Vector2d>& px1, 
        vector<Vector2d>& px2 
    ) const ;
    
    // draw the tracked points 
    void PlotTrackedPoints() const; 
    
    // accessors 
    TrackerStatusType Status() const { return _status; }
    
    list<cv::Point2f> GetPxRef() const { return _px_ref; }
    list<cv::Point2f> GetPxCurr() const { return _px_curr; }
    
protected:
    void TrackKLT( );
    
protected:
    Frame::Ptr _ref =nullptr;            // reference 
    Frame::Ptr _curr =nullptr;           // current  
    
    list<cv::Point2f> _px_ref;            // pixels in ref 
    list<cv::Point2f> _px_curr;           // pixels in curr 
    TrackerStatusType _status =TRACK_NOT_READY;
    
    shared_ptr<FeatureDetector> _detector; 
    
    // parameters 
    int _min_features_initializing; 
};

}

#endif