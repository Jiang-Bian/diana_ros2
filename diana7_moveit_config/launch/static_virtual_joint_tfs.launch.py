from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():

    world_tf = Node(
        package="tf2_ros",
        executable="static_transform_publisher",
        name="static_world_tf",
        arguments=[
            "0",
            "0",
            "0",
            "0",
            "0",
            "0",
            "world",
            "base_link",
        ],
    )

    return LaunchDescription(
        [
            world_tf,
        ]
    )
