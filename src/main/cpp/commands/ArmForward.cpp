// RobotBuilder Version: 5.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

// ROBOTBUILDER TYPE: Command.

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

#include "commands/ArmForward.h"

ArmForward::ArmForward(Pnenumatics* m_pnenumatics)
:m_pnenumatics(m_pnenumatics){

    // Use AddRequirements() here to declare subsystem dependencies
    // eg. AddRequirements(m_Subsystem);
    SetName("ArmForward");
    AddRequirements({m_pnenumatics});

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

}

// Called just before this Command runs the first time
void ArmForward::Initialize() {
    m_pnenumatics->setStage(1);
    m_pnenumatics->MoveStage(1);
}

// Called repeatedly when this Command is scheduled to run
void ArmForward::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool ArmForward::IsFinished() {
    return false;
}

// Called once after isFinished returns true
void ArmForward::End(bool interrupted) {

}

bool ArmForward::RunsWhenDisabled() const {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DISABLED
    return false;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DISABLED
}
