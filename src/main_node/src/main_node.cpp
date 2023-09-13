//
// Created by ryuzo on 2023/09/09.
//
#include <rclcpp/rclcpp.hpp>

#include "rclcpp_components/register_node_macro.hpp"
#include "main_node/main_node.hpp"


namespace main_node {

    MainNode::MainNode(const rclcpp::NodeOptions &options) : Node("main_node", options) {
        using namespace std::chrono_literals;

        declare_parameter("interval_ms", 10);
        interval_ms = this->get_parameter("interval_ms").as_int();
    }

}


RCLCPP_COMPONENTS_REGISTER_NODE(main_node::MainNode)