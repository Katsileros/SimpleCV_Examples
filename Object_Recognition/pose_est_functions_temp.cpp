// ston constructor

    frame_ = cv::Mat::zeros(frameHeight_,frameWidth_,CV_8UC1);


CameraCapture_ = new cv::VideoCapture(0);
    if(!CameraCapture_->isOpened())
    {
       std::cout<<"Selected camera is not initialized \n"<<std::endl;
    }
    
// sto .h
cv::VideoCapture* CameraCapture_;
cv::Mat frame_;

void getInitialPose();
void collectPoses(int k);

//stn main
pEst->getInitialPose();
pEst->collectPoses(1);


// sto .cpp
void poseEstimation::getInitialPose()
{
	cv::Mat grayframe = cv::Mat::zeros(frameHeight_,frameWidth_,CV_8UC1);
	int found;
	int KeyPressed;
	std::cout << "Give the initial pose of the object on the chessboard. \n" << std::endl;
	
	cv::namedWindow("initialPose",CV_WINDOW_AUTOSIZE);

	
	while(1){
			
	//!< Retrieve data(shnapshot) from camera
	CameraCapture_->grab();
	CameraCapture_->retrieve(frame_);
		
	// Convert image to gray scale.
	cv::cvtColor( frame_ , grayframe , CV_BGR2GRAY );
  
	//!<Find and draw corners for the camera's snapshot
    found = cv::findChessboardCorners(grayframe,patternSize_,corners_,
		 CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FAST_CHECK | CV_CALIB_CB_NORMALIZE_IMAGE);
         //~ cv::CALIB_CB_ADAPTIVE_THRESH+cv::CALIB_CB_NORMALIZE_IMAGE/*+CALIB_CB_FAST_CHECK*/);
         
    //!< Improve the found corners' coordinate accuracy for chessboard
    if(found==0 && (corners_.size()!=0))
    {
        cv::cornerSubPix(grayframe,corners_, cv::Size(11, 11), cv::Size(-1, -1),
                     cv::TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
    }
    //!< Draw the corners
    cv::drawChessboardCorners(frame_,patternSize_, cv::Mat(corners_),found);
    
	cv::imshow("initialPose",frame_);
	KeyPressed=cv::waitKey(10) & 255;
    if(KeyPressed==27) //KeyPressed==esc
    {
            std::cout<<"Ready to exit!!!\n"<<std::endl;
            break;
    }
    if (KeyPressed==99) //KeyPressed==c
    {
		pose1_ = frame_;
		break;
    }
     
  }
}

void poseEstimation::collectPoses(int k)
{
	cv::Mat grayframe = cv::Mat::zeros(frameHeight_,frameWidth_,CV_8UC1);
	int found;
	int KeyPressed;
	
	std::cout << "Take another pose.\n" << std::endl;
	
	cv::namedWindow("pose",CV_WINDOW_AUTOSIZE);

	
	while(1){	
	//!< Retrieve data(shnapshot) from camera
	CameraCapture_->grab();
	CameraCapture_->retrieve(frame_);
		
	// Convert image to gray scale.
	cv::cvtColor( frame_ , grayframe , CV_BGR2GRAY );
  
	//!<Find and draw corners for the camera's snapshot
    found = cv::findChessboardCorners(grayframe,patternSize_,corners_,
		 CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FAST_CHECK | CV_CALIB_CB_NORMALIZE_IMAGE);
         //~ cv::CALIB_CB_ADAPTIVE_THRESH+cv::CALIB_CB_NORMALIZE_IMAGE/*+CALIB_CB_FAST_CHECK*/);
         
    //!< Improve the found corners' coordinate accuracy for chessboard
    if(found==0 && (corners_.size()!=0))
    {
        cv::cornerSubPix(grayframe,corners_, cv::Size(11, 11), cv::Size(-1, -1),
                     cv::TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
    }
    //!< Draw the corners
    cv::drawChessboardCorners(frame_,patternSize_, cv::Mat(corners_),found);
    
	cv::imshow("pose",frame_);
	KeyPressed=cv::waitKey(10) & 255;
    if(KeyPressed==27) //KeyPressed==esc
    {
            std::cout<<"Ready to exit!!!\n"<<std::endl;
            break;
    }
    if (KeyPressed==99) //KeyPressed==c
    {
		pose2_ = frame_;
		break;
    }
     
  }
}


