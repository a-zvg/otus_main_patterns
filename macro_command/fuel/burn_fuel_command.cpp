#include <macro_command/fuel/burn_fuel_command.h>

void BurnFuelCommand::Execute()
{
    try
    {
        int result = fuelBurnable_->GetFuelLevel() - fuelBurnable_->GetFuelBurnSpeed();
        if ( result < 0 )
        {
            throw CommandError();
        }

        fuelBurnable_->SetFuelLevel( result );
    }
    catch ( std::exception& )
    {
        throw CommandError();
    }
}
