//
// Created by ryuzo on 2023/02/16.
//

#ifndef BUILD_MAIN_NODE_HPP
#define BUILD_MAIN_NODE_HPP

#include <rclcpp/rclcpp.hpp>

namespace main_node {
    class MainNode final : public rclcpp::Node {
    private:
        rclcpp::TimerBase::SharedPtr _pub_timer;
        int64_t interval_ms;
        rclcpp::QoS _qos = rclcpp::QoS(5);

    public:
        explicit MainNode(const rclcpp::NodeOptions& options = rclcpp::NodeOptions());
    };
}


#endif //BUILD_MAIN_NODE_HPP