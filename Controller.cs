using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;
using System.Threading;


public class Controller : MonoBehaviour
{
    [SerializeField] GameObject LeftHand;
    [SerializeField] InputActionReference controllerActionJoyLeft;
    [SerializeField] InputActionReference controllerActionJoyRight;
    [SerializeField] InputActionReference controllerActionBtnLT;
    [SerializeField] InputActionReference controllerActionBtnRT;
    [SerializeField] InputActionReference controllerActionBtnLB;
    [SerializeField] InputActionReference controllerActionBtnRB;
    [SerializeField] InputActionReference controllerActionBtnA;  // rightcontroller A
    [SerializeField] InputActionReference controllerActionBtnB;  // rightcontroller B
    [SerializeField] InputActionReference controllerActionBtnX;  // leftcontroller X
    [SerializeField] InputActionReference controllerActionBtnY;  // leftcontroller Y

    private float[] baseMoveCommand={0,0,0,0,0,0,0,0,0,0,0,0};
    private float[] buffer=new float[]{0,0,0,0,0,0,0,0,0,0,0,0};
    Quaternion baseRotation;

    private void Awake()
    {
        controllerActionJoyLeft.action.performed += JoyPressedLeft;
        controllerActionJoyRight.action.performed += JoyPressedRight;
        controllerActionBtnLT.action.performed += ControllerLT;
        controllerActionBtnRT.action.performed += ControllerRT;
        controllerActionBtnLB.action.performed += ControllerLB;
        controllerActionBtnRB.action.performed += ControllerRB;

        controllerActionBtnA.action.performed += ControllerB;
        controllerActionBtnB.action.performed += ControllerA;
        controllerActionBtnX.action.performed += ControllerX;
        controllerActionBtnY.action.performed += ControllerY;
        //
    }

    public void JoyPressedLeft(InputAction.CallbackContext obj)
    {
        Vector2 tempVector2 = obj.ReadValue<Vector2>();
        baseMoveCommand[0] = tempVector2[0];
        baseMoveCommand[1] = tempVector2[1];
        Debug.Log(tempVector2);
    }

    public void JoyPressedRight(InputAction.CallbackContext obj)
    {
        Vector2 tempVector2 = obj.ReadValue<Vector2>();
        baseMoveCommand[2] = tempVector2[0];
        baseMoveCommand[3] = tempVector2[1];
        Debug.Log(tempVector2);
    }

    public void ControllerLT(InputAction.CallbackContext obj)
    {
        float temp = obj.ReadValue<float>();
        baseMoveCommand[4] = temp;
        Debug.Log($"buttonLT: {temp}");
    }

    public void ControllerRT(InputAction.CallbackContext obj)
    {
        float temp = obj.ReadValue<float>();
        baseMoveCommand[5] = temp;
        Debug.Log($"buttonRT: {temp}");
    }

    public void ControllerLB(InputAction.CallbackContext obj)
    {
        float temp = obj.ReadValue<float>();
        baseMoveCommand[6] = temp;
        // if (temp >= 0.5f)
        // {
        //     buttonLB = true;
        // }
        // else
        // {
        //     buttonLB = false;
        // }
        Debug.Log($"buttonLB: {temp}");
    }

    public void ControllerRB(InputAction.CallbackContext obj)
    {
        float temp = obj.ReadValue<float>();
        baseMoveCommand[7] = temp;
        // if (temp >= 0.5f)
        // {
        //     buttonRB = true;
        // }
        // else
        // {
        //     buttonRB = false;
        // }
        Debug.Log($"buttonRB: {temp}");
    }


    public void ControllerA(InputAction.CallbackContext obj)
    {
        float temp = obj.ReadValue<float>();
        baseMoveCommand[8] = temp;
        // if (temp == 1)
        // {
        //     buttonA = true;
        // }
        // else
        // {
        //     buttonA = false;
        // }
        Debug.Log($"buttonA: {temp}");
    }

    public void ControllerB(InputAction.CallbackContext obj)
    {
        float temp = obj.ReadValue<float>();
        baseMoveCommand[9] = temp;

        // if (temp == 1)
        // {
        //     buttonB = true;
        // }
        // else
        // {
        //     buttonB = false;
        // }
        Debug.Log($"buttonB: {temp}");
    }

    public void ControllerX(InputAction.CallbackContext obj)
    {
        float temp = obj.ReadValue<float>();
        baseMoveCommand[10] = temp;
        // if (temp == 1)
        // {
        //     buttonX = true;
        // }
        // else
        // {
        //     //buttonX = false;
        // }
        Debug.Log($"buttonX: {temp}");
    }

    public void ControllerY(InputAction.CallbackContext obj)
    {
        float temp = obj.ReadValue<float>();
        baseMoveCommand[11] = temp;
        // if (temp == 1)
        // {
        //     buttonY = true;
        // }
        // else
        // {
        //     //buttonY = false;
        // }
        Debug.Log($"buttonY: {temp}");
    }

    public float[] GetBaseMoveCommand()
    {
        return baseMoveCommand;
    }


    public void SetZero()
    {
        for(int i=0;i<12;i++){
            if(i>7) { Thread.Sleep(20); baseMoveCommand[i]=0; }
            baseMoveCommand[i]=0;
        }
    }
}
