using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Unity.Robotics.ROSTCPConnector;
using Float32MultiArrayMsg = RosMessageTypes.Std.Float32MultiArrayMsg;
using PoseStampedMsg = RosMessageTypes.Geometry.PoseStampedMsg;
using Unity.Ros;



public class ControllerStatePub : MonoBehaviour
{
    [SerializeField] GameObject controller_reader;

    public string topicNameVel = "unity/ref_base_vel_command";

    ROSConnection m_Ros;
    // ROSConnection m_Ros2;

    Controller controller;

    private float awaitingResponseUntilTimestamp = -1;
    private Float32MultiArrayMsg ref_base_vel_command_msg;
    private float[] move_base_command_list = {0,0,0,0,0,0,0,0,0,0,0,0};

    private float[] joy_command={0,0,0,0,0,0,0,0,0,0,0,0};


    // Start is called before the first frame update
    void Start()
    {
        controller = controller_reader.GetComponent<Controller>();

        m_Ros = ROSConnection.GetOrCreateInstance();
        m_Ros.RegisterPublisher<Float32MultiArrayMsg>(topicNameVel);
        ref_base_vel_command_msg = new();

    }

    // Update is called once per frame
    void Update()
    {
        if (Time.time > awaitingResponseUntilTimestamp)
        {          
            for (int i = 0; i < 12; i++)
            { 
                move_base_command_list.SetValue(controller.GetBaseMoveCommand()[i], i);
            }
            ref_base_vel_command_msg.data = move_base_command_list;

            m_Ros.Publish(topicNameVel, ref_base_vel_command_msg);
            awaitingResponseUntilTimestamp = Time.time + 0.01f;

            controller.SetZero();
        }
    }
}
