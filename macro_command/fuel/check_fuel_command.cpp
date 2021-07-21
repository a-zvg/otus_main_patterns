#include <macro_command/fuel/check_fuel_command.h>

void CheckFuelCommand::Execute()
{
    if ( fuelCheckable_->GetFuelLevel() < fuelCheckable_->GetFuelBurnSpeed() )
    {
        throw CommandError();
    }
}
