/*
 * OpenVMP, 2022
 *
 * Author: Roman Kuzmenko
 * Created: 2022-12-10
 *
 * Licensed under Apache License, Version 2.0.
 */

#ifndef OPENVMP_CONTROL_INTERACTIVE_MODE_HANG_H
#define OPENVMP_CONTROL_INTERACTIVE_MODE_HANG_H

#include <memory>
#include <string>

#include "openvmp_control_interactive/control_traj_vel.hpp"
#include "openvmp_control_interactive/mode.hpp"

namespace openvmp_control_interactive {

class HangMode : public TrajVelControl {
 public:
  HangMode(rclcpp::Node *node,
           std::shared_ptr<interactive_markers::InteractiveMarkerServer> server)
      : TrajVelControl(node, server, HANG, "Hang"), lift_{0.0} {}

  virtual void enter(std::shared_ptr<ControlImpl> from) override;
  virtual void leave(std::shared_ptr<ControlImpl> to) override;

 private:
  trajectory_msgs::msg::JointTrajectory msg_template_;
  trajectory_msgs::msg::JointTrajectoryPoint point_template_;
  double lift_;
  static constexpr double LIFT_LIMIT_BOTTOM = -1.0;
  static constexpr double LIFT_LIMIT_TOP = 0.0;

  void processFeedback_(
      const visualization_msgs::msg::InteractiveMarkerFeedback::ConstSharedPtr
          &feedback);
};

}  // namespace openvmp_control_interactive

#endif  // OPENVMP_CONTROL_INTERACTIVE_MODE_HANG_H
