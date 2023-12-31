from launch import LaunchDescription, EventHandler
from launch.actions import EmitEvent, LogInfo, RegisterEventHandler
from launch.events import Shutdown, matches_action
from launch_ros.actions import LifecycleNode, Node
from launch_ros.event_handlers import OnStateTransition
from launch_ros.events.lifecycle import ChangeState
from lifecycle_msgs.msg import Transition

def generate_launch_description():

    # Nodeの定義
    node = Node(
        name='main_node',
        namespace='main_node',
        package='main_node',
        executable='main_node_exec',
        output='screen'
    )

    return LaunchDescription([
        node,
    ])