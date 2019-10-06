#include "Module.h"
#include <yarp/os/Network.h>
#include <cstdlib>
#include <yarp/os/LogStream.h>
#include <iostream>
#include <memory>

// YARP
#include <yarp/os/RFModule.h>
#include <yarp/os/BufferedPort.h>
#include <yarp/sig/Vector.h>
#include <yarp/os/LogStream.h>

// iDynTree
#include <iDynTree/Core/VectorFixSize.h>
#include <iDynTree/Core/EigenHelpers.h>
#include <iDynTree/yarp/YARPConversions.h>
#include <iDynTree/yarp/YARPEigenConversions.h>
#include <iDynTree/Model/Model.h>
#include <memory>
#include <deque>
#include <iDynTree/Core/VectorFixSize.h>
#include <iDynTree/ModelIO/ModelLoader.h>
int main(int argc, char **argv)
{
    using namespace yarp::os;
    using namespace yarp::sig;

    yarp::os::Network yarp;

    if (!yarp::os::Network::checkNetwork(5.0)) {
        std::cout << "Yarp network not found\n";
        return EXIT_FAILURE;
    }

    ResourceFinder rf = ResourceFinder::getResourceFinderSingleton();
    rf.configure(argc, argv);
    std::string model = rf.check("model",yarp::os::Value("model.urdf")).asString();
    std::string pathToModel = yarp::os::ResourceFinder::getResourceFinderSingleton().findFileByName(model);

    yInfo() << "[WalkingModule::setRobotModel] The model is found in: " << pathToModel;
    iDynTree::ModelLoader m_loader; /**< Model loader class. */
    // only the controlled joints are extracted from the URDF file




    std::vector<std::string> axesList;
       axesList.push_back("torso_pitch");
       axesList.push_back("torso_roll");
       axesList.push_back("torso_yaw");

       // Left arm
       axesList.push_back("l_shoulder_pitch");
       axesList.push_back("l_shoulder_roll");
       axesList.push_back("l_shoulder_yaw");
       axesList.push_back("l_elbow");

       // Right arm
       axesList.push_back("r_shoulder_pitch");
       axesList.push_back("r_shoulder_roll");
       axesList.push_back("r_shoulder_yaw");
       axesList.push_back("r_elbow");

       // Left leg
       axesList.push_back("l_hip_pitch");
       axesList.push_back("l_hip_roll");
       axesList.push_back("l_hip_yaw");
       axesList.push_back("l_knee");
       axesList.push_back("l_ankle_pitch");
       axesList.push_back("l_ankle_roll");

       // Right leg
       axesList.push_back("r_hip_pitch");
       axesList.push_back("r_hip_roll");
       axesList.push_back("r_hip_yaw");
       axesList.push_back("r_knee");
       axesList.push_back("r_ankle_pitch");
       axesList.push_back("r_ankle_roll");






    if(!m_loader.loadReducedModelFromFile(pathToModel, axesList))
    {
        yError() << "[WalkingModule::setRobotModel] Error while loading the model from " << pathToModel;
        return false;
    }
  //  Module module;


            auto head_imu_idx =m_loader.model().getFrameIndex("imu_frame");
            auto head_R_imu = m_loader.model().getFrameTransform(head_imu_idx).getRotation();

            yInfo()<<"head imu Roll"<<head_R_imu.asRPY()(0);
            yInfo()<<"head imu Pitch"<<head_R_imu.asRPY()(1);
            yInfo()<<"head imu Yaw"<<head_R_imu.asRPY()(2);

            auto root_imu_idx = m_loader.model().getFrameIndex("root_link_imu_frame");
            auto root_R = m_loader.model().getFrameTransform(root_imu_idx).getRotation();
    
    //return module.runModule(rf);


}
