#include <cstdio>
#include <rclcpp/rclcpp.hpp>
#include <cmath>

#include <memory>

#include "ros2_inverse_kinematics/robot_kinematics.h"



using namespace std;

void calc_inverse_kinematics(const std::shared_ptr<	> request, std::shared_ptr<	> response)
{
	robot_kinamatics robot_kinematics;

	
	robot_kinematics.inverse_kinematics(,);



	RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"");
	RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"sending back response:");

}

int main(int argc, char ** argv)
{
  (void) argc;
  (void) argv;

  rclcpp::init(argc, arg);

  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("inverse_kinematics_server");

  rclcpp::Service<	>::SharedPtr service = node->create_service<	>("inverse_kinematics");
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Inverse kinematics ready");

  rclcpp::spin(node);

}
