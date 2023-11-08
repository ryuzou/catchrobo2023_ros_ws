import launch
from ament_index_python.packages import get_package_share_directory
from launch.launch_description_sources import PythonLaunchDescriptionSource

def generate_launch_description():
    ros2_socketcan_interface_launch = launch.actions.IncludeLaunchDescription(
        PythonLaunchDescriptionSource([get_package_share_directory("socketcan_interface") + "/launch/socketcan_interface.launch.py"]))
    ros2_tcp_interface_launch = launch.actions.IncludeLaunchDescription(
        PythonLaunchDescriptionSource([get_package_share_directory("tcp_interface") + "/launch/tcp_interface.launch.py"]))
    main_node_launch = launch.actions.IncludeLaunchDescription(
        PythonLaunchDescriptionSource([get_package_share_directory("main_node") + "/launch/main_node.launch.py"]))
    return launch.LaunchDescription([
        ros2_socketcan_interface_launch,
        ros2_tcp_interface_launch,
        main_node_launch,
    ])