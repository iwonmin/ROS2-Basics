from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='ros2_cpp_tutorial',
            namespace='',
            executable='double_talker',
            name='mh'
        ),
        Node(
            package='ros2_cpp_tutorial',
            namespace='',
            executable='double_listener',
            name='dj'
        )
    ])