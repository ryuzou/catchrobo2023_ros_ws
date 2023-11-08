//
// Created by ryuzo on 2023/02/16.
//

#ifndef BUILD_MAIN_NODE_HPP
#define BUILD_MAIN_NODE_HPP

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float32.hpp>

#include "std_msgs/msg/string.hpp"
#include "tcp_interface/srv/tcp_socket_i_ctrl.hpp"
#include "socketcan_interface/msg/socketcan_if.hpp"
#include "tcp_interface/msg/tcp_socket.hpp"
#include "visibility_control.h"
#include "nlohmann/json.hpp"

using namespace nlohmann;

namespace main_node {
    class MainNode final : public rclcpp::Node {
    private:
        rclcpp::Client<tcp_interface::srv::TcpSocketICtrl>::SharedPtr client_;
        int64_t interval_ms;

        rclcpp::Subscription<std_msgs::msg::String>::SharedPtr _subscription_tcp_8011;
        rclcpp::Publisher<socketcan_interface::msg::SocketcanIF>::SharedPtr _publisher;
        rclcpp::TimerBase::SharedPtr _pub_timer;

        bool tcp8011_flag;
        json manual_instruction;
        float preset[4] = {1000, 1000, 1000, 1000};
        int preset_index = -1;

        rclcpp::QoS _qos = rclcpp::QoS(10);
        void _publisher_callback();
        void _subscriber_callback_tcp_8011(std_msgs::msg::String msg);

        void _callback_response_tcp8011(rclcpp::Client<tcp_interface::srv::TcpSocketICtrl>::SharedFuture future);

    public:
        explicit MainNode(const rclcpp::NodeOptions& options = rclcpp::NodeOptions());
    };
}


#endif //BUILD_MAIN_NODE_HPP