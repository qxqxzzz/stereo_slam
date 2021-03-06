/**
 * @file
 * @brief Pose class.
 */

#ifndef POSE_H
#define POSE_H

#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>

using namespace std;

namespace slam
{

class Pose
{

public:

	// Constructor
  Pose();

  struct Params
  {
    string pose_frame_id;             //!> Pose frame id for publisher
    string pose_child_frame_id;       //!> Base frame id for publisher

    // default settings
    Params () {
      pose_frame_id               = "/map";
      pose_child_frame_id         = "/robot";
    }
  };

  /**
   * @param params new parameters
   */
  inline void setParams(const Params& params)
  {
    params_ = params;
  }

  /**
   * @return current parameters
   */
  inline Params params() const { return params_; }

  // Advertises the pose message
  void advertisePoseMsg(ros::NodeHandle nh);

  // Correct odometry
  tf::Transform correctPose(tf::Transform pose,
                            tf::Transform last_graph_pose,
                            tf::Transform last_graph_odom);

  // Publish pose
  void publish(nav_msgs::Odometry odom_msg,
               tf::Transform pose);

private:

  // Stores parameters
  Params params_;

  // Pose publishers
  ros::Publisher pose_pub_;
  tf::TransformBroadcaster frame_to_child_;

};

} // namespace

#endif // POSE_H