from launch import LaunchDescription
from launch.actions import RegisterEventHandler

from launch.event_handlers import OnProcessStart

from launch_ros.actions import Node


def generate_launch_description():

    joint_state_broadcaster = Node(
        package="controller_manager",
        executable="spawner",
        arguments=[
            "joint_state_broadcaster",
            "--controller-manager",
            "/controller_manager",
        ],
        output="screen",
    )

    diana_arm_controller = Node(
        package="controller_manager",
        executable="spawner",
        arguments=[
            "diana_arm_controller",
            "--controller-manager",
            "/controller_manager",
        ],
        output="screen",
    )

    delay_arm_controller = RegisterEventHandler(
        OnProcessStart(
            target_action=joint_state_broadcaster,
            on_start=[
                diana_arm_controller,
            ],
        )
    )

    return LaunchDescription(
        [
            joint_state_broadcaster,
            delay_arm_controller,
        ]
    )
